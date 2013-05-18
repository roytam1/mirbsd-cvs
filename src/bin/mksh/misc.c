/*	$OpenBSD: misc.c,v 1.30 2006/03/12 00:26:58 deraadt Exp $	*/
/*	$OpenBSD: path.c,v 1.12 2005/03/30 17:16:37 deraadt Exp $	*/

#include "sh.h"

__RCSID("$MirOS: src/bin/mksh/misc.c,v 1.23 2006/11/10 01:13:52 tg Exp $\t"
	MKSH_SH_H_ID);

unsigned char chtypes[UCHAR_MAX + 1];	/* type bits for unsigned char */

static int do_gmatch(const unsigned char *, const unsigned char *,
    const unsigned char *, const unsigned char *);
static const unsigned char *cclass(const unsigned char *, int);
#ifdef TIOCSCTTY
static void parse_T(char *);
#endif
static char *do_phys_path(XString *, char *, const char *);

/*
 * Fast character classes
 */
void
setctypes(const char *s, int t)
{
	unsigned i;

	if (t & C_IFS) {
		for (i = 0; i < UCHAR_MAX+1; i++)
			chtypes[i] &= ~C_IFS;
		chtypes[0] |= C_IFS; /* include \0 in C_IFS */
	}
	while (*s != 0)
		chtypes[(unsigned char) *s++] |= t;
}

void
initctypes(void)
{
	int c;

	for (c = 'a'; c <= 'z'; c++)
		chtypes[c] |= C_ALPHA;
	for (c = 'A'; c <= 'Z'; c++)
		chtypes[c] |= C_ALPHA;
	chtypes['_'] |= C_ALPHA;
	setctypes("0123456789", C_DIGIT);
	setctypes(" \t\n|&;<>()", C_LEX1); /* \0 added automatically */
	setctypes("*@#!$-?", C_VAR1);
	setctypes(" \t\n", C_IFSWS);
	setctypes("=-+?", C_SUBOP1);
	setctypes(" \n\t\"#$&'()*;<>?[]\\`|", C_QUOTE);
}

/* Allocate a string of size n+1 and copy upto n characters from the possibly
 * null terminated string s into it.  Always returns a null terminated string
 * (unless n < 0).
 */
char *
str_nsave(const char *s, int n, Area *ap)
{
	char *ns = NULL;

	if (n >= 0 && s)
		strlcpy(ns = alloc(n + 1, ap), s, n + 1);
	return (ns);
}

#ifdef MKSH_SMALL
char *
str_save(const char *s, Area *ap)
{
	return (str_nsave(s, s ? strlen(s) : 0, ap));
}
#endif

/* called from XcheckN() to grow buffer */
char *
Xcheck_grow_(XString *xsp, char *xp, unsigned more)
{
	char *old_beg = xsp->beg;

	xsp->len += more > xsp->len ? more : xsp->len;
	xsp->beg = aresize(xsp->beg, xsp->len + 8, xsp->areap);
	xsp->end = xsp->beg + xsp->len;
	return xsp->beg + (xp - old_beg);
}

const struct option options[] = {
	/* Special cases (see parse_args()): -A, -o, -s.
	 * Options are sorted by their longnames - the order of these
	 * entries MUST match the order of sh_flag F* enumerations in sh.h.
	 */
	{ "allexport",	'a',		OF_ANY },
	{ "braceexpand",  0,		OF_ANY }, /* non-standard */
	{ "bgnice",	  0,		OF_ANY },
	{ NULL,		'c',	    OF_CMDLINE },
	{ "emacs",	  0,		OF_ANY },
	{ "emacs-usemeta",  0,		OF_ANY }, /* non-standard */
	{ "errexit",	'e',		OF_ANY },
	{ "gmacs",	  0,		OF_ANY },
	{ "ignoreeof",	  0,		OF_ANY },
	{ "interactive",'i',	    OF_CMDLINE },
	{ "keyword",	'k',		OF_ANY },
	{ "login",	'l',	    OF_CMDLINE },
	{ "markdirs",	'X',		OF_ANY },
	{ "monitor",	'm',		OF_ANY },
	{ "noclobber",	'C',		OF_ANY },
	{ "noexec",	'n',		OF_ANY },
	{ "noglob",	'f',		OF_ANY },
	{ "nohup",	  0,		OF_ANY },
	{ "nolog",	  0,		OF_ANY }, /* no effect */
	{ "notify",	'b',		OF_ANY },
	{ "nounset",	'u',		OF_ANY },
	{ "physical",	  0,		OF_ANY }, /* non-standard */
	{ "posix",	  0,		OF_ANY }, /* non-standard */
	{ "privileged",	'p',		OF_ANY },
	{ "restricted",	'r',	    OF_CMDLINE },
	{ "sh",		  0,		OF_ANY }, /* non-standard */
	{ "stdin",	's',	    OF_CMDLINE }, /* pseudo non-standard */
	{ "trackall",	'h',		OF_ANY },
	{ "utf8-hack",	'U',		OF_ANY }, /* non-standard */
	{ "verbose",	'v',		OF_ANY },
	{ "vi",		  0,		OF_ANY },
	{ "viraw",	  0,		OF_ANY }, /* no effect */
	{ "vi-show8",	  0,		OF_ANY }, /* non-standard */
	{ "vi-tabcomplete",  0,		OF_ANY }, /* non-standard */
	{ "vi-esccomplete",  0,		OF_ANY }, /* non-standard */
	{ "xtrace",	'x',		OF_ANY },
	/* Anonymous flags: used internally by shell only
	 * (not visible to user)
	 */
	{ NULL,		 0,	   OF_INTERNAL }, /* FTALKING_I */
};

/*
 * translate -o option into F* constant (also used for test -o option)
 */
int
option(const char *n)
{
	unsigned i;

	for (i = 0; i < NELEM(options); i++)
		if (options[i].name && strcmp(options[i].name, n) == 0)
			return i;

	return -1;
}

struct options_info {
	int opt_width;
	struct {
		const char *name;
		int	flag;
	} opts[NELEM(options)];
};

static char *options_fmt_entry(void *arg, int i, char *buf, int buflen);
static void printoptions(int verbose);

/* format a single select menu item */
static char *
options_fmt_entry(void *arg, int i, char *buf, int buflen)
{
	struct options_info *oi = (struct options_info *) arg;

	shf_snprintf(buf, buflen, "%-*s %s",
	    oi->opt_width, oi->opts[i].name,
	    Flag(oi->opts[i].flag) ? "on" : "off");
	return buf;
}

static void
printoptions(int verbose)
{
	unsigned i;

	if (verbose) {
		struct options_info oi;
		int n, len;

		/* verbose version */
		shprintf("Current option settings\n");

		for (i = n = oi.opt_width = 0; i < NELEM(options); i++)
			if (options[i].name) {
				len = strlen(options[i].name);
				oi.opts[n].name = options[i].name;
				oi.opts[n++].flag = i;
				if (len > oi.opt_width)
					oi.opt_width = len;
			}
		print_columns(shl_stdout, n, options_fmt_entry, &oi,
		    oi.opt_width + 5, 1);
	} else {
		/* short version ala ksh93 */
		shprintf("set");
		for (i = 0; i < NELEM(options); i++)
			if (Flag(i) && options[i].name)
				shprintf(" -o %s", options[i].name);
		shprintf(newline);
	}
}

char *
getoptions(void)
{
	unsigned i;
	char m[(int) FNFLAGS + 1];
	char *cp = m;

	for (i = 0; i < NELEM(options); i++)
		if (options[i].c && Flag(i))
			*cp++ = options[i].c;
	*cp = 0;
	return str_save(m, ATEMP);
}

/* change a Flag(*) value; takes care of special actions */
void
change_flag(enum sh_flag f,
    int what,		/* flag to change */
    int newval)		/* what is changing the flag (command line vs set) */
{
	int oldval;

	/* limited pdksh compatibility (FSH stays always off) */
	if (f == FSH)
		return;

	oldval = Flag(f);
	Flag(f) = newval;
	if (f == FMONITOR) {
		if (what != OF_CMDLINE && newval != oldval)
			j_change();
	} else if ((f == FVI || f == FEMACS || f == FGMACS) && newval) {
		Flag(FVI) = Flag(FEMACS) = Flag(FGMACS) = 0;
		Flag(f) = newval;
	} else if (f == FPRIVILEGED && oldval && !newval) {
		/* Turning off -p? */
		seteuid(ksheuid = kshuid = getuid());
		setuid(ksheuid);
		setegid(kshegid = kshgid = getgid());
		setgid(kshegid);
	} else if (f == FPOSIX && newval) {
		Flag(FBRACEEXPAND) = 0;
	}
	/* Changing interactive flag? */
	if (f == FTALKING) {
		if ((what == OF_CMDLINE || what == OF_SET) && procpid == kshpid)
			Flag(FTALKING_I) = newval;
	}
}

/* parse command line & set command arguments.  returns the index of
 * non-option arguments, -1 if there is an error.
 */
int
parse_args(char **argv,
    int what,			/* OF_CMDLINE or OF_SET */
    int *setargsp)
{
	static char cmd_opts[NELEM(options) + 5]; /* o:T:\0 */
	static char set_opts[NELEM(options) + 5]; /* Ao;s\0 */
	char *opts;
	char *array = NULL;
	Getopt go;
	int optc, set, sortargs = 0, arrayset = 0;
	unsigned i;

	/* First call?  Build option strings... */
	if (cmd_opts[0] == '\0') {
		char *p, *q;

		/* see cmd_opts[] declaration */
		strlcpy(cmd_opts, "o:T:", sizeof cmd_opts);
		p = cmd_opts + strlen(cmd_opts);
		/* see set_opts[] declaration */
		strlcpy(set_opts, "A:o;s", sizeof set_opts);
		q = set_opts + strlen(set_opts);
		for (i = 0; i < NELEM(options); i++) {
			if (options[i].c) {
				if (options[i].flags & OF_CMDLINE)
					*p++ = options[i].c;
				if (options[i].flags & OF_SET)
					*q++ = options[i].c;
			}
		}
		*p = '\0';
		*q = '\0';
	}

	if (what == OF_CMDLINE) {
		char *p;
		/* Set FLOGIN before parsing options so user can clear
		 * flag using +l.
		 */
		Flag(FLOGIN) = (argv[0][0] == '-' ||
		    ((p = strrchr(argv[0], '/')) && *++p == '-'));
		opts = cmd_opts;
	} else if (what == OF_FIRSTTIME) {
		opts = cmd_opts;
	} else
		opts = set_opts;
	ksh_getopt_reset(&go, GF_ERROR|GF_PLUSOPT);
	while ((optc = ksh_getopt(argv, &go, opts)) != -1) {
		set = (go.info & GI_PLUS) ? 0 : 1;
		switch (optc) {
		case 'A':
			if (what == OF_FIRSTTIME)
				break;
			arrayset = set ? 1 : -1;
			array = go.optarg;
			break;

		case 'o':
			if (what == OF_FIRSTTIME)
				break;
			if (go.optarg == NULL) {
				/* lone -o: print options
				 *
				 * Note that on the command line, -o requires
				 * an option (ie, can't get here if what is
				 * OF_CMDLINE).
				 */
				printoptions(set);
				break;
			}
			i = option(go.optarg);
			if (i != (unsigned)-1 && set == Flag(i))
				/* Don't check the context if the flag
				 * isn't changing - makes "set -o interactive"
				 * work if you're already interactive.  Needed
				 * if the output of "set +o" is to be used.
				 */
				;
			else if (i != (unsigned)-1 && (options[i].flags & what))
				change_flag((enum sh_flag) i, what, set);
			else {
				bi_errorf("%s: bad option", go.optarg);
				return -1;
			}
			break;

		case 'T':
			if (what != OF_FIRSTTIME)
				break;
#ifndef TIOCSCTTY
			bi_errorf("no TIOCSCTTY ioctl");
			return -1;
#else
			change_flag(FTALKING, OF_CMDLINE, 1);
			parse_T(go.optarg);
#endif
			break;

		case '?':
			return -1;

		default:
			if (what == OF_FIRSTTIME)
				break;
			/* -s: sort positional params (at&t ksh stupidity) */
			if (what == OF_SET && optc == 's') {
				sortargs = 1;
				break;
			}
			for (i = 0; i < NELEM(options); i++)
				if (optc == options[i].c &&
				    (what & options[i].flags)) {
					change_flag((enum sh_flag) i, what,
					    set);
					break;
				}
			if (i == NELEM(options)) {
				internal_errorf(1, "parse_args: '%c'", optc);
				return -1; /* not reached */
			}
		}
	}
	if (!(go.info & GI_MINUSMINUS) && argv[go.optind] &&
	    (argv[go.optind][0] == '-' || argv[go.optind][0] == '+') &&
	    argv[go.optind][1] == '\0') {
		/* lone - clears -v and -x flags */
		if (argv[go.optind][0] == '-')
			Flag(FVERBOSE) = Flag(FXTRACE) = 0;
		/* set skips lone - or + option */
		go.optind++;
	}
	if (setargsp)
		/* -- means set $#/$* even if there are no arguments */
		*setargsp = !arrayset && ((go.info & GI_MINUSMINUS) ||
		    argv[go.optind]);

	if (arrayset && (!*array || *skip_varname(array, false))) {
		bi_errorf("%s: is not an identifier", array);
		return -1;
	}
	if (sortargs) {
		for (i = go.optind; argv[i]; i++)
			;
		qsortp((void **) &argv[go.optind], (size_t) (i - go.optind),
		    xstrcmp);
	}
	if (arrayset) {
		set_array(array, arrayset, argv + go.optind);
		for (; argv[go.optind]; go.optind++)
			;
	}

	return go.optind;
}

/* parse a decimal number: returns 0 if string isn't a number, 1 otherwise */
int
getn(const char *as, int *ai)
{
	char *p;
	long n;

	n = strtol(as, &p, 10);

	if (!*as || *p || INT_MIN >= n || n >= INT_MAX)
		return 0;

	*ai = (int)n;
	return 1;
}

/* getn() that prints error */
int
bi_getn(const char *as, int *ai)
{
	int rv = getn(as, ai);

	if (!rv)
		bi_errorf("%s: bad number", as);
	return rv;
}

/* -------- gmatch.c -------- */

/*
 * int gmatch(string, pattern)
 * char *string, *pattern;
 *
 * Match a pattern as in sh(1).
 * pattern character are prefixed with MAGIC by expand.
 */

int
gmatchx(const char *s, const char *p, int isfile)
{
	const char *se, *pe;

	if (s == NULL || p == NULL)
		return 0;
	se = s + strlen(s);
	pe = p + strlen(p);
	/* isfile is false iff no syntax check has been done on
	 * the pattern.  If check fails, just to a strcmp().
	 */
	if (!isfile && !has_globbing(p, pe)) {
		size_t len = pe - p + 1;
		char tbuf[64];
		char *t = len <= sizeof(tbuf) ? tbuf :
		    (char *) alloc(len, ATEMP);
		debunk(t, p, len);
		return !strcmp(t, s);
	}
	return do_gmatch((const unsigned char *) s, (const unsigned char *) se,
	    (const unsigned char *) p, (const unsigned char *) pe);
}

/* Returns if p is a syntacticly correct globbing pattern, false
 * if it contains no pattern characters or if there is a syntax error.
 * Syntax errors are:
 *	- [ with no closing ]
 *	- imbalanced $(...) expression
 *	- [...] and *(...) not nested (eg, [a$(b|]c), *(a[b|c]d))
 */
/*XXX
- if no magic,
	if dest given, copy to dst
	return ?
- if magic && (no globbing || syntax error)
	debunk to dst
	return ?
- return ?
*/
int
has_globbing(const char *xp, const char *xpe)
{
	const unsigned char *p = (const unsigned char *) xp;
	const unsigned char *pe = (const unsigned char *) xpe;
	int c;
	int nest = 0, bnest = 0;
	int saw_glob = 0;
	int in_bracket = 0; /* inside [...] */

	for (; p < pe; p++) {
		if (!ISMAGIC(*p))
			continue;
		if ((c = *++p) == '*' || c == '?')
			saw_glob = 1;
		else if (c == '[') {
			if (!in_bracket) {
				saw_glob = 1;
				in_bracket = 1;
				if (ISMAGIC(p[1]) && p[2] == NOT)
					p += 2;
				if (ISMAGIC(p[1]) && p[2] == ']')
					p += 2;
			}
			/* XXX Do we need to check ranges here? POSIX Q */
		} else if (c == ']') {
			if (in_bracket) {
				if (bnest)		/* [a*(b]) */
					return 0;
				in_bracket = 0;
			}
		} else if ((c & 0x80) && strchr("*+?@! ", c & 0x7f)) {
			saw_glob = 1;
			if (in_bracket)
				bnest++;
			else
				nest++;
		} else if (c == '|') {
			if (in_bracket && !bnest)	/* *(a[foo|bar]) */
				return 0;
		} else if (c == /*(*/ ')') {
			if (in_bracket) {
				if (!bnest--)		/* *(a[b)c] */
					return 0;
			} else if (nest)
				nest--;
		}
		/* else must be a MAGIC-MAGIC, or MAGIC-!, MAGIC--, MAGIC-]
			 MAGIC-{, MAGIC-,, MAGIC-} */
	}
	return saw_glob && !in_bracket && !nest;
}

/* Function must return either 0 or 1 (assumed by code for 0x80|'!') */
static int
do_gmatch(const unsigned char *s, const unsigned char *se,
    const unsigned char *p, const unsigned char *pe)
{
	int sc, pc;
	const unsigned char *prest, *psub, *pnext;
	const unsigned char *srest;

	if (s == NULL || p == NULL)
		return 0;
	while (p < pe) {
		pc = *p++;
		sc = s < se ? *s : '\0';
		s++;
		if (!ISMAGIC(pc)) {
			if (sc != pc)
				return 0;
			continue;
		}
		switch (*p++) {
		case '[':
			if (sc == 0 || (p = cclass(p, sc)) == NULL)
				return 0;
			break;

		case '?':
			if (sc == 0)
				return 0;
			break;

		case '*':
			if (p == pe)
				return 1;
			s--;
			do {
				if (do_gmatch(s, se, p, pe))
					return 1;
			} while (s++ < se);
			return 0;

		  /*
		   * [*+?@!](pattern|pattern|..)
		   *
		   * Not ifdef'd KSH as this is needed for ${..%..}, etc.
		   */
		case 0x80|'+': /* matches one or more times */
		case 0x80|'*': /* matches zero or more times */
			if (!(prest = pat_scan(p, pe, 0)))
				return 0;
			s--;
			/* take care of zero matches */
			if (p[-1] == (0x80 | '*') &&
			    do_gmatch(s, se, prest, pe))
				return 1;
			for (psub = p; ; psub = pnext) {
				pnext = pat_scan(psub, pe, 1);
				for (srest = s; srest <= se; srest++) {
					if (do_gmatch(s, srest, psub, pnext - 2) &&
					    (do_gmatch(srest, se, prest, pe) ||
					    (s != srest && do_gmatch(srest,
					    se, p - 2, pe))))
						return 1;
				}
				if (pnext == prest)
					break;
			}
			return 0;

		case 0x80|'?': /* matches zero or once */
		case 0x80|'@': /* matches one of the patterns */
		case 0x80|' ': /* simile for @ */
			if (!(prest = pat_scan(p, pe, 0)))
				return 0;
			s--;
			/* Take care of zero matches */
			if (p[-1] == (0x80 | '?') &&
			    do_gmatch(s, se, prest, pe))
				return 1;
			for (psub = p; ; psub = pnext) {
				pnext = pat_scan(psub, pe, 1);
				srest = prest == pe ? se : s;
				for (; srest <= se; srest++) {
					if (do_gmatch(s, srest, psub, pnext - 2) &&
					    do_gmatch(srest, se, prest, pe))
						return 1;
				}
				if (pnext == prest)
					break;
			}
			return 0;

		case 0x80|'!': /* matches none of the patterns */
			if (!(prest = pat_scan(p, pe, 0)))
				return 0;
			s--;
			for (srest = s; srest <= se; srest++) {
				int matched = 0;

				for (psub = p; ; psub = pnext) {
					pnext = pat_scan(psub, pe, 1);
					if (do_gmatch(s, srest, psub,
					    pnext - 2)) {
						matched = 1;
						break;
					}
					if (pnext == prest)
						break;
				}
				if (!matched &&
				    do_gmatch(srest, se, prest, pe))
					return 1;
			}
			return 0;

		default:
			if (sc != p[-1])
				return 0;
			break;
		}
	}
	return s == se;
}

static const unsigned char *
cclass(const unsigned char *p, int sub)
{
	int c, d, not, found = 0;
	const unsigned char *orig_p = p;

	if ((not = (ISMAGIC(*p) && *++p == NOT)))
		p++;
	do {
		c = *p++;
		if (ISMAGIC(c)) {
			c = *p++;
			if ((c & 0x80) && !ISMAGIC(c)) {
				c &= 0x7f;/* extended pattern matching: *+?@! */
				/* XXX the ( char isn't handled as part of [] */
				if (c == ' ') /* simile for @: plain (..) */
					c = '(' /*)*/;
			}
		}
		if (c == '\0')
			/* No closing ] - act as if the opening [ was quoted */
			return sub == '[' ? orig_p : NULL;
		if (ISMAGIC(p[0]) && p[1] == '-' &&
		    (!ISMAGIC(p[2]) || p[3] != ']')) {
			p += 2; /* MAGIC- */
			d = *p++;
			if (ISMAGIC(d)) {
				d = *p++;
				if ((d & 0x80) && !ISMAGIC(d))
					d &= 0x7f;
			}
			/* POSIX says this is an invalid expression */
			if (c > d)
				return NULL;
		} else
			d = c;
		if (c == sub || (c <= sub && sub <= d))
			found = 1;
	} while (!(ISMAGIC(p[0]) && p[1] == ']'));

	return (found != not) ? p+2 : NULL;
}

/* Look for next ) or | (if match_sep) in *(foo|bar) pattern */
const unsigned char *
pat_scan(const unsigned char *p, const unsigned char *pe, int match_sep)
{
	int nest = 0;

	for (; p < pe; p++) {
		if (!ISMAGIC(*p))
			continue;
		if ((*++p == /*(*/ ')' && nest-- == 0) ||
		    (*p == '|' && match_sep && nest == 0))
			return ++p;
		if ((*p & 0x80) && strchr("*+?@! ", *p & 0x7f))
			nest++;
	}
	return NULL;
}


/* -------- qsort.c -------- */

/*
 * quick sort of array of generic pointers to objects.
 */
static void qsort1(void **base, void **lim, int (*f)(void *, void *));

void
qsortp(void **base,			/* base address */
    size_t n,				/* elements */
    int (*f) (void *, void *))		/* compare function */
{
	qsort1(base, base + n, f);
}

#define	swap2(a, b)	{\
	void *t; t = *(a); *(a) = *(b); *(b) = t;\
}
#define	swap3(a, b, c)	{\
	void *t; t = *(a); *(a) = *(c); *(c) = *(b); *(b) = t;\
}

static void
qsort1(void **base, void **lim, int (*f) (void *, void *))
{
	void **i, **j;
	void **lptr, **hptr;
	size_t n;
	int c;

 top:
	n = (lim - base) / 2;
	if (n == 0)
		return;
	hptr = lptr = base+n;
	i = base;
	j = lim - 1;

	for (;;) {
		if (i < lptr) {
			if ((c = (*f)(*i, *lptr)) == 0) {
				lptr --;
				swap2(i, lptr);
				continue;
			}
			if (c < 0) {
				i += 1;
				continue;
			}
		}

 begin:
		if (j > hptr) {
			if ((c = (*f)(*hptr, *j)) == 0) {
				hptr ++;
				swap2(hptr, j);
				goto begin;
			}
			if (c > 0) {
				if (i == lptr) {
					hptr ++;
					swap3(i, hptr, j);
					i = lptr += 1;
					goto begin;
				}
				swap2(i, j);
				j -= 1;
				i += 1;
				continue;
			}
			j -= 1;
			goto begin;
		}

		if (i == lptr) {
			if (lptr-base >= lim-hptr) {
				qsort1(hptr+1, lim, f);
				lim = lptr;
			} else {
				qsort1(base, lptr, f);
				base = hptr+1;
			}
			goto top;
		}

		lptr -= 1;
		swap3(j, lptr, i);
		j = hptr -= 1;
	}
}

int
xstrcmp(void *p1, void *p2)
{
	return (strcmp((char *)p1, (char *)p2));
}

/* Initialize a Getopt structure */
void
ksh_getopt_reset(Getopt *go, int flags)
{
	go->optind = 1;
	go->optarg = NULL;
	go->p = 0;
	go->flags = flags;
	go->info = 0;
	go->buf[1] = '\0';
}


/* getopt() used for shell built-in commands, the getopts command, and
 * command line options.
 * A leading ':' in options means don't print errors, instead return '?'
 * or ':' and set go->optarg to the offending option character.
 * If GF_ERROR is set (and option doesn't start with :), errors result in
 * a call to bi_errorf().
 *
 * Non-standard features:
 *	- ';' is like ':' in options, except the argument is optional
 *	  (if it isn't present, optarg is set to 0).
 *	  Used for 'set -o'.
 *	- ',' is like ':' in options, except the argument always immediately
 *	  follows the option character (optarg is set to the null string if
 *	  the option is missing).
 *	  Used for 'read -u2', 'print -u2' and fc -40.
 *	- '#' is like ':' in options, expect that the argument is optional
 *	  and must start with a digit.  If the argument doesn't start with a
 *	  digit, it is assumed to be missing and normal option processing
 *	  continues (optarg is set to 0 if the option is missing).
 *	  Used for 'typeset -LZ4'.
 *	- accepts +c as well as -c IF the GF_PLUSOPT flag is present.  If an
 *	  option starting with + is accepted, the GI_PLUS flag will be set
 *	  in go->info.
 */
int
ksh_getopt(char **argv, Getopt *go, const char *optionsp)
{
	char c;
	char *o;

	if (go->p == 0 || (c = argv[go->optind - 1][go->p]) == '\0') {
		char *arg = argv[go->optind], flag = arg ? *arg : '\0';

		go->p = 1;
		if (flag == '-' && arg[1] == '-' && arg[2] == '\0') {
			go->optind++;
			go->p = 0;
			go->info |= GI_MINUSMINUS;
			return -1;
		}
		if (arg == NULL ||
		    ((flag != '-' ) && /* neither a - nor a + (if + allowed) */
		    (!(go->flags & GF_PLUSOPT) || flag != '+')) ||
		    (c = arg[1]) == '\0') {
			go->p = 0;
			return -1;
		}
		go->optind++;
		go->info &= ~(GI_MINUS|GI_PLUS);
		go->info |= flag == '-' ? GI_MINUS : GI_PLUS;
	}
	go->p++;
	if (c == '?' || c == ':' || c == ';' || c == ',' || c == '#' ||
	    !(o = strchr(optionsp, c))) {
		if (optionsp[0] == ':') {
			go->buf[0] = c;
			go->optarg = go->buf;
		} else {
			warningf(true, "%s%s-%c: unknown option",
			    (go->flags & GF_NONAME) ? "" : argv[0],
			    (go->flags & GF_NONAME) ? "" : ": ", c);
			if (go->flags & GF_ERROR)
				bi_errorf(null);
		}
		return '?';
	}
	/* : means argument must be present, may be part of option argument
	 *   or the next argument
	 * ; same as : but argument may be missing
	 * , means argument is part of option argument, and may be null.
	 */
	if (*++o == ':' || *o == ';') {
		if (argv[go->optind - 1][go->p])
			go->optarg = argv[go->optind - 1] + go->p;
		else if (argv[go->optind])
			go->optarg = argv[go->optind++];
		else if (*o == ';')
			go->optarg = NULL;
		else {
			if (optionsp[0] == ':') {
				go->buf[0] = c;
				go->optarg = go->buf;
				return ':';
			}
			warningf(true, "%s%s-'%c' requires argument",
			    (go->flags & GF_NONAME) ? "" : argv[0],
			    (go->flags & GF_NONAME) ? "" : ": ", c);
			if (go->flags & GF_ERROR)
				bi_errorf(null);
			return '?';
		}
		go->p = 0;
	} else if (*o == ',') {
		/* argument is attached to option character, even if null */
		go->optarg = argv[go->optind - 1] + go->p;
		go->p = 0;
	} else if (*o == '#') {
		/* argument is optional and may be attached or unattached
		 * but must start with a digit.  optarg is set to 0 if the
		 * argument is missing.
		 */
		if (argv[go->optind - 1][go->p]) {
			if (digit(argv[go->optind - 1][go->p])) {
				go->optarg = argv[go->optind - 1] + go->p;
				go->p = 0;
			} else
				go->optarg = NULL;
		} else {
			if (argv[go->optind] && digit(argv[go->optind][0])) {
				go->optarg = argv[go->optind++];
				go->p = 0;
			} else
				go->optarg = NULL;
		}
	}
	return c;
}

/* print variable/alias value using necessary quotes
 * (POSIX says they should be suitable for re-entry...)
 * No trailing newline is printed.
 */
void
print_value_quoted(const char *s)
{
	const char *p;
	int inquote = 0;

	/* Test if any quotes are needed */
	for (p = s; *p; p++)
		if (ctype(*p, C_QUOTE))
			break;
	if (!*p) {
		shprintf("%s", s);
		return;
	}
	for (p = s; *p; p++) {
		if (*p == '\'') {
			shprintf("'\\'" + 1 - inquote);
			inquote = 0;
		} else {
			if (!inquote) {
				shprintf("'");
				inquote = 1;
			}
			shf_putc(*p, shl_stdout);
		}
	}
	if (inquote)
		shprintf("'");
}

/* Print things in columns and rows - func() is called to format the ith
 * element
 */
void
print_columns(struct shf *shf, int n, char *(*func) (void *, int, char *, int),
    void *arg, int max_width, int prefcol)
{
	char *str = (char *) alloc(max_width + 1, ATEMP);
	int i;
	int r, c;
	int rows, cols;
	int nspace;

	/* max_width + 1 for the space.  Note that no space
	 * is printed after the last column to avoid problems
	 * with terminals that have auto-wrap.
	 */
	cols = x_cols / (max_width + 1);
	if (!cols)
		cols = 1;
	rows = (n + cols - 1) / cols;
	if (prefcol && n && cols > rows) {
		int tmp = rows;

		rows = cols;
		cols = tmp;
		if (rows > n)
			rows = n;
	}

	nspace = (x_cols - max_width * cols) / cols;
	if (nspace <= 0)
		nspace = 1;
	for (r = 0; r < rows; r++) {
		for (c = 0; c < cols; c++) {
			i = c * rows + r;
			if (i < n) {
				shf_fprintf(shf, "%-*s",
				    max_width,
				    (*func)(arg, i, str, max_width + 1));
				if (c + 1 < cols)
					shf_fprintf(shf, "%*s", nspace, null);
			}
		}
		shf_putchar('\n', shf);
	}
	afree(str, ATEMP);
}

/* Strip any nul bytes from buf - returns new length (nbytes - # of nuls) */
int
strip_nuls(char *buf, int nbytes)
{
	char *dst;

	/* nbytes check because some systems (older FreeBSDs) have a buggy
	 * memchr()
	 */
	if (nbytes && (dst = memchr(buf, '\0', nbytes))) {
		char *end = buf + nbytes;
		char *p, *q;

		for (p = dst; p < end; p = q) {
			/* skip a block of nulls */
			while (++p < end && *p == '\0')
				;
			/* find end of non-null block */
			if (!(q = memchr(p, '\0', end - p)))
				q = end;
			memmove(dst, p, q - p);
			dst += q - p;
		}
		*dst = '\0';
		return dst - buf;
	}
	return nbytes;
}

/* Like read(2), but if read fails due to non-blocking flag, resets flag
 * and restarts read.
 */
int
blocking_read(int fd, char *buf, int nbytes)
{
	int ret;
	int tried_reset = 0;

	while ((ret = read(fd, buf, nbytes)) < 0) {
		if (!tried_reset && errno == EAGAIN) {
			int oerrno = errno;
			if (reset_nonblock(fd) > 0) {
				tried_reset = 1;
				continue;
			}
			errno = oerrno;
		}
		break;
	}
	return ret;
}

/* Reset the non-blocking flag on the specified file descriptor.
 * Returns -1 if there was an error, 0 if non-blocking wasn't set,
 * 1 if it was.
 */
int
reset_nonblock(int fd)
{
	int flags;

	if ((flags = fcntl(fd, F_GETFL, 0)) < 0)
		return -1;
	if (!(flags & O_NONBLOCK))
		return 0;
	flags &= ~O_NONBLOCK;
	if (fcntl(fd, F_SETFL, flags) < 0)
		return -1;
	return 1;
}


/* Like getcwd(), except bsize is ignored if buf is 0 (PATH_MAX is used) */
char *
ksh_get_wd(char *buf, int bsize)
{
	char *b;
	char *ret;

	/* Note: we could just use plain getcwd(), but then we'd had to
	 * inject possibly allocated space into the ATEMP area. */
	/* Assume getcwd() available */
	if (!buf) {
		bsize = PATH_MAX;
		b = alloc(PATH_MAX + 1, ATEMP);
	} else
		b = buf;

	ret = getcwd(b, bsize);

	if (!buf) {
		if (ret)
			ret = aresize(b, strlen(b) + 1, ATEMP);
		else
			afree(b, ATEMP);
	}

	return ret;
}

/*
 *	Makes a filename into result using the following algorithm.
 *	- make result NULL
 *	- if file starts with '/', append file to result & set cdpathp to NULL
 *	- if file starts with ./ or ../ append cwd and file to result
 *	  and set cdpathp to NULL
 *	- if the first element of cdpathp doesnt start with a '/' xx or '.' xx
 *	  then cwd is appended to result.
 *	- the first element of cdpathp is appended to result
 *	- file is appended to result
 *	- cdpathp is set to the start of the next element in cdpathp (or NULL
 *	  if there are no more elements.
 *	The return value indicates whether a non-null element from cdpathp
 *	was appended to result.
 */
int
make_path(const char *cwd, const char *file,
    char **cdpathp,		/* & of : separated list */
    XString *xsp,
    int *phys_pathp)
{
	int	rval = 0;
	int	use_cdpath = 1;
	char	*plist;
	int	len;
	int	plen = 0;
	char	*xp = Xstring(*xsp, xp);

	if (!file)
		file = null;

	if (file[0] == '/') {
		*phys_pathp = 0;
		use_cdpath = 0;
	} else {
		if (file[0] == '.') {
			char c = file[1];

			if (c == '.')
				c = file[2];
			if (c == '/' || c == '\0')
				use_cdpath = 0;
		}

		plist = *cdpathp;
		if (!plist)
			use_cdpath = 0;
		else if (use_cdpath) {
			char *pend;

			for (pend = plist; *pend && *pend != ':'; pend++)
				;
			plen = pend - plist;
			*cdpathp = *pend ? ++pend : NULL;
		}

		if ((use_cdpath == 0 || !plen || plist[0] != '/') &&
		    (cwd && *cwd)) {
			len = strlen(cwd);
			XcheckN(*xsp, xp, len);
			memcpy(xp, cwd, len);
			xp += len;
			if (cwd[len - 1] != '/')
				Xput(*xsp, xp, '/');
		}
		*phys_pathp = Xlength(*xsp, xp);
		if (use_cdpath && plen) {
			XcheckN(*xsp, xp, plen);
			memcpy(xp, plist, plen);
			xp += plen;
			if (plist[plen - 1] != '/')
				Xput(*xsp, xp, '/');
			rval = 1;
		}
	}

	len = strlen(file) + 1;
	XcheckN(*xsp, xp, len);
	memcpy(xp, file, len);

	if (!use_cdpath)
		*cdpathp = NULL;

	return rval;
}

/*
 * Simplify pathnames containing "." and ".." entries.
 * ie, simplify_path("/a/b/c/./../d/..") returns "/a/b"
 */
void
simplify_path(char *pathl)
{
	char	*cur;
	char	*t;
	int	isrooted;
	char	*very_start = pathl;
	char	*start;

	if (!*pathl)
		return;

	if ((isrooted = pathl[0] == '/'))
		very_start++;

	/* Before			After
	 *  /foo/			/foo
	 *  /foo/../../bar		/bar
	 *  /foo/./blah/..		/foo
	 *  .				.
	 *  ..				..
	 *  ./foo			foo
	 *  foo/../../../bar		../../bar
	 */

	for (cur = t = start = very_start; ; ) {
		/* treat multiple '/'s as one '/' */
		while (*t == '/')
			t++;

		if (*t == '\0') {
			if (cur == pathl)
				/* convert empty path to dot */
				*cur++ = '.';
			*cur = '\0';
			break;
		}

		if (t[0] == '.') {
			if (!t[1] || t[1] == '/') {
				t += 1;
				continue;
			} else if (t[1] == '.' && (!t[2] || t[2] == '/')) {
				if (!isrooted && cur == start) {
					if (cur != very_start)
						*cur++ = '/';
					*cur++ = '.';
					*cur++ = '.';
					start = cur;
				} else if (cur != start)
					while (--cur > start && *cur != '/')
						;
				t += 2;
				continue;
			}
		}

		if (cur != very_start)
			*cur++ = '/';

		/* find/copy next component of pathname */
		while (*t && *t != '/')
			*cur++ = *t++;
	}
}


void
set_current_wd(char *pathl)
{
	int len;
	char *p = pathl;

	if (!p && !(p = ksh_get_wd(NULL, 0)))
		p = null;

	len = strlen(p) + 1;

	if (len > current_wd_size)
		current_wd = aresize(current_wd, current_wd_size = len, APERM);
	memcpy(current_wd, p, len);
	if (p != pathl && p != null)
		afree(p, ATEMP);
}

char *
get_phys_path(const char *pathl)
{
	XString xs;
	char *xp;

	Xinit(xs, xp, strlen(pathl) + 1, ATEMP);

	xp = do_phys_path(&xs, xp, pathl);

	if (!xp)
		return NULL;

	if (Xlength(xs, xp) == 0)
		Xput(xs, xp, '/');
	Xput(xs, xp, '\0');

	return Xclose(xs, xp);
}

static char *
do_phys_path(XString *xsp, char *xp, const char *pathl)
{
	const char *p, *q;
	int len, llen;
	int savepos;
	char lbuf[PATH_MAX];

	Xcheck(*xsp, xp);
	for (p = pathl; p; p = q) {
		while (*p == '/')
			p++;
		if (!*p)
			break;
		len = (q = strchr(p, '/')) ? q - p : (int)strlen(p);
		if (len == 1 && p[0] == '.')
			continue;
		if (len == 2 && p[0] == '.' && p[1] == '.') {
			while (xp > Xstring(*xsp, xp)) {
				xp--;
				if (*xp == '/')
					break;
			}
			continue;
		}

		savepos = Xsavepos(*xsp, xp);
		Xput(*xsp, xp, '/');
		XcheckN(*xsp, xp, len + 1);
		memcpy(xp, p, len);
		xp += len;
		*xp = '\0';

		llen = readlink(Xstring(*xsp, xp), lbuf, sizeof(lbuf) - 1);
		if (llen < 0) {
			/* EINVAL means it wasn't a symlink... */
			if (errno != EINVAL)
				return NULL;
			continue;
		}
		lbuf[llen] = '\0';

		/* If absolute path, start from scratch.. */
		xp = lbuf[0] == '/' ? Xstring(*xsp, xp) :
		    Xrestpos(*xsp, xp, savepos);
		if (!(xp = do_phys_path(xsp, xp, lbuf)))
			return NULL;
	}
	return xp;
}

#ifdef TIOCSCTTY
static void
parse_T(char *fn)
{
	char dv[20];
	struct stat sb;
	int fd;

	if (stat(fn, &sb)) {
		memcpy(dv, "/dev/ttyC", 9);
		strlcpy(dv + 9, fn, 20 - 9);
		if (stat(dv, &sb)) {
			memmove(dv + 8, dv + 9, 20 - 9);
			if (stat(dv, &sb))
				bi_errorf("chvt: can't find tty %s", fn);
		}
		fn = dv;
	}
	if (!(sb.st_mode & S_IFCHR))
		bi_errorf("chvt: not a char device: %s", fn);
	if ((sb.st_uid != 0) && chown(fn, 0, 0))
		warningf(false, "chvt: cannot chown root %s", fn);
	if (((sb.st_mode & 07777) != 0600) && chmod(fn, 0600))
		warningf(false, "chvt: cannot chmod 0600 %s", fn);
#if !defined(__sun__) && !defined(__gnu_linux__) && !defined(__INTERIX)
	if (revoke(fn))
		warningf(false, "chvt: cannot revoke %s", fn);
#endif

	if ((fd = open(fn, O_RDWR)) == -1) {
		sleep(1);
		if ((fd = open(fn, O_RDWR)) == -1)
			bi_errorf("chvt: cannot open %s", fn);
	}
	switch (fork()) {
	case -1:
		bi_errorf("fork failed");
	case 0:
		break;
	default:
		_exit(0);
	}
	if (setsid() == -1)
		bi_errorf("chvt: setsid failed");
	if (ioctl(fd, TIOCSCTTY, NULL) == -1)
		bi_errorf("chvt: TIOCSCTTY failed");
	dup2(fd, 0);
	dup2(fd, 1);
	dup2(fd, 2);
	if (fd > 2)
		close(fd);
}
#endif
