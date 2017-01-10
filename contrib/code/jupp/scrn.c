/* $MirOS: contrib/code/jupp/scrn.c,v 1.12 2013/11/07 21:50:35 tg Exp $ */
/*
 *	Device independant TTY interface for JOE
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

#include "bw.h"
#include "blocks.h"
#include "scrn.h"
#include "termcap.h"
#include "charmap.h"
#include "utf8.h"
#include "utils.h"

int skiptop = 0;
int lines = 0;
int columns = 0;
int notite = 0;
int pastetite = 0;
int usetabs = 0;
int assume_color = 0;

/* How to display characters (especially the control ones) */
/* here are characters ... */
static const unsigned char xlatc[256] = {
	 64,  65,  66,  67,  68,  69,  70,  71,			/*   8 */
	 72,  73,  74,  75,  76,  77,  78,  79,			/*  16 */
	 80,  81,  82,  83,  84,  85,  86,  87,			/*  24 */
	 88,  89,  90,  91,  92,  93,  94,  95,			/*  32 */
	 32,  33,  34,  35,  36,  37,  38,  39,			/*  40 */
	 40,  41,  42,  43,  44,  45,  46,  47,			/*  48 */
	 48,  49,  50,  51,  52,  53,  54,  55,			/*  56 */
	 56,  57,  58,  59,  60,  61,  62,  63,			/*  64 */

	 64,  65,  66,  67,  68,  69,  70,  71,			/*  72 */
	 72,  73,  74,  75,  76,  77,  78,  79,			/*  80 */
	 80,  81,  82,  83,  84,  85,  86,  87,			/*  88 */
	 88,  89,  90,  91,  92,  93,  94,  95,			/*  96 */
	 96,  97,  98,  99, 100, 101, 102, 103,			/* 104 */
	104, 105, 106, 107, 108, 109, 110, 111,			/* 112 */
	112, 113, 114, 115, 116, 117, 118, 119,			/* 120 */
	120, 121, 122, 123, 124, 125, 126,  63,			/* 128 */

	 64,  65,  66,  67,  68,  69,  70,  71,			/* 136 */
	 72,  73,  74,  75,  76,  77,  78,  79,			/* 144 */
	 80,  81,  82,  83,  84,  85,  86,  87,			/* 152 */
	 88,  89,  90,  91,  92,  93,  94,  95,			/* 160 */
	 32,  33,  34,  35,  36,  37,  38,  39,			/* 168 */
	 40,  41,  42,  43,  44,  45,  46,  47,			/* 176 */
	 48,  49,  50,  51,  52,  53,  54,  55,			/* 184 */
	 56,  57,  58,  59,  60,  61,  62,  63,			/* 192 */

	 64,  65,  66,  67,  68,  69,  70,  71,			/* 200 */
	 72,  73,  74,  75,  76,  77,  78,  79,			/* 208 */
	 80,  81,  82,  83,  84,  85,  86,  87,			/* 216 */
	 88,  89,  90,  91,  92,  93,  94,  95,			/* 224 */
	 96,  97,  98,  99, 100, 101, 102, 103,			/* 232 */
	104, 105, 106, 107, 108, 109, 110, 111,			/* 240 */
	112, 113, 114, 115, 116, 117, 118, 119,			/* 248 */
	120, 121, 122, 123, 124, 125, 126,  63			/* 256 */
};
/* ... and here their attributes */ 
static const unsigned short xlata[256] = {
	UNDERLINE, UNDERLINE, UNDERLINE, UNDERLINE,		/*   4 */
	UNDERLINE, UNDERLINE, UNDERLINE, UNDERLINE,		/*   8 */
	UNDERLINE, UNDERLINE, UNDERLINE, UNDERLINE,		/*  12 */
	UNDERLINE, UNDERLINE, UNDERLINE, UNDERLINE,		/*  16 */
	UNDERLINE, UNDERLINE, UNDERLINE, UNDERLINE,		/*  20 */
	UNDERLINE, UNDERLINE, UNDERLINE, UNDERLINE,		/*  24 */
	UNDERLINE, UNDERLINE, UNDERLINE, UNDERLINE,		/*  28 */
	UNDERLINE, UNDERLINE, UNDERLINE, UNDERLINE,		/*  32 */
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,		/*  48 */
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,		/*  64 */
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,		/*  80 */
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,		/*  96 */
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,		/* 112 */
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, UNDERLINE,	/* 128 */

	INVERSE + UNDERLINE, INVERSE + UNDERLINE,		/* 130 */
	INVERSE + UNDERLINE, INVERSE + UNDERLINE,		/* 132 */
	INVERSE + UNDERLINE, INVERSE + UNDERLINE,		/* 134 */
	INVERSE + UNDERLINE, INVERSE + UNDERLINE,		/* 136 */
	INVERSE + UNDERLINE, INVERSE + UNDERLINE,		/* 138 */
	INVERSE + UNDERLINE, INVERSE + UNDERLINE,		/* 140 */
	INVERSE + UNDERLINE, INVERSE + UNDERLINE,		/* 142 */
	INVERSE + UNDERLINE, INVERSE + UNDERLINE,		/* 144 */
	INVERSE + UNDERLINE, INVERSE + UNDERLINE,		/* 146 */
	INVERSE + UNDERLINE, INVERSE + UNDERLINE,		/* 148 */
	INVERSE + UNDERLINE, INVERSE + UNDERLINE,		/* 150 */
	INVERSE + UNDERLINE, INVERSE + UNDERLINE,		/* 152 */
	INVERSE + UNDERLINE, INVERSE + UNDERLINE,		/* 154 */
	INVERSE + UNDERLINE, INVERSE + UNDERLINE,		/* 156 */
	INVERSE + UNDERLINE, INVERSE + UNDERLINE,		/* 158 */
	INVERSE + UNDERLINE, INVERSE + UNDERLINE,		/* 160 */

	INVERSE, INVERSE, INVERSE, INVERSE,			/* 164 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 168 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 172 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 176 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 180 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 184 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 188 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 192 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 196 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 200 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 204 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 208 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 212 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 216 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 220 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 224 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 228 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 232 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 236 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 240 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 244 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 248 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 252 */
	INVERSE, INVERSE, INVERSE, INVERSE + UNDERLINE		/* 256 */
};

/* Set attributes */

int set_attr(SCRN *t, int c)
{
	int e;

	c &= ~255;

	/* Attributes which have gone off */
	e = ((AT_MASK|FG_NOT_DEFAULT|BG_NOT_DEFAULT)&t->attrib & ~c);

	if (e) {	/* If any attribute go off, switch them all off: fixes bug on PCs */
		if (t->me)
			texec(t->cap, t->me, 1, 0, 0, 0, 0);
		else {
			if (t->ue)
				texec(t->cap, t->ue, 1, 0, 0, 0, 0);
			if (t->se)
				texec(t->cap, t->se, 1, 0, 0, 0, 0);
		}
		t->attrib = 0;
	}

	/* Attributes which have turned on */
	e = (c & ~t->attrib);

	if (e & INVERSE) {
		if (t->mr)
			texec(t->cap, t->mr, 1, 0, 0, 0, 0);
		else if (t->so)
			texec(t->cap, t->so, 1, 0, 0, 0, 0);
	}

	if (e & UNDERLINE)
		if (t->us)
			texec(t->cap, t->us, 1, 0, 0, 0, 0);
	if (e & BLINK)
		if (t->mb)
			texec(t->cap, t->mb, 1, 0, 0, 0, 0);
	if (e & BOLD)
		if (t->md)
			texec(t->cap, t->md, 1, 0, 0, 0, 0);
	if (e & DIM)
		if (t->mh)
			texec(t->cap, t->mh, 1, 0, 0, 0, 0);

	if ((t->attrib&FG_MASK)!=(c&FG_MASK))
		if (t->Sf) texec(t->cap,t->Sf,1,7-(((c&FG_VALUE)>>FG_SHIFT)),0,0,0);

	if ((t->attrib&BG_MASK)!=(c&BG_MASK))
		if (t->Sb) texec(t->cap,t->Sb,1,((c&BG_VALUE)>>BG_SHIFT),0,0,0);

	t->attrib = c;

	return 0;
}

/* Output character with attributes */

void outatr(struct charmap *map,SCRN *t,int *scrn,int *attrf,int xx,int yy,int c,int a)
{
	if(map->type)
		if(locale_map->type) {
			/* UTF-8 char to UTF-8 terminal */
			int wid;
			int uni_ctrl = 0;
			unsigned char buf[16];

			/* Deal with control characters */
			if (c<32) {
				c = c + '@';
				a ^= UNDERLINE;
			} else if (c==127) {
				c = '?';
				a ^= UNDERLINE;
			} else if (unictrl(c)) {
				a ^= UNDERLINE;
				uni_ctrl = 1;
			}

			if(*scrn==c && *attrf==a)
				return;

			wid = joe_wcwidth(1,c);

			*scrn = c;
			*attrf = a;
			if(t->ins)
				clrins(t);
			if(t->x != xx || t->y != yy)
				cpos(t, xx, yy);
			if(t->attrib != a)
				set_attr(t, a);
			if (uni_ctrl) {
				joe_snprintf_1((char *)buf,16,"<%X>",c);
				ttputs(buf);
			} else {
				utf8_encode(buf,c);
				ttputs(buf);
			}
			t->x+=wid;
			while (wid>1) {
				*++scrn= -1;
				*++attrf= 0;
				--wid;
			}
		} else {
			/* UTF-8 char to non-UTF-8 terminal */
			/* Don't convert control chars below 256 */
			if ((c>=32 && c<=126) || c>=160) {
				if (unictrl(c))
					a ^= UNDERLINE;
				c = from_uni(locale_map,c);
				if (c==-1)
					c = '?';
			}

			/* Deal with control characters */
			if (!joe_isprint(locale_map,c) && !(dspasis && c>=128)) {
				a ^= xlata[c];
				c = xlatc[c];
			}

			if(*scrn==c && *attrf==a)
				return;

			*scrn = c;
			*attrf = a;
			if(t->ins)
				clrins(t);
			if(t->x != xx || t->y != yy)
				cpos(t,xx,yy);
			if(t->attrib != a)
				set_attr(t,a);
			ttputc(c);
			t->x++;
		}
	else
		if (!locale_map->type) {
			/* Non UTF-8 char to non UTF-8 terminal */
			/* Byte-byte Translate? */

			/* Deal with control characters */
			if (!joe_isprint(locale_map,c) && !(dspasis && c>=128)) {
				a ^= xlata[c];
				c = xlatc[c];
			}

			if (*scrn==c && *attrf==a)
				return;

			*scrn = c;
			*attrf = a;

			if(t->ins)
				clrins(t);
			if(t->x != xx || t->y != yy)
				cpos(t,xx,yy);
			if(t->attrib != a)
				set_attr(t,a);
			ttputc(c);
			t->x++;
		} else {
			/* Non UTF-8 char to UTF-8 terminal */
			unsigned char buf[16];
			int wid;

			/* Deal with control characters */
			if (!(dspasis && c>=128) && !joe_isprint(map,c)) {
				a ^= xlata[c];
				c = xlatc[c];
			}

			c = to_uni(map,c);
			if (c < 32 || (c >= 0x7F && c < 0xA0)) {
				c = 0x1000FFFE;
				a = (a | UNDERLINE) ^ INVERSE;
			}
			utf8_encode(buf,c);

			if (*scrn == c && *attrf == a)
				return;

			wid = joe_wcwidth(0,c);
			*scrn = c;
			*attrf = a;
			if(t->ins)
				clrins(t);
			if(t->x != xx || t->y != yy)
				cpos(t, xx, yy);
			if(t->attrib != a)
				set_attr(t, a);
			ttputs(buf);
			t->x+=wid;
			while(wid>1) {
				*++scrn= -1;
				*++attrf= 0;
				--wid;
			}
		}
}

/* Set scrolling region */

static void setregn(SCRN *t, int top, int bot)
{
	if (!t->cs) {
		t->top = top;
		t->bot = bot;
		return;
	}
	if (t->top != top || t->bot != bot) {
		t->top = top;
		t->bot = bot;
		texec(t->cap, t->cs, 1, top, bot - 1, 0, 0);
		t->x = -1;
		t->y = -1;
	}
}

/* Enter insert mode */

static void setins(SCRN *t, int x)
{
	if (t->ins != 1 && t->im) {
		t->ins = 1;
		texec(t->cap, t->im, 1, x, 0, 0, 0);
	}
}

/* Exit insert mode */

int clrins(SCRN *t)
{
	if (t->ins != 0) {
		texec(t->cap, t->ei, 1, 0, 0, 0, 0);
		t->ins = 0;
	}
	return 0;
}

/* Erase from given screen coordinate to end of line */

int eraeol(SCRN *t, int x, int y)
{
	int *s, *ss, *a, *aa;
	int w = t->co - x - 1;	/* Don't worry about last column */

	if (w <= 0)
		return 0;
	s = t->scrn + y * t->co + x;
	a = t->attr + y * t->co + x;
	ss = s + w;
	aa = a + w;
	do {
		if (*--ss != ' ') {
			++ss;
			break;
		} else if (*--aa != 0) {
			++ss;
			++aa;
			break;
		}
	} while (ss != s);
	if ((ss - s > 3 || s[w] != ' ' || a[w] != 0) && t->ce) {
		cpos(t, x, y);
		set_attr(t, 0);
		texec(t->cap, t->ce, 1, 0, 0, 0, 0);
		msetI(s, ' ', w);
		msetI(a, 0, w);
	} else if (s != ss) {
		if (t->ins)
			clrins(t);
		if (t->x != x || t->y != y)
			cpos(t, x, y);
		if (t->attrib)
			set_attr(t, 0);
		while (s != ss) {
			*s = ' ';
			*a = 0;
			ttputc(' ');
			++t->x;
			++s;
			++a;
		}
	}
	return 0;
}

/* As above but useable in insert mode */
/* The cursor position must already be correct */

static void outatri(SCRN *t, int x, int y, int c, int a)
{
/*
	if (c == -1)
		c = ' ';
	if (a != t->attrib)
		set_attr(t, a);
	if (t->haz && c == '~')
		c = '\\';
	utf8_putc(c);
	t->x+=joe_wcwidth(1,c);
*/
	/* ++t->x; */
}

static void out(unsigned char *t, unsigned char c)
{
	ttputc(c);
}

SCRN *nopen(CAP *cap)
{
	SCRN *t = (SCRN *) joe_malloc(sizeof(SCRN));
	int x, y;

	ttopen();

	t->cap = cap;
	setcap(cap, baud, out, NULL);

	t->li = getnum(t->cap,US "li");
	if (t->li < 1)
		t->li = 24;
	t->co = getnum(t->cap,US "co");
	if (t->co < 2)
		t->co = 80;
	x = y = 0;
	ttgtsz(&x, &y);
	if (x > 7 && y > 3) {
		t->li = y;
		t->co = x;
	}

	t->haz = getflag(t->cap,US "hz");
	t->os = getflag(t->cap,US "os");
	t->eo = getflag(t->cap,US "eo");
	if (getflag(t->cap,US "hc"))
		t->os = 1;
	if (t->os || getflag(t->cap,US "ul"))
		t->ul = 1;
	else
		t->ul = 0;

	t->xn = getflag(t->cap,US "xn");
	t->am = getflag(t->cap,US "am");

	t->cl = jgetstr(t->cap,US "cl");
	t->cd = jgetstr(t->cap,US "cd");

	if (notite) {
		t->ti = NULL;
		t->te = NULL;
	} else {
		t->ti = jgetstr(t->cap,US "ti");
		t->te = jgetstr(t->cap,US "te");
	}
	if (pastetite && t->cap->paste_on && t->cap->paste_off) {
		if (notite) {
			t->ti = (void *)strdup(t->cap->paste_on);
			t->te = (void *)strdup(t->cap->paste_off);
		} else {
			size_t n1, n2;
			char *cp;

			n1 = t->ti ? strlen(t->ti) : 0;
			n2 = strlen(t->cap->paste_on);
			cp = joe_malloc(n1 + n2 + 1);
			if (t->ti)
				memcpy(cp, t->ti, n1);
			memcpy(cp + n1, t->cap->paste_on, n2 + 1);
			t->ti = cp;

			n1 = t->te ? strlen(t->te) : 0;
			n2 = strlen(t->cap->paste_off);
			cp = joe_malloc(n1 + n2 + 1);
			memcpy(cp, t->cap->paste_off, n2 + 1);
			if (t->te)
				memcpy(cp + n2, t->te, n1 + 1);
			t->te = cp;
		}
	}

	t->ut = getflag(t->cap,US "ut");
	t->Sb = jgetstr(t->cap,US "AB");
	if (!t->Sb) t->Sb = jgetstr(t->cap,US "Sb");
	t->Sf = jgetstr(t->cap,US "AF");
	if (!t->Sf) t->Sf = jgetstr(t->cap,US "Sf");

	t->mb = NULL;
	t->md = NULL;
	t->mh = NULL;
	t->mr = NULL;
	t->avattr = 0;
	if (!(t->me = jgetstr(t->cap,US "me")))
		goto oops;
	if ((t->mb = jgetstr(t->cap,US "mb")))
		t->avattr |= BLINK;
	if ((t->md = jgetstr(t->cap,US "md")))
		t->avattr |= BOLD;
	if ((t->mh = jgetstr(t->cap,US "mh")))
		t->avattr |= DIM;
	if ((t->mr = jgetstr(t->cap,US "mr")))
		t->avattr |= INVERSE;
      oops:


	if (assume_color) {
		/* Install color support if it looks like an ansi terminal (it has bold which begins with ESC [) */
#ifndef TERMINFO
		if (!t->Sf && t->md && t->md[0]=='\\' && t->md[1]=='E' && t->md[2]=='[') { 
			t->ut = 1;
			t->Sf =US "\\E[3%dm";
			t->Sb =US "\\E[4%dm";
		}
#else
		if (!t->Sf && t->md && t->md[0]=='\033' && t->md[1]=='[') { 
			t->ut = 1;
			t->Sf =US "\033[3%p1%dm";
			t->Sb =US "\033[4%p1%dm";
		}
#endif
	}

	t->so = NULL;
	t->se = NULL;
	if (getnum(t->cap,US "sg") <= 0 && !t->mr && jgetstr(t->cap,US "se")) {
		if ((t->so = jgetstr(t->cap,US "so")) != NULL)
			t->avattr |= INVERSE;
		t->se = jgetstr(t->cap,US "se");
	}
	if (getflag(t->cap,US "xs") || getflag(t->cap,US "xt"))
		t->so = NULL;

	t->us = NULL;
	t->ue = NULL;
	if (getnum(t->cap,US "ug") <= 0 && jgetstr(t->cap,US "ue")) {
		if ((t->us = jgetstr(t->cap,US "us")) != NULL)
			t->avattr |= UNDERLINE;
		t->ue = jgetstr(t->cap,US "ue");
	}

	if (!(t->uc = jgetstr(t->cap,US "uc")))
		if (t->ul)
			t->uc =US "_";
	if (t->uc)
		t->avattr |= UNDERLINE;

	t->ms = getflag(t->cap,US "ms");

	t->da = getflag(t->cap,US "da");
	t->db = getflag(t->cap,US "db");
	t->cs = jgetstr(t->cap,US "cs");
	t->rr = getflag(t->cap,US "rr");
	t->sf = jgetstr(t->cap,US "sf");
	t->sr = jgetstr(t->cap,US "sr");
	t->SF = jgetstr(t->cap,US "SF");
	t->SR = jgetstr(t->cap,US "SR");
	t->al = jgetstr(t->cap,US "al");
	t->dl = jgetstr(t->cap,US "dl");
	t->AL = jgetstr(t->cap,US "AL");
	t->DL = jgetstr(t->cap,US "DL");
	if (!getflag(t->cap,US "ns") && !t->sf)
		t->sf =US "\12";

	if (!getflag(t->cap,US "in") && baud < 38400) {
		t->dc = jgetstr(t->cap,US "dc");
		t->DC = jgetstr(t->cap,US "DC");
		t->dm = jgetstr(t->cap,US "dm");
		t->ed = jgetstr(t->cap,US "ed");

		t->im = jgetstr(t->cap,US "im");
		t->ei = jgetstr(t->cap,US "ei");
		t->ic = jgetstr(t->cap,US "ic");
		t->IC = jgetstr(t->cap,US "IC");
		t->ip = jgetstr(t->cap,US "ip");
		t->mi = getflag(t->cap,US "mi");
	} else {
		t->dm = NULL;
		t->dc = NULL;
		t->DC = NULL;
		t->ed = NULL;
		t->im = NULL;
		t->ic = NULL;
		t->IC = NULL;
		t->ip = NULL;
		t->ei = NULL;
		t->mi = 1;
	}

	t->bs = NULL;
	if (jgetstr(t->cap,US "bc"))
		t->bs = jgetstr(t->cap,US "bc");
	else if (jgetstr(t->cap,US "le"))
		t->bs = jgetstr(t->cap,US "le");
	if (getflag(t->cap,US "bs"))
		t->bs =US "\10";

	t->cbs = tcost(t->cap, t->bs, 1, 2, 2, 0, 0);

	t->lf =US "\12";
	if (jgetstr(t->cap,US "do"))
		t->lf = jgetstr(t->cap,US "do");
	t->clf = tcost(t->cap, t->lf, 1, 2, 2, 0, 0);

	t->up = jgetstr(t->cap,US "up");
	t->cup = tcost(t->cap, t->up, 1, 2, 2, 0, 0);

	t->nd = jgetstr(t->cap,US "nd");

	t->tw = 8;
	if (getnum(t->cap,US "it") > 0)
		t->tw = getnum(t->cap,US "it");
	else if (getnum(t->cap,US "tw") > 0)
		t->tw = getnum(t->cap,US "tw");

	if (!(t->ta = jgetstr(t->cap,US "ta")))
		if (getflag(t->cap,US "pt"))
			t->ta =US "\11";
	t->bt = jgetstr(t->cap,US "bt");
	if (getflag(t->cap,US "xt")) {
		t->ta = NULL;
		t->bt = NULL;
	}

	if (!usetabs) {
		t->ta = NULL;
		t->bt = NULL;
	}

	t->cta = tcost(t->cap, t->ta, 1, 2, 2, 0, 0);
	t->cbt = tcost(t->cap, t->bt, 1, 2, 2, 0, 0);

	t->ho = jgetstr(t->cap,US "ho");
	t->cho = tcost(t->cap, t->ho, 1, 2, 2, 0, 0);
	t->ll = jgetstr(t->cap,US "ll");
	t->cll = tcost(t->cap, t->ll, 1, 2, 2, 0, 0);

	t->cr =US "\15";
	if (jgetstr(t->cap,US "cr"))
		t->cr = jgetstr(t->cap,US "cr");
	if (getflag(t->cap,US "nc") || getflag(t->cap,US "xr"))
		t->cr = NULL;
	t->ccr = tcost(t->cap, t->cr, 1, 2, 2, 0, 0);

	t->cRI = tcost(t->cap, t->RI = jgetstr(t->cap,US "RI"), 1, 2, 2, 0, 0);
	t->cLE = tcost(t->cap, t->LE = jgetstr(t->cap,US "LE"), 1, 2, 2, 0, 0);
	t->cUP = tcost(t->cap, t->UP = jgetstr(t->cap,US "UP"), 1, 2, 2, 0, 0);
	t->cDO = tcost(t->cap, t->DO = jgetstr(t->cap,US "DO"), 1, 2, 2, 0, 0);
	t->cch = tcost(t->cap, t->ch = jgetstr(t->cap,US "ch"), 1, 2, 2, 0, 0);
	t->ccv = tcost(t->cap, t->cv = jgetstr(t->cap,US "cv"), 1, 2, 2, 0, 0);
	t->ccV = tcost(t->cap, t->cV = jgetstr(t->cap,US "cV"), 1, 2, 2, 0, 0);
	t->ccm = tcost(t->cap, t->cm = jgetstr(t->cap,US "cm"), 1, 2, 2, 0, 0);

	t->cce = tcost(t->cap, t->ce = jgetstr(t->cap,US "ce"), 1, 2, 2, 0, 0);

/* Make sure terminal can do absolute positioning */
	if (t->cm)
		goto ok;
	if (t->ch && t->cv)
		goto ok;
	if (t->ho && (t->lf || t->DO || t->cv))
		goto ok;
	if (t->ll && (t->up || t->UP || t->cv))
		goto ok;
	if (t->cr && t->cv)
		goto ok;
	leave = 1;
	ttclose();
	signrm();
#ifdef	DEBUG
	/* these are strings, but I do not know if %s is appropriate -mirabilos */
        fprintf(stderr,"cm=%d ch=%d cv=%d ho=%d lf=%d DO=%d ll=%d up=%d UP=%d cr=%d\n",
                       t->cm, t->ch, t->cv, t->ho, t->lf, t->DO, t->ll, t->up, t->UP, t->cr);
#endif
	fprintf(stderr,"Sorry, your terminal can't do absolute cursor positioning.\nIt's broken\n");
	return NULL;
      ok:

/* Determine if we can scroll */
	if (((t->sr || t->SR) && (t->sf || t->SF) && t->cs) || ((t->al || t->AL) && (t->dl || t->DL)))
		t->scroll = 1;
	else {
		t->scroll = 0;
		if (baud < 38400)
			mid = 1;
	}

/* Determine if we can ins/del within lines */
	if ((t->im || t->ic || t->IC) && (t->dc || t->DC))
		t->insdel = 1;
	else
		t->insdel = 0;

/* Adjust for high baud rates */
	if (baud >= 38400) {
		t->scroll = 0;
		t->insdel = 0;
	}

/* Send out terminal initialization string */
	if (t->ti)
		texec(t->cap, t->ti, 1, 0, 0, 0, 0);
	if (!skiptop && t->cl)
		texec(t->cap, t->cl, 1, 0, 0, 0, 0);

/* Initialize variable screen size dependant vars */
	t->scrn = NULL;
	t->attr = NULL;
	t->sary = NULL;
	t->updtab = NULL;
	t->syntab = NULL;
	t->compose = NULL;
	t->ofst = NULL;
	t->ary = NULL;
	t->htab = (struct hentry *) joe_malloc(256 * sizeof(struct hentry));

	nresize(t, t->co, t->li);

	return t;
}

/* Change size of screen */

void nresize(SCRN *t, int w, int h)
{
	if (h < 4)
		h = 4;
	if (w < 8)
		w = 8;
	t->li = h;
	t->co = w;
	if (t->sary)
		joe_free(t->sary);
	if (t->updtab)
		joe_free(t->updtab);
	if (t->syntab)
		joe_free(t->syntab);
	if (t->scrn)
		joe_free(t->scrn);
	if (t->attr)
		joe_free(t->attr);
	if (t->compose)
		joe_free(t->compose);
	if (t->ofst)
		joe_free(t->ofst);
	if (t->ary)
		joe_free(t->ary);
	t->scrn = (int *) joe_malloc(t->li * t->co * sizeof(int));
	t->attr = (int *) joe_malloc(t->li * t->co * sizeof(int));
	t->sary = (int *) joe_calloc(t->li, sizeof(int));
	t->updtab = (int *) joe_malloc(t->li * sizeof(int));
	t->syntab = (int *) joe_malloc(t->li * sizeof(int));
	t->compose = (int *) joe_malloc(t->co * sizeof(int));
	t->ofst = (int *) joe_malloc(t->co * sizeof(int));
	t->ary = (struct hentry *) joe_malloc(t->co * sizeof(struct hentry));

	nredraw(t);
}

/* Calculate cost of positioning the cursor using only relative cursor
 * positioning functions: t->(lf, DO, up, UP, bs, LE, RI, ta, bt) and rewriting
 * characters (to move right)
 *
 * This doesn't use the am and bw capabilities although it probably could.
 */

static int relcost(register SCRN *t, register int x, register int y, register int ox, register int oy)
{
	int cost = 0;

/* If we don't know the cursor position, force use of absolute positioning */
	if (oy == -1 || ox == -1)
		return 10000;

/* First adjust row */
	if (y > oy) {
		int dist = y - oy;

		/* Have to go down */
		if (t->lf) {
			int mult = dist * t->clf;

			if (dist < 10 && t->cDO < mult)
				cost += t->cDO;
			else if (dist >= 10 && t->cDO + 1 < mult)
				cost += t->cDO + 1;
			else
				cost += mult;
		} else if (t->DO)
			if (dist < 10)
				cost += t->cDO;
			else
				cost += t->cDO + 1;
		else
			return 10000;
	} else if (y < oy) {
		int dist = oy - y;

		/* Have to go up */
		if (t->up) {
			int mult = dist * t->cup;

			if (dist < 10 && t->cUP < mult)
				cost += t->cUP;
			else if (dist >= 10 && t->cUP < mult)
				cost += t->cUP + 1;
			else
				cost += mult;
		} else if (t->UP)
			if (dist < 10)
				cost += t->cUP;
			else
				cost += t->cUP + 1;
		else
			return 10000;
	}

/* Now adjust column */

/* Use tabs */
	if (x > ox && t->ta) {
		int dist = x - ox;
		int ntabs = (dist + ox % t->tw) / t->tw;
		int cstunder = x % t->tw + t->cta * ntabs;
		int cstover;

		if (x + t->tw < t->co && t->bs)
			cstover = t->cbs * (t->tw - x % t->tw) + t->cta * (ntabs + 1);
		else
			cstover = 10000;
		if (dist < 10 && cstunder < t->cRI && cstunder < x - ox && cstover > cstunder)
			return cost + cstunder;
		else if (cstunder < t->cRI + 1 && cstunder < x - ox && cstover > cstunder)
			return cost + cstunder;
		else if (dist < 10 && cstover < t->cRI && cstover < x - ox)
			return cost + cstover;
		else if (cstover < t->cRI + 1 && cstover < x - ox)
			return cost + cstover;
	} else if (x < ox && t->bt) {
		int dist = ox - x;
		int ntabs = (dist + t->tw - ox % t->tw) / t->tw;
		int cstunder, cstover;

		if (t->bs)
			cstunder = t->cbt * ntabs + t->cbs * (t->tw - x % t->tw);
		else
			cstunder = 10000;
		if (x - t->tw >= 0)
			cstover = t->cbt * (ntabs + 1) + x % t->tw;
		else
			cstover = 10000;
		if (dist < 10 && cstunder < t->cLE && (t->bs ? cstunder < (ox - x) * t->cbs : 1)
		    && cstover > cstunder)
			return cost + cstunder;
		if (cstunder < t->cLE + 1 && (t->bs ? cstunder < (ox - x) * t->cbs : 1)
		    && cstover > cstunder)
			return cost + cstunder;
		else if (dist < 10 && cstover < t->cRI && (t->bs ? cstover < (ox - x) * t->cbs : 1))
			return cost + cstover;
		else if (cstover < t->cRI + 1 && (t->bs ? cstover < (ox - x) * t->cbs : 1))
			return cost + cstover;
	}

/* Use simple motions */
	if (x < ox) {
		int dist = ox - x;

		/* Have to go left */
		if (t->bs) {
			int mult = dist * t->cbs;

			if (t->cLE < mult && dist < 10)
				cost += t->cLE;
			else if (t->cLE + 1 < mult)
				cost += t->cLE + 1;
			else
				cost += mult;
		} else if (t->LE)
			cost += t->cLE;
		else
			return 10000;
	} else if (x > ox) {
		int dist = x - ox;

		/* Have to go right */
		/* Hmm.. this should take into account possible attribute changes */
		if (t->cRI < dist && dist < 10)
			cost += t->cRI;
		else if (t->cRI + 1 < dist)
			cost += t->cRI + 1;
		else
			cost += dist;
	}

	return cost;
}

/* Find optimal set of cursor positioning commands to move from the current
 * cursor row and column (either or both of which might be unknown) to the
 * given new row and column and execute them.
 */

static void cposs(register SCRN *t, register int x, register int y)
{
	register int bestcost, cost;
	int bestway;
	int hy;
	int hl;

/* Home y position is usually 0, but it is 'top' if we have scrolling region
 * relative addressing
 */
	if (t->rr) {
		hy = t->top;
		hl = t->bot - 1;
	} else {
		hy = 0;
		hl = t->li - 1;
	}

/* Assume best way is with only using relative cursor positioning */

	bestcost = relcost(t, x, y, t->x, t->y);
	bestway = 0;

/* Now check if combinations of absolute cursor positioning functions are
 * better (or necessary in case one or both cursor positions are unknown)
 */

	if (t->ccm < bestcost) {
		cost = tcost(t->cap, t->cm, 1, y, x, 0, 0);
		if (cost < bestcost) {
			bestcost = cost;
			bestway = 6;
		}
	}
	if (t->ccr < bestcost) {
		cost = relcost(t, x, y, 0, t->y) + t->ccr;
		if (cost < bestcost) {
			bestcost = cost;
			bestway = 1;
		}
	}
	if (t->cho < bestcost) {
		cost = relcost(t, x, y, 0, hy) + t->cho;
		if (cost < bestcost) {
			bestcost = cost;
			bestway = 2;
		}
	}
	if (t->cll < bestcost) {
		cost = relcost(t, x, y, 0, hl) + t->cll;
		if (cost < bestcost) {
			bestcost = cost;
			bestway = 3;
		}
	}
	if (t->cch < bestcost && x != t->x) {
		cost = relcost(t, x, y, x, t->y) + tcost(t->cap, t->ch, 1, x, 0, 0, 0);
		if (cost < bestcost) {
			bestcost = cost;
			bestway = 4;
		}
	}
	if (t->ccv < bestcost && y != t->y) {
		cost = relcost(t, x, y, t->x, y) + tcost(t->cap, t->cv, 1, y, 0, 0, 0);
		if (cost < bestcost) {
			bestcost = cost;
			bestway = 5;
		}
	}
	if (t->ccV < bestcost) {
		cost = relcost(t, x, y, 0, y) + tcost(t->cap, t->cV, 1, y, 0, 0, 0);
		if (cost < bestcost) {
			bestcost = cost;
			bestway = 13;
		}
	}
	if (t->cch + t->ccv < bestcost && x != t->x && y != t->y) {
		cost = tcost(t->cap, t->cv, 1, y - hy, 0, 0, 0) + tcost(t->cap, t->ch, 1, x, 0, 0, 0);
		if (cost < bestcost) {
			bestcost = cost;
			bestway = 7;
		}
	}
	if (t->ccv + t->ccr < bestcost && y != t->y) {
		cost = tcost(t->cap, t->cv, 1, y, 0, 0, 0) + tcost(t->cap, t->cr, 1, 0, 0, 0, 0) + relcost(t, x, y, 0, y);
		if (cost < bestcost) {
			bestcost = cost;
			bestway = 8;
		}
	}
	if (t->cll + t->cch < bestcost) {
		cost = tcost(t->cap, t->ll, 1, 0, 0, 0, 0) + tcost(t->cap, t->ch, 1, x, 0, 0, 0) + relcost(t, x, y, x, hl);
		if (cost < bestcost) {
			bestcost = cost;
			bestway = 9;
		}
	}
	if (t->cll + t->ccv < bestcost) {
		cost = tcost(t->cap, t->ll, 1, 0, 0, 0, 0) + tcost(t->cap, t->cv, 1, y, 0, 0, 0) + relcost(t, x, y, 0, y);
		if (cost < bestcost) {
			bestcost = cost;
			bestway = 10;
		}
	}
	if (t->cho + t->cch < bestcost) {
		cost = tcost(t->cap, t->ho, 1, 0, 0, 0, 0) + tcost(t->cap, t->ch, 1, x, 0, 0, 0) + relcost(t, x, y, x, hy);
		if (cost < bestcost) {
			bestcost = cost;
			bestway = 11;
		}
	}
	if (t->cho + t->ccv < bestcost) {
		cost = tcost(t->cap, t->ho, 1, 0, 0, 0, 0) + tcost(t->cap, t->cv, 1, y, 0, 0, 0) + relcost(t, x, y, 0, y);
		if (cost < bestcost) {
			/* dead store: bestcost = cost; */
			bestway = 12;
		}
	}

/* Do absolute cursor positioning if we don't know the cursor position or
 * if it is faster than doing only relative cursor positioning
 */

	switch (bestway) {
	case 1:
		texec(t->cap, t->cr, 1, 0, 0, 0, 0);
		t->x = 0;
		break;
	case 2:
		texec(t->cap, t->ho, 1, 0, 0, 0, 0);
		t->x = 0;
		t->y = hy;
		break;
	case 3:
		texec(t->cap, t->ll, 1, 0, 0, 0, 0);
		t->x = 0;
		t->y = hl;
		break;
	case 9:
		texec(t->cap, t->ll, 1, 0, 0, 0, 0);
		t->x = 0;
		t->y = hl;
		goto doch;
	case 11:
		texec(t->cap, t->ho, 1, 0, 0, 0, 0);
		t->x = 0;
		t->y = hy;
doch:
	case 4:
		texec(t->cap, t->ch, 1, x, 0, 0, 0);
		t->x = x;
		break;
	case 10:
		texec(t->cap, t->ll, 1, 0, 0, 0, 0);
		t->x = 0;
		t->y = hl;
		goto docv;
	case 12:
		texec(t->cap, t->ho, 1, 0, 0, 0, 0);
		t->x = 0;
		t->y = hy;
		goto docv;
	case 8:
		texec(t->cap, t->cr, 1, 0, 0, 0, 0);
		t->x = 0;
docv:
	case 5:
		texec(t->cap, t->cv, 1, y, 0, 0, 0);
		t->y = y;
		break;
	case 6:
		texec(t->cap, t->cm, 1, y, x, 0, 0);
		t->y = y;
		t->x = x;
		break;
	case 7:
		texec(t->cap, t->cv, 1, y, 0, 0, 0);
		t->y = y;
		texec(t->cap, t->ch, 1, x, 0, 0, 0);
		t->x = x;
		break;
	case 13:
		texec(t->cap, t->cV, 1, y, 0, 0, 0);
		t->y = y;
		t->x = 0;
		break;
	}

/* Use relative cursor position functions if we're not there yet */

/* First adjust row */
	if (y > t->y) {
		/* Have to go down */
		if (!t->lf || t->cDO < (y - t->y) * t->clf) {
			texec(t->cap, t->DO, 1, y - t->y, 0, 0, 0);
			t->y = y;
		} else
			while (y > t->y) {
				texec(t->cap, t->lf, 1, 0, 0, 0, 0);
				++t->y;
			}
	} else if (y < t->y) {
		/* Have to go up */
		if (!t->up || t->cUP < (t->y - y) * t->cup) {
			texec(t->cap, t->UP, 1, t->y - y, 0, 0, 0);
			t->y = y;
		} else
			while (y < t->y) {
				texec(t->cap, t->up, 1, 0, 0, 0, 0);
				--t->y;
			}
	}

/* Use tabs */
	if (x > t->x && t->ta) {
		int ntabs = (x - t->x + t->x % t->tw) / t->tw;
		int cstunder = x % t->tw + t->cta * ntabs;
		int cstover;

		if (x + t->tw < t->co && t->bs)
			cstover = t->cbs * (t->tw - x % t->tw) + t->cta * (ntabs + 1);
		else
			cstover = 10000;
		if (cstunder < t->cRI && cstunder < x - t->x && cstover > cstunder) {
			if (ntabs) {
				t->x = x - x % t->tw;
				do {
					texec(t->cap, t->ta, 1, 0, 0, 0, 0);
				} while (--ntabs);
			}
		} else if (cstover < t->cRI && cstover < x - t->x) {
			t->x = t->tw + x - x % t->tw;
			++ntabs;
			do {
				texec(t->cap, t->ta, 1, 0, 0, 0, 0);
			} while (--ntabs);
		}
	} else if (x < t->x && t->bt) {
		int ntabs = ((t->x + t->tw - 1) - (t->x + t->tw - 1) % t->tw - ((x + t->tw - 1) - (x + t->tw - 1) % t->tw)) / t->tw;
		int cstunder, cstover;

		if (t->bs)
			cstunder = t->cbt * ntabs + t->cbs * (t->tw - x % t->tw);
		else
			cstunder = 10000;
		if (x - t->tw >= 0)
			cstover = t->cbt * (ntabs + 1) + x % t->tw;
		else
			cstover = 10000;
		if (cstunder < t->cLE && (t->bs ? cstunder < (t->x - x) * t->cbs : 1)
		    && cstover > cstunder) {
			if (ntabs) {
				do {
					texec(t->cap, t->bt, 1, 0, 0, 0, 0);
				} while (--ntabs);
				t->x = x + t->tw - x % t->tw;
			}
		} else if (cstover < t->cRI && (t->bs ? cstover < (t->x - x) * t->cbs : 1)) {
			t->x = x - x % t->tw;
			++ntabs;
			do {
				texec(t->cap, t->bt, 1, 0, 0, 0, 0);
			} while (--ntabs);
		}
	}

/* Now adjust column */
	if (x < t->x) {
		/* Have to go left */
		if (!t->bs || t->cLE < (t->x - x) * t->cbs) {
			texec(t->cap, t->LE, 1, t->x - x, 0, 0, 0);
			t->x = x;
		} else
			while (x < t->x) {
				texec(t->cap, t->bs, 1, 0, 0, 0, 0);
				--t->x;
			}
	} else if (x > t->x) {
		/* Have to go right */
		/* Hmm.. this should take into account possible attribute changes */
		if (x-t->x>1 && t->RI) {
			texec(t->cap, t->RI, 1, x - t->x, 0, 0, 0);
			t->x = x;
		} else {
			while(x>t->x) {
				texec(t->cap, t->nd, 1, 0, 0, 0, 0);
				++t->x;
			}
		}

		/* if (t->cRI < x - t->x) { */
/*		} else {
			int *s = t->scrn + t->x + t->y * t->co;
			int *a = t->attr + t->x + t->y * t->co;

			if (t->ins)
				clrins(t);
			while (x > t->x) {
				int atr, c;
				if(*s==-1) c=' ', atr=0;
				else c= *s, atr= *a;

				if (atr != t->attrib)
					set_attr(t, atr);
				utf8_putc(c);
				++s;
				++a;
				++t->x;
			}
		}
*/
	}
}

int cpos(register SCRN *t, register int x, register int y)
{
	/* Move cursor quickly if we can */
	if (y == t->y) {
		if (x > t->x && x - t->x < 4 && !t->ins) {
			int *cs = t->scrn + t->x + t->co * t->y;
			int *as = t->attr + t->x + t->co * t->y;
			do {
				/* We used to space over unknown chars, but they now could be
				   the right half of a UTF-8 two column character, so we can't.
				   Also do not try to emit utf-8 sequences here. */
				if(*cs<32 || *cs>=127)
					break;

				if (*as != t->attrib)
					set_attr(t, *as);

				ttputc(*cs);

				++cs;
				++as;
				++t->x;

			} while (x != t->x);
		}
		if (x == t->x)
			return 0;
	}
	if ((!t->ms && t->attrib & (INVERSE | UNDERLINE | BG_NOT_DEFAULT)) ||
	    (t->ut && (t->attrib & BG_NOT_DEFAULT)))
		set_attr(t, t->attrib & ~(INVERSE | UNDERLINE | BG_MASK));

	/* Should be in cposs */
	if (y < t->top || y >= t->bot)
		setregn(t, 0, t->li);

	cposs(t, x, y);
	return 0;
}

static void doinschr(SCRN *t, int x, int y, int *s, int *as, int n)
{
	int a;

	if (x < 0) {
		s -= x;
		as -= x;
		x = 0;
	}
	if (x >= t->co - 1 || n <= 0)
		return;
	if (t->im || t->ic || t->IC) {
		cpos(t, x, y);
		if ((n == 1 && t->ic) || !t->IC) {
			if (!t->ic)
				setins(t, x);
			for (a = 0; a != n; ++a) {
				texec(t->cap, t->ic, 1, x, 0, 0, 0);
				outatri(t, x + a, y, s[a], as[a]);
				texec(t->cap, t->ip, 1, x, 0, 0, 0);
			}
			if (!t->mi)
				clrins(t);
		} else {
			texec(t->cap, t->IC, 1, n, 0, 0, 0);
			for (a = 0; a != n; ++a)
				outatri(t, x + a, y, s[a], as[a]);
		}
	}
	mmove(t->scrn + x + t->co * y + n, t->scrn + x + t->co * y, (t->co - (x + n)) * sizeof(int));
	mmove(t->attr + x + t->co * y + n, t->attr + x + t->co * y, (t->co - (x + n)) * sizeof(int));
	mmove(t->scrn + x + t->co * y, s, n * sizeof(int));
	mmove(t->attr + x + t->co * y, s, n * sizeof(int));
}

static void dodelchr(SCRN *t, int x, int y, int n)
{
	int a;

	if (x < 0)
		x = 0;
	if (!n || x >= t->co - 1)
		return;
	if (t->dc || t->DC) {
		cpos(t, x, y);
		texec(t->cap, t->dm, 1, x, 0, 0, 0);	/* Enter delete mode */
		if ((n == 1 && t->dc) || !t->DC)
			for (a = n; a; --a)
				texec(t->cap, t->dc, 1, x, 0, 0, 0);
		else
			texec(t->cap, t->DC, 1, n, 0, 0, 0);
		texec(t->cap, t->ed, 1, x, 0, 0, 0);	/* Exit delete mode */
	}
	mmove(t->scrn + t->co * y + x, t->scrn + t->co * y + x + n, (t->co - (x + n)) * sizeof(int));
	mmove(t->attr + t->co * y + x, t->attr + t->co * y + x + n, (t->co - (x + n)) * sizeof(int));
	msetI(t->scrn + t->co * y + t->co - n, ' ', n);
	msetI(t->attr + t->co * y + t->co - n, 0, n);
}

/* Insert/Delete within line */
/* FIXME: doesn't know about attr */

void magic(SCRN *t, int y, int *cs, int *ca,int *s, int *a, int placex)
{
	struct hentry *htab = t->htab;
	int *ofst = t->ofst;
	int aryx = 1;
	int x;

	if (!(t->im || t->ic || t->IC) || !(t->dc || t->DC))
		return;
	mset(htab, 0, 256 * sizeof(struct hentry));

	msetI(ofst, 0, t->co);

/* Build hash table */
	for (x = 0; x != t->co - 1; ++x) {
		t->ary[aryx].next = htab[cs[x] & 255].next;
		t->ary[aryx].loc = x;
		++htab[cs[x] & 255].loc;
		htab[cs[x] & 255].next = aryx++;
	}

/* Build offset table */
	for (x = 0; x < t->co - 1;)
		if (htab[s[x] & 255].loc >= 15)
			ofst[x++] = t->co - 1;
		else {
			int aryy;
			int maxaryy = 0;
			int maxlen = 0;
			int best = 0;
			int bestback = 0;
			int z;

			for (aryy = htab[s[x] & 255].next; aryy; aryy = t->ary[aryy].next) {
				int amnt, back;
				int tsfo = t->ary[aryy].loc - x;
				int cst = -abs(tsfo);
				int pre = 32;

				for (amnt = 0; x + amnt < t->co - 1 && x + tsfo + amnt < t->co - 1; ++amnt) {
					if (cs[x + tsfo + amnt] != s[x + amnt])
						break;
					else if ((s[x + amnt] & 255) != 32 || pre != 32)
						++cst;
					pre = s[x + amnt] & 255;
				}
				pre = 32;
				for (back = 0; back + x > 0 && back + tsfo + x > 0; --back) {
					if (cs[x + tsfo + back - 1] != s[x + back - 1])
						break;
					else if ((s[x + back - 1] & 255) != 32 || pre != 32)
						++cst;
					pre = s[x + back - 1] & 255;
				}
				if (cst > best) {
					maxaryy = aryy;
					maxlen = amnt;
					best = cst;
					bestback = back;
				}
			}
			if (!maxlen) {
				ofst[x] = t->co - 1;
				maxlen = 1;
			} else if (best < 2)
				for (z = 0; z != maxlen; ++z)
					ofst[x + z] = t->co - 1;
			else
				for (z = 0; z != maxlen - bestback; ++z)
					ofst[x + z + bestback] = t->ary[maxaryy].loc - x;
			x += maxlen;
		}

/* Apply scrolling commands */

	for (x = 0; x != t->co - 1; ++x) {
		int q = ofst[x];

		if (q && q != t->co - 1) {
			if (q > 0) {
				int z, fu;

				for (z = x; z != t->co - 1 && ofst[z] == q; ++z) ;
				while (s[x] == cs[x] && x < placex)
					++x;
				dodelchr(t, x, y, q);
				for (fu = x; fu != t->co - 1; ++fu)
					if (ofst[fu] != t->co - 1)
						ofst[fu] -= q;
				x = z - 1;
			} else {
				int z, fu;

				for (z = x; z != t->co - 1 && ofst[z] == q; ++z) ;
				while (s[x + q] == cs[x + q] && x - q < placex)
					++x;
				doinschr(t, x + q, y, s + x + q, a + x + q, -q);
				for (fu = x; fu != t->co - 1; ++fu)
					if (ofst[fu] != t->co - 1)
						ofst[fu] -= q;
				x = z - 1;
			}
		}
	}
}

static void doupscrl(SCRN *t, int top, int bot, int amnt)
{
	int a = amnt;

	if (!amnt)
		return;
	set_attr(t, 0);
	if (top == 0 && bot == t->li && (t->sf || t->SF)) {
		setregn(t, 0, t->li);
		cpos(t, 0, t->li - 1);
		if ((amnt == 1 && t->sf) || !t->SF)
			while (a--)
				texec(t->cap, t->sf, 1, t->li - 1, 0, 0, 0);
		else
			texec(t->cap, t->SF, a, a, 0, 0, 0);
		goto done;
	}
	if (bot == t->li && (t->dl || t->DL)) {
		setregn(t, 0, t->li);
		cpos(t, 0, top);
		if ((amnt == 1 && t->dl) || !t->DL)
			while (a--)
				texec(t->cap, t->dl, 1, top, 0, 0, 0);
		else
			texec(t->cap, t->DL, a, a, 0, 0, 0);
		goto done;
	}
	if (t->cs && (t->sf || t->SF)) {
		setregn(t, top, bot);
		cpos(t, 0, bot - 1);
		if ((amnt == 1 && t->sf) || !t->SF)
			while (a--)
				texec(t->cap, t->sf, 1, bot - 1, 0, 0, 0);
		else
			texec(t->cap, t->SF, a, a, 0, 0, 0);
		goto done;
	}
	if ((t->dl || t->DL) && (t->al || t->AL)) {
		cpos(t, 0, top);
		if ((amnt == 1 && t->dl) || !t->DL)
			while (a--)
				texec(t->cap, t->dl, 1, top, 0, 0, 0);
		else
			texec(t->cap, t->DL, a, a, 0, 0, 0);
		a = amnt;
		cpos(t, 0, bot - amnt);
		if ((amnt == 1 && t->al) || !t->AL)
			while (a--)
				texec(t->cap, t->al, 1, bot - amnt, 0, 0, 0);
		else
			texec(t->cap, t->AL, a, a, 0, 0, 0);
		goto done;
	}
	msetI(t->updtab + top, 1, bot - top);
	msetI(t->syntab + top, -1, bot - top);
	return;

      done:
	mmove(t->scrn + top * t->co, t->scrn + (top + amnt) * t->co, (bot - top - amnt) * t->co * sizeof(int));
	mmove(t->attr + top * t->co, t->attr + (top + amnt) * t->co, (bot - top - amnt) * t->co * sizeof(int));

	if (bot == t->li && t->db) {
		msetI(t->scrn + (t->li - amnt) * t->co, -1, amnt * t->co);
		msetI(t->attr + (t->li - amnt) * t->co, 0, amnt * t->co);
		msetI(t->updtab + t->li - amnt, 1, amnt);
		msetI(t->syntab + t->li - amnt, -1, amnt);
	} else {
		msetI(t->scrn + (bot - amnt) * t->co, ' ', amnt * t->co);
		msetI(t->attr + (bot - amnt) * t->co, 0, amnt * t->co);
	}
}

static void dodnscrl(SCRN *t, int top, int bot, int amnt)
{
	int a = amnt;

	if (!amnt)
		return;
	set_attr(t, 0);
	if (top == 0 && bot == t->li && (t->sr || t->SR)) {
		setregn(t, 0, t->li);
		cpos(t, 0, 0);
		if ((amnt == 1 && t->sr) || !t->SR)
			while (a--)
				texec(t->cap, t->sr, 1, 0, 0, 0, 0);
		else
			texec(t->cap, t->SR, a, a, 0, 0, 0);
		goto done;
	}
	if (bot == t->li && (t->al || t->AL)) {
		setregn(t, 0, t->li);
		cpos(t, 0, top);
		if ((amnt == 1 && t->al) || !t->AL)
			while (a--)
				texec(t->cap, t->al, 1, top, 0, 0, 0);
		else
			texec(t->cap, t->AL, a, a, 0, 0, 0);
		goto done;
	}
	if (t->cs && (t->sr || t->SR)) {
		setregn(t, top, bot);
		cpos(t, 0, top);
		if ((amnt == 1 && t->sr) || !t->SR)
			while (a--)
				texec(t->cap, t->sr, 1, top, 0, 0, 0);
		else
			texec(t->cap, t->SR, a, a, 0, 0, 0);
		goto done;
	}
	if ((t->dl || t->DL) && (t->al || t->AL)) {
		cpos(t, 0, bot - amnt);
		if ((amnt == 1 && t->dl) || !t->DL)
			while (a--)
				texec(t->cap, t->dl, 1, bot - amnt, 0, 0, 0);
		else
			texec(t->cap, t->DL, a, a, 0, 0, 0);
		a = amnt;
		cpos(t, 0, top);
		if ((amnt == 1 && t->al) || !t->AL)
			while (a--)
				texec(t->cap, t->al, 1, top, 0, 0, 0);
		else
			texec(t->cap, t->AL, a, a, 0, 0, 0);
		goto done;
	}
	msetI(t->updtab + top, 1, bot - top);
	msetI(t->syntab + top, -1, bot - top);
	return;
      done:
	mmove(t->scrn + (top + amnt) * t->co, t->scrn + top * t->co, (bot - top - amnt) * t->co * sizeof(int));
	mmove(t->attr + (top + amnt) * t->co, t->attr + top * t->co, (bot - top - amnt) * t->co * sizeof(int));

	if (!top && t->da) {
		msetI(t->scrn, -1, amnt * t->co);
		msetI(t->attr, 0, amnt * t->co);
		msetI(t->updtab, 1, amnt);
		msetI(t->syntab, -1, amnt);
	} else {
		msetI(t->scrn + t->co * top, ' ', amnt * t->co);
		msetI(t->attr + t->co * top, 0, amnt * t->co);
	}
}

void nscroll(SCRN *t)
{
	int y, z, q, r, p;

	for (y = 0; y != t->li; ++y) {
		q = t->sary[y];
		if (ifhave)
			return;
		if (q && q != t->li) {
			if (q > 0) {
				for (z = y; z != t->li && t->sary[z] == q; ++z)
					t->sary[z] = 0;
				doupscrl(t, y, z + q, q);
				y = z - 1;
			} else {
				for (r = y; r != t->li && (t->sary[r] < 0 || t->sary[r] == t->li); ++r) ;
				p = r - 1;
				do {
					q = t->sary[p];
					if (q && q != t->li) {
						for (z = p; t->sary[z] = 0, (z && t->sary[z - 1] == q); --z) ;
						dodnscrl(t, z + q, p + 1, -q);
						p = z + 1;
					}
				} while (p-- != y);
				y = r - 1;
			}
		}
	}
	msetI(t->sary, 0, t->li);
}

void npartial(SCRN *t)
{
	set_attr(t, 0);
	clrins(t);
	setregn(t, 0, t->li);
}

void nescape(SCRN *t)
{
	npartial(t);
	cpos(t, 0, t->li - 1);
	eraeol(t, 0, t->li - 1);
	if (t->te)
		texec(t->cap, t->te, 1, 0, 0, 0, 0);
}

void nreturn(SCRN *t)
{
	if (t->ti)
		texec(t->cap, t->ti, 1, 0, 0, 0, 0);
	if (!skiptop && t->cl)
		texec(t->cap, t->cl, 1, 0, 0, 0, 0);
	nredraw(t);
}

void nclose(SCRN *t)
{
	leave = 1;
	set_attr(t, 0);
	clrins(t);
	setregn(t, 0, t->li);
	cpos(t, 0, t->li - 1);
	if (t->te)
		texec(t->cap, t->te, 1, 0, 0, 0, 0);
	ttclose();
	rmcap(t->cap);
	joe_free(t->scrn);
	joe_free(t->attr);
	joe_free(t->sary);
	joe_free(t->ofst);
	joe_free(t->htab);
	joe_free(t->ary);
	joe_free(t);
}

void nscrldn(SCRN *t, int top, int bot, int amnt)
{
	int x;

	if (!amnt || top >= bot || bot > t->li)
		return;
	if ((amnt < bot - top && bot - top - amnt < amnt / 2) || !t->scroll)
		amnt = bot - top;
	if (amnt < bot - top) {
		for (x = bot; x != top + amnt; --x) {
			t->sary[x - 1] = (t->sary[x - amnt - 1] == t->li ? t->li : t->sary[x - amnt - 1] - amnt);
			t->updtab[x - 1] = t->updtab[x - amnt - 1];
			t->syntab[x - 1] = t->syntab[x - amnt - 1];
		}
		for (x = top; x != top + amnt; ++x) {
			t->updtab[x] = 1;
			t->syntab[x] = -1;
			}
	}
	if (amnt > bot - top)
		amnt = bot - top;
	msetI(t->sary + top, t->li, amnt);
	if (amnt == bot - top) {
		msetI(t->updtab + top, 1, amnt);
		msetI(t->syntab + top, -1, amnt);
		}
}

void nscrlup(SCRN *t, int top, int bot, int amnt)
{
	int x;

	if (!amnt || top >= bot || bot > t->li)
		return;
	if ((amnt < bot - top && bot - top - amnt < amnt / 2) || !t->scroll)
		amnt = bot - top;
	if (amnt < bot - top) {
		for (x = top + amnt; x != bot; ++x) {
			t->sary[x - amnt] = (t->sary[x] == t->li ? t->li : t->sary[x] + amnt);
			t->updtab[x - amnt] = t->updtab[x];
			t->syntab[x - amnt] = t->syntab[x];
		}
		for (x = bot - amnt; x != bot; ++x) {
			t->updtab[x] = 1;
			t->syntab[x] = -1;
			}
	}
	if (amnt > bot - top)
		amnt = bot - top;
	msetI(t->sary + bot - amnt, t->li, amnt);
	if (amnt == bot - top) {
		msetI(t->updtab + bot - amnt, 1, amnt);
		msetI(t->syntab + bot - amnt, -1, amnt);
		}
}

extern volatile int dostaupd;

void nredraw(SCRN *t)
{
	dostaupd = 1;
	msetI(t->scrn, ' ', t->co * skiptop);
	msetI(t->attr, 0, t->co * skiptop);
	msetI(t->scrn + skiptop * t->co, -1, (t->li - skiptop) * t->co);
	msetI(t->attr + skiptop * t->co, 0, (t->li - skiptop) * t->co);
	msetI(t->sary, 0, t->li);
	msetI(t->updtab + skiptop, -1, t->li - skiptop);
	msetI(t->syntab + skiptop, -1, t->li - skiptop);
	t->x = -1;
	t->y = -1;
	t->top = t->li;
	t->bot = 0;
	t->attrib = -1;
	t->ins = -1;
	set_attr(t, 0);
	clrins(t);
	setregn(t, 0, t->li);

	if (!skiptop) {
		if (t->cl) {
			texec(t->cap, t->cl, 1, 0, 0, 0, 0);
			t->x = 0;
			t->y = 0;
			msetI(t->scrn, ' ', t->li * t->co);
			msetI(t->attr, 0, t->li * t->co);
		} else if (t->cd) {
			cpos(t, 0, 0);
			texec(t->cap, t->cd, 1, 0, 0, 0, 0);
			msetI(t->scrn, ' ', t->li * t->co);
			msetI(t->attr, 0, t->li * t->co);
		}
	}
}

/* Convert color/attribute name into internal code */

int meta_color(unsigned char *s)
{
	if(!strcmp((char *)s,"inverse"))
		return INVERSE;
	else if(!strcmp((char *)s,"underline"))
		return UNDERLINE;
	else if(!strcmp((char *)s,"bold"))
		return BOLD;
	else if(!strcmp((char *)s,"blink"))
		return BLINK;
	else if(!strcmp((char *)s,"dim"))
		return DIM;
	else if(!strcmp((char *)s,"white"))
		return FG_WHITE;
	else if(!strcmp((char *)s,"cyan"))
		return FG_CYAN;
	else if(!strcmp((char *)s,"magenta"))
		return FG_MAGENTA;
	else if(!strcmp((char *)s,"blue"))
		return FG_BLUE;
	else if(!strcmp((char *)s,"yellow"))
		return FG_YELLOW;
	else if(!strcmp((char *)s,"green"))
		return FG_GREEN;
	else if(!strcmp((char *)s,"red"))
		return FG_RED;
	else if(!strcmp((char *)s,"black"))
		return FG_BLACK;
	else if(!strcmp((char *)s,"bg_white"))
		return BG_WHITE;
	else if(!strcmp((char *)s,"bg_cyan"))
		return BG_CYAN;
	else if(!strcmp((char *)s,"bg_magenta"))
		return BG_MAGENTA;
	else if(!strcmp((char *)s,"bg_blue"))
		return BG_BLUE;
	else if(!strcmp((char *)s,"bg_yellow"))
		return BG_YELLOW;
	else if(!strcmp((char *)s,"bg_green"))
		return BG_GREEN;
	else if(!strcmp((char *)s,"bg_red"))
		return BG_RED;
	else if(!strcmp((char *)s,"bg_black"))
		return BG_BLACK;
	else
		return 0;
}

/* Generate a field
 *
 * 't' is SCRN to write to.
 * 'scrn' is address of field in character buffer
 * 'attr' is address of field in attribute buffer
 * 'x', 'y' are starting column and line numbers of field
 * 'ofst' is first column within string to display
 * 's', 'len' is string to generate in field
 * 'atr' is screeen attributes (and color) which should be used
 * 'width' is column width of field
 * 'flg' if set, erases to end of line
 */

void genfield(SCRN *t,int *scrn,int *attr,int x,int y,int ofst,unsigned char *s,int len,int atr,int width,int flg,int *fmt)
{
	int col;
	struct utf8_sm sm;
	int last_col = x + width;

	utf8_init(&sm);

	for (col = 0;len != 0 && x < last_col; len--) {
		int c = *s++;
		int wid = -1;
		int my_atr = atr;
		if (fmt) my_atr |= *fmt++;
		if (locale_map->type) {
			/* UTF-8 mode: decode character and determine its width */
			c = utf8_decode(&sm,c);
			if (c >= 0)
				wid = joe_wcwidth(1,c);
		} else {
			/* Byte mode: character is one column wide */
			wid = 1 ;
		}
		if (wid>=0) {
			if (col >= ofst) {
				if (x + wid > last_col) {
					/* Character crosses end of field, so fill balance of field with '>' characters instead */
					while (x < last_col) {
						outatr(utf8_map, t, scrn, attr, x, y, '>', my_atr);
						++scrn;
						++attr;
						++x;
					}
				} else if(wid) {
					/* Emit character */
					outatr(locale_map, t, scrn, attr, x, y, c, my_atr);
					x += wid;
					scrn += wid;
					attr += wid;
				}
			} else if ((col + wid) > ofst) {
				/* Wide character crosses left side of field */
				wid -= ofst - col;
				col = ofst;
				while (wid) {
					outatr(utf8_map, t, scrn, attr, x, y, '<', my_atr);
					++scrn;
					++attr;
					++x;
					++col;
					--wid;
				}
			} else
				col += wid;
	}
	}
	/* Fill balance of field with spaces */
	while (x < last_col) {
		outatr(utf8_map, t, scrn, attr, x, y, ' ', 0);
		++x;
		++scrn;
		++attr;
	}
	/* Erase to end of line */
	if (flg)
		eraeol(t, x, y);
}

/* Width function for above */

int txtwidth(unsigned char *s,int len)
{
	if (locale_map->type) {
		int col=0;
		struct utf8_sm sm;
		utf8_init(&sm);

		while(len--) {
			int d = utf8_decode(&sm,*s++);
			if (d >= 0)
				col += joe_wcwidth(1,d);
		}

		return col;
	} else
		return len;
}

/* Generate text with formatting escape sequences */

void genfmt(SCRN *t, int x, int y, int ofst, const unsigned char *s, int flg)
{
	int *scrn = t->scrn + y * t->co + x;
	int *attr = t->attr + y * t->co + x;
	int atr = 0;
	int col = 0;
	int c;
	struct utf8_sm sm;

	utf8_init(&sm);

	while ((c = *s++) != '\0')
		if (c == '\\') {
			switch (c = *s++) {
			case 'u':
			case 'U':
				atr ^= UNDERLINE;
				break;
			case 'i':
			case 'I':
				atr ^= INVERSE;
				break;
			case 'b':
			case 'B':
				atr ^= BOLD;
				break;
			case 'd':
			case 'D':
				atr ^= DIM;
				break;
			case 'f':
			case 'F':
				atr ^= BLINK;
				break;
			case 0:
				--s;
				break;
			default: {
				if (col++ >= ofst) {
					outatr(locale_map, t, scrn, attr, x, y, (c&0x7F), atr);
					++scrn;
					++attr;
					++x;
					}
				break;
				}
			}
		} else {
			int wid = -1;
			if (locale_map->type) {
				/* UTF-8 mode: decode character and determine its width */
				c = utf8_decode(&sm,c);
				if (c >= 0) {
						wid = joe_wcwidth(1,c);
				}
			} else {
				/* Byte mode: character is one column wide */
				wid = 1 ;
			}

			if (wid>=0) {
				if (col >= ofst) {
					outatr(locale_map, t, scrn, attr, x, y, c, atr);
					scrn += wid;
					attr += wid;
					x += wid;
					col += wid;
				} else if (col+wid>ofst) {
					while (col<ofst) {
						++col;
						--wid;
					}
					while (wid) {
						outatr(utf8_map, t, scrn, attr, x, y, '<', atr);
						++scrn;
						++attr;
						++x;
						++col;
						--wid;
					}
				} else
					col += wid;
		}
		}
	if (flg)
		eraeol(t, x, y);
}

/* Determine column width of string with format codes */

int fmtlen(const unsigned char *s)
{
	int col = 0;
	struct utf8_sm sm;
	int c;

	utf8_init(&sm);

	while ((c = (*s++))) {
		if (c == '\\') {
			switch (*s++) {
			case 'u':
			case 'i':
			case 'd':
			case 'f':
			case 'b':
			case 'U':
			case 'I':
			case 'D':
			case 'F':
			case 'B':
				continue;
			case 0:
				return col;
			default:
				++col;
				continue;
			}
		} else {
			int wid = 0;
			if(locale_map->type) {
				c = utf8_decode(&sm,c);
				if (c>=0)
					wid = joe_wcwidth(1,c);
			} else {
				wid = 1;
			}
			col += wid;
		}
	}
	return col;
}

/* Return offset within format string which corresponds to a particular
   column */

/* FIXME: this is not valid if we land in the middle of a double-wide character */

int fmtpos(unsigned char *s, int goal)
{
	unsigned char *org = s;
	int col = 0;
	int c;
	struct utf8_sm sm;

	utf8_init(&sm);

	while ((c= *s) && col<goal) {
		s++;
		if (c == '\\') {
			switch (*s++) {
			case 'u':
			case 'i':
			case 'd':
			case 'f':
			case 'b':
			case 'U':
			case 'I':
			case 'D':
			case 'F':
			case 'B':
				continue;
			case 0:
				--s;
				break;
			default:
				++col;
				continue;
			}
		} else {
			int wid = 0;
			if(locale_map->type) {
				c = utf8_decode(&sm,c);
				if (c>=0)
					wid = joe_wcwidth(1,c);
			} else {
				wid = 1;
			}
			col += wid;
		}
	}

	return s - org + goal - col;
}
