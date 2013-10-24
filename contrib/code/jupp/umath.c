/* $MirOS: contrib/code/jupp/umath.c,v 1.4 2012/12/20 20:11:54 tg Exp $ */
/*
 *	Math
 *	Copyright
 *		(C) 1992 Joseph H. Allen
 *
 *	This file is part of JOE (Joe's Own Editor)
 */
#include "config.h"
#include "types.h"

#include <stdio.h>
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#include <string.h>

#include "b.h"
#include "pw.h"
#include "utils.h"
#include "vs.h"
#include "utf8.h"
#include "charmap.h"
#include "w.h"

const unsigned char * volatile merr;

static char math_res[JOE_MSGBUFSIZE];
static char *math_exp;

static RETSIGTYPE fperr(int unused)
{
	if (!merr) {
		merr = US "Float point exception";
	}
	REINSTALL_SIGHANDLER(SIGFPE, fperr);
}

struct var {
	unsigned char *name;
	int set;
	double val;
	struct var *next;
} *vars = NULL;

static struct var *get(unsigned char *str)
{
	struct var *v;

	for (v = vars; v; v = v->next) {
		if (!strcmp(v->name, str)) {
			return v;
		}
	}
	v = (struct var *) joe_malloc(sizeof(struct var));

	v->set = 0;
	v->next = vars;
	vars = v;
	v->name = (unsigned char *)strdup((char *)str);
	return v;
}

unsigned char *ptr;
struct var *dumb;

static double expr(int prec, struct var **rtv)
{
	double x = 0.0;
	struct var *v = NULL;

	while (*ptr == ' ' || *ptr == '\t') {
		++ptr;
	}
	if ((*ptr >= 'a' && *ptr <= 'z') || (*ptr >= 'A' && *ptr <= 'Z')
	    || *ptr == '_') {
		unsigned char *s = ptr, c;

		while ((*ptr >= 'a' && *ptr <= 'z')
		       || (*ptr >= 'A' && *ptr <= 'Z')
		       || *ptr == '_' || (*ptr >= '0' && *ptr <= '9')) {
			++ptr;
		}
		c = *ptr;
		*ptr = 0;
		v = get(s);
		x = v->val;
		*ptr = c;
	} else if (ptr[0] == '0' && (ptr[1] | 0x20) == 'x') {
		unsigned long xi;

		sscanf((char *)ptr, "%li", &xi);
		x = (double)xi;
		ptr += 2;
		while ((*ptr >= '0' && *ptr <= '9') || ((*ptr | 0x20) >= 'a' && (*ptr | 0x20) <= 'f'))
			++ptr;
	} else if ((*ptr >= '0' && *ptr <= '9') || *ptr == '.') {
		sscanf((char *)ptr, "%lf", &x);
		while ((*ptr >= '0' && *ptr <= '9') || *ptr == '.' || *ptr == 'e' || *ptr == 'E')
			++ptr;
	} else if (*ptr == '(') {
		++ptr;
		x = expr(0, &v);
		if (*ptr == ')')
			++ptr;
		else {
			if (!merr)
				merr = US "Missing )";
		}
	} else if (*ptr == '-') {
		++ptr;
		x = -expr(10, &dumb);
	}
      loop:
	while (*ptr == ' ' || *ptr == '\t')
		++ptr;
	if (*ptr == '*' && 5 > prec) {
		++ptr;
		x *= expr(5, &dumb);
		goto loop;
	} else if (*ptr == '/' && 5 > prec) {
		++ptr;
		x /= expr(5, &dumb);
		goto loop;
	} else if (*ptr == '+' && 4 > prec) {
		++ptr;
		x += expr(4, &dumb);
		goto loop;
	} else if (*ptr == '-' && 4 > prec) {
		++ptr;
		x -= expr(4, &dumb);
		goto loop;
	} else if (*ptr == '=' && 2 >= prec) {
		++ptr;
		x = expr(2, &dumb);
		if (v) {
			v->val = x;
			v->set = 1;
		} else {
			if (!merr)
				merr = US "Left side of = is not an l-value";
		}
		goto loop;
	}
	*rtv = v;
	return x;
}

#if defined(SIZEOF_LONG_LONG) && (SIZEOF_LONG_LONG > 0)
typedef long long joe_imaxt;
#define JOE_IMAXT "ll"
#else
typedef long joe_imaxt;
#define JOE_IMAXT "l"
#endif

double calc(BW *bw, unsigned char *s)
{
	double result;
	struct var *v;
	BW *tbw = bw->parent->main->object;

	if (math_exp) {
		free(math_exp);
	}
	math_exp = strdup((void *)s);

	v = get(US "top");
	v->val = tbw->top->line + 1;
	v->set = 1;
	v = get(US "lines");
	v->val = tbw->b->eof->line + 1;
	v->set = 1;
	v = get(US "line");
	v->val = tbw->cursor->line + 1;
	v->set = 1;
	v = get(US "col");
	v->val = tbw->cursor->col + 1;
	v->set = 1;
	v = get(US "byte");
	v->val = tbw->cursor->byte + 1;
	v->set = 1;
	v = get(US "height");
	v->val = tbw->h;
	v->set = 1;
	v = get(US "width");
	v->val = tbw->w;
	v->set = 1;
	ptr = s;
	merr = 0;
      up:
	result = expr(0, &dumb);
	if (!merr) {
		while (*ptr == ' ' || *ptr == '\t') {
			++ptr;
		}
		if (*ptr == ';') {
			++ptr;
			while (*ptr == ' ' || *ptr == '\t') {
				++ptr;
			}
			if (*ptr) {
				goto up;
			}
		} else if (*ptr) {
			merr = US "Extra junk after end of expr";
		}
	}

	if (merr) {
		joe_snprintf_1(math_res, JOE_MSGBUFSIZE,
		    "math_error{%s}", merr);
	} else {
		joe_imaxt ires = (joe_imaxt)result;

		if ((double)ires == result) {
			/* representable as integer value */
			joe_snprintf_1(math_res, JOE_MSGBUFSIZE,
			    "%" JOE_IMAXT "d", ires);
		} else {
			/* use float with large precision */
			joe_snprintf_1(math_res, JOE_MSGBUFSIZE,
			    "%.60G", result);
		}
	}

	return result;
}

/* Main user interface */
static int domath(BW *bw, unsigned char *s, void *object, int *notify)
{
	calc(bw, s);

	if (notify) {
		*notify = 1;
	}
	if (merr) {
		msgnw(bw->parent, merr);
		return -1;
	}
	vsrm(s);
	memcpy(msgbuf, math_res, JOE_MSGBUFSIZE);
	if (bw->parent->watom->what != TYPETW) {
		binsm(bw->cursor, sz(msgbuf));
		pfwrd(bw->cursor, strlen((char *)msgbuf));
		bw->cursor->xcol = piscol(bw->cursor);
	} else {
		msgnw(bw->parent, msgbuf);
	}
	return 0;
}

B *mathhist = NULL;

int umath(BW *bw)
{
	joe_set_signal(SIGFPE, fperr);
	if (wmkpw(bw->parent, US "=", &mathhist, domath, US "math", NULL, NULL, NULL, NULL, locale_map)) {
		return 0;
	} else {
		return -1;
	}
}

int umathins(BW *bw)
{
	if (math_exp) {
		binss(bw->cursor, (void *)math_exp);
	}
	return 0;
}

int umathres(BW *bw)
{
	binss(bw->cursor, (void *)math_res);
	return 0;
}