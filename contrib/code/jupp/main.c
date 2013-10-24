/* $MirOS: contrib/code/jupp/main.c,v 1.20 2013/01/05 22:16:31 tg Exp $ */

#define JUPP_IS_COPYRIGHT_C_BY "2013 mirabilos"

/*-
 * Copyright (c) 2004ff. Thorsten Glaser
 * Copyright (C) 1992 Joseph H. Allen
 *
 * This file is part of "jupp", a variant of Joe's Own Editor "JOE".
 *
 * jupp is free software; you can redistribute and/or modify it, deal
 * in the work, etc. under the terms of the GNU General Public Licen-
 * se, version 1 (of February 1989) as published by the Free Software
 * Foundation, reproduced in the file COPYING in the jupp source code
 * distribution. If jupp is combined with other independent work, for
 * example libraries or when using crunchgen, into a combined binary,
 * that may be conveyed under any version of the GPL, as published by
 * the Free Software Foundation, and any compatible licence permitted
 * by the GPL.
 *
 * This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
 * the utmost extent permitted by applicable law, neither express nor
 * implied; without malicious intent or gross negligence. In no event
 * may a licensor, author or contributor be held liable for indirect,
 * direct, other damage, loss, or other issues arising in any way out
 * of dealing in the work, even if advised of the possibility of such
 * damage or existence of a defect, except proven that it results out
 * of said person's immediate fault when using the work as intended.
 *-
 * Editor startup and main edit loop
 */

#include "config.h"
#include "types.h"

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include "b.h"
#include "help.h"
#include "kbd.h"
#include "macro.h"
#include "path.h"
#include "rc.h"
#include "scrn.h"
#include "termcap.h"
#include "tw.h"
#include "vfile.h"
#include "vs.h"
#include "w.h"
#include "utf8.h"
#include "charmap.h"
#include "syntax.h"

extern int mid, dspasis, help, pgamnt, nobackups, lightoff, exask, lines, columns, dopadding, marking, dobeep;

extern int idleout;		/* Clear to use /dev/tty for screen */
extern unsigned char *joeterm;
int help = 0;			/* Set to have help on when starting */
int nonotice = 0;		/* Set to prevent copyright notice */
int orphan = 0;
unsigned char *exmsg = NULL;		/* Message to display when exiting the editor */

SCREEN *maint;			/* Main edit screen */

const char null[] = "";

/* Make windows follow cursor */

void dofollows(void)
{
	W *w = maint->curwin;

	do {
		if (w->y != -1 && w->watom->follow && w->object)
			w->watom->follow(w->object);
		w = (W *) (w->link.next);
	} while (w != maint->curwin);
}

/* Update screen */

int dostaupd = 1;
extern int staupd;

void edupd(int flg)
{
	W *w;
	int wid, hei;

	if (dostaupd) {
		staupd = 1;
		dostaupd = 0;
	}
	ttgtsz(&wid, &hei);
	if ((wid >= 2 && wid != maint->w) || (hei >= 1 && hei != maint->h)) {
		nresize(maint->t, wid, hei);
		sresize(maint);
	}
	dofollows();
	ttflsh();
	nscroll(maint->t);
	help_display(maint);
	w = maint->curwin;
	do {
		if (w->y != -1) {
			if (w->object && w->watom->disp)
				w->watom->disp(w->object, flg);
			msgout(w);
		}
		w = (W *) (w->link.next);
	} while (w != maint->curwin);
	cpos(maint->t, maint->curwin->x + maint->curwin->curx, maint->curwin->y + maint->curwin->cury);
	staupd = 0;
}

static int ahead = 0;
static int ungot = 0;
static int ungotc = 0;

void nungetc(int c)
{
	if (c != 'C' - '@' && c != 'M' - '@') {
		chmac();
		ungot = 1;
		ungotc = c;
	}
}

int edloop(int flg)
{
	int term = 0;
	int ret = 0;

	if (flg) {
		if (maint->curwin->watom->what == TYPETW)
			return 0;
		else
			maint->curwin->notify = &term;
	}
	while (!leave && (!flg || !term)) {
		MACRO *m;
		int c;

		if (exmsg && !flg) {
			vsrm(exmsg);
			exmsg = NULL;
		}
		edupd(1);
		if (!ahead && !have)
			ahead = 1;
		if (ungot) {
			c = ungotc;
			ungot = 0;
		} else
			c = ttgetc();

		if (!ahead && c == 10)
			c = 13;
		m = dokey(maint->curwin->kbd, c);
		if (maint->curwin->main && maint->curwin->main != maint->curwin) {
			int x = maint->curwin->kbd->x;

			maint->curwin->main->kbd->x = x;
			if (x)
				maint->curwin->main->kbd->seq[x - 1] = maint->curwin->kbd->seq[x - 1];
		}
		if (m)
			ret = exemac(m);
	}

	if (term == -1)
		return -1;
	else
		return ret;
}

unsigned char **mainenv;

int main(int argc, char **argv, char **envp)
{
	CAP *cap;
	unsigned char *s;
	unsigned char *run;
	SCRN *n;
	int opened = 0;
	int omid;
	int backopt;
	int c;

	joe_locale();

	mainenv = (unsigned char **)envp;
	run = namprt(argv[0]);

	if ((s = (unsigned char *)getenv("LINES")) != NULL)
		sscanf((char *)s, "%d", &lines);
	if ((s = (unsigned char *)getenv("COLUMNS")) != NULL)
		sscanf((char *)s, "%d", &columns);
	if ((s = (unsigned char *)getenv("BAUD")) != NULL)
		sscanf((char *)s, "%u", &Baud);
	if (getenv("DOPADDING"))
		dopadding = 1;
	if (getenv("NOXON"))
		noxon = 1;
	if ((s = (unsigned char *)getenv("JOETERM")) != NULL)
		joeterm = s;

	if (!(cap = getcap(NULL, 9600, NULL, NULL))) {
		fprintf(stderr, "Couldn't load termcap/terminfo entry\n");
		return 1;
	}

	s = (unsigned char *)getenv("HOME");
	if (s) {
		s = vsncpy(NULL, 0, sz(s));
		s = vsncpy(sv(s), sc("/."));
		s = vsncpy(sv(s), sv(run));
		s = vsncpy(sv(s), sc("rc"));
		c = procrc(cap, s);
		if (c == 0)
			goto donerc;
		if (c == 1) {
			unsigned char buf[8];

			fprintf(stderr, "There were errors in '%s'.  Use it anyway?", s);
			fflush(stderr);
			if (fgets((char *)buf, 8, stdin) != NULL &&
			    (buf[0] == 'y' || buf[0] == 'Y'))
				goto donerc;
		}
	}

	vsrm(s);
	s = vsncpy(NULL, 0, sc(JOERC));
	s = vsncpy(sv(s), sv(run));
	s = vsncpy(sv(s), sc("rc"));
	c = procrc(cap, s);
	if (c == 0)
		goto donerc;
	if (c == 1) {
		unsigned char buf[8];

		fprintf(stderr, "There were errors in '%s'.  Use it anyway?", s);
		fflush(stderr);
		if (fgets((char *)buf, 8, stdin) != NULL &&
		    (buf[0] == 'y' || buf[0] == 'Y'))
			goto donerc;
	}

	/* Try built-in joerc */
	vsrm(s);
	s = vsncpy(NULL, 0, sc("*"));
	s = vsncpy(sv(s), sv(run));
	s = vsncpy(sv(s), sc("rc"));
	c = procrc(cap, s);
	if (c == 0)
		goto donerc;
	if (c == 1) {
		unsigned char buf[8];

		fprintf(stderr, "There were errors in '%s'.  Use it anyway?", s);
		fflush(stderr);
		if (fgets((char *)buf, 8, stdin) != NULL &&
		    (buf[0] == 'y' || buf[0] == 'Y'))
			goto donerc;
	}

	fprintf(stderr, "Couldn't open '%s'\n", s);
	return 1;

      donerc:
	help_init(s);
	for (c = 1; argv[c]; ++c) {
		if (argv[c][0] == '-') {
			if (argv[c][1])
				switch (glopt(argv[c] + 1, argv[c + 1], NULL, 1)) {
				case 0:
					fprintf(stderr, "Unknown option '%s'\n", argv[c]);
					break;
				case 1:
					break;
				case 2:
					++c;
					break;
			} else
				idleout = 0;
		}
	}

	if (!(n = nopen(cap)))
		return 1;
	maint = screate(n);
	vmem = vtmp();

	for (c = 1, backopt = 0; argv[c]; ++c)
		if (argv[c][0] == '+' && argv[c][1]) {
			if (!backopt)
				backopt = c;
		} else if (argv[c][0] == '-' && argv[c][1]) {
			if (!backopt)
				backopt = c;
			if (glopt(argv[c] + 1, argv[c + 1], NULL, 0) == 2)
				++c;
		} else {
			B *b = bfind(argv[c]);
			BW *bw = NULL;
			int er = error;

			if (!orphan || !opened) {
				bw = wmktw(maint, b);
				if (er)
					msgnwt(bw->parent, msgs[-er]);
			} else
				b->orphan = 1;
			if (bw) {
				long lnum = 0;

				bw->o.readonly = bw->b->rdonly;
				if (backopt) {
					unsigned char *old_context;

					old_context = bw->o.context;
					while (backopt != c) {
						if (argv[backopt][0] == '+') {
							sscanf((char *)(argv[backopt] + 1), "%ld", &lnum);
							++backopt;
						} else {
							if (glopt(argv[backopt] + 1, argv[backopt + 1], &bw->o, 0) == 2)
								backopt += 2;
							else
								backopt += 1;
							lazy_opts(&bw->o);
						}
					}
					if (old_context != bw->o.context) {
						/* update keymap */
						rmkbd(bw->parent->kbd);
						bw->parent->kbd =
						    mkkbd(kmap_getcontext(bw->o.context, 1));
					}
				}
				bw->b->o = bw->o;
				bw->b->rdonly = bw->o.readonly;
				if (!opened)
					maint->curwin = bw->parent;
				if (er == -1 && bw->o.mnew)
					exemac(bw->o.mnew);
				if (er == 0 && bw->o.mold)
					exemac(bw->o.mold);
				if (lnum > 0)
					pline(bw->cursor, lnum - 1);
			}
			opened = 1;
			backopt = 0;
		}

	if (opened) {
		wshowall(maint);
		omid = mid;
		mid = 1;
		dofollows();
		mid = omid;
	} else {
		BW *bw = wmktw(maint, bfind(US ""));

		if (bw->o.mnew)
			exemac(bw->o.mnew);
	}
	maint->curwin = maint->topwin;

	if (help) {
		help_on(maint);
	}
	if (!nonotice) {
		joe_snprintf_4((char *)msgbuf,JOE_MSGBUFSIZE,
		    "\\i[ Joe's Own Editor v" VERSION
		    " | %s | %s " JUPP_IS_COPYRIGHT_C_BY " ]%s%s\\i",
		    locale_map->name, locale_map->type ? "©" : "(c)",
		    fdefault.hmsg ? " " : "",
		    fdefault.hmsg ? fdefault.hmsg : "");
		msgnw(((BASE *)lastw(maint)->object)->parent, msgbuf);
	}

	edloop(0);
	vclose(vmem);
	nclose(n);
	if (exmsg)
		fprintf(stderr, "\n%s\n", exmsg);
	return 0;
}