/* $XFree86: xc/programs/Xserver/hw/xfree86/xaa/xaaLineMisc.c,v 1.5 1999/01/14 13:05:27 dawes Exp $ */

#include "misc.h"
#include "xf86.h"
#include "xf86_ansic.h"
#include "xf86_OSproc.h"

#include "X.h"
#include "scrnintstr.h"
#include "miline.h"
#include "xf86str.h"
#include "xaa.h"
#include "xaalocal.h"
   

void 
XAASolidHorVertLineAsRects(
   ScrnInfoPtr pScrn,
   int x, int y, int len, int dir
){
    XAAInfoRecPtr infoRec = GET_XAAINFORECPTR_FROM_SCRNINFOPTR(pScrn);

    if(dir == DEGREES_0) 
	(*infoRec->SubsequentSolidFillRect)(pScrn, x, y, len, 1);
    else
	(*infoRec->SubsequentSolidFillRect)(pScrn, x, y, 1, len);
}
   

void 
XAASolidHorVertLineAsTwoPoint(
   ScrnInfoPtr pScrn,
   int x, int y, int len, int dir
){
    XAAInfoRecPtr infoRec = GET_XAAINFORECPTR_FROM_SCRNINFOPTR(pScrn);

    len--;

    if(dir == DEGREES_0) 
	(*infoRec->SubsequentSolidTwoPointLine)(pScrn, x, y, x + len, y, 0);
    else
	(*infoRec->SubsequentSolidTwoPointLine)(pScrn, x, y, x, y + len, 0);
}
   
void 
XAASolidHorVertLineAsBresenham(
   ScrnInfoPtr pScrn,
   int x, int y, int len, int dir
){
    XAAInfoRecPtr infoRec = GET_XAAINFORECPTR_FROM_SCRNINFOPTR(pScrn);

    if(dir == DEGREES_0) 
	(*infoRec->SubsequentSolidBresenhamLine)(
		pScrn, x, y, len << 1, 0, -len, len, 0);
    else
	(*infoRec->SubsequentSolidBresenhamLine)(
		pScrn, x, y, len << 1, 0, -len, len, YMAJOR);
}


void
XAAComputeDash(GCPtr pGC)
{
    XAAInfoRecPtr infoRec = GET_XAAINFORECPTR_FROM_GC(pGC);
    XAAGCPtr   pGCPriv = (XAAGCPtr) (pGC)->devPrivates[XAAGCIndex].ptr;
    Bool EvenDash = (pGC->numInDashList & 0x01) ? FALSE : TRUE;
    int PatternLength = 0;
    unsigned char* DashPtr = (unsigned char*)pGC->dash;
    CARD32 *ptr;
    int count = pGC->numInDashList; 
    int shift, value, direction;
    Bool set;

    if(pGCPriv->DashPattern)
	xfree(pGCPriv->DashPattern);

    pGCPriv->DashPattern = NULL;
    pGCPriv->DashLength = 0; 
 
    while(count--) 
	PatternLength += *(DashPtr++);

    if(!EvenDash)
	PatternLength <<= 1;

    if(PatternLength > infoRec->DashPatternMaxLength) 
	return;

    if((infoRec->DashedLineFlags & LINE_PATTERN_POWER_OF_2_ONLY) && 
				(PatternLength & (PatternLength - 1)))
	return;

    pGCPriv->DashPattern = xcalloc((PatternLength + 31) >> 5, 4);
    if(!pGCPriv->DashPattern) return;
    pGCPriv->DashLength = PatternLength;

    if(infoRec->DashedLineFlags & (LINE_PATTERN_LSBFIRST_MSBJUSTIFIED |
 	 	 		   LINE_PATTERN_LSBFIRST_LSBJUSTIFIED)) {
	direction = 1;
	set = TRUE;
	DashPtr = (unsigned char*)pGC->dash;
    } else {
	direction = -1;
	set = FALSE;
	DashPtr = (unsigned char*)pGC->dash + pGC->numInDashList - 1;
    }

    if(infoRec->DashedLineFlags & (LINE_PATTERN_LSBFIRST_MSBJUSTIFIED |
 	 	 		   LINE_PATTERN_MSBFIRST_MSBJUSTIFIED))
	shift = 32 - (PatternLength & 31);
    else
	shift = 0;

    ptr = (CARD32*)(pGCPriv->DashPattern);

CONCATENATE:

    count = pGC->numInDashList;

    while(count--) {
	value = *DashPtr;
	DashPtr += direction;
	while(value) {
	    if(value < (32 - shift)) {
		if(set) *ptr |= XAAShiftMasks[value] << shift;
		shift += value;
		break;
	     } else {
		if(set) *ptr |= ~0L << shift;
		value -= (32 - shift);
		shift = 0;
		ptr++;
	     }
	}
	if(set) set = FALSE;
	else set = TRUE;
    }

    if(!EvenDash) {
	EvenDash = TRUE;
	if(infoRec->DashedLineFlags & (LINE_PATTERN_LSBFIRST_MSBJUSTIFIED |
				       LINE_PATTERN_LSBFIRST_LSBJUSTIFIED))
	   DashPtr = (unsigned char*)pGC->dash;
	else
	   DashPtr = (unsigned char*)pGC->dash + pGC->numInDashList;
	goto CONCATENATE;
    }
}
