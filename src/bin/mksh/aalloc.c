#include "sh.h"

__RCSID("$MirOS: src/bin/mksh/aalloc.c,v 1.1 2008/11/12 04:55:17 tg Exp $");

/* mksh integration of aalloc */

#ifndef AALLOC_ABORT
#define AALLOC_ABORT		internal_errorf
#endif

#ifndef AALLOC_WARN
#define AALLOC_WARN		internal_warningf
#endif

#ifndef AALLOC_RANDOM
#if HAVE_ARC4RANDOM
#define AALLOC_RANDOM()		arc4random()
#else
#define AALLOC_RANDOM()		(rand() * RAND_MAX + rand())
#endif
#endif

#ifdef DEBUG
#define AALLOC_DEBUG
#endif

/* generic area-based allocator built for mmap malloc or omalloc */

#define PVALIGN			(sizeof (void *))
#define PVMASK			(sizeof (void *) - 1)

#ifndef AALLOC_INITSZ
#define AALLOC_INITSZ		64	/* must hold at least 4 pointers */
#endif

typedef /* unsigned */ ptrdiff_t TCookie;

typedef union {
	TCookie iv;
	void *pv;
} TPtr;

/*
 * The separation between TBlock and TArea does not seem to make
 * sense at first, especially in the !AALLOC_TRACK case, but is
 * necessary to keep PArea values constant even if the storage is
 * enlarged. While we could use an extensible array to keep track
 * of the TBlock instances, kind of like we use TBlock.storage to
 * track the allocations, it would require another TBlock member
 * and a fair amount of backtracking; since omalloc can optimise
 * pointer sized allocations like a !AALLOC_TRACK TArea, we don't
 * do that then.
 */

struct TBlock {
	TCookie cookie;
	void *endp;
	void *last;
	void *storage;
};
typedef struct TBlock *PBlock;

struct TArea {
	TPtr bp;
#ifdef AALLOC_TRACK
	TPtr prev;
	TCookie ocookie;
#endif
};

static TCookie gcookie;

#ifdef AALLOC_TRACK
static PArea track;
static void track_check(void);
#endif

#ifdef AALLOC_MPROTECT
#undef AALLOC_INITSZ
#define AALLOC_INITSZ		pagesz
static size_t pagesz;
#define AALLOC_ACCESS(bp, n, p)	mprotect((bp), (bp)->endp - (bp), (p))
#define AALLOC_ALLOW(bp)	\
	AALLOC_ACCESS((bp), (bp)->endp - (bp), PROT_READ | PROT_WRITE);
#define AALLOC_DENY(bp)		\
	AALLOC_ACCESS((bp), (bp)->endp - (bp), PROT_NONE)
#define AALLOC_PEEK(bp)		\
	AALLOC_ACCESS((bp), sizeof (struct TArea), PROT_READ | PROT_WRITE)
#else
#define AALLOC_ALLOW(bp)	/* nothing */
#define AALLOC_DENY(bp)		/* nothing */
#define AALLOC_PEEK(bp)		/* nothing */
#endif

/*
 * Some nice properties: allocations are always PVALIGNed, which
 * includes the pointers seen by our user, the forward and back
 * pointers, the AALLOC_TRACK prev pointer, etc.
 */

#define safe_realloc(dest, len) do {					\
	if (((dest) = realloc((dest), (len))) == NULL)			\
		AALLOC_ABORT("unable to allocate %zu bytes: %s",	\
		    (len), strerror(errno));				\
	if ((ptrdiff_t)(dest) & PVMASK)					\
		AALLOC_ABORT("unaligned malloc result: %p", (dest));	\
} while (/* CONSTCOND */ 0)

#define MUL_NO_OVERFLOW (1UL << (sizeof (size_t) * 8 / 2))
#define safe_muladd(nmemb, size, extra) do {				\
	if ((nmemb >= MUL_NO_OVERFLOW || size >= MUL_NO_OVERFLOW) &&	\
	    nmemb > 0 && SIZE_MAX / nmemb < size)			\
		AALLOC_ABORT("attempted integer overflow:"		\
		    " %zu * %zu", nmemb, size);				\
	size *= nmemb;							\
	if (size >= SIZE_MAX - extra)					\
		AALLOC_ABORT("unable to allocate %zu bytes: %s",	\
		    size, "value plus extra too big");			\
} while (/* CONSTCOND */ 0)

static PBlock check_bp(PArea, const char *, TCookie);
static TPtr *check_ptr(void *, PArea, PBlock *, const char *, const char *);

PArea
anew(void)
{
	PArea ap;
	PBlock bp;

#ifdef AALLOC_DEBUG
	if (PVALIGN != 2 && PVALIGN != 4 && PVALIGN != 8 && PVALIGN != 16)
		AALLOC_ABORT("PVALIGN not a power of two: %zu", PVALIGN);
	if (sizeof (TPtr) != sizeof (TCookie) || sizeof (TPtr) != PVALIGN)
		AALLOC_ABORT("TPtr sizes do not match: %zu, %zu, %zu",
		    sizeof (TPtr), sizeof (TCookie), PVALIGN);
	if (AALLOC_INITSZ < sizeof (struct TBlock))
		AALLOC_ABORT("AALLOC_INITSZ constant too small: %zu < %zu",
		    AALLOC_INITSZ, sizeof (struct TBlock));
#endif

#ifdef AALLOC_MPROTECT
	if (!pagesz) {
		if ((pagesz = sysconf(_SC_PAGESIZE)) == (size_t)-1 ||
		    pagesz < PVALIGN)
			AALLOC_ABORT("sysconf(_SC_PAGESIZE) failed: %zd %s",
			    pagesz, strerror(errno));
	}
#endif

	if (!gcookie) {
		size_t v;

		/* ensure unaligned cookie */
		do {
			gcookie = AALLOC_RANDOM();
			v = AALLOC_RANDOM() & 7;
		} while (!(gcookie & PVMASK) || !v);
		/* randomise seed afterwards */
		while (v--)
			AALLOC_RANDOM();
#ifdef AALLOC_TRACK
		atexit(track_check);
#endif
	}

	ap = NULL; safe_realloc(ap, sizeof (struct TArea));
	bp = NULL; safe_realloc(bp, (size_t)AALLOC_INITSZ);
	/* ensure unaligned cookie */
	do {
		bp->cookie = AALLOC_RANDOM();
	} while (!(bp->cookie & PVMASK));

	/* first byte after block */
	bp->endp = bp + AALLOC_INITSZ;		/* bp + size of the block */
	/* next entry (forward pointer) available for new allocation */
	bp->last = &bp->storage;		/* first entry */

	ap->bp.pv = bp;
	ap->bp.iv ^= gcookie;
#ifdef AALLOC_TRACK
	ap->prev.pv = track;
	ap->prev.iv ^= track_cookie;
	ap->ocookie = bp->cookie ^ gcookie;
	track = ap;
#endif
	AALLOC_DENY(bp);
	return (ap);
}

/*
 * Validate block in Area “ap”, return unlocked block pointer.
 * If “ocookie” is not 0, make sure block cookie is equal.
 */
static PBlock
check_bp(PArea ap, const char *funcname, TCookie ocookie)
{
	TPtr p;
	PBlock bp;

	if (ap->bp.pv == NULL) {
		AALLOC_WARN("%s: area %p already freed", funcname, ap);
		return (NULL);
	}
	p.iv = ap->bp.iv ^ gcookie;
	if ((ptrdiff_t)(bp = p.pv) & PVMASK) {
		AALLOC_WARN("%s: area %p block pointer destroyed: %08tX",
		    funcname, ap, p.iv);
		return (NULL);
	}
	AALLOC_PEEK(bp);
	if (ocookie && bp->cookie != ocookie) {
		AALLOC_WARN("%s: block %p cookie destroyed: %08tX, %08tX",
		    funcname, bp, ocookie, bp->cookie);
		return (NULL);
	}
	if (((ptrdiff_t)bp->endp & PVMASK) || ((ptrdiff_t)bp->last & PVMASK)) {
		AALLOC_WARN("%s: block %p data structure destroyed: %p, %p",
		    funcname, bp, bp->endp, bp->last);
		return (NULL);
	}
	if (bp->endp < (void *)bp) {
		AALLOC_WARN("%s: block %p end pointer out of bounds: %p",
		    funcname, bp, bp->endp);
		return (NULL);
	}
	if ((bp->last < (void *)&bp->storage) || (bp->last >= bp->endp)) {
		AALLOC_WARN("%s: block %p last pointer out of bounds: "
		    "%p < %p < %p", funcname, bp, &bp->storage, bp->last,
		    bp->endp);
		return (NULL);
	}
	AALLOC_ALLOW(bp);
	return (bp);
}

#ifdef AALLOC_TRACK
/*
 * At exit, dump and free any leaked allocations, blocks and areas.
 */
static void
track_check(void)
{
	PArea ap;
	PBlock bp;

	while (track) {
		ap = track;
		ap->ocookie ^= track_cookie;
		ap->prev.iv ^= track_cookie;
		if ((ap->prev.iv & PVMASK) || !ap->ocookie) {
			/* buffer overflow or something? */
			AALLOC_WARN("AALLOC_TRACK data structure %p destroyed:"
			    " %p, %08X, %08X", ap, ap->prev.pv,
			    ap->bp.iv, ap->ocookie);
			return;
		}
		if (!(bp = check_bp(ap, "atexit:track_check", tp->ocookie)))
			goto track_next;
		if (bp->last == &bp->storage) {
			AALLOC_WARN("leaking empty area %p (%p %tu)", ap,
			    bp, bp->endp - bp);
			goto track_freebp;
		}
		while (bp->last > &bp->storage) {
			TPtr *cp;

			bp->last -= PVALIGN;
			cp = *((void **)bp->last);
			cp->iv ^= bp->cookie;
			AALLOC_WARN("leaking %s pointer %p in area %p (%p %tu)",
			    cp->pv == bp->last ? "valid" : "underflown",
			    (char *)cp + PVALIGN, ap, bp, bp->endp - bp);
			free(cp);
		}
 track_freebp:
		free(bp);
 track_next:
		track = ap->prev.pv;
		free(ap);
	}
}
#endif

void
adelete(PArea *pap)
{
#ifdef AALLOC_TRACK
	PArea tp;
#endif
	PBlock bp;

	if ((bp = check_bp(*pap, "adelete", 0)) == NULL)
		goto adelete_freeap;	/* ignore invalid areas */

	if (bp->last != &bp->storage)
		adelete_leak(bp);
	free(bp);
 adelete_freeap:
#ifdef AALLOC_TRACK
	if (track == *pap) {
		(*pap)->prev.iv ^= gcookie;
		track = (*pap)->prev.pv;
		goto adelete_tracked;
	}
	/* find the TArea whose prev is *pap */
	tp = track;
	while (tp) {
		TPtr lp;
		lp.iv = tp->prev.iv ^ gcookie;
		if ((lp.iv & PVMASK) || !lp->ocookie) {
			AALLOC_WARN("AALLOC_TRACK data structure %p destroyed:"
			    " %p, %08X, %08X", tp, tp->prev.pv,
			    tp->bp.iv, tp->ocookie);
			tp = NULL;
			break;
		}
		if (lp.pv == *pap)
			break;
		tp = lp.pv;
	}
	if (tp)
		tp->prev.iv = (*pap)->prev.iv;	/* decouple *pap */
	else
		AALLOC_WARN("area %p not in found AALLOC_TRACK data structure",
		    *pap);
 adelete_tracked:
#endif
	free(*pap);
	*pap = NULL;
}

void *
alloc(size_t nmemb, size_t size, PArea ap)
{
	PBlock bp;
	TPtr *ptr;

	/* obtain the memory region requested, retaining guards */
	safe_muladd(nmemb, size, sizeof (TPtr));
	ptr = NULL; safe_realloc(ptr, size);

	/* chain into area */
	if ((bp = check_bp(ap, "alloc", 0)) == NULL)
		AALLOC_ABORT("cannot continue");
	if (bp->last == bp->endp) {
		size_t bsz;

		/* make room for more forward ptrs in the block allocation */
		bsz = bp->endp - (void *)bp;
		safe_muladd((size_t)2, bsz, 0);
		safe_realloc(bp, bsz);

		/* “bp” has possibly changed, enter its new value into ap */
		ap->bp.pv = bp;
		ap->bp.iv ^= gcookie;
	}
	*((void **)bp->last) = ptr;	/* next available forward ptr */
	ptr->pv = bp->last;		/* backpointer to fwdptr storage */
	ptr->iv ^= bp->cookie;		/* apply block cookie */
	bp->last += PVALIGN;		/* advance next-avail pointer */
	AALLOC_DENY(bp);

	/* return aligned storage just after the cookied backpointer */
	return ((char *)ptr + PVALIGN);
}

void *
aresize(void *vp, size_t nmemb, size_t size, PArea ap)
{
	PBlock bp;
	TPtr *ptr;

	if (vp == NULL)
		return (alloc(nmemb, size, ap));

	/* validate allocation and backpointer against forward pointer */
	if ((ptr = check_ptr(vp, ap, &bp, "aresize", "")) == NULL)
		AALLOC_ABORT("cannot continue");

	/* move allocation to size and possibly new location */
	safe_muladd(nmemb, size, sizeof (TPtr));
	safe_realloc(ptr, size);

	/* write new address of allocation into the block forward pointer */
	memcpy(ptr->pv, &ptr, PVALIGN);
	/* apply the cookie on the backpointer again */
	ptr->iv ^= bp->cookie;
	AALLOC_DENY(bp);

	return ((char *)ptr + PVALIGN);
}

/*
 * Try to find “vp” inside Area “ap”, use “what” and “extra” for error msgs.
 *
 * If an error occurs, returns NULL with no side effects.
 * Otherwise, returns address of the allocation, with the cookie on the
 * backpointer unapplied; *bpp contains the unlocked block pointer.
 */
static TPtr *
check_ptr(void *vp, PArea ap, PBlock *bpp, const char *what, const char *extra)
{
	PBlock bp;
	TPtr *ptr;

	if ((ptrdiff_t)vp & PVMASK) {
		AALLOC_WARN("trying to %s rogue unaligned pointer %p from "
		    "area %p%s", what + 1, vp, ap, extra);
		return (NULL);
	}

	ptr = (TPtr *)((char *)vp - PVALIGN);
	if (!ptr->iv) {
		AALLOC_WARN("trying to %s already freed pointer %p from "
		    "area %p%s", what + 1, vp, ap, extra);
		return (NULL);
	}

	if ((bp = check_bp(ap, what, 0)) == NULL)
		AALLOC_ABORT("cannot continue");
	ptr->iv ^= bp->cookie;
	if (ptr->pv < (void *)&bp->storage || ptr->pv >= bp->last) {
		AALLOC_WARN("trying to %s rogue pointer %p from area %p "
		    "(block %p..%p), backpointer %p out of bounds%s",
		    what + 1, vp, ap, bp, bp->last, ptr->pv, extra);
		AALLOC_DENY(bp);
		return (NULL);
	}
	if (*((void **)ptr->pv) != ptr) {
		AALLOC_WARN("trying to %s rogue pointer %p from area %p "
		    "(block %p..%p), backpointer %p, forward pointer to "
		    "%p instead%s", what + 1, vp, ap, bp, bp->last,
		    ptr->pv, *((void **)ptr->pv), extra);
		AALLOC_DENY(bp);
		return (NULL);
	}
	*bpp = bp;
	return (ptr);
}

void
afree(void *vp, PArea ap)
{
	PBlock bp;
	TPtr *ptr;

	if (vp == NULL)
		return;

	/* validate allocation and backpointer, ignore rogues */
	if ((ptr = check_ptr(vp, ap, &bp, "afree", ", ignoring")) == NULL)
		return;

	/* note: the block allocation does not ever shrink */
	bp->last -= PVALIGN;	/* mark the last forward pointer as free */
	/* if our forward pointer was not the last one, relocate the latter */
	if (ptr->pv < bp->last) {
		TPtr *tmp = bp->last;	/* former last forward pointer */

		tmp->pv = ptr->pv;	/* its backpointer to former our … */
		tmp->iv ^= bp->cookie;	/* … forward pointer, and cookie it */

		memcpy(ptr->pv, bp->last, PVALIGN);	/* relocate fwd ptr */
	}
	ptr->iv = 0;	/* our backpointer, just in case, for double frees */
	free(ptr);

	AALLOC_DENY(bp);
	return;
}
