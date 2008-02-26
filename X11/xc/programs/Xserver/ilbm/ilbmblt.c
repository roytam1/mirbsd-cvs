/* $XFree86: xc/programs/Xserver/ilbm/ilbmblt.c,v 3.0 1996/08/18 01:53:39 dawes Exp $ */
/*
 * ilbm copy area
 */

/*

Copyright (c) 1989  X Consortium

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
X CONSORTIUM BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of the X Consortium shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from the X Consortium.

Author: Keith Packard

*/
/* $XConsortium: ilbmblt.c,v 1.11 94/04/17 20:28:16 dpw Exp $ */

/* Modified jun 95 by Geert Uytterhoeven (Geert.Uytterhoeven@cs.kuleuven.ac.be)
   to use interleaved bitplanes instead of normal bitplanes */

#include "X.h"
#include "Xmd.h"
#include "Xproto.h"
#include "ilbm.h"
#include "gcstruct.h"
#include "windowstr.h"
#include "scrnintstr.h"
#include "pixmapstr.h"
#include "regionstr.h"
#include "maskbits.h"
#include "fastblt.h"
#include "mergerop.h"

void
MROP_NAME(ilbmDoBitblt)(pSrc, pDst, alu, prgnDst, pptSrc, planemask)
	DrawablePtr pSrc, pDst;
	int alu;
	RegionPtr prgnDst;
	DDXPointPtr pptSrc;
	unsigned long planemask;
{
	PixelType *psrcBase, *pdstBase;	/* start of src and dst bitmaps */
	int widthSrc, widthDst;			/* add to get to same position in next line */
	int heightSrc, heightDst;
	int auxSrc, auxDst;

	BoxPtr pbox;
	int nbox;

	BoxPtr pboxTmp, pboxNext, pboxBase, pboxNew1, pboxNew2;
												/* temporaries for shuffling rectangles */
	DDXPointPtr pptTmp, pptNew1, pptNew2;
												/* shuffling boxes entails shuffling the
													source points too */
	int w, h;
	int xdir;						/* 1 = left right, -1 = right left/ */
	int ydir;						/* 1 = top down, -1 = bottom up */

	PixelType *psrcLine, *pdstLine;
										/* pointers to line with current src and dst */
	register PixelType *psrc;	/* pointer to current src longword */
	register PixelType *pdst;	/* pointer to current dst longword */

	MROP_DECLARE_REG()

										/* following used for looping through a line */
	PixelType startmask, endmask;		/* masks for writing ends of dst */
	int nlMiddle;					/* whole longwords in dst */
	int xoffSrc, xoffDst;
	register int leftShift, rightShift;
	register PixelType bits;
	register PixelType bits1;
	register int nl;				/* temp copy of nlMiddle */

										/* place to store full source word */
	int nstart;						/* number of ragged bits at start of dst */
	int nend;						/* number of ragged bits at end of dst */
	int srcStartOver;				/* pulling nstart bits from src
											overflows into the next word? */
	int careful;
	int tmpSrc;
	int depthSrc;
	int depthDst;

	MROP_INITIALIZE(alu,0);

	ilbmGetPixelWidthAuxDepthAndPointer(pSrc, widthSrc, auxSrc, depthSrc,
													psrcBase);
	ilbmGetPixelWidthAuxDepthAndPointer(pDst, widthDst, auxDst, depthDst,
													pdstBase);

	/* Special case where depth of dest pixmap is 1 but source pixmap isn't
	 * Used for GetImage to copy a plane from a source pixmap to a particular
	 * dest pixmap plane.
	 * Note: planemask should have only one bit set or several planes from
	 * the source will be copied to the same dest plane.
	 */
	if (depthDst == 1 && depthDst != depthSrc)
		widthDst = 0;

	/* XXX we have to err on the side of safety when both are windows,
	 * because we don't know if IncludeInferiors is being used.
	 */
	careful = ((pSrc == pDst) ||
				  ((pSrc->type == DRAWABLE_WINDOW) &&
					(pDst->type == DRAWABLE_WINDOW)));

	pbox = REGION_RECTS(prgnDst);
	nbox = REGION_NUM_RECTS(prgnDst);

	pboxNew1 = NULL;
	pptNew1 = NULL;
	pboxNew2 = NULL;
	pptNew2 = NULL;
	if (careful && (pptSrc->y < pbox->y1)) {
		/* walk source botttom to top */
		ydir = -1;
		auxSrc = -auxSrc;
		auxDst = -auxDst;

		if (nbox > 1) {
			/* keep ordering in each band, reverse order of bands */
			pboxNew1 = (BoxPtr)ALLOCATE_LOCAL(sizeof(BoxRec)*nbox);
			if (!pboxNew1)
				return;
			pptNew1 = (DDXPointPtr)ALLOCATE_LOCAL(sizeof(DDXPointRec)*nbox);
			if (!pptNew1) {
				DEALLOCATE_LOCAL(pboxNew1);
				return;
			}
			pboxBase = pboxNext = pbox+nbox-1;
			while (pboxBase >= pbox) {
				while ((pboxNext >= pbox) &&
					   (pboxBase->y1 == pboxNext->y1))
					pboxNext--;
				pboxTmp = pboxNext+1;
				pptTmp = pptSrc + (pboxTmp - pbox);
				while (pboxTmp <= pboxBase) {
					*pboxNew1++ = *pboxTmp++;
					*pptNew1++ = *pptTmp++;
				}
				pboxBase = pboxNext;
			}
			pboxNew1 -= nbox;
			pbox = pboxNew1;
			pptNew1 -= nbox;
			pptSrc = pptNew1;
		}
	} else {
		/* walk source top to bottom */
		ydir = 1;
	}

	if (careful && (pptSrc->x < pbox->x1)) {
		/* walk source right to left */
		xdir = -1;

		if (nbox > 1) {
			/* reverse order of rects in each band */
			pboxNew2 = (BoxPtr)ALLOCATE_LOCAL(sizeof(BoxRec) * nbox);
			pptNew2 = (DDXPointPtr)ALLOCATE_LOCAL(sizeof(DDXPointRec) * nbox);
			if (!pboxNew2 || !pptNew2) {
				if (pptNew2)
					DEALLOCATE_LOCAL(pptNew2);
				if (pboxNew2)
					DEALLOCATE_LOCAL(pboxNew2);
				if (pboxNew1) {
					DEALLOCATE_LOCAL(pptNew1);
					DEALLOCATE_LOCAL(pboxNew1);
				}
				return;
			}
			pboxBase = pboxNext = pbox;
			while (pboxBase < pbox+nbox) {
				while ((pboxNext < pbox+nbox) && (pboxNext->y1 == pboxBase->y1))
					pboxNext++;
				pboxTmp = pboxNext;
				pptTmp = pptSrc + (pboxTmp - pbox);
				while (pboxTmp != pboxBase) {
					*pboxNew2++ = *--pboxTmp;
					*pptNew2++ = *--pptTmp;
				}
				pboxBase = pboxNext;
			}
			pboxNew2 -= nbox;
			pbox = pboxNew2;
			pptNew2 -= nbox;
			pptSrc = pptNew2;
		}
	} else {
		/* walk source left to right */
		xdir = 1;
	}

	while (nbox--) {
		int d;
		for (d = 0; d < depthSrc; d++) {
			PixelType *psrcB;
			PixelType *pdstB;

			if (!(planemask & (1 << d)))
				continue;

			psrcB = psrcBase + widthSrc * d;			/* @@@ NEXT PLANE @@@ */
			pdstB = pdstBase + widthDst * d;			/* @@@ NEXT PLANE @@@ */

			w = pbox->x2 - pbox->x1;
			h = pbox->y2 - pbox->y1;

			if (ydir == -1) { /* start at last scanline of rectangle */
				psrcLine = ilbmScanlineDeltaSrc(psrcB, -(pptSrc->y+h-1), auxSrc);
				pdstLine = ilbmScanlineDeltaDst(pdstB, -(pbox->y2-1), auxDst);
			} else { /* start at first scanline */
				psrcLine = ilbmScanlineDeltaSrc(psrcB, pptSrc->y, auxSrc);
				pdstLine = ilbmScanlineDeltaDst(pdstB, pbox->y1, auxDst);
			}
			if ((pbox->x1 & PIM) + w <= PPW) {
				maskpartialbits (pbox->x1, w, startmask);
				endmask = 0;
				nlMiddle = 0;
			} else {
				maskbits(pbox->x1, w, startmask, endmask, nlMiddle);
			}
			if (xdir == 1) {
				xoffSrc = pptSrc->x & PIM;
				xoffDst = pbox->x1 & PIM;
				pdstLine += (pbox->x1 >> PWSH);
				psrcLine += (pptSrc->x >> PWSH);
#ifdef DO_UNALIGNED_BITBLT
				nl = xoffSrc - xoffDst;
				psrcLine = (PixelType *)(((unsigned char *) psrcLine) + nl);
#else
				if (xoffSrc == xoffDst)
#endif
				{
					while (h--) {
						psrc = psrcLine;
						pdst = pdstLine;
						if (startmask) {
							*pdst = MROP_MASK(*psrc, *pdst, startmask);
							psrc++;
							pdst++;
						}
						nl = nlMiddle;

#ifdef LARGE_INSTRUCTION_CACHE
#ifdef FAST_CONSTANT_OFFSET_MODE

						psrc += nl & (UNROLL-1);
						pdst += nl & (UNROLL-1);

#define BodyOdd(n) pdst[-n] = MROP_SOLID (psrc[-n], pdst[-n]);
#define BodyEven(n) pdst[-n] = MROP_SOLID (psrc[-n], pdst[-n]);

#define LoopReset \
pdst += UNROLL; \
psrc += UNROLL;

#else

#define BodyOdd(n)  *pdst = MROP_SOLID (*psrc, *pdst); pdst++; psrc++;
#define BodyEven(n) BodyOdd(n)

#define LoopReset   ;

#endif
						PackedLoop

#undef BodyOdd
#undef BodyEven
#undef LoopReset

#else
#ifdef NOTDEF
						/* you'd think this would be faster --
						 * a single instruction instead of 6
						 * but measurements show it to be ~15% slower
						 */
						while ((nl -= 6) >= 0) {
							asm ("moveml %1+,#0x0c0f;moveml#0x0c0f,%0"
								 : "=m" (*(char *)pdst)
								 : "m" (*(char *)psrc)
								 : "d0", "d1", "d2", "d3",
								   "a2", "a3");
							pdst += 6;
						}
						nl += 6;
						while (nl--)
							*pdst++ = *psrc++;
#endif
						DuffL(nl, label1,
								*pdst = MROP_SOLID (*psrc, *pdst);
								pdst++; psrc++;)
#endif

						if (endmask)
							*pdst = MROP_MASK(*psrc, *pdst, endmask);
						ilbmScanlineIncDst(pdstLine, auxDst);
						ilbmScanlineIncSrc(psrcLine, auxSrc);
					}
				}
#ifndef DO_UNALIGNED_BITBLT
				else {
					if (xoffSrc > xoffDst) {
						leftShift = (xoffSrc - xoffDst);
						rightShift = PPW - leftShift;
					} else {
						rightShift = (xoffDst - xoffSrc);
						leftShift = PPW - rightShift;
					}
					while (h--) {
						psrc = psrcLine;
						pdst = pdstLine;
						bits = 0;
						if (xoffSrc > xoffDst)
							bits = *psrc++;
						if (startmask) {
							bits1 = BitLeft(bits,leftShift);
							bits = *psrc++;
							bits1 |= BitRight(bits,rightShift);
							*pdst = MROP_MASK(bits1, *pdst, startmask);
							pdst++;
						}
						nl = nlMiddle;

#ifdef LARGE_INSTRUCTION_CACHE
						bits1 = bits;

#ifdef FAST_CONSTANT_OFFSET_MODE

						psrc += nl & (UNROLL-1);
						pdst += nl & (UNROLL-1);

#define BodyOdd(n) \
bits = psrc[-n]; \
pdst[-n] = MROP_SOLID(BitLeft(bits1, leftShift) | BitRight(bits, rightShift), pdst[-n]);

#define BodyEven(n) \
bits1 = psrc[-n]; \
pdst[-n] = MROP_SOLID(BitLeft(bits, leftShift) | BitRight(bits1, rightShift), pdst[-n]);

#define LoopReset \
pdst += UNROLL; \
psrc += UNROLL;

#else

#define BodyOdd(n) \
bits = *psrc++; \
*pdst = MROP_SOLID(BitLeft(bits1, leftShift) | BitRight(bits, rightShift), *pdst); \
pdst++;

#define BodyEven(n) \
bits1 = *psrc++; \
*pdst = MROP_SOLID(BitLeft(bits, leftShift) | BitRight(bits1, rightShift), *pdst); \
pdst++;

#define LoopReset   ;

#endif		/* !FAST_CONSTANT_OFFSET_MODE */

						PackedLoop

#undef BodyOdd
#undef BodyEven
#undef LoopReset

#else
						DuffL(nl,label2,
							bits1 = BitLeft(bits, leftShift);
							bits = *psrc++;
							*pdst = MROP_SOLID (bits1 | BitRight(bits, rightShift), *pdst);
							pdst++;
						)
#endif

						if (endmask) {
							bits1 = BitLeft(bits, leftShift);
							if (BitLeft(endmask, rightShift)) {
								bits = *psrc;
									bits1 |= BitRight(bits, rightShift);
							}
							*pdst = MROP_MASK (bits1, *pdst, endmask);
						}
						ilbmScanlineIncDst(pdstLine, auxDst);
						ilbmScanlineIncSrc(psrcLine, auxSrc);
					}
				}
#endif /* DO_UNALIGNED_BITBLT */
			} else {		/* xdir == -1 */
				xoffSrc = (pptSrc->x + w - 1) & PIM;
				xoffDst = (pbox->x2 - 1) & PIM;
				pdstLine += ((pbox->x2-1) >> PWSH) + 1;
				psrcLine += ((pptSrc->x+w - 1) >> PWSH) + 1;
#ifdef DO_UNALIGNED_BITBLT
				nl = xoffSrc - xoffDst;
				psrcLine = (PixelType *)
							(((unsigned char *) psrcLine) + nl);
#else
				if (xoffSrc == xoffDst)
#endif
				{
					while (h--) {
						psrc = psrcLine;
						pdst = pdstLine;
						if (endmask) {
							pdst--;
							psrc--;
							*pdst = MROP_MASK (*psrc, *pdst, endmask);
						}
						nl = nlMiddle;

#ifdef LARGE_INSTRUCTION_CACHE
#ifdef FAST_CONSTANT_OFFSET_MODE
						psrc -= nl & (UNROLL - 1);
						pdst -= nl & (UNROLL - 1);

#define BodyOdd(n) pdst[n-1] = MROP_SOLID (psrc[n-1], pdst[n-1]);

#define BodyEven(n) BodyOdd(n)

#define LoopReset \
pdst -= UNROLL;\
psrc -= UNROLL;

#else

#define BodyOdd(n)  --pdst; --psrc; *pdst = MROP_SOLID(*psrc, *pdst);
#define BodyEven(n) BodyOdd(n)
#define LoopReset   ;

#endif
						PackedLoop

#undef BodyOdd
#undef BodyEven
#undef LoopReset

#else
						DuffL(nl,label3,
							 --pdst; --psrc; *pdst = MROP_SOLID (*psrc, *pdst);)
#endif

						if (startmask) {
							--pdst;
							--psrc;
							*pdst = MROP_MASK(*psrc, *pdst, startmask);
						}
						ilbmScanlineIncDst(pdstLine, auxDst);
						ilbmScanlineIncSrc(psrcLine, auxSrc);
					}
				}
#ifndef DO_UNALIGNED_BITBLT
				else {
					if (xoffDst > xoffSrc) {
						rightShift = (xoffDst - xoffSrc);
						leftShift = PPW - rightShift;
					} else {
						leftShift = (xoffSrc - xoffDst);
						rightShift = PPW - leftShift;
					}
					while (h--) {
						psrc = psrcLine;
						pdst = pdstLine;
						bits = 0;
						if (xoffDst > xoffSrc)
							bits = *--psrc;
						if (endmask) {
							bits1 = BitRight(bits, rightShift);
							bits = *--psrc;
							bits1 |= BitLeft(bits, leftShift);
							pdst--;
							*pdst = MROP_MASK(bits1, *pdst, endmask);
						}
						nl = nlMiddle;

#ifdef LARGE_INSTRUCTION_CACHE
						bits1 = bits;
#ifdef FAST_CONSTANT_OFFSET_MODE
						psrc -= nl & (UNROLL - 1);
						pdst -= nl & (UNROLL - 1);

#define BodyOdd(n) \
bits = psrc[n-1]; \
pdst[n-1] = MROP_SOLID(BitRight(bits1, rightShift) | BitLeft(bits, leftShift),pdst[n-1]);

#define BodyEven(n) \
bits1 = psrc[n-1]; \
pdst[n-1] = MROP_SOLID(BitRight(bits, rightShift) | BitLeft(bits1, leftShift),pdst[n-1]);

#define LoopReset \
pdst -= UNROLL; \
psrc -= UNROLL;

#else

#define BodyOdd(n) \
bits = *--psrc; --pdst; \
*pdst = MROP_SOLID(BitRight(bits1, rightShift) | BitLeft(bits, leftShift),*pdst);

#define BodyEven(n) \
bits1 = *--psrc; --pdst; \
*pdst = MROP_SOLID(BitRight(bits, rightShift) | BitLeft(bits1, leftShift),*pdst);

#define LoopReset   ;

#endif

						PackedLoop

#undef BodyOdd
#undef BodyEven
#undef LoopReset

#else
						DuffL(nl, label4,
							bits1 = BitRight(bits, rightShift);
							bits = *--psrc;
							--pdst;
							*pdst = MROP_SOLID(bits1 | BitLeft(bits, leftShift),*pdst);
						)
#endif

						if (startmask) {
							bits1 = BitRight(bits, rightShift);
							if (BitRight (startmask, leftShift)) {
								bits = *--psrc;
								bits1 |= BitLeft(bits, leftShift);
							}
							--pdst;
							*pdst = MROP_MASK(bits1, *pdst, startmask);
						}
						ilbmScanlineIncDst(pdstLine, auxDst);
						ilbmScanlineIncSrc(psrcLine, auxSrc);
					}
				}
#endif
			}
		}
		pbox++;
		pptSrc++;
	}
	if (pboxNew2) {
		DEALLOCATE_LOCAL(pptNew2);
		DEALLOCATE_LOCAL(pboxNew2);
	}
	if (pboxNew1) {
		DEALLOCATE_LOCAL(pptNew1);
		DEALLOCATE_LOCAL(pboxNew1);
	}
}
