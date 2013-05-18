/* $MirOS: contrib/code/jupp/regex.c,v 1.4 2010/04/08 15:31:03 tg Exp $ */
/*
 *	Regular expression subroutines
 *	Copyright
 *		(C) 1992 Joseph H. Allen
 *
 *	This file is part of JOE (Joe's Own Editor)
 */
#include "config.h"
#include "types.h"

#include <stdio.h> 

#include "b.h"
#include "utf8.h"
#include "charmap.h"
#include "vs.h"

int escape(int utf8_,unsigned char **a, int *b)
{
	int c;
	unsigned char *s = *a;
	int l = *b;

	if (*s == '\\' && l >= 2) {
		++s; --l;
		switch (*s) {
		case 'n':
			c = 10;
			++s; --l;
			break;
		case 't':
			c = 9;
			++s; --l;
			break;
		case 'a':
			c = 7;
			++s; --l;
			break;
		case 'b':
			c = 8;
			++s; --l;
			break;
		case 'f':
			c = 12;
			++s; --l;
			break;
		case 'e':
			c = 27;
			++s; --l;
			break;
		case 'r':
			c = 13;
			++s; --l;
			break;
		case '8':
			c = 8;
			++s; --l;
			break;
		case '9':
			c = 9;
			++s; --l;
			break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
			c = *s - '0';
			++s; --l;
			if (l > 0 && *s >= '0' && *s <= '7') {
				c = c * 8 + s[1] - '0';
				++s; --l;
			}
			if (l > 0 && *s >= '0' && *s <= '7') {
				c = c * 8 + s[1] - '0';
				++s; --l;
			}
			break;
		case 'x':
		case 'X':
			c = 0;
			++s; --l;
			if (l > 0 && *s >= '0' && *s <= '9') {
				c = c * 16 + *s - '0';
				++s; --l;
			} else if (l > 0 && *s >= 'A' && *s <= 'F') {
				c = c * 16 + *s - 'A' + 10;
				++s; --l;
			} else if (l > 0 && *s >= 'a' && *s <= 'f') {
				c = c * 16 + *s - 'a' + 10;
				++s; --l;
			}

			if (l > 0 && *s >= '0' && *s <= '9') {
				c = c * 16 + *s - '0';
				++s; --l;
			} else if (l > 0 && *s >= 'A' && *s <= 'F') {
				c = c * 16 + *s - 'A' + 10;
				++s; --l;
			} else if (l > 0 && *s >= 'a' && *s <= 'f') {
				c = c * 16 + *s - 'a' + 10;
				++s; --l;
			}
			break;
		default:
			if (utf8_)
				c = utf8_decode_fwrd(&s, &l);
			else {
				c = *s++;
				--l;
			}
			break;
		}
	} else if (utf8_) {
		c = utf8_decode_fwrd(&s,&l);
	} else {
		c = *s++;
		--l;
	}
	*a = s;
	*b = l;
	return c;
}

static int brack(int utf8_,unsigned char **a, int *la, int c)
{
	int inverse = 0;
	int flag = 0;
	unsigned char *s = *a;
	int l = *la;

	if (!l)
		return 0;
	if (*s == '^' || *s == '*') {
		inverse = 1;
		++s;
		--l;
	}
	if (l && *s == ']') {
		++s;
		--l;
		if (c == ']')
			flag = 1;
	}
	while (l)
		if (*s == ']') {
			++s;
			--l;
			break;
		} else {
			int cl, cr;

			cl = escape(utf8_, &s, &l);

			if (l >= 2 && s[0] == '-' && s[1] != ']') {
				--l;
				++s;
				cr = escape(utf8_, &s, &l);
				if (c >= cl && c <= cr)
					flag = 1;
			} else if (c == cl)
				flag = 1;
		}
	*a = s;
	*la = l;
	if (inverse)
		return !flag;
	else
		return flag;
}

static void savec(int utf8_,unsigned char **pieces, int n, int c)
{
	unsigned char buf[16];
	int len;
	unsigned char *s = NULL;

	if (utf8_)
		len = utf8_encode(buf,c);
	else {
		buf[0] = c;
		len = 1;
	}

	if (pieces[n])
		vsrm(pieces[n]);
	s = vsncpy(s, 0, buf, len);
	pieces[n] = s;
}

#define MAX_REGEX_SAVED 16384 /* Largest regex string we will save */

static void saves(unsigned char **pieces, int n, P *p, long int szz)
{
	if (szz > MAX_REGEX_SAVED)
		pieces[n] = vstrunc(pieces[n], 0);
	else {
		pieces[n] = vstrunc(pieces[n], (int) szz);
		brmem(p, pieces[n], (int) szz);
	}
}

/* Returns -1 (NO_MORE_DATA) for end of file.
 * Returns -2 if we skipped a special sequence and didn't take the character
 * after it (this happens for "strings").
 * Otherwise returns character after sequence (character will be >=0).
 */

static int skip_special(P *p)
{
	int to, s;

	switch (s = pgetc(p)) {
	case '"':
		do {
			if ((s = pgetc(p)) == '\\') {
				pgetc(p);
				s = pgetc(p);
			}
		} while (s != NO_MORE_DATA && s != '"');
		if (s == '"')
			return -2;
		break;
	case '\'':
		if ((s = pgetc(p)) == '\\') {
			pgetc(p);
			s = pgetc(p);
		}
		if (s == '\'')
			return -2;
		if ((s = pgetc(p)) == '\'')
			return -2;
		if ((s = pgetc(p)) == '\'')
			return -2;
		break;
	case '[':
		to = ']';
		goto skip;
	case '(':
		to = ')';
		goto skip;
	case '{':
		to = '}';
skip:
		do {
			s = skip_special(p);
		} while (s != to && s != NO_MORE_DATA);
		if (s == to)
			return -2;
		break;
	case '/':
		s = pgetc(p);
		if (s == '*')
			do {
				s = pgetc(p);
				while (s == '*')
					if ((s = pgetc(p)) == '/')
						return -2;
			} while (s != NO_MORE_DATA);
		else if (s != NO_MORE_DATA)
			s = prgetc(p);
		else
			s = '/';
		break;
	}
	return s;
}

int pmatch(unsigned char **pieces, unsigned char *regex, int len, P *p, int n, int icase)
{
	int c, d;
	P *q = pdup(p);
	P *o = NULL;
	int utf8_ = p->b->o.charmap->type;
	struct charmap *map = p->b->o.charmap;
	struct utf8_sm sm;

	utf8_init(&sm);

	while (len) {
		if (utf8_) {
			do {
				c = utf8_decode(&sm,*regex++);
				--len;
			} while (len && c<0);
			if (c<0)
				return 0;
		} else {
			c = *regex++;
			--len;
		}

		switch (c) {
		case '\\':
			if (!len--)
				goto fail;
			switch (c = *regex++) {
			case '?':
				d = pgetc(p);
				if (d == NO_MORE_DATA)
					goto fail;
				savec(utf8_, pieces, n++, d);
				break;
			case 'n':
			case 'r':
			case 'a':
			case 'f':
			case 'b':
			case 't':
			case 'e':
			case 'x':
			case 'X':
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				regex -= 2;
				len += 2;
				if (pgetc(p) != escape(utf8_, &regex, &len))
					goto fail;
				break;
			case '*':
				/* Find shortest matching sequence */
				o = pdup(p);
				do {
					long pb = p->byte;

					if (pmatch(pieces, regex, len, p, n + 1, icase)) {
						saves(pieces, n, o, pb - o->byte);
						goto succeed;
					}
					c = pgetc(p);
				} while (c != NO_MORE_DATA && c != '\n');
				goto fail;
			case 'c':
				o = pdup(p);
				do {
					long pb = p->byte;

					if (pmatch(pieces, regex, len, p, n + 1, icase)) {
						saves(pieces, n, o, pb - o->byte);
						goto succeed;
					}
				} while (skip_special(p) != NO_MORE_DATA);
				goto fail;
			case '[':
				d = pgetc(p);
				if (d == NO_MORE_DATA)
					goto fail;
				if (!brack(utf8_, &regex, &len, d))
					goto fail;
				savec(utf8_, pieces, n++, d);
				break;
			case '+':
				{
					unsigned char *oregex = regex;	/* Point to character to skip */
					int olen = len;

					unsigned char *tregex;
					int tlen;

					int match;

					P *r = NULL;

					d = 0;

					o = pdup(p);

					/* Advance over character to skip.  Save character in d unless
					   we're skipping over a \[..] */
					if (len >= 2 && regex[0] == '\\') {
						if (regex[1] == '[') {
							regex += 2;
							len -= 2;
							brack(utf8_, &regex, &len, 0);
						} else {
							d = escape(utf8_, &regex, &len);
							if (icase)
								d = joe_tolower(map,d);
						}
					} else if (utf8_) {
						if ((d = utf8_decode_fwrd(&regex, &len)) < 0)
							goto done;
						else if (icase)
							d = joe_tolower(map,d);
					} else {
						if (len >= 1) {
							--len;
							d = *regex++;
							if (icase)
								d = joe_tolower(map,d);
						} else
							goto done;
					}

					/* Now oregex/olen point to character to skip over and
					   regex/len point to sequence which follows */

					do {
						P *z = pdup(p);

						if (pmatch(pieces, regex, len, p, n + 1, icase)) {
							saves(pieces, n, o, z->byte - o->byte);
							if (r)
								prm(r);
							r = pdup(p);
						}
						pset(p, z);
						prm(z);
						c = pgetc(p);
						tregex = oregex;
						tlen = olen;
						if (*oregex == '\\') {
							if (oregex[1] == '[') {
								tregex += 2;
								tlen -= 2;
								match = brack(utf8_, &tregex, &tlen, c);
							} else
								match = (d == c);
						} else {
							if(icase)
								match = (joe_tolower(map,c) == d);
							else
								match = (c == d);
						}
					} while (c != NO_MORE_DATA && match);

				      done:
					if (r) {
						pset(p, r);
						prm(r);
					}
					if (r)
						goto succeed;
					else
						goto fail;
				}
			case '^':
				if (!pisbol(p))
					goto fail;
				break;
			case '$':
				if (!piseol(p))
					goto fail;
				break;
			case '<':
				if (!pisbow(p))
					goto fail;
				break;
			case '>':
				if (!piseow(p))
					goto fail;
				break;
			case '\\':
				d = pgetc(p);
				if (d != c)
					goto fail;
				break;
			default:
				goto fail;
			}
			break;
		default:
			d = pgetc(p);
			if (icase) {
				if (joe_tolower(map,d) != joe_tolower(map,c))
					goto fail;
			} else {
				if (d != c)
					goto fail;
			}
		}
	}
succeed:
	if (o)
		prm(o);
	prm(q);
	return 1;

fail:
	if (o)
		prm(o);
	pset(p, q);
	prm(q);
	return 0;
}
