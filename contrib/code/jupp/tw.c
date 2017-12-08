/*
 *	Text editing windows
 *	Copyright
 *		(C) 1992 Joseph H. Allen
 *
 *	This file is part of JOE (Joe's Own Editor)
 */
#include "config.h"
#include "types.h"

__RCSID("$MirOS: contrib/code/jupp/tw.c,v 1.16 2017/12/07 02:10:17 tg Exp $");

#include <stdlib.h>
#include <string.h>
#ifdef HAVE_TIME_H
#include <time.h>
#endif

#ifdef HAVE_BSD_STRING_H
#include <bsd/string.h>
#endif

#include "b.h"
#include "bw.h"
#include "macro.h"
#include "main.h"
#include "qw.h"
#include "scrn.h"
#include "uedit.h"
#include "ufile.h"
#include "ushell.h"
#include "utils.h"
#include "vs.h"
#include "syntax.h"
#include "charmap.h"
#include "tw.h"
#include "w.h"

#if !HAVE_DECL_CTIME
char *ctime(const time_t *);
#endif

extern int square;
int staen = 0;
int staupd = 0;
int keepup = 0;

/* Move text window */

static void movetw(jobject jO, int x, int y)
{
	BW *bw = jO.bw;
	TW *tw = (TW *) bw->object;

	if (y || !staen) {
		if (!tw->staon) {	/* Scroll down and shrink */
			nscrldn(bw->parent->t->t, y, bw->parent->nh + y, 1);
		}
		bwmove(bw, x + (bw->o.linums ? LINCOLS : 0), y + 1);
		tw->staon = 1;
	} else {
		if (tw->staon) {	/* Scroll up and grow */
			nscrlup(bw->parent->t->t, y, bw->parent->nh + y, 1);
		}
		bwmove(bw, x + (bw->o.linums ? LINCOLS : 0), y);
		tw->staon = 0;
	}
}

/* Resize text window */

static void resizetw(jobject jO, int wi, int he)
{
	BW *bw = jO.bw;

	if (bw->parent->ny || !staen)
		bwresz(bw, wi - (bw->o.linums ? LINCOLS : 0), he - 1);
	else
		bwresz(bw, wi - (bw->o.linums ? LINCOLS : 0), he);
}

/* Get current context */

/* Find first line (going backwards) which has 0 indentation level
 * and is not a comment, blank, or block structuring line.  This is
 * likely to be the line with the function name.
 *
 * There are actually two possibilities:
 *
 * We want the first line-
 *
 * int
 * foo(int x,int y) {
 *
 *   }
 *
 * We want the last line-
 *
 * program foo(input,output);
 * var a, b, c : real;
 * begin
 *
 */

static unsigned char *
get_context(BW *bw)
{
	P *p = pdup(bw->cursor);
	static unsigned char buf1[stdsiz];


	buf1[0] = 0;
	/* Find first line with 0 indentation which is not a comment line */
	do {
		p_goto_bol(p);
		if (!pisindent(p) && !pisblank(p)) {
			/* Uncomment to get the last line instead of the first line (see above)
			next:
			*/
			brzs(p,stdbuf,stdsiz-1);
			/* Ignore comment and block structuring lines */
			if (!(stdbuf[0]=='{' ||
			    (stdbuf[0]=='/' && stdbuf[1]=='*') ||
			    (stdbuf[0]=='\f') ||
			    (stdbuf[0]=='/' && stdbuf[1]=='/') ||
			    (stdbuf[0]=='#') ||
			    (stdbuf[0]=='b' && stdbuf[1]=='e' && stdbuf[2]=='g' && stdbuf[3]=='i' && stdbuf[4]=='n') ||
			    (stdbuf[0]=='B' && stdbuf[1]=='E' && stdbuf[2]=='G' && stdbuf[3]=='I' && stdbuf[4]=='N') ||
			    (stdbuf[0]=='-' && stdbuf[1]=='-') ||
			    stdbuf[0]==';')) {
				strlcpy(buf1,stdbuf,stdsiz);
				/* Uncomment to get the last line instead of the first line (see above)
				if (pprevl(p)) {
					p_goto_bol(p);
					if (!pisindent(p) && !pisblank(p))
						goto next;
				}
				*/
				break;
			}

		}
	} while (!buf1[0] && pprevl(p));

	prm(p);

	return buf1;
}

static unsigned char *stagen(unsigned char *stalin, BW *bw, unsigned char *s, int fill)
{
	unsigned char *cp, *cp2, uc;
	unsigned char buf[80];
	int x;
	W *w = bw->parent;
	time_t tt;
	int special_aA = 0;

	cp = s;
	while ((cp2 = strstr(cp, "%a")) != NULL) {
		cp2 += /* %a */ 2;
		if (cp2[1] == '%')
			++cp2;
		if (cp2[0] == '%' && cp2[1] == 'A') {
			special_aA = 1;
			break;
		}
	}
	if (!special_aA) while ((cp2 = strstr(cp, "%A")) != NULL) {
		cp2 += /* %A */ 2;
		if (cp2[1] == '%')
			++cp2;
		if (cp2[0] == '%' && cp2[1] == 'a') {
			special_aA = 1;
			break;
		}
	}

	stalin = vstrunc(stalin, 0);
	while (*s) {
		if (*s == '%' && s[1]) {
			switch (*++s) {
			case 'x':
				/* Context (but only if autoindent is enabled) */
				if (bw->o.autoindent) {
					cp = get_context(bw);
					stalin = vsncpy(sv(stalin), sz(cp));
				}
				break;

			case 'y':
				if (bw->o.syntax) {
					joe_snprintf_1((char *)buf, sizeof(buf), "(%s)", bw->o.syntax->name);
					stalin = vsncpy(sv(stalin), sz(buf));
				}
				break;
			case 't':
				tt = time(NULL);
				cp = (unsigned char *)ctime(&tt);

				x = (cp[11] - '0') * 10 + cp[12] - '0';
				if (x > 12)
					x -= 12;
				joe_snprintf_1((char *)buf, sizeof(buf), "%2.2d", x);
				if (buf[0] == '0')
					buf[0] = fill;
				stalin = vsncpy(sv(stalin), buf, 2);
				stalin = vsncpy(sv(stalin), cp + 13, 3);
				break;
			case 'u':
				tt = time(NULL);
				cp = (unsigned char *)ctime(&tt);
				stalin = vsncpy(sv(stalin), cp + 11, 5);
				break;
			case 'T':
				if (bw->o.overtype)
					stalin = vsadd(stalin, 'O');
				else
					stalin = vsadd(stalin, 'I');
				break;
			case 'W':
				if (bw->o.wordwrap)
					stalin = vsadd(stalin, 'W');
				else
					stalin = vsadd(stalin, fill);
				break;
			case 'I':
				if (bw->o.autoindent)
					stalin = vsadd(stalin, 'A');
				else
					stalin = vsadd(stalin, fill);
				break;
			case 'X':
				if (square)
					stalin = vsadd(stalin, 'X');
				else
					stalin = vsadd(stalin, fill);
				break;
			case 'n':
				if (!bw->b->name) {
					stalin = vsncpy(sv(stalin), sc("Unnamed"));
					break;
				}
				cp = bw->b->name;
 escape_loop:
				switch ((uc = *cp++)) {
				case '\\':
					stalin = vsadd(stalin, uc);
					/* FALLTHROUGH */
				default:
					stalin = vsadd(stalin, uc);
					goto escape_loop;
				case '\0':
					break;
				}
				break;
			case 'm':
				if (bw->b->changed)
					stalin = vsncpy(sv(stalin), sc("(Modified)"));
				break;
			case 'R':
				if (bw->b->rdonly)
					stalin = vsncpy(sv(stalin), sc("(Read only)"));
				break;
			case '*':
				if (bw->b->changed)
					stalin = vsadd(stalin, '*');
				else
					stalin = vsadd(stalin, fill);
				break;
			case 'r':
				joe_snprintf_1((char *)buf, sizeof(buf), "%-4ld", bw->cursor->line + 1);
				for (x = 0; buf[x]; ++x)
					if (buf[x] == ' ')
						buf[x] = fill;
				stalin = vsncpy(sv(stalin), sz(buf));
				break;
			case 'o':
				joe_snprintf_1((char *)buf, sizeof(buf), "%-4ld", bw->cursor->byte);
				for (x = 0; buf[x]; ++x)
					if (buf[x] == ' ')
						buf[x] = fill;
				stalin = vsncpy(sv(stalin), sz(buf));
				break;
			case 'O':
				joe_snprintf_1((char *)buf, sizeof(buf), "%-4lX", bw->cursor->byte);
				for (x = 0; buf[x]; ++x)
					if (buf[x] == ' ')
						buf[x] = fill;
				stalin = vsncpy(sv(stalin), sz(buf));
				break;
			case 'a':
				if (bw->b->o.charmap->type && !(special_aA && brch(bw->cursor) == 0x1000FFFE)) {
					/* UTF-8: don't display decimal value */
					buf[0] = 'u';
					buf[1] = 0;
				} else {
					if (!piseof(bw->cursor))
						joe_snprintf_1((char *)buf, sizeof(buf), "%3d", 255 & brc(bw->cursor));
					else
						joe_snprintf_0((char *)buf, sizeof(buf), "   ");
					for (x = 0; buf[x]; ++x)
						if (buf[x] == ' ')
							buf[x] = fill;
				}
				stalin = vsncpy(sv(stalin), sz(buf));
				break;
			case 'A':
				if (bw->b->o.charmap->type) {
					/* UTF-8, display UCS-2 value */
					if (!piseof(bw->cursor)) {
						int uch = brch(bw->cursor);
						if (uch == 0x1000FFFE)
							joe_snprintf_1((char *)buf, sizeof(buf), special_aA ? "%02X" : "  %02X", 255 & brc(bw->cursor));
						else if (uch == 0x1000FFFF)
							joe_snprintf_0((char *)buf, sizeof(buf), "<-2>");
						else
							joe_snprintf_1((char *)buf, sizeof(buf), "%04X", uch);
					} else
						joe_snprintf_0((char *)buf, sizeof(buf), "    ");
				} else {
					if (!piseof(bw->cursor))
						joe_snprintf_1((char *)buf, sizeof(buf), "%2.2X", 255 & brc(bw->cursor));
					else
						joe_snprintf_0((char *)buf, sizeof(buf), "  ");
				}
				for (x = 0; buf[x]; ++x)
					if (buf[x] == ' ')
						buf[x] = fill;
				stalin = vsncpy(sv(stalin), sz(buf));
				break;
			case 'c':
				joe_snprintf_1((char *)buf, sizeof(buf), "%-3ld", piscol(bw->cursor) + 1);
				for (x = 0; buf[x]; ++x)
					if (buf[x] == ' ')
						buf[x] = fill;
				stalin = vsncpy(sv(stalin), sz(buf));
				break;
			case 'p':
				if (bw->b->eof->byte)
					joe_snprintf_1((char *)buf, sizeof(buf), "%3ld", bw->cursor->byte * 100 / bw->b->eof->byte);
				else
					joe_snprintf_0((char *)buf, sizeof(buf), "100");
				for (x = 0; buf[x]; ++x)
					if (buf[x] == ' ')
						buf[x] = fill;
				stalin = vsncpy(sv(stalin), sz(buf));
				break;
			case 'l':
				joe_snprintf_1((char *)buf, sizeof(buf), "%-4ld", bw->b->eof->line + 1);
				for (x = 0; buf[x]; ++x)
					if (buf[x] == ' ')
						buf[x] = fill;
				stalin = vsncpy(sv(stalin), sz(buf));
				break;
			case 'k':
				cp = buf;
				buf[0] = 0;
				if (w->kbd->x && w->kbd->seq[0])
					for (x = 0; x != w->kbd->x; ++x) {
						uc = w->kbd->seq[x] & 127;

						if (uc < 32) {
							cp[0] = '^';
							cp[1] = uc + '@';
							cp += 2;
						} else if (uc == 127) {
							cp[0] = '^';
							cp[1] = '?';
							cp += 2;
						} else {
							cp[0] = uc;
							cp += 1;
						}
					}
				*cp++ = fill;
				while (cp - buf < 4)
					*cp++ = fill;
				stalin = vsncpy(sv(stalin), buf, cp - buf);
				break;
			case 'S':
				if (bw->b->pid)
					stalin = vsncpy(sv(stalin), sc("*SHELL*"));
				break;
			case 'M':
				if (recmac) {
					joe_snprintf_1((char *)buf, sizeof(buf), "(Macro %d recording...)", recmac->n);
					stalin = vsncpy(sv(stalin), sz(buf));
				}
				break;
			default:
				stalin = vsadd(stalin, *s);
			}
		} else
			stalin = vsadd(stalin, *s);
		++s;
	}
	return stalin;
}

static void disptw(jobject jO, int flg)
{
	BW *bw = jO.bw;
	W *w = bw->parent;
	TW *tw = (TW *) bw->object;

	if (bw->o.linums != bw->linums) {
		bw->linums = bw->o.linums;
		resizetw(jO, w->w, w->h);
		movetw(jO, w->x, w->y);
		bwfllw(jO);
	}

	if (bw->o.hex) {
		w->cury = (bw->cursor->byte-bw->top->byte)/16 + bw->y - w->y;
		w->curx = (bw->cursor->byte-bw->top->byte)%16 + 60 - bw->offset;
	} else {
		w->cury = bw->cursor->line - bw->top->line + bw->y - w->y;
		w->curx = bw->cursor->xcol - bw->offset + (bw->o.linums ? LINCOLS : 0);
	}

	if ((staupd || keepup || bw->cursor->line != tw->prevline || bw->b->changed != tw->changed || bw->b != tw->prev_b) && (w->y || !staen)) {
		int fill;

		tw->prevline = bw->cursor->line;
		tw->changed = bw->b->changed;
		tw->prev_b = bw->b;
		if (bw->o.rmsg[0])
			fill = bw->o.rmsg[0];
		else
			fill = ' ';
		tw->stalin = stagen(tw->stalin, bw, bw->o.lmsg, fill);
		tw->staright = stagen(tw->staright, bw, bw->o.rmsg, fill);
		if (fmtlen(tw->staright) < w->w) {
			int x = fmtpos(tw->stalin, w->w - fmtlen(tw->staright));

			if (x > sLEN(tw->stalin))
				tw->stalin = vsfill(sv(tw->stalin), fill, x - sLEN(tw->stalin));
			tw->stalin = vsncpy(tw->stalin, fmtpos(tw->stalin, w->w - fmtlen(tw->staright)), sv(tw->staright));
		}
		tw->stalin = vstrunc(tw->stalin, fmtpos(tw->stalin, w->w));
		genfmt(w->t->t, w->x, w->y, 0, tw->stalin, 0);
		w->t->t->updtab[w->y] = 0;
	}

	if (flg) {
		if (bw->o.hex)
			bwgenh(bw);
		else
			bwgen(bw, bw->o.linums);
	}
}

/* Split current window */

static void iztw(TW *tw, int y)
{
	tw->stalin = NULL;
	tw->staright = NULL;
	tw->changed = -1;
	tw->prevline = -1;
	tw->staon = (!staen || y);
	tw->prev_b = 0;
}

extern int dostaupd;

int usplitw(BW *bw)
{
	W *w = bw->parent;
	int newh = getgrouph(w);
	W *new;
	TW *newtw;
	BW *newbw;

	dostaupd = 1;
	if (newh / 2 < FITHEIGHT)
		return -1;
	new = wcreate(w->t, w->watom, findbotw(w), NULL, w, newh / 2 + (newh & 1), NULL, NULL);
	if (!new)
		return -1;
	wfit(new->t);
	new->object.bw = newbw = bwmk(new, bw->b, 0);
	++bw->b->count;
	newbw->offset = bw->offset;
	newbw->object = newtw = malloc(sizeof(TW));
	iztw(newtw, new->y);
	pset(newbw->top, bw->top);
	pset(newbw->cursor, bw->cursor);
	newbw->cursor->xcol = bw->cursor->xcol;
	new->t->curwin = new;
	return 0;
}

int uduptw(BW *bw)
{
	W *w = bw->parent;
	int newh = getgrouph(w);
	W *new;
	TW *newtw;
	BW *newbw;

	dostaupd = 1;
	new = wcreate(w->t, w->watom, findbotw(w), NULL, NULL, newh, NULL, NULL);
	if (!new)
		return -1;
	if (demotegroup(w))
		new->t->topwin = new;
	new->object.bw = newbw = bwmk(new, bw->b, 0);
	++bw->b->count;
	newbw->offset = bw->offset;
	newbw->object = newtw = malloc(sizeof(TW));
	iztw(newtw, new->y);
	pset(newbw->top, bw->top);
	pset(newbw->cursor, bw->cursor);
	newbw->cursor->xcol = bw->cursor->xcol;
	new->t->curwin = new;
	wfit(w->t);
	return 0;
}

static void instw(BW *bw, B *b, long int l, long int n, int flg)
{
	if (b == bw->b)
		bwins(bw, l, n, flg);
}

static void deltw(BW *bw, B *b, long int l, long int n, int flg)
{
	if (b == bw->b)
		bwdel(bw, l, n, flg);
}

WATOM watomtw = {
	US "main",
	disptw,
	bwfllw,
	NULL,
	rtntw,
	utypebw,
	resizetw,
	movetw,
	instw,
	deltw,
	TYPETW
};

int abortit(BW *bw)
{
	W *w;
	TW *tw;
	B *b;
	if (bw->parent->watom != &watomtw)
		return wabort(bw->parent);
	if (bw->b->pid && bw->b->count==1)
		return ukillpid(bw);
	w = bw->parent;
	tw = (TW *) bw->object;
	/* If only one main window on the screen... */
	if (countmain(w->t) == 1)
		/* Replace it with an orphaned buffer if there are any */
		if ((b = borphan()) != NULL) {
			void *object = bw->object;
			/* FIXME: Shouldn't we wabort() and wcreate here to kill
			   any prompt windows? */

			bwrm(bw);
			w->object.bw = bw = bwmk(w, b, 0);
			wredraw(bw->parent);
			bw->object = object;
			return 0;
		}
	bwrm(bw);
	vsrm(tw->stalin);
	free(tw);
	w->object.base = NULL;
	wabort(w);	/* Eliminate this window and it's children */
	return 0;
}

/* User routine for aborting a text window */

static int naborttw(BW *bw, int k, void *object, int *notify)
{
	if (notify)
		*notify = 1;
	if (k != 'y' && k != 'Y')
		return -1;

	genexmsg(bw, 0, NULL);
	return abortit(bw);
}

static int naborttw1(BW *bw, int k, void *object, int *notify)
{
	if (notify)
		*notify = 1;
	if (k != 'y' && k != 'Y')
		return -1;

	if (!exmsg) genexmsg(bw, 0, NULL);
	return abortit(bw);
}

/* k is last character types which lead to uabort.  If k is -1, it means uabort
   was called internally, and not by the user: which means uabort will not send
   Ctrl-C to process */
int uabort(BW *bw, int k)
{
	if (bw->parent->watom != &watomtw)
		return wabort(bw->parent);
	if (bw->b->pid && bw->b->count==1)
		return ukillpid(bw);
	if (bw->b->changed && bw->b->count == 1 && !bw->b->scratch)
		if (mkqw(bw->parent, sc("Lose changes to this file (y,n,^C)? "), naborttw, NULL, NULL, NULL))
			return 0;
		else
			return -1;
	else
		return naborttw(bw, 'y', NULL, NULL);
}

int ucancel(BW *bw, int k)
{
	if (bw->parent->watom != &watomtw) {
		wabort(bw->parent);
		return 0;
	} else
		return uabort(bw,k);
}

/* Same as above, but only calls genexmsg if nobody else has */

int uabort1(BW *bw, int k)
{
	if (bw->parent->watom != &watomtw)
		return wabort(bw->parent);
	if (bw->b->pid && bw->b->count==1)
		return ukillpid(bw);
	if (bw->b->changed && bw->b->count == 1 && !bw->b->scratch)
		if (mkqw(bw->parent, sc("Lose changes to this file (y,n,^C)? "), naborttw1, NULL, NULL, NULL))
			return 0;
		else
			return -1;
	else
		return naborttw1(bw, 'y', NULL, NULL);
}

/* Abort buffer without prompting: just fail if this is last window on buffer */

int uabortbuf(BW *bw)
{
	W *w = bw->parent;
	B *b;

	if (bw->b->pid && bw->b->count==1)
		return ukillpid(bw);

	if (okrepl(bw))
		return -1;

	if ((b = borphan()) != NULL) {
		void *object = bw->object;

		bwrm(bw);
		w->object.bw = bw = bwmk(w, b, 0);
		wredraw(bw->parent);
		bw->object = object;
		return 0;
	}

	return naborttw(bw, 'y', NULL, NULL);
}

/* Kill current window (orphans buffer) */

int utw0(BASE *b)
{
	BW *bw = b->parent->main->object.bw;

	if (countmain(b->parent->t) == 1)
		return -1;
	if (bw->b->count == 1)
		orphit(bw);
	return uabort(bw, -1);
}

/* Kill all other windows (orphans buffers) */

int utw1(BASE *b)
{
	W *starting = b->parent;
	W *mainw = starting->main;
	SCREEN *t = mainw->t;
	int yn;

	do {
		yn = 0;
	      loop:
		do {
			wnext(t);
		} while (t->curwin->main == mainw && t->curwin != starting);
		if (t->curwin->main != mainw) {
			BW *bw = t->curwin->main->object.bw;
			utw0((BASE *)bw);
			yn = 1;
			goto loop;
		}
	} while (yn);
	return 0;
}

void setline(B *b, long int line)
{
	W *w = maint->curwin;

	do {
		if (w->watom->what == TYPETW) {
			BW *bw = w->object.bw;

			if (bw->b == b) {
				long oline = bw->top->line;

				pline(bw->top, line);
				pline(bw->cursor, line);
				if (w->y >= 0 && bw->top->line > oline && bw->top->line - oline < bw->h)
					nscrlup(w->t->t, bw->y, bw->y + bw->h, (int) (bw->top->line - oline));
				else if (w->y >= 0 && bw->top->line < oline && oline - bw->top->line < bw->h)
					nscrldn(w->t->t, bw->y, bw->y + bw->h, (int) (oline - bw->top->line));
			}
		}
	} while ((w = w->link.next) != maint->curwin);
}

/* Create a text window.  It becomes the last window on the screen */

BW *wmktw(SCREEN *t, B *b)
{
	W *w;
	BW *bw;
	TW *tw;

	w = wcreate(t, &watomtw, NULL, NULL, NULL, t->h, NULL, NULL);
	wfit(w->t);
	w->object.bw = bw = bwmk(w, b, 0);
	bw->object = tw = malloc(sizeof(TW));
	iztw(tw, w->y);
	return bw;
}
