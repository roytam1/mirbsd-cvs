/*
 *	Editor engine
 *	Copyright
 *		(C) 1992 Joseph H. Allen
 *
 *	This file is part of JOE (Joe's Own Editor)
 */
#define EXTERN_B_C
#include "config.h"
#include "types.h"

__RCSID("$MirOS: contrib/code/jupp/b.c,v 1.33 2018/01/07 20:32:45 tg Exp $");

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pwd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#ifdef HAVE_TIME_H
#include <time.h>
#endif

#include "b.h"
#include "blocks.h"
#include "main.h"
#include "path.h"
#include "queue.h"
#include "rc.h"
#include "scrn.h"
#include "uerror.h"
#include "undo.h"
#include "utils.h"
#include "va.h"
#include "vfile.h"
#include "vs.h"
#include "charmap.h"
#include "w.h"

#if !HAVE_DECL_CTIME
char *ctime(const time_t *);
#endif
#if !HAVE_DECL_POPEN
FILE *popen(const char *, const char *);
int pclose(FILE *);
#endif

unsigned char stdbuf[stdsiz];

int guesscrlf = 0;
int guessindent = 0;

int error;
int force = 0;
VFILE *vmem;

const unsigned char *msgs[] = {
	UC "No error",
	UC "New File",
	UC "Error reading file",
	UC "Error seeking file",
	UC "Error opening file",
	UC "Error writing file",
	UC "File on disk is newer"
};

/* Get size of gap (amount of free space) */
#define GGAPSZ(hdr) ((hdr)->ehole - (hdr)->hole)

/* Get number of characters in gap buffer */
#define GSIZE(hdr) (SEGSIZ - GGAPSZ(hdr))

/* Get char from buffer (with jumping around the gap) */
#define GCHAR(p) ((p)->ofst >= (p)->hdr->hole ? (p)->ptr[(p)->ofst + GGAPSZ((p)->hdr)] \
					      : (p)->ptr[(p)->ofst])

/* Set position of gap */
static void gstgap(H *hdr, unsigned char *ptr, int ofst)
{
	if (ofst > hdr->hole) {
		mmove(ptr + hdr->hole, ptr + hdr->ehole, ofst - hdr->hole);
		vchanged(ptr);
	} else if (ofst < hdr->hole) {
		mmove(ptr + hdr->ehole - (hdr->hole - ofst), ptr + ofst, hdr->hole - ofst);
		vchanged(ptr);
	}
	hdr->ehole = ofst + hdr->ehole - hdr->hole;
	hdr->hole = ofst;
}

/* Insert a block */
static void ginsm(H *hdr, unsigned char *ptr, int ofst, const unsigned char *blk, int size)
{
	if (ofst != hdr->hole)
		gstgap(hdr, ptr, ofst);
	mmove(ptr + hdr->hole, blk, size);
	hdr->hole += size;
	vchanged(ptr);
}

/* Read block */
static void grmem(H *hdr, unsigned char *ptr, int ofst, unsigned char *blk, int size)
{
	if (ofst < hdr->hole)
		if (size > hdr->hole - ofst) {
			mmove(blk, ptr + ofst, hdr->hole - ofst);
			mmove(blk + hdr->hole - ofst, ptr + hdr->ehole, size - (hdr->hole - ofst));
		} else
			mmove(blk, ptr + ofst, size);
	else
		mmove(blk, ptr + ofst + hdr->ehole - hdr->hole, size);
}


static H nhdrs = { {&nhdrs, &nhdrs}, 0, 0, 0, 0 };
static H ohdrs = { {&ohdrs, &ohdrs}, 0, 0, 0, 0 };

/* Header allocation */
static H *halloc(void)
{
	H *h;

	if (qempty(H, link, &ohdrs)) {
		h = (H *) alitem(&nhdrs, sizeof(H));
		h->seg = my_valloc(vmem, (long) SEGSIZ);
	} else
		h = deque_f(H, link, ohdrs.link.next);
	h->hole = 0;
	h->ehole = SEGSIZ;
	h->nlines = 0;
	izque(H, link, h);
	return h;
}

static void hfree(H *h)
{
	enquef(H, link, &ohdrs, h);
}

static void hfreechn(H *h)
{
	splicef(H, link, &ohdrs, h);
}


static P frptrs = { {&frptrs, &frptrs}, NULL, 0, 0, NULL, 0, 0, 0, 0, 0, 0, NULL };

/* Pointer allocation */
static P *palloc(void)
{
	return alitem(&frptrs, sizeof(P));
}

static void pfree(P *p)
{
	enquef(P, link, &frptrs, p);
}

/* Doubly linked list of buffers and free buffer structures */
static B bufs = { {&bufs, &bufs}, NULL, NULL, NULL, 0, 0, 0, 0, 0, NULL, { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, { NULL, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, 0, 0 }, NULL, NULL, 0, 0, 0, 0, 0, 0 };
static B frebufs = { {&frebufs, &frebufs}, NULL, NULL, NULL, 0, 0, 0, 0, 0, NULL, { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, { NULL, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, 0, 0 }, NULL, NULL, 0, 0, 0, 0, 0, 0 };

B *bnext(void)
{
	B *b;

	do {
		b = bufs.link.prev;
		deque(B, link, &bufs);
		enqueb(B, link, b, &bufs);
	} while (b->internal);
	return b;
}

B *bprev(void)
{
	B *b;

	do {
		b = bufs.link.next;
		deque(B, link, &bufs);
		enquef(B, link, b, &bufs);
	} while (b->internal);
	return b;
}

/* Make a buffer out of a chain */
static B *bmkchn(H *chn, B *prop, long amnt, long nlines)
{
	B *b = alitem(&frebufs, sizeof(B));

	b->undo = undomk(b);
	if (prop)
		b->o = prop->o;
	else
		b->o = pdefault;
	mset(b->marks, 0, sizeof(b->marks));
	b->rdonly = 0;
	b->orphan = 0;
	b->oldcur = NULL;
	b->oldtop = NULL;
	b->backup = 1;
	b->internal = 1;
	b->scratch = 0;
	b->changed = 0;
	b->count = 1;
	b->name = NULL;
	b->er = -3;
	b->bof = palloc();
	izque(P, link, b->bof);
	b->bof->end = 0;
	b->bof->b = b;
	b->bof->owner = NULL;
	b->bof->hdr = chn;
	b->bof->ptr = vlock(vmem, b->bof->hdr->seg);
	b->bof->ofst = 0;
	b->bof->byte = 0;
	b->bof->line = 0;
	b->bof->col = 0;
	b->bof->xcol = 0;
	b->bof->valcol = 1;
	b->eof = pdup(b->bof);
	b->eof->end = 1;
	vunlock(b->eof->ptr);
	b->eof->hdr = chn->link.prev;
	b->eof->ptr = vlock(vmem, b->eof->hdr->seg);
	b->eof->ofst = GSIZE(b->eof->hdr);
	b->eof->byte = amnt;
	b->eof->line = nlines;
	b->eof->valcol = 0;
	b->pid = 0;
	b->out = -1;
	enquef(B, link, &bufs, b);
	pcoalesce(b->bof);
	pcoalesce(b->eof);
	return b;
}

/* Create an empty buffer */
B *bmk(B *prop)
{
	return bmkchn(halloc(), prop, 0L, 0L);
}


extern B *errbuf;

/* Eliminate a buffer */
void brm(B *b)
{
	if (b && !--b->count) {
		if (b->changed)
			abrerr(b->name);
		if (b == errbuf)
			errbuf = NULL;
		if (b->undo)
			undorm(b->undo);
		hfreechn(b->eof->hdr);
		while (!qempty(P, link, b->bof))
			prm(b->bof->link.next);
		prm(b->bof);
		if (b->name)
			free(b->name);
		demote(B, link, &frebufs, b);
	}
}

P *poffline(P *p)
{
	if (p->ptr) {
		vunlock(p->ptr);
		p->ptr = NULL;
	}
	return p;
}

P *ponline(P *p)
{
	if (!p->ptr)
		p->ptr = vlock(vmem, p->hdr->seg);
	return p;
}

B *boffline(B *b)
{
	P *p = b->bof;

	do {
		poffline(p);
	} while ((p = p->link.next) != b->bof);
	return b;
}

B *bonline(B *b)
{
	P *p = b->bof;

	do {
		ponline(p);
	} while ((p = p->link.next) != b->bof);
	return b;
}

P *pdup(P *p)
{
	P *n = palloc();

	n->end = 0;
	n->ptr = NULL;
	n->owner = NULL;
	enquef(P, link, p, n);
	return pset(n, p);
}

P *pdupown(P *p, P **o)
{
	P *n = palloc();

	n->end = 0;
	n->ptr = NULL;
	n->owner = o;
	enquef(P, link, p, n);
	pset(n, p);
	if (*o)
		prm(*o);
	*o = n;
	return n;
}

void prm(P *p)
{
	if (!p)
		return;
	if (p->owner)
		*p->owner = NULL;
	if (p->ptr)
		vunlock(p->ptr);
	pfree(deque_f(P, link, p));
}

P *pset(P *n, P *p)
{
	if (n != p) {
		n->b = p->b;
		n->ofst = p->ofst;
		n->hdr = p->hdr;
		if (n->ptr)
			vunlock(n->ptr);
		if (p->ptr) {
			n->ptr = p->ptr;
			vupcount(n->ptr);
		} else
			n->ptr = vlock(vmem, n->hdr->seg);
		n->byte = p->byte;
		n->line = p->line;
		n->col = p->col;
		n->valcol = p->valcol;
	}
	return n;
}

P *p_goto_bof(P *p)
{
	return pset(p, p->b->bof);
}

P *p_goto_eof(P *p)
{
	return pset(p, p->b->eof);
}

/* is p at the beginning of file? */
int pisbof(P *p)
{
	return p->hdr == p->b->bof->hdr && !p->ofst;
}

/* is p at the end of file? */
int piseof(P *p)
{
	return p->ofst == GSIZE(p->hdr);
}

/* is p at the end of line? */
int piseol(P *p)
{
	int c;

	if (piseof(p))
		return 1;
	c = brc(p);
	if (c == '\n')
		return 1;
	if (p->b->o.crlf)
		if (c == '\r') {
			P *q = pdup(p);

			pfwrd(q, 1L);
			if (pgetb(q) == '\n') {
				prm(q);
				return 1;
			} else
				prm(q);
		}
	return 0;
}

/* is p at the beginning of line? */
int pisbol(P *p)
{
	int c;

	if (pisbof(p))
		return 1;
	c = prgetb(p);
	pgetb(p);
	return c == '\n';
}

/* is p at the beginning of word? */
int pisbow(P *p)
{
	P *q = pdup(p);
	int c = brc(p);
	int d = prgetc(q);

	prm(q);
	if (joe_isalnux(p->b->o.charmap,c) && (!joe_isalnux(p->b->o.charmap,d) || pisbof(p)))
		return 1;
	else
		return 0;
}

/* is p at the end of word? */
int piseow(P *p)
{
	P *q = pdup(p);
	int d = brc(q);
	int c = prgetc(q);

	prm(q);
	if (joe_isalnux(p->b->o.charmap,c) && (!joe_isalnux(p->b->o.charmap,d) || piseof(p)))
		return 1;
	else
		return 0;
}

/* is p on the blank line (ie. full of spaces/tabs)? */
int pisblank(P *p)
{
	P *q = pdup(p);

	p_goto_bol(q);
	while (joe_isblank(p->b->o.charmap,brc(q)))
		pgetb(q);
	if (piseol(q)) {
		prm(q);
		return 1;
	} else {
		prm(q);
		return 0;
	}
}

/* is p at end of line or spaces followed by end of line? */
int piseolblank(P *p)
{
	P *q = pdup(p);

	while (joe_isblank(p->b->o.charmap,brc(q)))
		pgetb(q);
	if (piseol(q)) {
		prm(q);
		return 1;
	} else {
		prm(q);
		return 0;
	}
}

/* return column of first nonblank character */
long pisindent(P *p)
{
	P *q = pdup(p);
	long col;

	p_goto_bol(q);
	while (joe_isblank(p->b->o.charmap,brc(q)))
		pgetc(q);
	col = q->col;
	prm(q);
	return col;
}

/* return true if all characters to left of cursor match c */

int pispure(P *p,int c)
{
	P *q = pdup(p);
	p_goto_bol(q);
	while (q->byte!=p->byte)
		if (pgetc(q)!=c) {
			prm(q);
			return 0;
		}
	prm(q);
	return 1;
}

int pnext(P *p)
{
	if (p->hdr == p->b->eof->hdr) {
		p->ofst = GSIZE(p->hdr);
		return 0;
	}
	p->hdr = p->hdr->link.next;
	p->ofst = 0;
	vunlock(p->ptr);
	p->ptr = vlock(vmem, p->hdr->seg);
	return 1;
}

int pprev(P *p)
{
	if (p->hdr == p->b->bof->hdr) {
		p->ofst = 0;
		return 0;
	}
	p->hdr = p->hdr->link.prev;
	p->ofst = GSIZE(p->hdr);
	vunlock(p->ptr);
	p->ptr = vlock(vmem, p->hdr->seg);
	return 1;
}

/* return current byte and move p to the next byte.  column will be unchanged. */
int pgetb(P *p)
{
	unsigned char c;

	if (p->ofst == GSIZE(p->hdr))
		return NO_MORE_DATA;
	c = GCHAR(p);
	if (++p->ofst == GSIZE(p->hdr))
		pnext(p);
	++p->byte;
	if (c == '\n') {
		++(p->line);
		p->col = 0;
		p->valcol = 1;
	} else if (p->b->o.crlf && c == '\r') {
		if (brc(p) == '\n')
			return pgetb(p);
		else
			p->valcol = 0;
	} else {
		p->valcol = 0;
	}
	return c;
}

/* return current character and move p to the next character.  column will be updated if it was valid. */
int pgetc(P *p)
{
	if (p->b->o.charmap->type) {
		int c, n, oc, wid, val;

		val = p->valcol;	/* Remember if column number was valid */
		c = pgetb(p);		/* Get first byte */

		if (c==NO_MORE_DATA)
			return c;

		oc = c;			/* Save in case of invalid sequences */

		if ((c&0x80)==0x00) {        /* One byte */
			n = 0;
		} else if ((c&0xE0)==0xC0) { /* Two bytes */
			n = 1;
			c &= 0x1F;
		} else if ((c&0xF0)==0xE0) { /* Three bytes */
			n = 2;
			c &= 0x0F;
		} else if ((c&0xF8)==0xF0) { /* Four bytes */
			n = 3;
			c &= 0x07;
		} else if ((c&0xFC)==0xF8) { /* Five bytes */
			n = 4;
			c &= 0x03;
		} else if ((c&0xFE)==0xFC) { /* Six bytes */
			n = 5;
			c &= 0x01;
		} else { /* 128-191, 254, 255: Not a valid UTF-8 start character */
 eilseq:
			n = 0;
			c = 0x80000000 | (oc & 0xFF);
		}

		if (n) {
			int d, m = n;	/* Save in case of invalid sequences */

			do {
				d = brc(p);
				if (d == NO_MORE_DATA || (d&0xC0)!=0x80)
					break;
				pgetb(p);
				c = ((c<<6)|(d&0x3F));
			} while (--n);
			if (n) { /* There was a bad UTF-8 sequence */
				pbkwd(p, m - n);
				goto eilseq;
			} else if (val)
				wid = joe_wcwidth(c);
		} else {
			wid = 1;
		}

		if (val) { /* Update column no. if it was valid to start with */
			p->valcol = 1;
			if (c=='\t')
				p->col += (p->b->o.tab) - (p->col) % (p->b->o.tab);
			else if (c=='\n')
				p->col = 0;
			else
				p->col += wid;
		}

		return c;
	} else {
		unsigned char c;

		if (p->ofst == GSIZE(p->hdr))
			return NO_MORE_DATA;
		c = GCHAR(p);
		if (++p->ofst == GSIZE(p->hdr))
			pnext(p);
		++p->byte;

		if (c == '\n') {
			++(p->line);
			p->col = 0;
			p->valcol = 1;
		} else if (p->b->o.crlf && c == '\r') {
			if (brc(p) == '\n')
				return pgetc(p);
			else
				++p->col;
		} else {
			if (c == '\t')
				p->col += (p->b->o.tab) - (p->col) % (p->b->o.tab);
			else
				++(p->col);
		}
		return c;
	}
}

/* move p n characters forward */
P *pfwrd(P *p, long n)
{
	if (!n)
		return p;
	p->valcol = 0;
	do {
		if (p->ofst == GSIZE(p->hdr))
			do {
				if (!p->ofst) {
					p->byte += GSIZE(p->hdr);
					n -= GSIZE(p->hdr);
					p->line += p->hdr->nlines;
				}
				if (!pnext(p))
					return NULL;
			} while (n > GSIZE(p->hdr));
		if (GCHAR(p) == '\n')
			++p->line;
		++p->byte;
		++p->ofst;
	} while (--n);
	if (p->ofst == GSIZE(p->hdr))
		pnext(p);
	return p;
}

/* move p to the previous byte: does not take into account -crlf mode */
static int prgetb1(P *p)
{
	unsigned char c;

	if (!p->ofst)
		if (!pprev(p))
			return NO_MORE_DATA;
	--p->ofst;
	c = GCHAR(p);
	--p->byte;
	p->valcol = 0;
	if (c == '\n')
		--p->line;
	return c;
}

/* move p to the previous byte */
int prgetb(P *p)
{
	int c = prgetb1(p);

	if (p->b->o.crlf && c == '\n') {
		c = prgetb1(p);
		if (c == '\r')
			return '\n';
		if (c != NO_MORE_DATA)
			pgetb(p);
		c = '\n';
	}
	return c;
}

/* move p to the previous character (try to keep col updated) */
int
prgetc(P *p)
{
	P *q, *r;

	if (!p->b->o.charmap->type || pisbol(p))
		return (prgetb(p));

	q = pdup(p);
	p_goto_bol(q);
	r = pdup(q);
	while (q->byte < p->byte) {
		pset(r, q);
		pgetc(q);
	}
	pset(p, r);
	prm(r);
	prm(q);
	return (brch(p));
}

/* move p n characters backwards */
P *pbkwd(P *p, long n)
{
	if (!n)
		return p;
	p->valcol = 0;
	do {
		if (!p->ofst)
			do {
				if (p->ofst) {
					p->byte -= p->ofst;
					n -= p->ofst;
					p->line -= p->hdr->nlines;
				}
				if (!pprev(p))
					return NULL;
			} while (n > GSIZE(p->hdr));
		--p->ofst;
		--p->byte;
		if (GCHAR(p) == '\n')
			--p->line;
	} while (--n);
	return p;
}

/* move p n characters forwards/backwards according to loc */
P *pgoto(P *p, long loc)
{
	if (loc > p->byte)
		pfwrd(p, loc - p->byte);
	else if (loc < p->byte)
		pbkwd(p, p->byte - loc);
	return p;
}

/* make p->col valid */
P *pfcol(P *p)
{
	long pos = p->byte;

	p_goto_bol(p);
	while (p->byte < pos)
		pgetc(p);
	return p;
}

/* move p to the beginning of line */
P *p_goto_bol(P *p)
{
	if (pprevl(p))
		pgetb(p);
	p->col = 0;
	p->valcol = 1;
	return p;
}

/* move p to the indentation point */
P *p_goto_indent(P *p, int c)
{
	int d;
	p_goto_bol(p);
	while ((d=brc(p)), d==c || ((c==' ' || c=='\t') && (d==' ' || d=='\t')))
		pgetc(p);
	return p;
}

/* move p to the end of line */
P *p_goto_eol(P *p)
{
	if (p->b->o.crlf || p->b->o.charmap->type)
		while (!piseol(p))
			pgetc(p);
	else
		while (p->ofst != GSIZE(p->hdr)) {
			unsigned char c;

			c = GCHAR(p);
			if (c == '\n')
				break;
			else {
				++p->byte;
				++p->ofst;
				if (c == '\t')
					p->col += p->b->o.tab - p->col % p->b->o.tab;
				else
					++p->col;
				if (p->ofst == GSIZE(p->hdr))
					pnext(p);
			}
		}
	return p;
}

/* move p to the beginning of next line */
P *pnextl(P *p)
{
	int c;

	do {
		if (p->ofst == GSIZE(p->hdr))
			do {
				p->byte += GSIZE(p->hdr) - p->ofst;
				if (!pnext(p))
					return NULL;
			} while (!p->hdr->nlines);
		c = GCHAR(p);
		++p->byte;
		++p->ofst;
	} while (c != '\n');
	++p->line;
	p->col = 0;
	p->valcol = 1;
	if (p->ofst == GSIZE(p->hdr))
		pnext(p);
	return p;
}

/* move p to the end of previous line */
P *pprevl(P *p)
{
	int c;

	p->valcol = 0;
	do {
		if (!p->ofst)
			do {
				p->byte -= p->ofst;
				if (!pprev(p))
					return NULL;
			} while (!p->hdr->nlines);
		--p->ofst;
		--p->byte;
		c = GCHAR(p);
	} while (c != '\n');
	--p->line;
	if (p->b->o.crlf && c == '\n') {
		int k = prgetb1(p);

		if (k != '\r' && k != NO_MORE_DATA)
			pgetb(p);
	}
	return p;
}

/* move p to the given 'line' line */
P *pline(P *p, long line)
{
	if (line > p->b->eof->line) {
		pset(p, p->b->eof);
		return p;
	}
	if (line < labs(p->line - line))
		pset(p, p->b->bof);
	if (labs(p->b->eof->line - line) < labs(p->line - line))
		pset(p, p->b->eof);
	if (p->line == line) {
		p_goto_bol(p);
		return p;
	}
	while (line > p->line)
		pnextl(p);
	if (line < p->line) {
		while (line < p->line)
			pprevl(p);
		p_goto_bol(p);
	}
	return p;
}

/* move p to the given 'goalcol' column */
/* lands at exact column or on character which would cause us to go past goalcol */
P *pcol(P *p, long goalcol)
{
	p_goto_bol(p);
	if(p->b->o.charmap->type) {
		do {
			int c;
			int wid;

			c = brch(p);

			if (c == NO_MORE_DATA)
				break;

			if (c == '\n')
				break;

			if (p->b->o.crlf && c == '\r' && piseol(p))
				break;

			if (c == '\t')
				wid = p->b->o.tab - p->col % p->b->o.tab;
			else
				wid = joe_wcwidth(c);

			if (p->col + wid > goalcol)
				break;

			pgetc(p);
		} while (p->col != goalcol);
	} else {
		do {
			unsigned char c;
			int wid;

			if (p->ofst == GSIZE(p->hdr))
				break;
			c = GCHAR(p);
			if (c == '\n')
				break;
			if (p->b->o.crlf && c == '\r' && piseol(p))
				break;
			if (c == '\t')
				wid = p->b->o.tab - p->col % p->b->o.tab;
			else
				wid = 1;
			if (p->col + wid > goalcol)
				break;
			if (++p->ofst == GSIZE(p->hdr))
				pnext(p);
			++p->byte;
			p->col += wid;
		} while (p->col != goalcol);
	}
	return p;
}

/* Move to goal column, then skip backwards to just after first non-whitespace character */
P *pcolwse(P *p, long goalcol)
{
	int c;

	pcol(p, goalcol);
	do {
		c = prgetc(p);
	} while (c == ' ' || c == '\t');
	if (c != NO_MORE_DATA)
		pgetc(p);
	return p;
}

/* Move p to goalcol: stops after first character which equals or exceeds goal col (unlike
   pcol() which will stops before character which would exceed goal col) */
P *pcoli(P *p, long goalcol)
{
	p_goto_bol(p);
	if (p->b->o.charmap->type) {
		while (p->col < goalcol) {
			int c;
			c = brc(p);

			if (c == NO_MORE_DATA)
				break;

			if (c == '\n')
				break;

			if (p->b->o.crlf && c=='\r' && piseol(p))
				break;

			pgetc(p);
		}
	} else {
		while (p->col < goalcol) {
			unsigned char c;

			if (p->ofst == GSIZE(p->hdr))
				break;
			c = GCHAR(p);
			if (c == '\n')
				break;

			if (p->b->o.crlf && c == '\r' && piseol(p))
				break;

			if (c == '\t')
				p->col += p->b->o.tab - p->col % p->b->o.tab;
			else
				++p->col;
			if (++p->ofst == GSIZE(p->hdr))
				pnext(p);
			++p->byte;
		}
	}
	return p;
}

/* fill space between curent column and 'to' column with tabs/spaces */
void pfill(P *p, long to, int usetabs)
{
	if (usetabs=='\t')
		while (piscol(p) < to)
			if (p->col + p->b->o.tab - p->col % p->b->o.tab <= to) {
				binsc(p, '\t');
				pgetc(p);
			} else {
				binsc(p, ' ');
				pgetc(p);
			}
	else
		while (piscol(p) < to) {
			binsc(p, usetabs);
			pgetc(p);
		}
}

/* delete sequence of whitespaces - backwards */
void pbackws(P *p)
{
	int c;
	P *q = pdup(p);

	do {
		c = prgetc(q);
	} while (c == ' ' || c == '\t');
	if (c != NO_MORE_DATA)
		pgetc(q);
	bdel(q, p);
	prm(q);
}

static int frgetc(P *p)
{
	if (!p->ofst)
		pprev(p);
	--p->ofst;
	return GCHAR(p);
}

static void ffwrd(P *p, int n)
{
	while (n > GSIZE(p->hdr) - p->ofst) {
		n -= GSIZE(p->hdr) - p->ofst;
		if (!pnext(p))
			return;
	}
	if ((p->ofst += n) == GSIZE(p->hdr))
		pnext(p);
}

/* forward find pattern 's' in text pointed by 'p' (Boyer-Moore algorithm) */
static P *ffind(P *p, unsigned char *s, int len)
{
	long amnt = p->b->eof->byte - p->byte;
	int x;
	unsigned char table[256], c;

	if (len > amnt)
		return NULL;
	if (!len)
		return p;
	p->valcol = 0;
	mset(table, 255, 256);
	for (x = 0; x != len - 1; ++x)
		table[s[x]] = x;
	ffwrd(p, len);
	amnt -= len;
	x = len;
	do {
		if ((c = frgetc(p)) != s[--x]) {
			if (table[c] == 255) {
				ffwrd(p, len + 1);
				amnt -= x + 1;
			} else if (x <= table[c]) {
				ffwrd(p, len - x + 1);
				--amnt;
			} else {
				ffwrd(p, len - table[c]);
				amnt -= x - table[c];
			}
			if (amnt < 0)
				return NULL;
			else
				x = len;
		}
	} while (x);
	return p;
}

/* forward find (case insensitive) pattern 's' in text pointed by 'p' (Boyer-Moore algorithm) */
static P *fifind(P *p, unsigned char *s, int len)
{
	long amnt = p->b->eof->byte - p->byte;
	int x;
	struct charmap *map = p->b->o.charmap;
	unsigned char table[256], c;

	if (len > amnt)
		return NULL;
	if (!len)
		return p;
	p->valcol = 0;
	mset(table, 255, 256);
	for (x = 0; x != len - 1; ++x)
		table[s[x]] = x;
	ffwrd(p, len);
	amnt -= len;
	x = len;
	do {
		if ((c = joe_tolower(map,frgetc(p))) != s[--x]) {
			if (table[c] == 255) {
				ffwrd(p, len + 1);
				amnt -= x + 1;
			} else if (x <= table[c]) {
				ffwrd(p, len - x + 1);
				--amnt;
			} else {
				ffwrd(p, len - table[c]);
				amnt -= x - table[c];
			}
			if (amnt < 0)
				return NULL;
			else
				x = len;
		}
	} while (x);
	return p;
}

/* move cursor p to q's position and set p's col, line, ofst, byte etc. accordingly */
/* same as rgetto() but p is before q */
static P *getto(P *p, P *q)
{
	while (p->hdr != q->hdr || p->ofst != q->ofst) {
		if (GCHAR(p) == '\n')
			++p->line;
		++p->byte;
		++p->ofst;
		if (p->ofst == GSIZE(p->hdr))
			pnext(p);
		while (!p->ofst && p->hdr != q->hdr) {
			p->byte += GSIZE(p->hdr);
			p->line += p->hdr->nlines;
			pnext(p);
		}
	}
	return p;
}

/* find forward substring s in text pointed by p and set p after found substring */
P *pfind(P *p, unsigned char *s, int len)
{
	P *q = pdup(p);

	if (ffind(q, s, len)) {
		getto(p, q);
		prm(q);
		return p;
	} else {
		prm(q);
		return NULL;
	}
}

/* same as pfind() but case insensitive */
P *pifind(P *p, unsigned char *s, int len)
{
	P *q = pdup(p);

	if (fifind(q, s, len)) {
		getto(p, q);
		prm(q);
		return p;
	} else {
		prm(q);
		return NULL;
	}
}

static void fbkwd(P *p, int n)
{
	while (n > p->ofst) {
		n -= p->ofst;
		if (!pprev(p))
			return;
	}
	if (p->ofst >= n)
		p->ofst -= n;
	else
		p->ofst = 0;
}

static int fpgetc(P *p)
{
	int c;

	if (p->ofst == GSIZE(p->hdr))
		return NO_MORE_DATA;
	c = GCHAR(p);
	if (++p->ofst == GSIZE(p->hdr))
		pnext(p);
	return c;
}

/* backward find pattern 's' in text pointed by 'p' (Boyer-Moore algorithm) */
static P *frfind(P *p, unsigned char *s, int len)
{
	long amnt = p->byte;
	int x;
	unsigned char table[256], c;

	if (len > p->b->eof->byte - p->byte) {
		x = len - (p->b->eof->byte - p->byte);
		if (amnt < x)
			return NULL;
		amnt -= x;
		fbkwd(p, x);
	}
	if (!len)
		return p;
	p->valcol = 0;
	mset(table, 255, 256);
	for (x = len; --x; table[s[x]] = len - x - 1) ;
	x = 0;
	do {
		if ((c = fpgetc(p)) != s[x++]) {
			if (table[c] == 255) {
				fbkwd(p, len + 1);
				amnt -= len - x + 1;
			} else if (len - table[c] <= x) {
				fbkwd(p, x + 1);
				--amnt;
			} else {
				fbkwd(p, len - table[c]);
				amnt -= len - table[c] - x;
			}
			if (amnt < 0)
				return NULL;
			else
				x = 0;
		}
	} while (x != len);
	fbkwd(p, len);
	return p;
}

/* backward find (case insensitive) pattern 's' in text pointed by 'p' (Boyer-Moore algorithm) */
static P *frifind(P *p, unsigned char *s, int len)
{
	long amnt = p->byte;
	int x;
	unsigned char table[256], c;
	struct charmap *map = p->b->o.charmap;

	if (len > p->b->eof->byte - p->byte) {
		x = len - (p->b->eof->byte - p->byte);
		if (amnt < x)
			return NULL;
		amnt -= x;
		fbkwd(p, x);
	}
	if (!len)
		return p;
	p->valcol = 0;
	mset(table, 255, 256);
	for (x = len; --x; table[s[x]] = len - x - 1) ;
	x = 0;
	do {
		if ((c = joe_tolower(map,fpgetc(p))) != s[x++]) {
			if (table[c] == 255) {
				fbkwd(p, len + 1);
				amnt -= len - x + 1;
			} else if (len - table[c] <= x) {
				fbkwd(p, x + 1);
				--amnt;
			} else {
				fbkwd(p, len - table[c]);
				amnt -= len - table[c] - x;
			}
			if (amnt < 0)
				return NULL;
			else
				x = 0;
		}
	} while (x != len);
	fbkwd(p, len);
	return p;
}

/* move cursor p to q's position and set p's col, line, ofst, byte etc. accordingly */
/* same as getto() but q is before p */
static P *rgetto(P *p, P *q)
{
	while (p->hdr != q->hdr || p->ofst != q->ofst) {
		if (!p->ofst)
			do {
				if (p->ofst) {
					p->byte -= p->ofst;
					p->line -= p->hdr->nlines;
				}
				pprev(p);
			} while (p->hdr != q->hdr);
		--p->ofst;
		--p->byte;
		if (GCHAR(p) == '\n')
			--p->line;
	}
	return p;
}

/* find backward substring s in text pointed by p and set p on the first of found substring */
P *prfind(P *p, unsigned char *s, int len)
{
	P *q = pdup(p);

	if (frfind(q, s, len)) {
		rgetto(p, q);
		prm(q);
		return p;
	} else {
		prm(q);
		return NULL;
	}
}

/* same as prfind() but case insensitive */
P *prifind(P *p, unsigned char *s, int len)
{
	P *q = pdup(p);

	if (frifind(q, s, len)) {
		rgetto(p, q);
		prm(q);
		return p;
	} else {
		prm(q);
		return NULL;
	}
}

/* copy text between 'from' and 'to' into new buffer */
B *bcpy(P *from, P *to)
{
	H anchor, *l;
	unsigned char *ptr;
	P *q;

	if (from->byte >= to->byte)
		return bmk(from->b);

	q = pdup(from);
	izque(H, link, &anchor);

	if (q->hdr == to->hdr) {
		l = halloc();
		ptr = vlock(vmem, l->seg);
		if (q->ofst != q->hdr->hole)
			gstgap(q->hdr, q->ptr, q->ofst);
		l->nlines = mcnt(q->ptr + q->hdr->ehole, '\n', l->hole = to->ofst - q->ofst);
		mmove(ptr, q->ptr + q->hdr->ehole, l->hole);
		vchanged(ptr);
		vunlock(ptr);
		enqueb(H, link, &anchor, l);
	} else {
		l = halloc();
		ptr = vlock(vmem, l->seg);
		if (q->ofst != q->hdr->hole)
			gstgap(q->hdr, q->ptr, q->ofst);
		l->nlines = mcnt(q->ptr + q->hdr->ehole, '\n', l->hole = SEGSIZ - q->hdr->ehole);
		mmove(ptr, q->ptr + q->hdr->ehole, l->hole);
		vchanged(ptr);
		vunlock(ptr);
		enqueb(H, link, &anchor, l);
		pnext(q);
		while (q->hdr != to->hdr) {
			l = halloc();
			ptr = vlock(vmem, l->seg);
			l->nlines = q->hdr->nlines;
			mmove(ptr, q->ptr, q->hdr->hole);
			mmove(ptr + q->hdr->hole, q->ptr + q->hdr->ehole, SEGSIZ - q->hdr->ehole);
			l->hole = GSIZE(q->hdr);
			vchanged(ptr);
			vunlock(ptr);
			enqueb(H, link, &anchor, l);
			pnext(q);
		}
		if (to->ofst) {
			l = halloc();
			ptr = vlock(vmem, l->seg);
			if (to->ofst != to->hdr->hole)
				gstgap(to->hdr, to->ptr, to->ofst);
			l->nlines = mcnt(to->ptr, '\n', to->ofst);
			mmove(ptr, to->ptr, l->hole = to->ofst);
			vchanged(ptr);
			vunlock(ptr);
			enqueb(H, link, &anchor, l);
		}
	}

	l = anchor.link.next;
	deque(H, link, &anchor);
	prm(q);

	return bmkchn(l, from->b, to->byte - from->byte, to->line - from->line);
}

/* Coalesce small blocks into a single larger one */
void pcoalesce(P *p)
{
	if (p->hdr != p->b->eof->hdr && GSIZE(p->hdr) + GSIZE(p->hdr->link.next) <= SEGSIZ - SEGSIZ / 4) {
		H *hdr = p->hdr->link.next;
		unsigned char *ptr = vlock(vmem, hdr->seg);
		int osize = GSIZE(p->hdr);
		int size = GSIZE(hdr);
		P *q;

		gstgap(hdr, ptr, size);
		ginsm(p->hdr, p->ptr, GSIZE(p->hdr), ptr, size);
		p->hdr->nlines += hdr->nlines;
		vunlock(ptr);
		hfree(deque_f(H, link, hdr));
		for (q = p->link.next; q != p; q = q->link.next)
			if (q->hdr == hdr) {
				q->hdr = p->hdr;
				if (q->ptr) {
					vunlock(q->ptr);
					q->ptr = vlock(vmem, q->hdr->seg);
				}
				q->ofst += osize;
			}
	}
	if (p->hdr != p->b->bof->hdr && GSIZE(p->hdr) + GSIZE(p->hdr->link.prev) <= SEGSIZ - SEGSIZ / 4) {
		H *hdr = p->hdr->link.prev;
		unsigned char *ptr = vlock(vmem, hdr->seg);
		int size = GSIZE(hdr);
		P *q;

		gstgap(hdr, ptr, size);
		ginsm(p->hdr, p->ptr, 0, ptr, size);
		p->hdr->nlines += hdr->nlines;
		vunlock(ptr);
		hfree(deque_f(H, link, hdr));
		p->ofst += size;
		for (q = p->link.next; q != p; q = q->link.next)
			if (q->hdr == hdr) {
				q->hdr = p->hdr;
				if (q->ptr)
					vunlock(q->ptr);
				q->ptr = vlock(vmem, q->hdr->seg);
			} else if (q->hdr == p->hdr)
				q->ofst += size;
	}
}

/* Delete the text between two pointers from a buffer and return it in a new
 * buffer.
 *
 * This routine calls these functions:
 *  gstgap	- to position gaps
 *  halloc	- to allocate new header/segment pairs
 *  vlock	- virtual memory routines
 *  vunlock
 *  vchanged
 *  vupcount
 *  mcnt	- to count NLs
 *  snip	- queue routines
 *  enqueb
 *  splicef
 *  scrdel	- to tell screen update to scroll when NLs are deleted
 *  bmkchn	- to make a buffer out of a chain
 */

/* This is only to be used for bdel() */
static B *bcut(P *from, P *to)
{
	H *h,			/* The deleted text */
	*i;
	unsigned char *ptr;
	P *p;
	long nlines;		/* No. EOLs to delete */
	long amnt;		/* No. bytes to delete */
	int toamnt;		/* Amount to delete from segment in 'to' */
	int bofmove = 0;	/* Set if bof got deleted */

	if (!(amnt = to->byte - from->byte))
		return NULL;	/* ...nothing to delete */

	nlines = to->line - from->line;

	if (from->hdr == to->hdr) {	/* Delete is within a single segment */
		/* Move gap to deletion point */
		if (from->ofst != from->hdr->hole)
			gstgap(from->hdr, from->ptr, from->ofst);

		/* Store the deleted text */
		h = halloc();
		ptr = vlock(vmem, h->seg);
		mmove(ptr, from->ptr + from->hdr->ehole, (int) amnt);
		h->hole = amnt;
		h->nlines = nlines;
		vchanged(ptr);
		vunlock(ptr);

		/* Delete */
		from->hdr->ehole += amnt;
		from->hdr->nlines -= nlines;

		toamnt = amnt;
	} else {		/* Delete crosses segments */
		H *a;

		if ((toamnt = to->ofst) != 0) {
			/* Delete beginning of to */
			/* Move gap to deletion point */
			/* To could be deleted if it's at the end of the file */
			if (to->ofst != to->hdr->hole)
				gstgap(to->hdr, to->ptr, to->ofst);

			/* Save deleted text */
			i = halloc();
			ptr = vlock(vmem, i->seg);
			mmove(ptr, to->ptr, to->hdr->hole);
			i->hole = to->hdr->hole;
			i->nlines = mcnt(to->ptr, '\n', to->hdr->hole);
			vchanged(ptr);
			vunlock(ptr);

			/* Delete */
			to->hdr->nlines -= i->nlines;
			to->hdr->hole = 0;
		} else
			i = 0;

		/* Delete end of from */
		if (!from->ofst) {
			/* ... unless from needs to be deleted too */
			a = from->hdr->link.prev;
			h = NULL;
			if (a == from->b->eof->hdr)
				bofmove = 1;
		} else {
			a = from->hdr;
			/* Move gap to deletion point */
			if (from->ofst != from->hdr->hole)
				gstgap(from->hdr, from->ptr, from->ofst);

			/* Save deleted text */
			h = halloc();
			ptr = vlock(vmem, h->seg);
			mmove(ptr, from->ptr + from->hdr->ehole, SEGSIZ - from->hdr->ehole);
			h->hole = SEGSIZ - from->hdr->ehole;
			h->nlines = mcnt(ptr, '\n', h->hole);
			vchanged(ptr);
			vunlock(ptr);

			/* Delete */
			from->hdr->nlines -= h->nlines;
			from->hdr->ehole = SEGSIZ;
		}

		/* Make from point to header/segment of to */
		from->hdr = to->hdr;
		vunlock(from->ptr);
		from->ptr = to->ptr;
		vupcount(to->ptr);
		from->ofst = 0;

		/* Delete headers/segments between a and to->hdr (if there are any) */
		if (a->link.next != to->hdr)
			if (!h) {
				h = snip(H, link, a->link.next, to->hdr->link.prev);
				if (i)
					enqueb(H, link, h, i);
			} else {
				splicef(H, link, h, snip(H, link, a->link.next, to->hdr->link.prev));
				if (i)
					enqueb(H, link, h, i);
		} else if (!h)
			h = i;
		else if (i)
			enqueb(H, link, h, i);
	}

	/* If to is empty, then it must have been at the end of the file.  If
	   the file did not become empty, delete to */
	if (!GSIZE(to->hdr) && from->byte) {
		H *ph = from->hdr->link.prev;

		hfree(deque_f(H, link, from->hdr));
		vunlock(from->ptr);
		from->hdr = ph;
		from->ptr = vlock(vmem, from->hdr->seg);
		from->ofst = GSIZE(ph);
		vunlock(from->b->eof->ptr);
		from->b->eof->ptr = from->ptr;
		vupcount(from->ptr);
		from->b->eof->hdr = from->hdr;
		from->b->eof->ofst = from->ofst;
	}

	/* The deletion is now done */

	/* Scroll if necessary */

	if (bofmove)
		pset(from->b->bof, from);
	if (nlines && !pisbol(from)) {
		scrdel(from->b, from->line, nlines, 1);
		delerr(from->b->name, from->line, nlines);
	} else {
		scrdel(from->b, from->line, nlines, 0);
		delerr(from->b->name, from->line, nlines);
	}

	/* Fix pointers */

	for (p = from->link.next; p != from; p = p->link.next)
		if (p->line == from->line && p->byte > from->byte)
			p->valcol = 0;
	for (p = from->link.next; p != from; p = p->link.next) {
		if (p->byte >= from->byte) {
			if (p->byte <= from->byte + amnt) {
				if (p->ptr) {
					pset(p, from);
				} else {
					poffline(pset(p, from));
				}
			} else {
				if (p->hdr == to->hdr)
					p->ofst -= toamnt;
				p->byte -= amnt;
				p->line -= nlines;
			}
		}
	}

	pcoalesce(from);

	/* Make buffer out of deleted text and return it */
	return bmkchn(h, from->b, amnt, nlines);
}

void bdel(P *from, P *to)
{
	if (to->byte - from->byte) {
		B *b = bcut(from, to);

		if (from->b->undo)
			undodel(from->b->undo, from->byte, b);
		else
			brm(b);
		from->b->changed = 1;
	}
}

/* Split a block at p's ofst */
/* p is placed in the new block such that it points to the same text but with
 * p->ofst==0
 */
static void bsplit(P *p)
{
	if (p->ofst) {
		H *hdr;
		unsigned char *ptr;
		P *pp;

		hdr = halloc();
		ptr = vlock(vmem, hdr->seg);

		if (p->ofst != p->hdr->hole)
			gstgap(p->hdr, p->ptr, p->ofst);
		mmove(ptr, p->ptr + p->hdr->ehole, SEGSIZ - p->hdr->ehole);
		hdr->hole = SEGSIZ - p->hdr->ehole;
		hdr->nlines = mcnt(ptr, '\n', hdr->hole);
		p->hdr->nlines -= hdr->nlines;
		vchanged(ptr);
		p->hdr->ehole = SEGSIZ;

		enquef(H, link, p->hdr, hdr);

		vunlock(p->ptr);

		for (pp = p->link.next; pp != p; pp = pp->link.next)
			if (pp->hdr == p->hdr && pp->ofst >= p->ofst) {
				pp->hdr = hdr;
				if (pp->ptr) {
					vunlock(pp->ptr);
					pp->ptr = ptr;
					vupcount(ptr);
				}
				pp->ofst -= p->ofst;
			}

		p->ptr = ptr;
		p->hdr = hdr;
		p->ofst = 0;
	}
}

/* Make a chain out of a block of memory (the block must not be empty) */
static H *bldchn(const unsigned char *blk, int size, long *nlines)
{
	H anchor, *l;

	*nlines = 0;
	izque(H, link, &anchor);
	do {
		unsigned char *ptr;
		int amnt;

		ptr = vlock(vmem, (l = halloc())->seg);
		if (size > SEGSIZ)
			amnt = SEGSIZ;
		else
			amnt = size;
		mmove(ptr, blk, amnt);
		l->hole = amnt;
		l->ehole = SEGSIZ;
		(*nlines) += (l->nlines = mcnt(ptr, '\n', amnt));
		vchanged(ptr);
		vunlock(ptr);
		enqueb(H, link, &anchor, l);
		blk += amnt;
		size -= amnt;
	} while (size);
	l = anchor.link.next;
	deque(H, link, &anchor);
#ifdef CLANG_SCAN_BUILD
	/* this can only be fixed properly by using ({ … }) in queue.h */
	ITEM = NULL;
	QUEUE = NULL;
#endif
	return l;
}

/* Insert a chain into a buffer (this does not update pointers) */
static void inschn(P *p, H *a)
{
	if (!p->b->eof->byte) {	/* P's buffer is empty: replace the empty segment in p with a */
		hfree(p->hdr);
		p->hdr = a;
		vunlock(p->ptr);
		p->ptr = vlock(vmem, a->seg);
		pset(p->b->bof, p);

		p->b->eof->hdr = a->link.prev;
		vunlock(p->b->eof->ptr);
		p->b->eof->ptr = vlock(vmem, p->b->eof->hdr->seg);
		p->b->eof->ofst = GSIZE(p->b->eof->hdr);
	} else if (piseof(p)) {	/* We're at the end of the file: append a to the file */
		p->b->eof->hdr = a->link.prev;
		spliceb(H, link, p->b->bof->hdr, a);
		vunlock(p->b->eof->ptr);
		p->b->eof->ptr = vlock(vmem, p->b->eof->hdr->seg);
		p->b->eof->ofst = GSIZE(p->b->eof->hdr);
		p->hdr = a;
		vunlock(p->ptr);
		p->ptr = vlock(vmem, p->hdr->seg);
		p->ofst = 0;
	} else if (pisbof(p)) {	/* We're at the beginning of the file: insert chain and set bof pointer */
		p->hdr = spliceb_f(H, link, p->hdr, a);
		vunlock(p->ptr);
		p->ptr = vlock(vmem, a->seg);
		pset(p->b->bof, p);
	} else {		/* We're in the middle of the file: split and insert */
		bsplit(p);
		p->hdr = spliceb_f(H, link, p->hdr, a);
		vunlock(p->ptr);
		p->ptr = vlock(vmem, a->seg);
	}
}

static void fixupins(P *p, long amnt, long nlines, H *hdr, int hdramnt)
{
	P *pp;

	if (nlines && !pisbol(p))
		scrins(p->b, p->line, nlines, 1);
	else
		scrins(p->b, p->line, nlines, 0);
	inserr(p->b->name, p->line, nlines, pisbol(p));	/* FIXME: last arg ??? */

	for (pp = p->link.next; pp != p; pp = pp->link.next)
		if (pp->line == p->line && (pp->byte > p->byte || (pp->end && pp->byte == p->byte)))
			pp->valcol = 0;
	for (pp = p->link.next; pp != p; pp = pp->link.next)
		if (pp->byte == p->byte && !pp->end)
			if (pp->ptr)
				pset(pp, p);
			else
				poffline(pset(pp, p));
		else if (pp->byte > p->byte || (pp->end && pp->byte == p->byte)) {
			pp->byte += amnt;
			pp->line += nlines;
			if (pp->hdr == hdr)
				pp->ofst += hdramnt;
		}
	if (p->b->undo)
		undoins(p->b->undo, p, amnt);
	p->b->changed = 1;
}

/* Insert a buffer at pointer position (the buffer goes away) */
P *binsb(P *p, B *b)
{
	if (b->eof->byte) {
		P *q = pdup(p);

		inschn(q, b->bof->hdr);
		b->eof->hdr = halloc();
		fixupins(q, b->eof->byte, b->eof->line, NULL, 0);
		pcoalesce(q);
		prm(q);
	}
	brm(b);
	return p;
}

/* insert memory block 'blk' at 'p' */
P *binsm(P *p, const unsigned char *blk, int amnt)
{
	long nlines;
	H *h = NULL;
	int hdramnt = 0;
	P *q;

	if (!amnt)
		return p;
	q = pdup(p);
	if (amnt <= GGAPSZ(q->hdr)) {
		h = q->hdr;
		hdramnt = amnt;
		ginsm(q->hdr, q->ptr, q->ofst, blk, amnt);
		q->hdr->nlines += (nlines = mcnt(blk, '\n', amnt));
	} else if (!q->ofst && q->hdr != q->b->bof->hdr && amnt <= GGAPSZ(q->hdr->link.prev)) {
		pprev(q);
		ginsm(q->hdr, q->ptr, q->ofst, blk, amnt);
		q->hdr->nlines += (nlines = mcnt(blk, '\n', amnt));
	} else {
		H *a = bldchn(blk, amnt, &nlines);

		inschn(q, a);
	}
	fixupins(q, (long) amnt, nlines, h, hdramnt);
	pcoalesce(q);
	prm(q);
	return p;
}

/* insert byte 'c' at 'p' */
P *binsbyte(P *p, unsigned char c)
{
	if (p->b->o.crlf && c == '\n')
		return binsm(p, UC "\r\n", 2);
	else
		return binsm(p, &c, 1);
}

/* UTF-8 encode a character and insert it */
P *binsc(P *p, int c)
{
	if (c>127 && p->b->o.charmap->type) {
		unsigned char buf[8];
		int len = utf8_encode(buf,c);
		return binsm(p,buf,len);
	} else {
		unsigned char ch = c;
		if (p->b->o.crlf && c == '\n')
			return binsm(p, UC "\r\n", 2);
		else
			return binsm(p, &ch, 1);
	}
}

/* insert zero-terminated string 's' at 'p' */
P *binss(P *p, unsigned char *s)
{
	return binsm(p, s, strlen((char *)s));
}

/* Read 'size' bytes from file or stream.  Stops and returns amnt. read
 * when requested size has been read or when end of file condition occurs.
 * Returns with -2 in error for read error or 0 in error for success.
 */
static int bkread(int fi, unsigned char *buff, int size)
{
	int a, b;

	if (!size) {
		error = 0;
		return 0;
	}
	for (a = b = 0; (a < size) && ((b = joe_read(fi, buff + a, size - a)) > 0); a += b) ;
	if (b < 0)
		error = -2;
	else
		error = 0;
	return a;
}

/* Read up to 'max' bytes from a file into a buffer */
/* Returns with 0 in error or -2 in error for read error */
B *bread(int fi, long int max)
{
	H anchor, *l;
	long lines = 0, total = 0;
	int amnt;
	unsigned char *seg;

	izque(H, link, &anchor);
	error = 0;
	while (seg = vlock(vmem, (l = halloc())->seg), !error && (amnt = bkread(fi, seg, max >= SEGSIZ ? SEGSIZ : (int) max))) {
		total += amnt;
		max -= amnt;
		l->hole = amnt;
		lines += (l->nlines = mcnt(seg, '\n', amnt));
		vchanged(seg);
		vunlock(seg);
		enqueb(H, link, &anchor, l);
	}
	hfree(l);
	vunlock(seg);
	if (!total)
		return bmk(NULL);
	l = anchor.link.next;
	deque(H, link, &anchor);
	return bmkchn(l, NULL, total, lines);
}

/* Parse file name.
 *
 * Removes ',xxx,yyy' from end of name and puts their value into skip and amnt
 * Replaces ~user/ with directory of given user unless -DJOE_NOPWNAM
 * Replaces ~/ with $HOME
 *
 * Returns new variable length string.
 */
unsigned char *
parsens(const unsigned char *s, long int *skip, long int *amnt)
{
	unsigned char *n = vsncpy(NULL, 0, sz(s));
	size_t x;

	*skip = 0;
	*amnt = LONG_MAX;
	for (x = sLEN(n) - 1; x > 0 && ((n[x] >= '0' && n[x] <= '9') || (n[x] | 0x20) == 'x'); --x)
		/* nothing */;
	if (n[x] == ',') {
		void *vp;

		n[x] = 0;
		*skip = ustol(n + x + 1, &vp, USTOL_EOS);
		for (--x; x > 0 && ((n[x] >= '0' && n[x] <= '9') || (n[x] | 0x20) == 'x'); --x)
			/* nothing */;
		if (n[x] == ',') {
			n[x] = 0;
			if (vp != NULL)
				*amnt = *skip;
			*skip = ustol(n + x + 1, NULL, USTOL_EOS);
		}
	}
	if (n[0] == '~') {
		for (x = 1; n[x] && n[x] != '/'; ++x) ;
		if (n[x] == '/') {
			if (x == 1) {
				unsigned char *z;

				s = (unsigned char *)getenv("HOME");
				z = vsncpy(NULL, 0, sz(s));
				z = vsncpy(z, sLEN(z), sz(n + x));
				vsrm(n);
				n = z;
#ifndef JOE_NOPWNAM
			} else {
				struct passwd *passwd;

				n[x] = 0;
				passwd = getpwnam((char *)(n + 1));
				n[x] = '/';
				if (passwd) {
					unsigned char *z = vsncpy(NULL, 0,
					    sz((unsigned char *)(passwd->pw_dir)));

					z = vsncpy(z, sLEN(z), sz(n + x));
					vsrm(n);
					n = z;
				}
#endif
			}
		}
	}
	return n;
}

/* Load file into new buffer and return the new buffer */
/* Returns with error set to 0 for success,
 * -1 for new file (file doesn't exist)
 * -2 for read error
 * -3 for seek error
 * -4 for open error
 */
B *
bload(const unsigned char *s)
{
	unsigned char buffer[SEGSIZ];
	FILE *fi;
	B *b = NULL;
	long skip, amnt;
	unsigned char *n;
	int nowrite = 0;
	P *p;
	int x;
	long mod_time = 0;
	struct stat sbuf;

	if (!s || !s[0]) {
		error = -1;
		b = bmk(NULL);
		setopt(b, UC "");
		b->rdonly = b->o.readonly;
		b->er = error;
		return b;
	}

	n = parsens(s, &skip, &amnt);

	/* Open file or stream */
	if (s[0] == '!') {
		nescape(maint->t);
		ttclsn();
		fi = popen((char *)(n + 1), "r");
	} else
	if (!strcmp(n, "-"))
		fi = stdin;
	else {
		fi = fopen((char *)n, "r+");
		if (!fi)
			nowrite = 1;
		else
			fclose(fi);
		fi = fopen((char *)n, "r");
		if (!fi)
			nowrite = 0;
		if (fi) {
			fstat(fileno(fi),&sbuf);
			mod_time = sbuf.st_mtime;
		}
	}
#if HAVE_BACKSLASH_PATHS
	joesep(n);
#endif

	/* Abort if couldn't open */
	if (!fi) {
		if (errno == ENOENT)
			error = -1;
		else
			error = -4;
		goto opnerr;
	}

	/* Skip data if we need to */
	if (skip && lseek(fileno(fi), skip, 0) < 0) {
		int r;

		while (skip > SEGSIZ) {
			r = bkread(fileno(fi), buffer, SEGSIZ);
			if (r != SEGSIZ || error) {
				error = -3;
				goto err;
			}
			skip -= SEGSIZ;
		}
		skip -= bkread(fileno(fi), buffer, (int) skip);
		if (skip || error) {
			error = -3;
			goto err;
		}
	}

	/* Read from stream into new buffer */
	b = bread(fileno(fi), amnt);
	b->mod_time = mod_time;
	setopt(b,n);
	b->rdonly = b->o.readonly;

	/* Close stream */
 err:
	if (s[0] == '!')
		pclose(fi);
	else if (strcmp(n, "-"))
		fclose(fi);

 opnerr:
	if (!b) {
		/* error case */
		b = bmk(NULL);
		setopt(b,n);
		b->rdonly = b->o.readonly;
	}

	if (s[0] == '!') {
		ttopnn();
		nreturn(maint->t);
	}

	/* Set name */
	b->name = joesep((unsigned char *)strdup(s));

	/* Set flags */
	if (error || s[0] == '!' || skip || amnt != LONG_MAX) {
		b->backup = 1;
		b->changed = 0;
	} else if (!strcmp(n, "-")) {
		b->backup = 1;
		b->changed = 1;
	} else {
		b->backup = 0;
		b->changed = 0;
	}
	if (nowrite)
		b->rdonly = b->o.readonly = 1;

	/* If first line has CR-LF, assume MS-DOS file */
	if (guesscrlf) {
		p=pdup(b->bof);
		b->o.crlf = 0;
		for(x=0;x!=1024;++x) {
			int c = pgetc(p);
			if(c == '\r') {
				b->o.crlf = 1;
				break;
				}
			if(c == '\n') {
				b->o.crlf = 0;
				break;
				}
			if(c == NO_MORE_DATA)
				break;
		}
		prm(p);
	}

	/* Search backwards through file: if first indented line
	   is indented with a tab, assume indentc is tab */
	if (guessindent) {
		p=pdup(b->eof);
		for (x=0; x!=20; ++x) {
			p_goto_bol(p);
			if (pisindent(p)) {
				if (brc(p)=='\t') {
					b->o.indentc = '\t';
					b->o.istep = 1;
				} else {
					b->o.indentc = ' ';
					b->o.istep = 2;
				}
				break;
			}
			if (prgetc(p)==NO_MORE_DATA)
				break;
		}
		prm(p);
	}

	/* Eliminate parsed name */
	vsrm(n);

	b->er = error;
	return b;
}

/* Find already loaded buffer or load file into new buffer */
B *
bfind(const unsigned char *s)
{
	B *b;

	if (!s || !s[0]) {
		error = -1;
		b = bmk(NULL);
		setopt(b, UC "");
		b->rdonly = b->o.readonly;
		b->internal = 0;
		b->er = error;
		return b;
	}
	for (b = bufs.link.next; b != &bufs; b = b->link.next)
		if (b->name && !strcmp(s, b->name)) {
			if (!b->orphan)
				++b->count;
			else
				b->orphan = 0;
			error = 0;
			b->internal = 0;
			return b;
		}
	b = bload(s);
	b->internal = 0;
	return b;
}

/* Find already loaded buffer or load file into new buffer */
B *
bfind_scratch(const unsigned char *s)
{
	B *b;

	if (!s || !s[0]) {
		error = -1;
		b = bmk(NULL);
		setopt(b, UC "");
		b->rdonly = b->o.readonly;
		b->internal = 0;
		b->er = error;
		return b;
	}
	for (b = bufs.link.next; b != &bufs; b = b->link.next)
		if (b->name && !strcmp(s, b->name)) {
			if (!b->orphan)
				++b->count;
			else
				b->orphan = 0;
			error = 0;
			b->internal = 0;
			return b;
		}
	b = bmk(NULL);
	error = -1;
	setopt(b,s);
	b->internal = 0;
	b->rdonly = b->o.readonly;
	b->er = error;
	b->name = (unsigned char *)strdup((char *)s);
	b->scratch = 1;
	return b;
}

B *
bfind_reload(const unsigned char *s)
{
	B *b;
	b = bload(s);
	b->internal = 0;
	return b;
}

B *
bcheck_loaded(const unsigned char *s)
{
	B *b;

	if (!s || !s[0]) {
		return NULL;
	}
	for (b = bufs.link.next; b != &bufs; b = b->link.next)
		if (b->name && !strcmp(s, b->name)) {
			return b;
		}

	return NULL;
}

unsigned char **getbufs(void)
{
	unsigned char **s = vamk(16);
	B *b;

	for (b = bufs.link.next; b != &bufs; b = b->link.next)
		if (b->name)
			s = vaadd(s, vsncpy(NULL, 0, sz(b->name)));
	return s;
}

/* Find an orphaned buffer */
B *borphan(void)
{
	B *b;

	for (b = bufs.link.next; b != &bufs; b = b->link.next)
		if (b->orphan) {
			b->orphan = 0;
			return b;
		}
	return NULL;
}

/* Write 'size' bytes from file beginning at 'p' to open file 'fd'.
 * Returns error.
 * error is set to -5 for write error or 0 for success.
 * Don't attempt to write past the end of the file
 */
int bsavefd(P *p, int fd, long int size)
{
	P *np = pdup(p);
	int amnt;

	while (size > (amnt = GSIZE(np->hdr) - np->ofst)) {
		if (np->ofst < np->hdr->hole) {
			if (joe_write(fd, np->ptr + np->ofst, np->hdr->hole - np->ofst) < 0)
				goto err;
			if (joe_write(fd, np->ptr + np->hdr->ehole, SEGSIZ - np->hdr->ehole) < 0)
				goto err;
		} else if (joe_write(fd, np->ptr + np->ofst + GGAPSZ(np->hdr), amnt) < 0)
			goto err;
		size -= amnt;
		pnext(np);
	}
	if (size) {
		if (np->ofst < np->hdr->hole) {
			if (size > np->hdr->hole - np->ofst) {
				if (joe_write(fd, np->ptr + np->ofst, np->hdr->hole - np->ofst) < 0)
					goto err;
				if (joe_write(fd, np->ptr + np->hdr->ehole, (int) size - np->hdr->hole + np->ofst) < 0)
					goto err;
			} else {
				if (joe_write(fd, np->ptr + np->ofst, (int) size) < 0)
					goto err;
			}
		} else {
			if (joe_write(fd, np->ptr + np->ofst + GGAPSZ(np->hdr), (int) size) < 0)
				goto err;
		}
	}
	prm(np);
	return error = 0;
 err:
	prm(np);
	return error = 5;
}

/* Save 'size' bytes beginning at 'p' in file 's' */

/* If flag is set, update original time of file if it makes
 * sense to do so (it's a normal file, we're saving with
 * same name as buffer or is about to get this name).
 */

int bsave(P *p, unsigned char *s, long int size, int flag)
{
	FILE *f;
	long skip, amnt;
	struct stat sbuf;
	int norm = 0;

	s = parsens(s, &skip, &amnt);

	if (amnt < size)
		size = amnt;

	if (s[0] == '!') {
		nescape(maint->t);
		ttclsn();
		f = popen((char *)(s + 1), "w");
	} else if (s[0] == '>' && s[1] == '>')
		f = fopen((char *)(s + 2), "a");
	else if (!strcmp(s, "-")) {
		nescape(maint->t);
		ttclsn();
		f = stdout;
	} else if (skip || amnt != LONG_MAX)
		f = fopen((char *)s, "r+");
	else {
		f = fopen((char *)s, "w");
		norm = 1;
	}
#if HAVE_BACKSLASH_PATHS
	joesep(s);
#endif

	if (!f) {
		error = -4;
		goto opnerr;
	}
	fflush(f);

	if (skip && lseek(fileno(f), skip, 0) < 0) {
		error = -3;
		goto err;
	}

	bsavefd(p, fileno(f), size);

	if (!error && force && size && !skip && amnt == LONG_MAX) {
		P *q = pdup(p);
		unsigned char nl = '\n';

		pfwrd(q, size - 1);
		if (brc(q) != '\n' && joe_write(fileno(f), &nl, 1) < 0)
			error = -5;
		prm(q);
	}

 err:
	if (s[0] == '!')
		pclose(f);
	else if (strcmp(s, "-"))
		fclose(f);
	else
		fflush(f);

	/* Update orignal date of file */
	/* If it's not named, it's about to be */
	if (!error && norm && flag && (!p->b->name || !strcmp((char *)s,p->b->name))) {
		if (!stat((char *)s,&sbuf))
			p->b->mod_time = sbuf.st_mtime;
	}

 opnerr:
	if (s[0] == '!' || !strcmp(s, "-")) {
		ttopnn();
		nreturn(maint->t);
	}
	return error;
}

/* Return byte at p */

int brc(P *p)
{
	if (p->ofst == GSIZE(p->hdr))
		return NO_MORE_DATA;
	return GCHAR(p);
}

/* Return character at p */

int brch(P *p)
{
	if (p->b->o.charmap->type) {
		P *q = pdup(p);
		int c = pgetc(q);
		prm(q);
		return c;
	} else {
		return brc(p);
	}
}

unsigned char *brmem(P *p, unsigned char *blk, int size)
{
	unsigned char *bk = blk;
	P *np;
	int amnt;

	np = pdup(p);
	while (size > (amnt = GSIZE(np->hdr) - np->ofst)) {
		grmem(np->hdr, np->ptr, np->ofst, bk, amnt);
		bk += amnt;
		size -= amnt;
		pnext(np);
	}
	if (size)
		grmem(np->hdr, np->ptr, np->ofst, bk, size);
	prm(np);
	return blk;
}

unsigned char *brs(P *p, int size)
{
	unsigned char *s = malloc(size + 1);

	s[size] = 0;
	return brmem(p, s, size);
}

unsigned char *brvs(P *p, int size)
{
	unsigned char *s = vstrunc(NULL, size);

	return brmem(p, (unsigned char *)s, size);
}

unsigned char *brzs(P *p, unsigned char *buf, int size)
{
	P *q=pdup(p);
	p_goto_eol(q);

	if(q->byte-p->byte<size)
		size = q->byte - p->byte;

	prm(q);
	brmem(p,buf,size);
	buf[size]=0;
	return buf;
}

/* Save edit buffers when editor dies */

RETSIGTYPE
ttsig(int sig)
{
	ttabrt(sig, NULL);
	_exit(1);
}

void
ttabrt(int sig, const char *msg)
{
	time_t tim = time(NULL);
	B *b;
	FILE *f;
	int tmpfd;
	struct stat sbuf;

	if (msg) {
		fprintf(stderr, "\r\n*** Aborting JOE because: %s ***\r\n", msg);
		fflush(stderr);
	}

	if ((tmpfd = open("DEADJOE", O_RDWR | O_EXCL | O_CREAT, 0600)) < 0) {
		struct stat cbuf;

		if (lstat("DEADJOE", &sbuf) < 0)
			_exit(-1);
		if (!S_ISREG(sbuf.st_mode) || sbuf.st_uid != geteuid())
			_exit(-1);
		if ((tmpfd = open("DEADJOE", O_RDWR | O_APPEND)) < 0)
			_exit(-1);
		/* https://stackoverflow.com/a/2917482/2171120 */
		if (fstat(tmpfd, &cbuf) < 0 ||
		    cbuf.st_dev != sbuf.st_dev || cbuf.st_ino != sbuf.st_ino)
			_exit(-1);
		if (fchmod(tmpfd, S_IRUSR | S_IWUSR) < 0)
			_exit(-1);
	}
	if ((f = fdopen(tmpfd, "a")) == NULL)
		_exit(-1);

	fprintf(f, "\n*** Modified files in JOE when it aborted on %s", ctime(&tim));
	if (msg)
		fprintf(f, "*** JOE was aborted: %s\n", msg);
	else if (sig)
		fprintf(f, "*** JOE was aborted by signal %d\n", sig);
	else
		fprintf(f, "*** JOE was aborted because the terminal closed\n");
	fflush(f);
	for (b = bufs.link.next; b != &bufs; b = b->link.next)
		if (b->changed) {
			if (b->name)
				fprintf(f, "\n*** File \'%s\'\n", b->name);
			else
				fprintf(f, "\n*** File \'(Unnamed)\'\n");
			fflush(f);
			bsavefd(b->bof, fileno(f), b->eof->byte);
		}
	fclose(f);
	if (sig)
		ttclsn();
}
