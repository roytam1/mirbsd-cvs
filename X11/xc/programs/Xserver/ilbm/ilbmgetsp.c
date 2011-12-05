/* $XFree86: xc/programs/Xserver/ilbm/ilbmgetsp.c,v 3.0 1996/08/18 01:53:54 dawes Exp $ */
/* Combined Purdue/PurduePlus patches, level 2.0, 1/17/89 */
/***********************************************************

Copyright (c) 1987  X Consortium

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


Copyright 1987 by Digital Equipment Corporation, Maynard, Massachusetts.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its
documentation for any purpose and without fee is hereby granted,
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in
supporting documentation, and that the name of Digital not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.

DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/
/* $XConsortium: ilbmgetsp.c,v 5.10 94/04/17 20:28:24 dpw Exp $ */

/* Modified jun 95 by Geert Uytterhoeven (Geert.Uytterhoeven@cs.kuleuven.ac.be)
   to use interleaved bitplanes instead of normal bitplanes */

#include "X.h"
#include "Xmd.h"

#include "misc.h"
#include "region.h"
#include "gc.h"
#include "windowstr.h"
#include "pixmapstr.h"
#include "scrnintstr.h"

#include "ilbm.h"
#include "maskbits.h"

#include "servermd.h"

/* GetSpans -- for each span, gets bits from drawable starting at ppt[i]
 * and continuing for pwidth[i] bits
 * Each scanline returned will be server scanline padded, i.e., it will come
 * out to an integral number of words.
 */
/*ARGSUSED*/
void
ilbmGetSpans(pDrawable, wMax, ppt, pwidth, nspans, pchardstStart)
	DrawablePtr				pDrawable;		/* drawable from which to get bits */
	int						wMax;				/* largest value of all *pwidths */
	register DDXPointPtr ppt;				/* points to start copying from */
	int						*pwidth;		/* list of number of bits to copy */
	int						nspans;				/* number of scanlines to copy */
	char				*pchardstStart;		/* where to put the bits */
{
	PixelType				*pdstStart = (PixelType *)pchardstStart;
	register PixelType		*pdst;		/* where to put the bits */
	register PixelType		*psrc;		/* where to get the bits */
	register PixelType		tmpSrc;		/* scratch buffer for bits */
	PixelType				*psrcBase;		/* start of src bitmap */
	int						widthSrc;		/* width of pixmap in bytes */
	int						auxSrc;
	int						depthSrc;
	register DDXPointPtr pptLast;		/* one past last point to get */
	int		 		xEnd;				/* last pixel to copy from */
	register int		nstart;
	register int		d;
	int		 				nend;
	int		 				srcStartOver;
	PixelType 				startmask, endmask;
	unsigned int		srcBit;
	int		 				nlMiddle, nl;
	int						w;

	pptLast = ppt + nspans;

	ilbmGetPixelWidthAuxDepthAndPointer(pDrawable, widthSrc, auxSrc, depthSrc,
													psrcBase);
	pdst = pdstStart;

	while (ppt < pptLast) {
		/* XXX should this really be << PWSH, or * 8, or * PGSZB? */
		xEnd = min(ppt->x + *pwidth, widthSrc << PWSH);
		pwidth++;
		for (d = 0; d < depthSrc; d++) {
			psrc = ilbmScanline(psrcBase, ppt->x, ppt->y, auxSrc);
			psrcBase += widthSrc;	/* @@@ NEXT PLANE @@@ */
			w = xEnd - ppt->x;
			srcBit = ppt->x & PIM;

			if (srcBit + w <= PPW)
			{
				getandputbits0(psrc, srcBit, w, pdst);
				pdst++;
			}
			else
			{

				maskbits(ppt->x, w, startmask, endmask, nlMiddle);
				if (startmask)
					nstart = PPW - srcBit;
				else
					nstart = 0;
				if (endmask)
					nend = xEnd & PIM;
				srcStartOver = srcBit + nstart > PLST;
				if (startmask)
				{
					getandputbits0(psrc, srcBit, nstart, pdst);
					if (srcStartOver)
						psrc++;
				}
				nl = nlMiddle;
#ifdef FASTPUTBITS
				Duff(nl, putbits(*psrc, nstart, PPW, pdst); psrc++; pdst++;);
#else
				while (nl--)
				{
					tmpSrc = *psrc;
					putbits(tmpSrc, nstart, PPW, pdst);
					psrc++;
					pdst++;
				}
#endif
				if (endmask)
				{
					putbits(*psrc, nstart, nend, pdst);
					if (nstart + nend > PPW)
						pdst++;
				}
				if (startmask || endmask)
					pdst++;
			}
		}
		ppt++;
	}
}
