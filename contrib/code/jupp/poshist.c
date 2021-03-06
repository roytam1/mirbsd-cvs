/*
 *	Position history
 *	Copyright
 *		(C) 1992 Joseph H. Allen
 *
 *	This file is part of JOE (Joe's Own Editor)
 */
#include "config.h"
#include "types.h"

__RCSID("$MirOS: contrib/code/jupp/poshist.c,v 1.7 2017/12/07 02:10:17 tg Exp $");

#include <stdlib.h>

#include "b.h"
#include "poshist.h"
#include "queue.h"
#include "w.h"

typedef struct pos POS;

struct pos {
	LINK(POS) link;
	P *p;
	W *w;
};

POS pos = { {&pos, &pos}, NULL, NULL };
POS frpos = { {&frpos, &frpos}, NULL, NULL };
POS *curpos = &pos;
int npos = 0;

static void markpos(W *w, P *p)
{
	POS *new = alitem(&frpos, sizeof(POS));

	new->p = NULL;
	pdupown(p, &new->p);
	poffline(new->p);
	new->w = w;
	enqueb(POS, link, &pos, new);
	if (npos == 20) {
		new = pos.link.next;
		prm(new->p);
		demote(POS, link, &frpos, new);
	} else {
		++npos;
	}
}

void afterpos(void)
{
	if (curpos != &pos) {
		demote(POS, link, &pos, curpos);
		curpos = &pos;
	}
}

void aftermove(W *w, P *p)
{
	if (pos.link.prev != &pos && pos.link.prev->w == w && pos.link.prev->p && labs(pos.link.prev->p->line - p->line) < 3) {
		poffline(pset(pos.link.prev->p, p));
	} else {
		markpos(w, p);
	}
}

void windie(W *w)
{
	POS *n;

	for (n = pos.link.prev; n != &pos; n = n->link.prev) {
		if (n->w == w) {
			n->w = NULL;
		}
	}
}

int unextpos(BW *bw)
{
	W *w = bw->parent;

 lp:
	if (curpos->link.next != &pos && curpos != &pos) {
		curpos = curpos->link.next;
		if (!curpos->p || !curpos->w) {
			goto lp;
		}
		if (w->t->curwin == curpos->w && curpos->p->byte == w->t->curwin->object.bw->cursor->byte) {
			goto lp;
		}
		if (w->t->curwin != curpos->w) {
			w->t->curwin = curpos->w;
			if (w->t->curwin->y == -1) {
				wfit(w->t);
			}
		}
		w = w->t->curwin;
		bw = w->object.bw;
		if (bw->cursor->byte != curpos->p->byte) {
			pset(bw->cursor, curpos->p);
		}
		return 0;
	} else {
		return -1;
	}
}

int uprevpos(BW *bw)
{
	W *w = bw->parent;

 lp:
	if (curpos->link.prev != &pos) {
		curpos = curpos->link.prev;
		if (!curpos->p || !curpos->w) {
			goto lp;
		}
		if (w->t->curwin == curpos->w && curpos->p->byte == w->t->curwin->object.bw->cursor->byte) {
			goto lp;
		}
		if (w->t->curwin != curpos->w) {
			w->t->curwin = curpos->w;
			if (w->t->curwin->y == -1) {
				wfit(w->t);
			}
		}
		w = w->t->curwin;
		bw = w->object.bw;
		if (bw->cursor->byte != curpos->p->byte) {
			pset(bw->cursor, curpos->p);
		}
		return 0;
	} else {
		return -1;
	}
}
