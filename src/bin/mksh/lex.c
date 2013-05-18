
/*	$OpenBSD: lex.c,v 1.44 2008/07/03 17:52:08 otto Exp $	*/

/*-
 * Copyright (c) 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010, 2011
 *	Thorsten Glaser <tg@mirbsd.org>
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un-
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
 *
 * This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
 * the utmost extent permitted by applicable law, neither express nor
 * implied; without malicious intent or gross negligence. In no event
 * may a licensor, author or contributor be held liable for indirect,
 * direct, other damage, loss, or other issues arising in any way out
 * of dealing in the work, even if advised of the possibility of such
 * damage or existence of a defect, except proven that it results out
 * of said person's immediate fault when using the work as intended.
 */

#include "sh.h"

__RCSID("$MirOS: src/bin/mksh/lex.c,v 1.125 2011/03/07 20:07:52 tg Exp $");

/*
 * states while lexing word
 */
#define SBASE		0	/* outside any lexical constructs */
#define SWORD		1	/* implicit quoting for substitute() */
#define SLETPAREN	2	/* inside (( )), implicit quoting */
#define SSQUOTE		3	/* inside '' */
#define SDQUOTE		4	/* inside "" */
#define SEQUOTE		5	/* inside $'' */
#define SBRACE		6	/* inside ${} */
#define SQBRACE		7	/* inside "${}" */
#define SBQUOTE		8	/* inside `` */
#define SASPAREN	9	/* inside $(( )) */
#define SHEREDELIM	10	/* parsing <<,<<- delimiter */
#define SHEREDQUOTE	11	/* parsing " in <<,<<- delimiter */
#define SPATTERN	12	/* parsing *(...|...) pattern (*+?@!) */
#define STBRACE		13	/* parsing ${...[#%]...} */
#define SLETARRAY	14	/* inside =( ), just copy */
#define SADELIM		15	/* like SBASE, looking for delimiter */
#define SHERESTRING	16	/* parsing <<< string */
#define SINVALID	255	/* invalid state */

/*
 * Structure to keep track of the lexing state and the various pieces of info
 * needed for each particular state.
 */
typedef struct lex_state {
	union {
		/* point to the next state block */
		Lex_state *base;
		/* marks start of $(( in output string */
		int start;
		/* SBQUOTE: true if in double quotes: "`...`" */
		/* SEQUOTE: got NUL, ignore rest of string */
		bool abool;
		/* SADELIM information */
		struct {
			/* SADELIM_BASH, later extensions */
			unsigned char style;
			/* character to search for */
			unsigned char delimiter;
			/* max. number of delimiters */
			unsigned char num;
			/* ofs. into sadelim_flags[] */
			unsigned char flags;
		} adelim;
	} u;
	/* count open parentheses */
	short nparen;
	/* type of this state */
	uint8_t type;
} Lex_state;
#define ls_base		u.base
#define ls_start	u.start
#define ls_bool		u.abool
#define ls_adelim	u.adelim
#define SADELIM_BASH	0

typedef struct {
	Lex_state *base;
	Lex_state *end;
} State_info;

static void readhere(struct ioword *);
static int getsc__(void);
static void getsc_line(Source *);
static int getsc_bn(void);
static int s_get(void);
static void s_put(int);
static char *get_brace_var(XString *, char *);
static int arraysub(char **);
static const char *ungetsc(int);
static void gethere(bool);
static Lex_state *push_state_(State_info *, Lex_state *);
static Lex_state *pop_state_(State_info *, Lex_state *);

static int dopprompt(const char *, int, bool);

static int backslash_skip;
static int ignore_backslash_newline;

/* optimised getsc_bn() */
#define _getsc()	(*source->str != '\0' && *source->str != '\\' \
			 && !backslash_skip && !(source->flags & SF_FIRST) \
			 ? *source->str++ : getsc_bn())
/* optimised getsc__() */
#define	_getsc_()	((*source->str != '\0') && !(source->flags & SF_FIRST) \
			 ? *source->str++ : getsc__())

#ifdef MKSH_SMALL
static int getsc(void);
static int getsc_(void);

static int
getsc(void)
{
	return (_getsc());
}

static int
getsc_(void)
{
	return (_getsc_());
}
#else
/* !MKSH_SMALL: use them inline */
#define getsc()		_getsc()
#define getsc_()	_getsc_()
#endif

#define STATE_BSIZE	8

#define PUSH_STATE(s)	do {					\
	if (++statep == state_info.end)				\
		statep = push_state_(&state_info, statep);	\
	state = statep->type = (s);				\
} while (0)

#define POP_STATE()	do {					\
	if (--statep == state_info.base)			\
		statep = pop_state_(&state_info, statep);	\
	state = statep->type;					\
} while (0)

/**
 * Lexical analyser
 *
 * tokens are not regular expressions, they are LL(1).
 * for example, "${var:-${PWD}}", and "$(size $(whence ksh))".
 * hence the state stack.
 */

int
yylex(int cf)
{
	Lex_state states[STATE_BSIZE], *statep, *s2, *base;
	State_info state_info;
	int c, c2, state;
	XString ws;		/* expandable output word */
	char *wp;		/* output word pointer */
	char *sp, *dp;

 Again:
	states[0].type = SINVALID;
	states[0].ls_base = NULL;
	statep = &states[1];
	state_info.base = states;
	state_info.end = &state_info.base[STATE_BSIZE];

	Xinit(ws, wp, 64, ATEMP);

	backslash_skip = 0;
	ignore_backslash_newline = 0;

	if (cf&ONEWORD)
		state = SWORD;
	else if (cf&LETEXPR) {
		/* enclose arguments in (double) quotes */
		*wp++ = OQUOTE;
		state = SLETPAREN;
		statep->nparen = 0;
#ifndef MKSH_SMALL
	} else if (cf&LETARRAY) {
		state = SLETARRAY;
		statep->nparen = 0;
#endif
	} else {
		/* normal lexing */
		state = (cf & HEREDELIM) ? SHEREDELIM : SBASE;
		while ((c = getsc()) == ' ' || c == '\t')
			;
		if (c == '#') {
			ignore_backslash_newline++;
			while ((c = getsc()) != '\0' && c != '\n')
				;
			ignore_backslash_newline--;
		}
		ungetsc(c);
	}
	if (source->flags & SF_ALIAS) {
		/* trailing ' ' in alias definition */
		source->flags &= ~SF_ALIAS;
		cf |= ALIAS;
	}

	/* Initial state: one of SBASE SHEREDELIM SWORD SASPAREN */
	statep->type = state;

	/* check for here string */
	if (state == SHEREDELIM) {
		c = getsc();
		if (c == '<') {
			state = SHERESTRING;
			while ((c = getsc()) == ' ' || c == '\t')
				;
			ungetsc(c);
			c = '<';
			goto accept_nonword;
		}
		ungetsc(c);
	}

	/* collect non-special or quoted characters to form word */
	while (!((c = getsc()) == 0 ||
	    ((state == SBASE || state == SHEREDELIM || state == SHERESTRING) &&
	    ctype(c, C_LEX1)))) {
 accept_nonword:
		Xcheck(ws, wp);
		switch (state) {
		case SADELIM:
			if (c == '(')
				statep->nparen++;
			else if (c == ')')
				statep->nparen--;
			else if (statep->nparen == 0 &&
			    (c == /*{*/ '}' || c == statep->ls_adelim.delimiter)) {
				*wp++ = ADELIM;
				*wp++ = c;
				if (c == /*{*/ '}' || --statep->ls_adelim.num == 0)
					POP_STATE();
				if (c == /*{*/ '}')
					POP_STATE();
				break;
			}
			/* FALLTHROUGH */
		case SBASE:
			if (c == '[' && (cf & (VARASN|ARRAYVAR))) {
				/* temporary */
				*wp = EOS;
				if (is_wdvarname(Xstring(ws, wp), false)) {
					char *p, *tmp;

					if (arraysub(&tmp)) {
						*wp++ = CHAR;
						*wp++ = c;
						for (p = tmp; *p; ) {
							Xcheck(ws, wp);
							*wp++ = CHAR;
							*wp++ = *p++;
						}
						afree(tmp, ATEMP);
						break;
					} else {
						Source *s;

						s = pushs(SREREAD,
						    source->areap);
						s->start = s->str =
						    s->u.freeme = tmp;
						s->next = source;
						source = s;
					}
				}
				*wp++ = CHAR;
				*wp++ = c;
				break;
			}
			/* FALLTHROUGH */
 Sbase1:		/* includes *(...|...) pattern (*+?@!) */
			if (c == '*' || c == '@' || c == '+' || c == '?' ||
			    c == '!') {
				c2 = getsc();
				if (c2 == '(' /*)*/ ) {
					*wp++ = OPAT;
					*wp++ = c;
					PUSH_STATE(SPATTERN);
					break;
				}
				ungetsc(c2);
			}
			/* FALLTHROUGH */
 Sbase2:		/* doesn't include *(...|...) pattern (*+?@!) */
			switch (c) {
			case '\\':
 getsc_qchar:
				if ((c = getsc())) {
					/* trailing \ is lost */
					*wp++ = QCHAR;
					*wp++ = c;
				}
				break;
			case '\'':
 open_ssquote:
				*wp++ = OQUOTE;
				ignore_backslash_newline++;
				PUSH_STATE(SSQUOTE);
				break;
			case '"':
 open_sdquote:
				*wp++ = OQUOTE;
				PUSH_STATE(SDQUOTE);
				break;
			default:
				goto Subst;
			}
			break;

 Subst:
			switch (c) {
			case '\\':
				c = getsc();
				switch (c) {
				case '"':
					if ((cf & HEREDOC))
						goto heredocquote;
					/* FALLTHROUGH */
				case '\\':
				case '$': case '`':
 store_qchar:
					*wp++ = QCHAR;
					*wp++ = c;
					break;
				default:
 heredocquote:
					Xcheck(ws, wp);
					if (c) {
						/* trailing \ is lost */
						*wp++ = CHAR;
						*wp++ = '\\';
						*wp++ = CHAR;
						*wp++ = c;
					}
					break;
				}
				break;
			case '$':
 subst_dollar:
				c = getsc();
				if (c == '(') /*)*/ {
					c = getsc();
					if (c == '(') /*)*/ {
						PUSH_STATE(SASPAREN);
						statep->nparen = 2;
						statep->ls_start =
						    Xsavepos(ws, wp);
						*wp++ = EXPRSUB;
					} else {
						ungetsc(c);
 subst_command:
						sp = yyrecursive();
						c2 = strlen(sp) + 1;
						XcheckN(ws, wp, c2);
						*wp++ = COMSUB;
						memcpy(wp, sp, c2);
						wp += c2;
					}
				} else if (c == '{') /*}*/ {
					*wp++ = OSUBST;
					*wp++ = '{'; /*}*/
					wp = get_brace_var(&ws, wp);
					c = getsc();
					/* allow :# and :% (ksh88 compat) */
					if (c == ':') {
						*wp++ = CHAR;
						*wp++ = c;
						c = getsc();
						if (c == ':') {
							*wp++ = CHAR;
							*wp++ = '0';
							*wp++ = ADELIM;
							*wp++ = ':';
							PUSH_STATE(SBRACE);
							PUSH_STATE(SADELIM);
							statep->ls_adelim.style = SADELIM_BASH;
							statep->ls_adelim.delimiter = ':';
							statep->ls_adelim.num = 1;
							statep->nparen = 0;
							break;
						} else if (ksh_isdigit(c) ||
						    c == '('/*)*/ || c == ' ' ||
						    /*XXX what else? */
						    c == '$') {
							/* substring subst. */
							if (c != ' ') {
								*wp++ = CHAR;
								*wp++ = ' ';
							}
							ungetsc(c);
							PUSH_STATE(SBRACE);
							PUSH_STATE(SADELIM);
							statep->ls_adelim.style = SADELIM_BASH;
							statep->ls_adelim.delimiter = ':';
							statep->ls_adelim.num = 2;
							statep->nparen = 0;
							break;
						}
					} else if (c == '/') {
						*wp++ = CHAR;
						*wp++ = c;
						if ((c = getsc()) == '/') {
							*wp++ = ADELIM;
							*wp++ = c;
						} else
							ungetsc(c);
						PUSH_STATE(SBRACE);
						PUSH_STATE(SADELIM);
						statep->ls_adelim.style = SADELIM_BASH;
						statep->ls_adelim.delimiter = '/';
						statep->ls_adelim.num = 1;
						statep->nparen = 0;
						break;
					}
					/*
					 * If this is a trim operation,
					 * treat (,|,) specially in STBRACE.
					 */
					if (ctype(c, C_SUBOP2)) {
						ungetsc(c);
						PUSH_STATE(STBRACE);
					} else {
						ungetsc(c);
						if (state == SDQUOTE)
							PUSH_STATE(SQBRACE);
						else
							PUSH_STATE(SBRACE);
					}
				} else if (ksh_isalphx(c)) {
					*wp++ = OSUBST;
					*wp++ = 'X';
					do {
						Xcheck(ws, wp);
						*wp++ = c;
						c = getsc();
					} while (ksh_isalnux(c));
					*wp++ = '\0';
					*wp++ = CSUBST;
					*wp++ = 'X';
					ungetsc(c);
				} else if (ctype(c, C_VAR1 | C_DIGIT)) {
					Xcheck(ws, wp);
					*wp++ = OSUBST;
					*wp++ = 'X';
					*wp++ = c;
					*wp++ = '\0';
					*wp++ = CSUBST;
					*wp++ = 'X';
				} else if (c == '\'' && (state == SBASE)) {
					/* XXX which other states are valid? */
					*wp++ = OQUOTE;
					ignore_backslash_newline++;
					PUSH_STATE(SEQUOTE);
					statep->ls_bool = false;
					break;
				} else if (c == '"' && (state == SBASE)) {
					/* XXX which other states are valid? */
					goto DEQUOTE;
				} else {
					*wp++ = CHAR;
					*wp++ = '$';
 DEQUOTE:
					ungetsc(c);
				}
				break;
			case '`':
 subst_gravis:
				PUSH_STATE(SBQUOTE);
				*wp++ = COMSUB;
				/*
				 * Need to know if we are inside double quotes
				 * since sh/AT&T-ksh translate the \" to " in
				 * "`...\"...`".
				 * This is not done in POSIX mode (section
				 * 3.2.3, Double Quotes: "The backquote shall
				 * retain its special meaning introducing the
				 * other form of command substitution (see
				 * 3.6.3). The portion of the quoted string
				 * from the initial backquote and the
				 * characters up to the next backquote that
				 * is not preceded by a backslash (having
				 * escape characters removed) defines that
				 * command whose output replaces `...` when
				 * the word is expanded."
				 * Section 3.6.3, Command Substitution:
				 * "Within the backquoted style of command
				 * substitution, backslash shall retain its
				 * literal meaning, except when followed by
				 * $ ` \.").
				 */
				statep->ls_bool = false;
				s2 = statep;
				base = state_info.base;
				while (1) {
					for (; s2 != base; s2--) {
						if (s2->type == SDQUOTE) {
							statep->ls_bool = true;
							break;
						}
					}
					if (s2 != base)
						break;
					if (!(s2 = s2->ls_base))
						break;
					base = s2-- - STATE_BSIZE;
				}
				break;
			case QCHAR:
				if (cf & LQCHAR) {
					*wp++ = QCHAR;
					*wp++ = getsc();
					break;
				}
				/* FALLTHROUGH */
			default:
 store_char:
				*wp++ = CHAR;
				*wp++ = c;
			}
			break;

		case SEQUOTE:
			if (c == '\'') {
				POP_STATE();
				*wp++ = CQUOTE;
				ignore_backslash_newline--;
			} else if (c == '\\') {
				if ((c2 = unbksl(true, s_get, s_put)) == -1)
					c2 = s_get();
				if (c2 == 0)
					statep->ls_bool = true;
				if (!statep->ls_bool) {
					char ts[4];

					if ((unsigned int)c2 < 0x100) {
						*wp++ = QCHAR;
						*wp++ = c2;
					} else {
						c = utf_wctomb(ts, c2 - 0x100);
						ts[c] = 0;
						for (c = 0; ts[c]; ++c) {
							*wp++ = QCHAR;
							*wp++ = ts[c];
						}
					}
				}
			} else if (!statep->ls_bool) {
				*wp++ = QCHAR;
				*wp++ = c;
			}
			break;

		case SSQUOTE:
			if (c == '\'') {
				POP_STATE();
				*wp++ = CQUOTE;
				ignore_backslash_newline--;
			} else {
				*wp++ = QCHAR;
				*wp++ = c;
			}
			break;

		case SDQUOTE:
			if (c == '"') {
				POP_STATE();
				*wp++ = CQUOTE;
			} else
				goto Subst;
			break;

		/* $(( ... )) */
		case SASPAREN:
			/*
			 * XXX should nest using existing state machine
			 * (embed "...", $(...), etc.)
			 */
			if (c == '(')
				statep->nparen++;
			else if (c == ')') {
				statep->nparen--;
				if (statep->nparen == 1) {
					if ((c2 = getsc()) == /*(*/')') {
						POP_STATE();
						/* end of EXPRSUB */
						*wp++ = 0;
						break;
					} else {
						Source *s;

						ungetsc(c2);
						/*
						 * mismatched parenthesis -
						 * assume we were really
						 * parsing a $(...) expression
						 */
						*wp = EOS;
						wp = Xrestpos(ws, wp,
						    statep->ls_start);
						POP_STATE();
						/* dp = $((blah))\0 */
						dp = wdstrip(wp, true, false);
						s = pushs(SREREAD,
						    source->areap);
						s->start = s->str =
						    (s->u.freeme = dp) + 2;
						dp[strlen(dp) - 1] = 0;
						/* s->str = (blah)\0 */
						s->next = source;
						source = s;
						goto subst_command;
					}
				}
			}
			*wp++ = c;
			break;

		case SQBRACE:
			if (c == '\\') {
				/*
				 * perform POSIX "quote removal" if the back-
				 * slash is "special", i.e. same cases as the
				 * {case '\\':} in Subst: plus closing brace;
				 * in mksh code "quote removal" on '\c' means
				 * write QCHAR+c, otherwise CHAR+\+CHAR+c are
				 * emitted (in heredocquote:)
				 */
				if ((c = getsc()) == '"' || c == '\\' ||
				    c == '$' || c == '`' || c == /*{*/'}')
					goto store_qchar;
				goto heredocquote;
			}
			goto common_SQBRACE;

		case SBRACE:
			if (c == '\'')
				goto open_ssquote;
			else if (c == '\\')
				goto getsc_qchar;
 common_SQBRACE:
			if (c == '"')
				goto open_sdquote;
			else if (c == '$')
				goto subst_dollar;
			else if (c == '`')
				goto subst_gravis;
			else if (c != /*{*/ '}')
				goto store_char;
			POP_STATE();
			*wp++ = CSUBST;
			*wp++ = /*{*/ '}';
			break;

		case STBRACE:
			/* Same as SBASE, except (,|,) treated specially */
			if (c == /*{*/ '}') {
				POP_STATE();
				*wp++ = CSUBST;
				*wp++ = /*{*/ '}';
			} else if (c == '|') {
				*wp++ = SPAT;
			} else if (c == '(') {
				*wp++ = OPAT;
				/* simile for @ */
				*wp++ = ' ';
				PUSH_STATE(SPATTERN);
			} else
				goto Sbase1;
			break;

		case SBQUOTE:
			if (c == '`') {
				*wp++ = 0;
				POP_STATE();
			} else if (c == '\\') {
				switch (c = getsc()) {
				case '\\':
				case '$': case '`':
					*wp++ = c;
					break;
				case '"':
					if (statep->ls_bool) {
						*wp++ = c;
						break;
					}
					/* FALLTHROUGH */
				default:
					if (c) {
						/* trailing \ is lost */
						*wp++ = '\\';
						*wp++ = c;
					}
					break;
				}
			} else
				*wp++ = c;
			break;

		/* ONEWORD */
		case SWORD:
			goto Subst;

		/* LETEXPR: (( ... )) */
		case SLETPAREN:
			if (c == /*(*/ ')') {
				if (statep->nparen > 0)
					--statep->nparen;
				else if ((c2 = getsc()) == /*(*/ ')') {
					c = 0;
					*wp++ = CQUOTE;
					goto Done;
				} else {
					Source *s;

					ungetsc(c2);
					/*
					 * mismatched parenthesis -
					 * assume we were really
					 * parsing a (...) expression
					 */
					*wp = EOS;
					sp = Xstring(ws, wp);
					dp = wdstrip(sp, true, false);
					s = pushs(SREREAD, source->areap);
					s->start = s->str = s->u.freeme = dp;
					s->next = source;
					source = s;
					return ('('/*)*/);
				}
			} else if (c == '(')
				/*
				 * parentheses inside quotes and
				 * backslashes are lost, but AT&T ksh
				 * doesn't count them either
				 */
				++statep->nparen;
			goto Sbase2;

#ifndef MKSH_SMALL
		/* LETARRAY: =( ... ) */
		case SLETARRAY:
			if (c == '('/*)*/)
				++statep->nparen;
			else if (c == /*(*/')')
				if (statep->nparen-- == 0) {
					c = 0;
					goto Done;
				}
			*wp++ = CHAR;
			*wp++ = c;
			break;
#endif

		/* <<< delimiter */
		case SHERESTRING:
			if (c == '\\') {
				c = getsc();
				if (c) {
					/* trailing \ is lost */
					*wp++ = QCHAR;
					*wp++ = c;
				}
				/* invoke quoting mode */
				Xstring(ws, wp)[0] = QCHAR;
			} else if (c == '$') {
				if ((c2 = getsc()) == '\'') {
					PUSH_STATE(SEQUOTE);
					statep->ls_bool = false;
					goto sherestring_quoted;
				} else if (c2 == '"')
					goto sherestring_dquoted;
				ungetsc(c2);
				goto sherestring_regular;
			} else if (c == '\'') {
				PUSH_STATE(SSQUOTE);
 sherestring_quoted:
				*wp++ = OQUOTE;
				ignore_backslash_newline++;
				/* invoke quoting mode */
				Xstring(ws, wp)[0] = QCHAR;
			} else if (c == '"') {
 sherestring_dquoted:
				state = statep->type = SHEREDQUOTE;
				*wp++ = OQUOTE;
				/* just don't IFS split; no quoting mode */
			} else {
 sherestring_regular:
				*wp++ = CHAR;
				*wp++ = c;
			}
			break;

		/* <<,<<- delimiter */
		case SHEREDELIM:
			/*
			 * XXX chuck this state (and the next) - use
			 * the existing states ($ and \`...` should be
			 * stripped of their specialness after the
			 * fact).
			 */
			/*
			 * here delimiters need a special case since
			 * $ and `...` are not to be treated specially
			 */
			if (c == '\\') {
				c = getsc();
				if (c) {
					/* trailing \ is lost */
					*wp++ = QCHAR;
					*wp++ = c;
				}
			} else if (c == '$') {
				if ((c2 = getsc()) == '\'') {
					PUSH_STATE(SEQUOTE);
					statep->ls_bool = false;
					goto sheredelim_quoted;
				} else if (c2 == '"')
					goto sheredelim_dquoted;
				ungetsc(c2);
				goto sheredelim_regular;
			} else if (c == '\'') {
				PUSH_STATE(SSQUOTE);
 sheredelim_quoted:
				*wp++ = OQUOTE;
				ignore_backslash_newline++;
			} else if (c == '"') {
 sheredelim_dquoted:
				state = statep->type = SHEREDQUOTE;
				*wp++ = OQUOTE;
			} else {
 sheredelim_regular:
				*wp++ = CHAR;
				*wp++ = c;
			}
			break;

		/* " in <<,<<- delimiter */
		case SHEREDQUOTE:
			if (c == '"') {
				*wp++ = CQUOTE;
				state = statep->type =
				    /* dp[1] == '<' means here string */
				    Xstring(ws, wp)[1] == '<' ?
				    SHERESTRING : SHEREDELIM;
			} else {
				if (c == '\\') {
					switch (c = getsc()) {
					case '\\': case '"':
					case '$': case '`':
						break;
					default:
						if (c) {
							/* trailing \ lost */
							*wp++ = CHAR;
							*wp++ = '\\';
						}
						break;
					}
				}
				*wp++ = CHAR;
				*wp++ = c;
			}
			break;

		/* in *(...|...) pattern (*+?@!) */
		case SPATTERN:
			if (c == /*(*/ ')') {
				*wp++ = CPAT;
				POP_STATE();
			} else if (c == '|') {
				*wp++ = SPAT;
			} else if (c == '(') {
				*wp++ = OPAT;
				/* simile for @ */
				*wp++ = ' ';
				PUSH_STATE(SPATTERN);
			} else
				goto Sbase1;
			break;
		}
	}
 Done:
	Xcheck(ws, wp);
	if (statep != &states[1])
		/* XXX figure out what is missing */
		yyerror("no closing quote\n");

#ifndef MKSH_SMALL
	if (state == SLETARRAY && statep->nparen != -1)
		yyerror("%s: %s\n", T_synerr, "missing )");
#endif

	/* This done to avoid tests for SHEREDELIM wherever SBASE tested */
	if (state == SHEREDELIM || state == SHERESTRING)
		state = SBASE;

	dp = Xstring(ws, wp);
	if ((c == '<' || c == '>' || c == '&') && state == SBASE) {
		struct ioword *iop = alloc(sizeof(struct ioword), ATEMP);

		if (Xlength(ws, wp) == 0)
			iop->unit = c == '<' ? 0 : 1;
		else for (iop->unit = 0, c2 = 0; c2 < Xlength(ws, wp); c2 += 2) {
			if (dp[c2] != CHAR)
				goto no_iop;
			if (!ksh_isdigit(dp[c2 + 1]))
				goto no_iop;
			iop->unit = (iop->unit * 10) + dp[c2 + 1] - '0';
		}

		if (iop->unit >= FDBASE)
			goto no_iop;

		if (c == '&') {
			if ((c2 = getsc()) != '>') {
				ungetsc(c2);
				goto no_iop;
			}
			c = c2;
			iop->flag = IOBASH;
		} else
			iop->flag = 0;

		c2 = getsc();
		/* <<, >>, <> are ok, >< is not */
		if (c == c2 || (c == '<' && c2 == '>')) {
			iop->flag |= c == c2 ?
			    (c == '>' ? IOCAT : IOHERE) : IORDWR;
			if (iop->flag == IOHERE) {
				if ((c2 = getsc()) == '-')
					iop->flag |= IOSKIP;
				else
					ungetsc(c2);
			}
		} else if (c2 == '&')
			iop->flag |= IODUP | (c == '<' ? IORDUP : 0);
		else {
			iop->flag |= c == '>' ? IOWRITE : IOREAD;
			if (c == '>' && c2 == '|')
				iop->flag |= IOCLOB;
			else
				ungetsc(c2);
		}

		iop->name = NULL;
		iop->delim = NULL;
		iop->heredoc = NULL;
		/* free word */
		Xfree(ws, wp);
		yylval.iop = iop;
		return (REDIR);
 no_iop:
		;
	}

	if (wp == dp && state == SBASE) {
		/* free word */
		Xfree(ws, wp);
		/* no word, process LEX1 character */
		if ((c == '|') || (c == '&') || (c == ';') || (c == '('/*)*/)) {
			if ((c2 = getsc()) == c)
				c = (c == ';') ? BREAK :
				    (c == '|') ? LOGOR :
				    (c == '&') ? LOGAND :
				    /* c == '(' ) */ MDPAREN;
			else if (c == '|' && c2 == '&')
				c = COPROC;
			else
				ungetsc(c2);
		} else if (c == '\n') {
			gethere(false);
			if (cf & CONTIN)
				goto Again;
		} else if (c == '\0')
			/* need here strings at EOF */
			gethere(true);
		return (c);
	}

	/* terminate word */
	*wp++ = EOS;
	yylval.cp = Xclose(ws, wp);
	if (state == SWORD || state == SLETPAREN
	    /* XXX ONEWORD? */
#ifndef MKSH_SMALL
	    || state == SLETARRAY
#endif
	    )
		return (LWORD);

	/* unget terminator */
	ungetsc(c);

	/*
	 * note: the alias-vs-function code below depends on several
	 * interna: starting from here, source->str is not modified;
	 * the way getsc() and ungetsc() operate; etc.
	 */

	/* copy word to unprefixed string ident */
	sp = yylval.cp;
	dp = ident;
	if ((cf & HEREDELIM) && (sp[1] == '<'))
		while (dp < ident+IDENT) {
			if ((c = *sp++) == CHAR)
				*dp++ = *sp++;
			else if ((c != OQUOTE) && (c != CQUOTE))
				break;
		}
	else
		while (dp < ident+IDENT && (c = *sp++) == CHAR)
			*dp++ = *sp++;
	/* Make sure the ident array stays '\0' padded */
	memset(dp, 0, (ident+IDENT) - dp + 1);
	if (c != EOS)
		/* word is not unquoted */
		*ident = '\0';

	if (*ident != '\0' && (cf&(KEYWORD|ALIAS))) {
		struct tbl *p;
		uint32_t h = hash(ident);

		if ((cf & KEYWORD) && (p = ktsearch(&keywords, ident, h)) &&
		    (!(cf & ESACONLY) || p->val.i == ESAC ||
		    p->val.i == /*{*/ '}')) {
			afree(yylval.cp, ATEMP);
			return (p->val.i);
		}
		if ((cf & ALIAS) && (p = ktsearch(&aliases, ident, h)) &&
		    (p->flag & ISSET)) {
			/*
			 * this still points to the same character as the
			 * ungetsc'd terminator from above
			 */
			const char *cp = source->str;

			/* prefer POSIX but not Korn functions over aliases */
			while (*cp == ' ' || *cp == '\t')
				/*
				 * this is like getsc() without skipping
				 * over Source boundaries (including not
				 * parsing ungetsc'd characters that got
				 * pushed into an SREREAD) which is what
				 * we want here anyway: find out whether
				 * the alias name is followed by a POSIX
				 * function definition (only the opening
				 * parenthesis is checked though)
				 */
				++cp;
			/* prefer functions over aliases */
			if (*cp == '(' /*)*/)
				/*
				 * delete alias upon encountering function
				 * definition
				 */
				ktdelete(p);
			else {
				Source *s = source;

				while (s && (s->flags & SF_HASALIAS))
					if (s->u.tblp == p)
						return (LWORD);
					else
						s = s->next;
				/* push alias expansion */
				s = pushs(SALIAS, source->areap);
				s->start = s->str = p->val.s;
				s->u.tblp = p;
				s->flags |= SF_HASALIAS;
				s->next = source;
				if (source->type == SEOF) {
					/* prevent infinite recursion at EOS */
					source->u.tblp = p;
					source->flags |= SF_HASALIAS;
				}
				source = s;
				afree(yylval.cp, ATEMP);
				goto Again;
			}
		}
	}

	return (LWORD);
}

static void
gethere(bool iseof)
{
	struct ioword **p;

	for (p = heres; p < herep; p++)
		if (iseof && (*p)->delim[1] != '<')
			/* only here strings at EOF */
			return;
		else
			readhere(*p);
	herep = heres;
}

/*
 * read "<<word" text into temp file
 */

static void
readhere(struct ioword *iop)
{
	int c;
	char *volatile eof;
	char *eofp;
	int skiptabs;
	XString xs;
	char *xp;
	int xpos;

	if (iop->delim[1] == '<') {
		/* process the here string */
		xp = iop->heredoc = evalstr(iop->delim, DOBLANK);
		c = strlen(xp) - 1;
		memmove(xp, xp + 1, c);
		xp[c] = '\n';
		return;
	}

	eof = evalstr(iop->delim, 0);

	if (!(iop->flag & IOEVAL))
		ignore_backslash_newline++;

	Xinit(xs, xp, 256, ATEMP);

	for (;;) {
		eofp = eof;
		skiptabs = iop->flag & IOSKIP;
		xpos = Xsavepos(xs, xp);
		while ((c = getsc()) != 0) {
			if (skiptabs) {
				if (c == '\t')
					continue;
				skiptabs = 0;
			}
			if (c != *eofp)
				break;
			Xcheck(xs, xp);
			Xput(xs, xp, c);
			eofp++;
		}
		/*
		 * Allow EOF here so commands with out trailing newlines
		 * will work (eg, ksh -c '...', $(...), etc).
		 */
		if (*eofp == '\0' && (c == 0 || c == '\n')) {
			xp = Xrestpos(xs, xp, xpos);
			break;
		}
		ungetsc(c);
		while ((c = getsc()) != '\n') {
			if (c == 0)
				yyerror("%s '%s' unclosed\n", "here document",
				    eof);
			Xcheck(xs, xp);
			Xput(xs, xp, c);
		}
		Xcheck(xs, xp);
		Xput(xs, xp, c);
	}
	Xput(xs, xp, '\0');
	iop->heredoc = Xclose(xs, xp);

	if (!(iop->flag & IOEVAL))
		ignore_backslash_newline--;
}

void
yyerror(const char *fmt, ...)
{
	va_list va;

	/* pop aliases and re-reads */
	while (source->type == SALIAS || source->type == SREREAD)
		source = source->next;
	/* zap pending input */
	source->str = null;

	error_prefix(true);
	va_start(va, fmt);
	shf_vfprintf(shl_out, fmt, va);
	va_end(va);
	errorfz();
}

/*
 * input for yylex with alias expansion
 */

Source *
pushs(int type, Area *areap)
{
	Source *s;

	s = alloc(sizeof(Source), areap);
	memset(s, 0, sizeof(Source));
	s->type = type;
	s->str = null;
	s->areap = areap;
	if (type == SFILE || type == SSTDIN)
		XinitN(s->xs, 256, s->areap);
	return (s);
}

static int
getsc__(void)
{
	Source *s = source;
	int c;

 getsc_again:
	while ((c = *s->str++) == 0) {
		/* return 0 for EOF by default */
		s->str = NULL;
		switch (s->type) {
		case SEOF:
			s->str = null;
			return (0);

		case SSTDIN:
		case SFILE:
			getsc_line(s);
			break;

		case SWSTR:
			break;

		case SSTRING:
			break;

		case SWORDS:
			s->start = s->str = *s->u.strv++;
			s->type = SWORDSEP;
			break;

		case SWORDSEP:
			if (*s->u.strv == NULL) {
				s->start = s->str = "\n";
				s->type = SEOF;
			} else {
				s->start = s->str = " ";
				s->type = SWORDS;
			}
			break;

		case SALIAS:
			if (s->flags & SF_ALIASEND) {
				/* pass on an unused SF_ALIAS flag */
				source = s->next;
				source->flags |= s->flags & SF_ALIAS;
				s = source;
			} else if (*s->u.tblp->val.s &&
			    (c = strnul(s->u.tblp->val.s)[-1], ksh_isspace(c))) {
				/* pop source stack */
				source = s = s->next;
				/*
				 * Note that this alias ended with a
				 * space, enabling alias expansion on
				 * the following word.
				 */
				s->flags |= SF_ALIAS;
			} else {
				/*
				 * At this point, we need to keep the current
				 * alias in the source list so recursive
				 * aliases can be detected and we also need to
				 * return the next character. Do this by
				 * temporarily popping the alias to get the
				 * next character and then put it back in the
				 * source list with the SF_ALIASEND flag set.
				 */
				/* pop source stack */
				source = s->next;
				source->flags |= s->flags & SF_ALIAS;
				c = getsc__();
				if (c) {
					s->flags |= SF_ALIASEND;
					s->ugbuf[0] = c; s->ugbuf[1] = '\0';
					s->start = s->str = s->ugbuf;
					s->next = source;
					source = s;
				} else {
					s = source;
					/* avoid reading EOF twice */
					s->str = NULL;
					break;
				}
			}
			continue;

		case SREREAD:
			if (s->start != s->ugbuf)
				/* yuck */
				afree(s->u.freeme, ATEMP);
			source = s = s->next;
			continue;
		}
		if (s->str == NULL) {
			s->type = SEOF;
			s->start = s->str = null;
			return ('\0');
		}
		if (s->flags & SF_ECHO) {
			shf_puts(s->str, shl_out);
			shf_flush(shl_out);
		}
	}
	/* check for UTF-8 byte order mark */
	if (s->flags & SF_FIRST) {
		s->flags &= ~SF_FIRST;
		if (((unsigned char)c == 0xEF) &&
		    (((const unsigned char *)(s->str))[0] == 0xBB) &&
		    (((const unsigned char *)(s->str))[1] == 0xBF)) {
			s->str += 2;
			UTFMODE = 1;
			goto getsc_again;
		}
	}
	return (c);
}

static void
getsc_line(Source *s)
{
	char *xp = Xstring(s->xs, xp), *cp;
	bool interactive = Flag(FTALKING) && s->type == SSTDIN;
	int have_tty = interactive && (s->flags & SF_TTY);

	/* Done here to ensure nothing odd happens when a timeout occurs */
	XcheckN(s->xs, xp, LINE);
	*xp = '\0';
	s->start = s->str = xp;

	if (have_tty && ksh_tmout) {
		ksh_tmout_state = TMOUT_READING;
		alarm(ksh_tmout);
	}
	if (interactive)
		change_winsz();
	if (have_tty && (
#if !MKSH_S_NOVI
	    Flag(FVI) ||
#endif
	    Flag(FEMACS) || Flag(FGMACS))) {
		int nread;

		nread = x_read(xp, LINE);
		if (nread < 0)
			/* read error */
			nread = 0;
		xp[nread] = '\0';
		xp += nread;
	} else {
		if (interactive)
			pprompt(prompt, 0);
		else
			s->line++;

		while (1) {
			char *p = shf_getse(xp, Xnleft(s->xs, xp), s->u.shf);

			if (!p && shf_error(s->u.shf) &&
			    shf_errno(s->u.shf) == EINTR) {
				shf_clearerr(s->u.shf);
				if (trap)
					runtraps(0);
				continue;
			}
			if (!p || (xp = p, xp[-1] == '\n'))
				break;
			/* double buffer size */
			/* move past NUL so doubling works... */
			xp++;
			XcheckN(s->xs, xp, Xlength(s->xs, xp));
			/* ...and move back again */
			xp--;
		}
		/*
		 * flush any unwanted input so other programs/builtins
		 * can read it. Not very optimal, but less error prone
		 * than flushing else where, dealing with redirections,
		 * etc.
		 * TODO: reduce size of shf buffer (~128?) if SSTDIN
		 */
		if (s->type == SSTDIN)
			shf_flush(s->u.shf);
	}
	/*
	 * XXX: temporary kludge to restore source after a
	 * trap may have been executed.
	 */
	source = s;
	if (have_tty && ksh_tmout) {
		ksh_tmout_state = TMOUT_EXECUTING;
		alarm(0);
	}
	cp = Xstring(s->xs, xp);
#ifndef MKSH_SMALL
	if (interactive && *cp == '!' && cur_prompt == PS1) {
		int linelen;

		linelen = Xlength(s->xs, xp);
		XcheckN(s->xs, xp, Tn_fc_e_ + /* NUL */ 1);
		/* reload after potential realloc */
		cp = Xstring(s->xs, xp);
		/* change initial '!' into space */
		*cp = ' ';
		/* NUL terminate the current string */
		*xp = '\0';
		/* move the actual string forward */
		memmove(cp + Tn_fc_e_, cp, linelen + /* NUL */ 1);
		xp += Tn_fc_e_;
		/* prepend it with "fc -e -" */
		memcpy(cp, T_fc_e_, Tn_fc_e_);
	}
#endif
	s->start = s->str = cp;
	strip_nuls(Xstring(s->xs, xp), Xlength(s->xs, xp));
	/* Note: if input is all nulls, this is not eof */
	if (Xlength(s->xs, xp) == 0) {
		/* EOF */
		if (s->type == SFILE)
			shf_fdclose(s->u.shf);
		s->str = NULL;
	} else if (interactive && *s->str &&
	    (cur_prompt != PS1 || !ctype(*s->str, C_IFS | C_IFSWS))) {
		histsave(&s->line, s->str, true, true);
#if !defined(MKSH_SMALL) && HAVE_PERSISTENT_HISTORY
	} else if (interactive && cur_prompt == PS1) {
		cp = Xstring(s->xs, xp);
		while (*cp && ctype(*cp, C_IFSWS))
			++cp;
		if (!*cp)
			histsync();
#endif
	}
	if (interactive)
		set_prompt(PS2, NULL);
}

void
set_prompt(int to, Source *s)
{
	cur_prompt = to;

	switch (to) {
	/* command */
	case PS1:
		/*
		 * Substitute ! and !! here, before substitutions are done
		 * so ! in expanded variables are not expanded.
		 * NOTE: this is not what AT&T ksh does (it does it after
		 * substitutions, POSIX doesn't say which is to be done.
		 */
		{
			struct shf *shf;
			char * volatile ps1;
			Area *saved_atemp;

			ps1 = str_val(global("PS1"));
			shf = shf_sopen(NULL, strlen(ps1) * 2,
			    SHF_WR | SHF_DYNAMIC, NULL);
			while (*ps1)
				if (*ps1 != '!' || *++ps1 == '!')
					shf_putchar(*ps1++, shf);
				else
					shf_fprintf(shf, "%d",
						s ? s->line + 1 : 0);
			ps1 = shf_sclose(shf);
			saved_atemp = ATEMP;
			newenv(E_ERRH);
			if (sigsetjmp(e->jbuf, 0)) {
				prompt = safe_prompt;
				/*
				 * Don't print an error - assume it has already
				 * been printed. Reason is we may have forked
				 * to run a command and the child may be
				 * unwinding its stack through this code as it
				 * exits.
				 */
			} else {
				char *cp = substitute(ps1, 0);
				strdupx(prompt, cp, saved_atemp);
			}
			quitenv(NULL);
		}
		break;
	/* command continuation */
	case PS2:
		prompt = str_val(global("PS2"));
		break;
	}
}

static int
dopprompt(const char *cp, int ntruncate, bool doprint)
{
	int columns = 0, lines = 0, indelimit = 0;
	char delimiter = 0;

	/*
	 * Undocumented AT&T ksh feature:
	 * If the second char in the prompt string is \r then the first
	 * char is taken to be a non-printing delimiter and any chars
	 * between two instances of the delimiter are not considered to
	 * be part of the prompt length
	 */
	if (*cp && cp[1] == '\r') {
		delimiter = *cp;
		cp += 2;
	}
	for (; *cp; cp++) {
		if (indelimit && *cp != delimiter)
			;
		else if (*cp == '\n' || *cp == '\r') {
			lines += columns / x_cols + ((*cp == '\n') ? 1 : 0);
			columns = 0;
		} else if (*cp == '\t') {
			columns = (columns | 7) + 1;
		} else if (*cp == '\b') {
			if (columns > 0)
				columns--;
		} else if (*cp == delimiter)
			indelimit = !indelimit;
		else if (UTFMODE && ((unsigned char)*cp > 0x7F)) {
			const char *cp2;
			columns += utf_widthadj(cp, &cp2);
			if (doprint && (indelimit ||
			    (ntruncate < (x_cols * lines + columns))))
				shf_write(cp, cp2 - cp, shl_out);
			cp = cp2 - /* loop increment */ 1;
			continue;
		} else
			columns++;
		if (doprint && (*cp != delimiter) &&
		    (indelimit || (ntruncate < (x_cols * lines + columns))))
			shf_putc(*cp, shl_out);
	}
	if (doprint)
		shf_flush(shl_out);
	return (x_cols * lines + columns);
}


void
pprompt(const char *cp, int ntruncate)
{
	dopprompt(cp, ntruncate, true);
}

int
promptlen(const char *cp)
{
	return (dopprompt(cp, 0, false));
}

/*
 * Read the variable part of a ${...} expression (i.e. up to but not
 * including the :[-+?=#%] or close-brace).
 */
static char *
get_brace_var(XString *wsp, char *wp)
{
	enum parse_state {
		PS_INITIAL, PS_SAW_HASH, PS_IDENT,
		PS_NUMBER, PS_VAR1
	} state;
	char c;

	state = PS_INITIAL;
	while (1) {
		c = getsc();
		/* State machine to figure out where the variable part ends. */
		switch (state) {
		case PS_INITIAL:
			if (c == '#' || c == '!' || c == '%') {
				state = PS_SAW_HASH;
				break;
			}
			/* FALLTHROUGH */
		case PS_SAW_HASH:
			if (ksh_isalphx(c))
				state = PS_IDENT;
			else if (ksh_isdigit(c))
				state = PS_NUMBER;
			else if (ctype(c, C_VAR1))
				state = PS_VAR1;
			else
				goto out;
			break;
		case PS_IDENT:
			if (!ksh_isalnux(c)) {
				if (c == '[') {
					char *tmp, *p;

					if (!arraysub(&tmp))
						yyerror("missing ]\n");
					*wp++ = c;
					for (p = tmp; *p; ) {
						Xcheck(*wsp, wp);
						*wp++ = *p++;
					}
					afree(tmp, ATEMP);
					/* the ] */
					c = getsc();
				}
				goto out;
			}
			break;
		case PS_NUMBER:
			if (!ksh_isdigit(c))
				goto out;
			break;
		case PS_VAR1:
			goto out;
		}
		Xcheck(*wsp, wp);
		*wp++ = c;
	}
 out:
	/* end of variable part */
	*wp++ = '\0';
	ungetsc(c);
	return (wp);
}

/*
 * Save an array subscript - returns true if matching bracket found, false
 * if eof or newline was found.
 * (Returned string double null terminated)
 */
static int
arraysub(char **strp)
{
	XString ws;
	char *wp, c;
	/* we are just past the initial [ */
	int depth = 1;

	Xinit(ws, wp, 32, ATEMP);

	do {
		c = getsc();
		Xcheck(ws, wp);
		*wp++ = c;
		if (c == '[')
			depth++;
		else if (c == ']')
			depth--;
	} while (depth > 0 && c && c != '\n');

	*wp++ = '\0';
	*strp = Xclose(ws, wp);

	return (depth == 0 ? 1 : 0);
}

/* Unget a char: handles case when we are already at the start of the buffer */
static const char *
ungetsc(int c)
{
	if (backslash_skip)
		backslash_skip--;
	/* Don't unget EOF... */
	if (source->str == null && c == '\0')
		return (source->str);
	if (source->str > source->start)
		source->str--;
	else {
		Source *s;

		s = pushs(SREREAD, source->areap);
		s->ugbuf[0] = c; s->ugbuf[1] = '\0';
		s->start = s->str = s->ugbuf;
		s->next = source;
		source = s;
	}
	return (source->str);
}


/* Called to get a char that isn't a \newline sequence. */
static int
getsc_bn(void)
{
	int c, c2;

	if (ignore_backslash_newline)
		return (getsc_());

	if (backslash_skip == 1) {
		backslash_skip = 2;
		return (getsc_());
	}

	backslash_skip = 0;

	while (1) {
		c = getsc_();
		if (c == '\\') {
			if ((c2 = getsc_()) == '\n')
				/* ignore the \newline; get the next char... */
				continue;
			ungetsc(c2);
			backslash_skip = 1;
		}
		return (c);
	}
}

static Lex_state *
push_state_(State_info *si, Lex_state *old_end)
{
	Lex_state *news = alloc2(STATE_BSIZE, sizeof(Lex_state), ATEMP);

	news[0].ls_base = old_end;
	si->base = &news[0];
	si->end = &news[STATE_BSIZE];
	return (&news[1]);
}

static Lex_state *
pop_state_(State_info *si, Lex_state *old_end)
{
	Lex_state *old_base = si->base;

	si->base = old_end->ls_base - STATE_BSIZE;
	si->end = old_end->ls_base;

	afree(old_base, ATEMP);

	return (si->base + STATE_BSIZE - 1);
}

static int
s_get(void)
{
	return (getsc());
}

static void
s_put(int c)
{
	ungetsc(c);
}
