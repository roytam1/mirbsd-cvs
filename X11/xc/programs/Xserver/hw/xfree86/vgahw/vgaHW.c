/* $XFree86: xc/programs/Xserver/hw/xfree86/vgahw/vgaHW.c,v 1.61 2004/10/26 22:26:38 tsi Exp $ */

/*
 * Loosely based on code bearing the following copyright:
 *
 *   Copyright 1990,91 by Thomas Roell, Dinkelscherben, Germany.
 */

/*
 * Copyright 1991-1999 by The XFree86 Project, Inc.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 *   1.  Redistributions of source code must retain the above copyright
 *       notice, this list of conditions, and the following disclaimer.
 *
 *   2.  Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer
 *       in the documentation and/or other materials provided with the
 *       distribution, and in the same place and form as other copyright,
 *       license and disclaimer information.
 *
 *   3.  The end-user documentation included with the redistribution,
 *       if any, must include the following acknowledgment: "This product
 *       includes software developed by The XFree86 Project, Inc
 *       (http://www.xfree86.org/) and its contributors", in the same
 *       place and form as other third-party acknowledgments.  Alternately,
 *       this acknowledgment may appear in the software itself, in the
 *       same form and location as other such third-party acknowledgments.
 *
 *   4.  Except as contained in this notice, the name of The XFree86
 *       Project, Inc shall not be used in advertising or otherwise to
 *       promote the sale, use or other dealings in this Software without
 *       prior written authorization from The XFree86 Project, Inc.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE XFREE86 PROJECT, INC OR ITS CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
 * OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#define _NEED_SYSI86

#include "X.h"
#include "misc.h"

#include "xf86.h"
#include "xf86_OSproc.h"
#include "xf86_ansic.h"
#include "vgaHW.h"

#include "compiler.h"

#include "xf86cmap.h"

#ifndef SAVE_FONT1
#define SAVE_FONT1
#endif

/*
 * These used to be OS-specific, which made this module have an undesirable
 * OS dependency.  Define them by default for all platforms.
 */
#ifndef NEED_SAVED_CMAP
#define NEED_SAVED_CMAP
#endif
#ifndef SAVE_TEXT
#define SAVE_TEXT
#endif
#ifndef SAVE_FONT2
#define SAVE_FONT2
#endif

/* bytes per plane to save for text */
#define TEXT_AMOUNT 16384

/* bytes per plane to save for font data */
#define FONT_AMOUNT (8*8192)

#if 0
/* Override all of these for now */
#undef SAVE_FONT1
#define SAVE_FONT1
#undef SAVE_FONT2
#define SAVE_FONT2
#undef SAVE_TEST
#define SAVE_TEST
#undef FONT_AMOUNT
#define FONT_AMOUNT 65536
#undef TEXT_AMOUNT
#define TEXT_AMOUNT 65536
#endif

/* DAC indices for white and black */
#define WHITE_VALUE 0x3F
#define BLACK_VALUE 0x00
#define OVERSCAN_VALUE 0x01


/* Use a private definition of this here */
#undef VGAHWPTR
#define VGAHWPTRLVAL(p) (p)->privates[vgaHWPrivateIndex].ptr
#define VGAHWPTR(p) ((vgaHWPtr)(VGAHWPTRLVAL(p)))

static int vgaHWPrivateIndex = -1;

#define DAC_TEST_MASK 0x3F

#ifdef NEED_SAVED_CMAP
/* This default colourmap is used only when it can't be read from the VGA */

static CARD8 defaultDAC[768] =
{
     0,  0,  0,    0,  0, 42,    0, 42,  0,    0, 42, 42,
    42,  0,  0,   42,  0, 42,   42, 21,  0,   42, 42, 42,
    21, 21, 21,   21, 21, 63,   21, 63, 21,   21, 63, 63,
    63, 21, 21,   63, 21, 63,   63, 63, 21,   63, 63, 63,
     0,  0,  0,    5,  5,  5,    8,  8,  8,   11, 11, 11,
    14, 14, 14,   17, 17, 17,   20, 20, 20,   24, 24, 24,
    28, 28, 28,   32, 32, 32,   36, 36, 36,   40, 40, 40,
    45, 45, 45,   50, 50, 50,   56, 56, 56,   63, 63, 63,
     0,  0, 63,   16,  0, 63,   31,  0, 63,   47,  0, 63,
    63,  0, 63,   63,  0, 47,   63,  0, 31,   63,  0, 16,
    63,  0,  0,   63, 16,  0,   63, 31,  0,   63, 47,  0,
    63, 63,  0,   47, 63,  0,   31, 63,  0,   16, 63,  0,
     0, 63,  0,    0, 63, 16,    0, 63, 31,    0, 63, 47,
     0, 63, 63,    0, 47, 63,    0, 31, 63,    0, 16, 63,
    31, 31, 63,   39, 31, 63,   47, 31, 63,   55, 31, 63,
    63, 31, 63,   63, 31, 55,   63, 31, 47,   63, 31, 39,
    63, 31, 31,   63, 39, 31,   63, 47, 31,   63, 55, 31,
    63, 63, 31,   55, 63, 31,   47, 63, 31,   39, 63, 31,
    31, 63, 31,   31, 63, 39,   31, 63, 47,   31, 63, 55,
    31, 63, 63,   31, 55, 63,   31, 47, 63,   31, 39, 63,
    45, 45, 63,   49, 45, 63,   54, 45, 63,   58, 45, 63,
    63, 45, 63,   63, 45, 58,   63, 45, 54,   63, 45, 49,
    63, 45, 45,   63, 49, 45,   63, 54, 45,   63, 58, 45,
    63, 63, 45,   58, 63, 45,   54, 63, 45,   49, 63, 45,
    45, 63, 45,   45, 63, 49,   45, 63, 54,   45, 63, 58,
    45, 63, 63,   45, 58, 63,   45, 54, 63,   45, 49, 63,
     0,  0, 28,    7,  0, 28,   14,  0, 28,   21,  0, 28,
    28,  0, 28,   28,  0, 21,   28,  0, 14,   28,  0,  7,
    28,  0,  0,   28,  7,  0,   28, 14,  0,   28, 21,  0,
    28, 28,  0,   21, 28,  0,   14, 28,  0,    7, 28,  0,
     0, 28,  0,    0, 28,  7,    0, 28, 14,    0, 28, 21,
     0, 28, 28,    0, 21, 28,    0, 14, 28,    0,  7, 28,
    14, 14, 28,   17, 14, 28,   21, 14, 28,   24, 14, 28,
    28, 14, 28,   28, 14, 24,   28, 14, 21,   28, 14, 17,
    28, 14, 14,   28, 17, 14,   28, 21, 14,   28, 24, 14,
    28, 28, 14,   24, 28, 14,   21, 28, 14,   17, 28, 14,
    14, 28, 14,   14, 28, 17,   14, 28, 21,   14, 28, 24,
    14, 28, 28,   14, 24, 28,   14, 21, 28,   14, 17, 28,
    20, 20, 28,   22, 20, 28,   24, 20, 28,   26, 20, 28,
    28, 20, 28,   28, 20, 26,   28, 20, 24,   28, 20, 22,
    28, 20, 20,   28, 22, 20,   28, 24, 20,   28, 26, 20,
    28, 28, 20,   26, 28, 20,   24, 28, 20,   22, 28, 20,
    20, 28, 20,   20, 28, 22,   20, 28, 24,   20, 28, 26,
    20, 28, 28,   20, 26, 28,   20, 24, 28,   20, 22, 28,
     0,  0, 16,    4,  0, 16,    8,  0, 16,   12,  0, 16,
    16,  0, 16,   16,  0, 12,   16,  0,  8,   16,  0,  4,
    16,  0,  0,   16,  4,  0,   16,  8,  0,   16, 12,  0,
    16, 16,  0,   12, 16,  0,    8, 16,  0,    4, 16,  0,
     0, 16,  0,    0, 16,  4,    0, 16,  8,    0, 16, 12,
     0, 16, 16,    0, 12, 16,    0,  8, 16,    0,  4, 16,
     8,  8, 16,   10,  8, 16,   12,  8, 16,   14,  8, 16,
    16,  8, 16,   16,  8, 14,   16,  8, 12,   16,  8, 10,
    16,  8,  8,   16, 10,  8,   16, 12,  8,   16, 14,  8,
    16, 16,  8,   14, 16,  8,   12, 16,  8,   10, 16,  8,
     8, 16,  8,    8, 16, 10,    8, 16, 12,    8, 16, 14,
     8, 16, 16,    8, 14, 16,    8, 12, 16,    8, 10, 16,
    11, 11, 16,   12, 11, 16,   13, 11, 16,   15, 11, 16,
    16, 11, 16,   16, 11, 15,   16, 11, 13,   16, 11, 12,
    16, 11, 11,   16, 12, 11,   16, 13, 11,   16, 15, 11,
    16, 16, 11,   15, 16, 11,   13, 16, 11,   12, 16, 11,
    11, 16, 11,   11, 16, 12,   11, 16, 13,   11, 16, 15,
    11, 16, 16,   11, 15, 16,   11, 13, 16,   11, 12, 16,
     0,  0,  0,    0,  0,  0,    0,  0,  0,    0,  0,  0,
     0,  0,  0,    0,  0,  0,    0,  0,  0,    0,  0,  0,
};
#endif /* NEED_SAVED_CMAP */

/*
 * Standard VGA versions of the register access functions.
 */
static void
stdWriteCrtc(vgaHWPtr hwp, CARD8 index, CARD8 value)
{
    outb(hwp->IOBase + hwp->PIOOffset + VGA_CRTC_INDEX_OFFSET, index);
    outb(hwp->IOBase + hwp->PIOOffset + VGA_CRTC_DATA_OFFSET, value);
}

static CARD8
stdReadCrtc(vgaHWPtr hwp, CARD8 index)
{
    outb(hwp->IOBase + hwp->PIOOffset + VGA_CRTC_INDEX_OFFSET, index);
    return inb(hwp->IOBase + hwp->PIOOffset + VGA_CRTC_DATA_OFFSET);
}

static void
stdWriteGr(vgaHWPtr hwp, CARD8 index, CARD8 value)
{
    outb(hwp->PIOOffset + VGA_GRAPH_INDEX, index);
    outb(hwp->PIOOffset + VGA_GRAPH_DATA, value);
}

static CARD8
stdReadGr(vgaHWPtr hwp, CARD8 index)
{
    outb(hwp->PIOOffset + VGA_GRAPH_INDEX, index);
    return inb(hwp->PIOOffset + VGA_GRAPH_DATA);
}

static void
stdWriteSeq(vgaHWPtr hwp, CARD8 index, CARD8 value)
{
    outb(hwp->PIOOffset + VGA_SEQ_INDEX, index);
    outb(hwp->PIOOffset + VGA_SEQ_DATA, value);
}

static CARD8
stdReadSeq(vgaHWPtr hwp, CARD8 index)
{
    outb(hwp->PIOOffset + VGA_SEQ_INDEX, index);
    return inb(hwp->PIOOffset + VGA_SEQ_DATA);
}

static CARD8
stdReadST00(vgaHWPtr hwp)
{
    return inb(hwp->PIOOffset + VGA_IN_STAT_0);
}

static CARD8
stdReadST01(vgaHWPtr hwp)
{
    return inb(hwp->IOBase + hwp->PIOOffset + VGA_IN_STAT_1_OFFSET);
}

static CARD8
stdReadFCR(vgaHWPtr hwp)
{
    return inb(hwp->PIOOffset + VGA_FEATURE_R);
}

static void
stdWriteFCR(vgaHWPtr hwp, CARD8 value)
{
    outb(hwp->IOBase + hwp->PIOOffset + VGA_FEATURE_W_OFFSET,value);
}

static void
stdWriteAttr(vgaHWPtr hwp, CARD8 index, CARD8 value)
{
    if (hwp->paletteEnabled)
	index &= ~0x20;
    else
	index |= 0x20;

    (void) inb(hwp->IOBase + hwp->PIOOffset + VGA_IN_STAT_1_OFFSET);
    outb(hwp->PIOOffset + VGA_ATTR_INDEX, index);
    outb(hwp->PIOOffset + VGA_ATTR_DATA_W, value);
}

static CARD8
stdReadAttr(vgaHWPtr hwp, CARD8 index)
{
    if (hwp->paletteEnabled)
	index &= ~0x20;
    else
	index |= 0x20;

    (void) inb(hwp->IOBase + hwp->PIOOffset + VGA_IN_STAT_1_OFFSET);
    outb(hwp->PIOOffset + VGA_ATTR_INDEX, index);
    return inb(hwp->PIOOffset + VGA_ATTR_DATA_R);
}

static void
stdWriteMiscOut(vgaHWPtr hwp, CARD8 value)
{
    outb(hwp->PIOOffset + VGA_MISC_OUT_W, value);
}

static CARD8
stdReadMiscOut(vgaHWPtr hwp)
{
    return inb(hwp->PIOOffset + VGA_MISC_OUT_R);
}

static void
stdEnablePalette(vgaHWPtr hwp)
{
    (void) inb(hwp->IOBase + hwp->PIOOffset + VGA_IN_STAT_1_OFFSET);
    outb(hwp->PIOOffset + VGA_ATTR_INDEX, 0x00);
    hwp->paletteEnabled = TRUE;
}

static void
stdDisablePalette(vgaHWPtr hwp)
{
    (void) inb(hwp->IOBase + hwp->PIOOffset + VGA_IN_STAT_1_OFFSET);
    outb(hwp->PIOOffset + VGA_ATTR_INDEX, 0x20);
    hwp->paletteEnabled = FALSE;
}

static void
stdWriteDacMask(vgaHWPtr hwp, CARD8 value)
{
    outb(hwp->PIOOffset + VGA_DAC_MASK, value);
}

static CARD8
stdReadDacMask(vgaHWPtr hwp)
{
    return inb(hwp->PIOOffset + VGA_DAC_MASK);
}

static void
stdWriteDacReadAddr(vgaHWPtr hwp, CARD8 value)
{
    outb(hwp->PIOOffset + VGA_DAC_READ_ADDR, value);
}

static void
stdWriteDacWriteAddr(vgaHWPtr hwp, CARD8 value)
{
    outb(hwp->PIOOffset + VGA_DAC_WRITE_ADDR, value);
}

static void
stdWriteDacData(vgaHWPtr hwp, CARD8 value)
{
    outb(hwp->PIOOffset + VGA_DAC_DATA, value);
}

static CARD8
stdReadDacData(vgaHWPtr hwp)
{
    return inb(hwp->PIOOffset + VGA_DAC_DATA);
}

static CARD8
stdReadEnable(vgaHWPtr hwp)
{
    return inb(hwp->PIOOffset + VGA_ENABLE);
}

static void
stdWriteEnable(vgaHWPtr hwp, CARD8 value)
{
    outb(hwp->PIOOffset + VGA_ENABLE, value);
}

void
vgaHWSetStdFuncs(vgaHWPtr hwp)
{
    hwp->writeCrtc		= stdWriteCrtc;
    hwp->readCrtc		= stdReadCrtc;
    hwp->writeGr		= stdWriteGr;
    hwp->readGr			= stdReadGr;
    hwp->readST00               = stdReadST00;
    hwp->readST01               = stdReadST01;
    hwp->readFCR                = stdReadFCR;
    hwp->writeFCR               = stdWriteFCR;
    hwp->writeAttr		= stdWriteAttr;
    hwp->readAttr		= stdReadAttr;
    hwp->writeSeq		= stdWriteSeq;
    hwp->readSeq		= stdReadSeq;
    hwp->writeMiscOut		= stdWriteMiscOut;
    hwp->readMiscOut		= stdReadMiscOut;
    hwp->enablePalette		= stdEnablePalette;
    hwp->disablePalette		= stdDisablePalette;
    hwp->writeDacMask		= stdWriteDacMask;
    hwp->readDacMask		= stdReadDacMask;
    hwp->writeDacWriteAddr	= stdWriteDacWriteAddr;
    hwp->writeDacReadAddr	= stdWriteDacReadAddr;
    hwp->writeDacData		= stdWriteDacData;
    hwp->readDacData		= stdReadDacData;
    hwp->PIOOffset		= 0;
    hwp->readEnable		= stdReadEnable;
    hwp->writeEnable		= stdWriteEnable;
}

/*
 * MMIO versions of the register access functions.  These require
 * hwp->MemBase to be set in such a way that when the standard VGA port
 * adderss is added the correct memory address results.
 */

#define minb(p) MMIO_IN8(hwp->MMIOBase, (hwp->MMIOOffset + (p)))
#define moutb(p,v) MMIO_OUT8(hwp->MMIOBase, (hwp->MMIOOffset + (p)),(v))

static void
mmioWriteCrtc(vgaHWPtr hwp, CARD8 index, CARD8 value)
{
    moutb(hwp->IOBase + VGA_CRTC_INDEX_OFFSET, index);
    moutb(hwp->IOBase + VGA_CRTC_DATA_OFFSET, value);
}

static CARD8
mmioReadCrtc(vgaHWPtr hwp, CARD8 index)
{
    moutb(hwp->IOBase + VGA_CRTC_INDEX_OFFSET, index);
    return minb(hwp->IOBase + VGA_CRTC_DATA_OFFSET);
}

static void
mmioWriteGr(vgaHWPtr hwp, CARD8 index, CARD8 value)
{
    moutb(VGA_GRAPH_INDEX, index);
    moutb(VGA_GRAPH_DATA, value);
}

static CARD8
mmioReadGr(vgaHWPtr hwp, CARD8 index)
{
    moutb(VGA_GRAPH_INDEX, index);
    return minb(VGA_GRAPH_DATA);
}

static void
mmioWriteSeq(vgaHWPtr hwp, CARD8 index, CARD8 value)
{
    moutb(VGA_SEQ_INDEX, index);
    moutb(VGA_SEQ_DATA, value);
}

static CARD8
mmioReadSeq(vgaHWPtr hwp, CARD8 index)
{
    moutb(VGA_SEQ_INDEX, index);
    return minb(VGA_SEQ_DATA);
}

static CARD8
mmioReadST00(vgaHWPtr hwp)
{
    return minb(VGA_IN_STAT_0);
}

static CARD8
mmioReadST01(vgaHWPtr hwp)
{
    return minb(hwp->IOBase + VGA_IN_STAT_1_OFFSET);
}

static CARD8
mmioReadFCR(vgaHWPtr hwp)
{
    return minb(VGA_FEATURE_R);
}

static void
mmioWriteFCR(vgaHWPtr hwp, CARD8 value)
{
    moutb(hwp->IOBase + VGA_FEATURE_W_OFFSET,value);
}

static void
mmioWriteAttr(vgaHWPtr hwp, CARD8 index, CARD8 value)
{
    if (hwp->paletteEnabled)
	index &= ~0x20;
    else
	index |= 0x20;

    (void) minb(hwp->IOBase + VGA_IN_STAT_1_OFFSET);
    moutb(VGA_ATTR_INDEX, index);
    moutb(VGA_ATTR_DATA_W, value);
}

static CARD8
mmioReadAttr(vgaHWPtr hwp, CARD8 index)
{
    if (hwp->paletteEnabled)
	index &= ~0x20;
    else
	index |= 0x20;

    (void) minb(hwp->IOBase + VGA_IN_STAT_1_OFFSET);
    moutb(VGA_ATTR_INDEX, index);
    return minb(VGA_ATTR_DATA_R);
}

static void
mmioWriteMiscOut(vgaHWPtr hwp, CARD8 value)
{
    moutb(VGA_MISC_OUT_W, value);
}

static CARD8
mmioReadMiscOut(vgaHWPtr hwp)
{
    return minb(VGA_MISC_OUT_R);
}

static void
mmioEnablePalette(vgaHWPtr hwp)
{
    (void) minb(hwp->IOBase + VGA_IN_STAT_1_OFFSET);
    moutb(VGA_ATTR_INDEX, 0x00);
    hwp->paletteEnabled = TRUE;
}

static void
mmioDisablePalette(vgaHWPtr hwp)
{
    (void) minb(hwp->IOBase + VGA_IN_STAT_1_OFFSET);
    moutb(VGA_ATTR_INDEX, 0x20);
    hwp->paletteEnabled = FALSE;
}

static void
mmioWriteDacMask(vgaHWPtr hwp, CARD8 value)
{
    moutb(VGA_DAC_MASK, value);
}

static CARD8
mmioReadDacMask(vgaHWPtr hwp)
{
    return minb(VGA_DAC_MASK);
}

static void
mmioWriteDacReadAddr(vgaHWPtr hwp, CARD8 value)
{
    moutb(VGA_DAC_READ_ADDR, value);
}

static void
mmioWriteDacWriteAddr(vgaHWPtr hwp, CARD8 value)
{
    moutb(VGA_DAC_WRITE_ADDR, value);
}

static void
mmioWriteDacData(vgaHWPtr hwp, CARD8 value)
{
    moutb(VGA_DAC_DATA, value);
}

static CARD8
mmioReadDacData(vgaHWPtr hwp)
{
    return minb(VGA_DAC_DATA);
}

static CARD8
mmioReadEnable(vgaHWPtr hwp)
{
    return minb(VGA_ENABLE);
}

static void
mmioWriteEnable(vgaHWPtr hwp, CARD8 value)
{
    moutb(VGA_ENABLE, value);
}

void
vgaHWSetMmioFuncs(vgaHWPtr hwp, CARD8 *base, int offset)
{
    hwp->writeCrtc		= mmioWriteCrtc;
    hwp->readCrtc		= mmioReadCrtc;
    hwp->writeGr		= mmioWriteGr;
    hwp->readGr			= mmioReadGr;
    hwp->readST00               = mmioReadST00;
    hwp->readST01               = mmioReadST01;
    hwp->readFCR                = mmioReadFCR;
    hwp->writeFCR               = mmioWriteFCR;
    hwp->writeAttr		= mmioWriteAttr;
    hwp->readAttr		= mmioReadAttr;
    hwp->writeSeq		= mmioWriteSeq;
    hwp->readSeq		= mmioReadSeq;
    hwp->writeMiscOut		= mmioWriteMiscOut;
    hwp->readMiscOut		= mmioReadMiscOut;
    hwp->enablePalette		= mmioEnablePalette;
    hwp->disablePalette		= mmioDisablePalette;
    hwp->writeDacMask		= mmioWriteDacMask;
    hwp->readDacMask		= mmioReadDacMask;
    hwp->writeDacWriteAddr	= mmioWriteDacWriteAddr;
    hwp->writeDacReadAddr	= mmioWriteDacReadAddr;
    hwp->writeDacData		= mmioWriteDacData;
    hwp->readDacData		= mmioReadDacData;
    hwp->MMIOBase		= base;
    hwp->MMIOOffset		= offset;
    hwp->readEnable		= mmioReadEnable;
    hwp->writeEnable		= mmioWriteEnable;
}

/*
 * vgaHWProtect --
 *	Protect VGA registers and memory from corruption during loads.
 */

void
vgaHWProtect(ScrnInfoPtr pScrn, Bool on)
{
  vgaHWPtr hwp = VGAHWPTR(pScrn);
  
  unsigned char tmp;
  
  if (pScrn->vtSema) {
    if (on) {
      /*
       * Turn off screen and disable sequencer.
       */
      tmp = hwp->readSeq(hwp, 0x01);

      vgaHWSeqReset(hwp, TRUE);			/* start synchronous reset */
      hwp->writeSeq(hwp, 0x01, tmp | 0x20);	/* disable the display */

      hwp->enablePalette(hwp);
    } else {
      /*
       * Reenable sequencer, then turn on screen.
       */
  
      tmp = hwp->readSeq(hwp, 0x01);

      hwp->writeSeq(hwp, 0x01, tmp & ~0x20);	/* reenable display */
      vgaHWSeqReset(hwp, FALSE);		/* clear synchronousreset */

      hwp->disablePalette(hwp);
    }
  }
}


/*
 * vgaHWBlankScreen -- blank the screen.
 */

void
vgaHWBlankScreen(ScrnInfoPtr pScrn, Bool on)
{
  vgaHWPtr hwp = VGAHWPTR(pScrn);
  unsigned char scrn;

  scrn = hwp->readSeq(hwp, 0x01);

  if (on) {
    scrn &= ~0x20;			/* enable screen */
  } else {
    scrn |= 0x20;			/* blank screen */
  }

  vgaHWSeqReset(hwp, TRUE);
  hwp->writeSeq(hwp, 0x01, scrn);	/* change mode */
  vgaHWSeqReset(hwp, FALSE);
}


/*
 * vgaHWSaveScreen -- blank the screen.
 */

Bool
vgaHWSaveScreen(ScreenPtr pScreen, int mode)
{
   ScrnInfoPtr pScrn = NULL;
   Bool on;

   if (pScreen != NULL)
      pScrn = xf86Screens[pScreen->myNum];

   on = xf86IsUnblank(mode);

#if 0
   if (on)
      SetTimeSinceLastInputEvent();
#endif

   if ((pScrn != NULL) && pScrn->vtSema) {
     vgaHWBlankScreen(pScrn, on);
   }
   return (TRUE);
}


/*
 * vgaHWDPMSSet -- Sets VESA Display Power Management Signaling (DPMS) Mode
 *
 * This generic VGA function can only set the Off and On modes.  If the
 * Standby and Suspend modes are to be supported, a chip specific replacement
 * for this function must be written.
 */

void
vgaHWDPMSSet(ScrnInfoPtr pScrn, int PowerManagementMode, int flags)
{
  unsigned char seq1 = 0, crtc17 = 0;
  vgaHWPtr hwp = VGAHWPTR(pScrn);

  if (!pScrn->vtSema) return;

  switch (PowerManagementMode) {
  case DPMSModeOn:
    /* Screen: On; HSync: On, VSync: On */
    seq1 = 0x00;
    crtc17 = 0x80;
    break;
  case DPMSModeStandby:
    /* Screen: Off; HSync: Off, VSync: On -- Not Supported */
    seq1 = 0x20;
    crtc17 = 0x80;
    break;
  case DPMSModeSuspend:
    /* Screen: Off; HSync: On, VSync: Off -- Not Supported */
    seq1 = 0x20;
    crtc17 = 0x80;
    break;
  case DPMSModeOff:
    /* Screen: Off; HSync: Off, VSync: Off */
    seq1 = 0x20;
    crtc17 = 0x00;
    break;
  }
  hwp->writeSeq(hwp, 0x00, 0x01);		/* Synchronous Reset */
  seq1 |= hwp->readSeq(hwp, 0x01) & ~0x20;
  hwp->writeSeq(hwp, 0x01, seq1);
  crtc17 |= hwp->readCrtc(hwp, 0x17) & ~0x80;
  usleep(10000);
  hwp->writeCrtc(hwp, 0x17, crtc17);
  hwp->writeSeq(hwp, 0x00, 0x03);		/* End Reset */
}


/*
 * vgaHWSeqReset
 *      perform a sequencer reset.
 */

void
vgaHWSeqReset(vgaHWPtr hwp, Bool start)
{
  if (start)
    hwp->writeSeq(hwp, 0x00, 0x01);		/* Synchronous Reset */
  else
    hwp->writeSeq(hwp, 0x00, 0x03);		/* End Reset */
}


void
vgaHWRestoreFonts(ScrnInfoPtr scrninfp, vgaRegPtr restore)
{
    vgaHWPtr hwp = VGAHWPTR(scrninfp);
    int savedIOBase;
    unsigned char miscOut, attr10, gr1, gr3, gr4, gr5, gr6, gr8, seq2, seq4;
    Bool doMap = FALSE;

#if defined(SAVE_TEXT) || defined(SAVE_FONT1) || defined(SAVE_FONT2)

    /* If nothing to do, return now */
    if (!hwp->FontInfo1 && !hwp->FontInfo2 && !hwp->TextInfo)
	return;

    if (hwp->Base == NULL) {
	doMap = TRUE;
	if (!vgaHWMapMem(scrninfp)) {
	    xf86DrvMsg(scrninfp->scrnIndex, X_ERROR,
		       "vgaHWRestoreFonts: vgaHWMapMem() failed\n");
	    return;
	}
    }

    /* save the registers that are needed here */
    miscOut = hwp->readMiscOut(hwp);
    attr10 = hwp->readAttr(hwp, 0x10);
    gr1 = hwp->readGr(hwp, 0x01);
    gr3 = hwp->readGr(hwp, 0x03);
    gr4 = hwp->readGr(hwp, 0x04);
    gr5 = hwp->readGr(hwp, 0x05);
    gr6 = hwp->readGr(hwp, 0x06);
    gr8 = hwp->readGr(hwp, 0x08);
    seq2 = hwp->readSeq(hwp, 0x02);
    seq4 = hwp->readSeq(hwp, 0x04);

    /* save hwp->IOBase and temporarily set it for colour mode */
    savedIOBase = hwp->IOBase;
    hwp->IOBase = VGA_IOBASE_COLOR;

    /* Force into colour mode */
    hwp->writeMiscOut(hwp, miscOut | 0x01);

    vgaHWBlankScreen(scrninfp, FALSE);

    /*
     * here we temporarily switch to 16 colour planar mode, to simply
     * copy the font-info and saved text.
     *
     * BUG ALERT: The (S)VGA's segment-select register MUST be set correctly!
     */
#if 0
    hwp->writeAttr(hwp, 0x10, 0x01);	/* graphics mode */
#endif

    hwp->writeSeq(hwp, 0x04, 0x06);	/* enable plane graphics */
    hwp->writeGr(hwp, 0x05, 0x00);	/* write mode 0, read mode 0 */
    hwp->writeGr(hwp, 0x06, 0x05);	/* set graphics */

    if (scrninfp->depth == 4) {
	/* GJA */
	hwp->writeGr(hwp, 0x03, 0x00);	/* don't rotate, write unmodified */
	hwp->writeGr(hwp, 0x08, 0xFF);	/* write all bits in a byte */
	hwp->writeGr(hwp, 0x01, 0x00);	/* all planes come from CPU */
    }

#ifdef SAVE_FONT1
    if (hwp->FontInfo1) {
	hwp->writeSeq(hwp, 0x02, 0x04);	/* write to plane 2 */
	hwp->writeGr(hwp, 0x04, 0x02);	/* read plane 2 */
	slowbcopy_tobus(hwp->FontInfo1, hwp->Base, FONT_AMOUNT);
    }
#endif

#ifdef SAVE_FONT2
    if (hwp->FontInfo2) {
	hwp->writeSeq(hwp, 0x02, 0x08);	/* write to plane 3 */
	hwp->writeGr(hwp, 0x04, 0x03);	/* read plane 3 */
	slowbcopy_tobus(hwp->FontInfo2, hwp->Base, FONT_AMOUNT);
    }
#endif

#ifdef SAVE_TEXT
    if (hwp->TextInfo) {
	hwp->writeSeq(hwp, 0x02, 0x01);	/* write to plane 0 */
	hwp->writeGr(hwp, 0x04, 0x00);	/* read plane 0 */
	slowbcopy_tobus(hwp->TextInfo, hwp->Base, TEXT_AMOUNT);
	hwp->writeSeq(hwp, 0x02, 0x02);	/* write to plane 1 */
	hwp->writeGr(hwp, 0x04, 0x01);	/* read plane 1 */
	slowbcopy_tobus((unsigned char *)hwp->TextInfo + TEXT_AMOUNT,
			hwp->Base, TEXT_AMOUNT);
    }
#endif

    vgaHWBlankScreen(scrninfp, TRUE);

    /* restore the registers that were changed */
    hwp->writeMiscOut(hwp, miscOut);
    hwp->writeAttr(hwp, 0x10, attr10);
    hwp->writeGr(hwp, 0x01, gr1);
    hwp->writeGr(hwp, 0x03, gr3);
    hwp->writeGr(hwp, 0x04, gr4);
    hwp->writeGr(hwp, 0x05, gr5);
    hwp->writeGr(hwp, 0x06, gr6);
    hwp->writeGr(hwp, 0x08, gr8);
    hwp->writeSeq(hwp, 0x02, seq2);
    hwp->writeSeq(hwp, 0x04, seq4);
    hwp->IOBase = savedIOBase;

    if (doMap)
	vgaHWUnmapMem(scrninfp);

#endif /* defined(SAVE_TEXT) || defined(SAVE_FONT1) || defined(SAVE_FONT2) */
}


void
vgaHWRestoreMode(ScrnInfoPtr scrninfp, vgaRegPtr restore)
{
    vgaHWPtr hwp = VGAHWPTR(scrninfp);
    int i;

    if (restore->MiscOutReg & 0x01)
	hwp->IOBase = VGA_IOBASE_COLOR;
    else
	hwp->IOBase = VGA_IOBASE_MONO;

    hwp->writeMiscOut(hwp, restore->MiscOutReg);

    for (i = 1; i < restore->numSequencer; i++)
	hwp->writeSeq(hwp, i, restore->Sequencer[i]);
  
    /* Ensure CRTC registers 0-7 are unlocked by clearing bit 7 of CRTC[17] */
    hwp->writeCrtc(hwp, 17, restore->CRTC[17] & ~0x80);

    for (i = 0; i < restore->numCRTC; i++)
	hwp->writeCrtc(hwp, i, restore->CRTC[i]);

    for (i = 0; i < restore->numGraphics; i++)
	hwp->writeGr(hwp, i, restore->Graphics[i]);

    hwp->enablePalette(hwp);
    for (i = 0; i < restore->numAttribute; i++)
	hwp->writeAttr(hwp, i, restore->Attribute[i]);
    hwp->disablePalette(hwp);
}


void
vgaHWRestoreColormap(ScrnInfoPtr scrninfp, vgaRegPtr restore)
{
    vgaHWPtr hwp = VGAHWPTR(scrninfp);
    int i;

#if 0
    hwp->enablePalette(hwp);
#endif

    hwp->writeDacMask(hwp, 0xFF);
    hwp->writeDacWriteAddr(hwp, 0x00);
    for (i = 0; i < 768; i++) {
	hwp->writeDacData(hwp, restore->DAC[i]);
	DACDelay(hwp);
    }

    hwp->disablePalette(hwp);
}


/*
 * vgaHWRestore --
 *      restore the VGA state
 */

void
vgaHWRestore(ScrnInfoPtr scrninfp, vgaRegPtr restore, int flags)
{
    if (flags & VGA_SR_MODE)
	vgaHWRestoreMode(scrninfp, restore);

    if (flags & VGA_SR_FONTS)
	vgaHWRestoreFonts(scrninfp, restore);

    if (flags & VGA_SR_CMAP)
	vgaHWRestoreColormap(scrninfp, restore);
}

void
vgaHWSaveFonts(ScrnInfoPtr scrninfp, vgaRegPtr save)
{
    vgaHWPtr hwp = VGAHWPTR(scrninfp);
    int savedIOBase;
    unsigned char miscOut, attr10, gr4, gr5, gr6, seq2, seq4;
    Bool doMap = FALSE;

#if defined(SAVE_TEXT) || defined(SAVE_FONT1) || defined(SAVE_FONT2)

    if (hwp->Base == NULL) {
	doMap = TRUE;
	if (!vgaHWMapMem(scrninfp)) {
	    xf86DrvMsg(scrninfp->scrnIndex, X_ERROR,
		       "vgaHWSaveFonts: vgaHWMapMem() failed\n");
	    return;
	}
    }

    /* If in graphics mode, don't save anything */
    attr10 = hwp->readAttr(hwp, 0x10);
    if (attr10 & 0x01)
	return;

    /* save the registers that are needed here */
    miscOut = hwp->readMiscOut(hwp);
    gr4 = hwp->readGr(hwp, 0x04);
    gr5 = hwp->readGr(hwp, 0x05);
    gr6 = hwp->readGr(hwp, 0x06);
    seq2 = hwp->readSeq(hwp, 0x02);
    seq4 = hwp->readSeq(hwp, 0x04);

    /* save hwp->IOBase and temporarily set it for colour mode */
    savedIOBase = hwp->IOBase;
    hwp->IOBase = VGA_IOBASE_COLOR;

    /* Force into colour mode */
    hwp->writeMiscOut(hwp, miscOut | 0x01);

    vgaHWBlankScreen(scrninfp, FALSE);
  
    /*
     * get the character sets, and text screen if required
     */
    /*
     * Here we temporarily switch to 16 colour planar mode, to simply
     * copy the font-info
     *
     * BUG ALERT: The (S)VGA's segment-select register MUST be set correctly!
     */
#if 0
    hwp->writeAttr(hwp, 0x10, 0x01);	/* graphics mode */
#endif

    hwp->writeSeq(hwp, 0x04, 0x06);	/* enable plane graphics */
    hwp->writeGr(hwp, 0x05, 0x00);	/* write mode 0, read mode 0 */
    hwp->writeGr(hwp, 0x06, 0x05);	/* set graphics */

#ifdef SAVE_FONT1
    if (hwp->FontInfo1 || (hwp->FontInfo1 = xalloc(FONT_AMOUNT))) {
	hwp->writeSeq(hwp, 0x02, 0x04);	/* write to plane 2 */
	hwp->writeGr(hwp, 0x04, 0x02);	/* read plane 2 */
	slowbcopy_frombus(hwp->Base, hwp->FontInfo1, FONT_AMOUNT);
    }
#endif /* SAVE_FONT1 */
#ifdef SAVE_FONT2
    if (hwp->FontInfo2 || (hwp->FontInfo2 = xalloc(FONT_AMOUNT))) {
	hwp->writeSeq(hwp, 0x02, 0x08);	/* write to plane 3 */
	hwp->writeGr(hwp, 0x04, 0x03);	/* read plane 3 */
	slowbcopy_frombus(hwp->Base, hwp->FontInfo2, FONT_AMOUNT);
    }
#endif /* SAVE_FONT2 */
#ifdef SAVE_TEXT
    if (hwp->TextInfo || (hwp->TextInfo = xalloc(2 * TEXT_AMOUNT))) {
	hwp->writeSeq(hwp, 0x02, 0x01);	/* write to plane 0 */
	hwp->writeGr(hwp, 0x04, 0x00);	/* read plane 0 */
	slowbcopy_frombus(hwp->Base, hwp->TextInfo, TEXT_AMOUNT);
	hwp->writeSeq(hwp, 0x02, 0x02);	/* write to plane 1 */
	hwp->writeGr(hwp, 0x04, 0x01);	/* read plane 1 */
	slowbcopy_frombus(hwp->Base,
		(unsigned char *)hwp->TextInfo + TEXT_AMOUNT, TEXT_AMOUNT);
    }
#endif /* SAVE_TEXT */

    /* Restore clobbered registers */
    hwp->writeAttr(hwp, 0x10, attr10);
    hwp->writeSeq(hwp, 0x02, seq2);
    hwp->writeSeq(hwp, 0x04, seq4);
    hwp->writeGr(hwp, 0x04, gr4);
    hwp->writeGr(hwp, 0x05, gr5);
    hwp->writeGr(hwp, 0x06, gr6);
    hwp->writeMiscOut(hwp, miscOut);
    hwp->IOBase = savedIOBase;

    vgaHWBlankScreen(scrninfp, TRUE);

    if (doMap)
	vgaHWUnmapMem(scrninfp);

#endif /* defined(SAVE_TEXT) || defined(SAVE_FONT1) || defined(SAVE_FONT2) */
}

void
vgaHWSaveMode(ScrnInfoPtr scrninfp, vgaRegPtr save)
{
    vgaHWPtr hwp = VGAHWPTR(scrninfp);
    int i;

    save->MiscOutReg = hwp->readMiscOut(hwp);
    if (save->MiscOutReg & 0x01)
	hwp->IOBase = VGA_IOBASE_COLOR;
    else
	hwp->IOBase = VGA_IOBASE_MONO;

    for (i = 0; i < save->numCRTC; i++) {
	save->CRTC[i] = hwp->readCrtc(hwp, i);
#ifdef DEBUG
	ErrorF("CRTC[0x%02x] = 0x%02x\n", i, save->CRTC[i]);
#endif
    }

    hwp->enablePalette(hwp);
    for (i = 0; i < save->numAttribute; i++) {
	save->Attribute[i] = hwp->readAttr(hwp, i);
#ifdef DEBUG
	ErrorF("Attribute[0x%02x] = 0x%02x\n", i, save->Attribute[i]);
#endif
    }
    hwp->disablePalette(hwp);

    for (i = 0; i < save->numGraphics; i++) {
	save->Graphics[i] = hwp->readGr(hwp, i);
#ifdef DEBUG
	ErrorF("Graphics[0x%02x] = 0x%02x\n", i, save->Graphics[i]);
#endif
    }

    for (i = 1; i < save->numSequencer; i++) {
	save->Sequencer[i] = hwp->readSeq(hwp, i);
#ifdef DEBUG
	ErrorF("Sequencer[0x%02x] = 0x%02x\n", i, save->Sequencer[i]);
#endif
    }
}


void
vgaHWSaveColormap(ScrnInfoPtr scrninfp, vgaRegPtr save)
{
    vgaHWPtr hwp = VGAHWPTR(scrninfp);
    Bool readError = FALSE;
    int i;

#ifdef NEED_SAVED_CMAP
    /*
     * Some ET4000 chips from 1991 have a HW bug that prevents the reading
     * of the color lookup table.  Mask rev 9042EAI is known to have this bug.
     *
     * If the colourmap is not readable, we set the saved map to a default
     * map (taken from Ferraro's "Programmer's Guide to the EGA and VGA
     * Cards" 2nd ed).
     */

    /* Only save it once */
    if (hwp->cmapSaved)
	return;

#if 0
    hwp->enablePalette(hwp);
#endif

    hwp->writeDacMask(hwp, 0xFF);

    /*
     * check if we can read the lookup table
     */
    hwp->writeDacReadAddr(hwp, 0x00);
    for (i = 0; i < 6; i++) {
	save->DAC[i] = hwp->readDacData(hwp);
#ifdef DEBUG
	switch (i % 3) {
	case 0:
	    ErrorF("DAC[0x%02x] = 0x%02x, ", i / 3, save->DAC[i]);
	    break;
	case 1:
	    ErrorF("0x%02x, ", save->DAC[i]);
	    break;
	case 2:
	    ErrorF("0x%02x\n", save->DAC[i]);
	}
#endif
    }

    /*
     * Check if we can read the palette -
     * use foreground color to prevent flashing.
     */
    hwp->writeDacWriteAddr(hwp, 0x01);
    for (i = 3; i < 6; i++)
	hwp->writeDacData(hwp, ~save->DAC[i] & DAC_TEST_MASK);
    hwp->writeDacReadAddr(hwp, 0x01);
    for (i = 3; i < 6; i++) {
	if (hwp->readDacData(hwp) != (~save->DAC[i] & DAC_TEST_MASK))
	    readError = TRUE;
    }
    hwp->writeDacWriteAddr(hwp, 0x01);
    for (i = 3; i < 6; i++)
	hwp->writeDacData(hwp, save->DAC[i]);

    if (readError) {
	/*			 
	 * save the default lookup table
	 */
	memmove(save->DAC, defaultDAC, 768);
	xf86DrvMsg(scrninfp->scrnIndex, X_WARNING,
	   "Cannot read colourmap from VGA.  Will restore with default\n");
    } else {
	/* save the colourmap */
	hwp->writeDacReadAddr(hwp, 0x02);
	for (i = 6; i < 768; i++) {
	    save->DAC[i] = hwp->readDacData(hwp);
	    DACDelay(hwp);
#ifdef DEBUG
	    switch (i % 3) {
	    case 0:
		ErrorF("DAC[0x%02x] = 0x%02x, ", i / 3, save->DAC[i]);
		break;
	    case 1:
		ErrorF("0x%02x, ", save->DAC[i]);
		break;
	    case 2:
		ErrorF("0x%02x\n", save->DAC[i]);
	    }
#endif
	}
    }

    hwp->disablePalette(hwp);
    hwp->cmapSaved = TRUE;
#endif
}

/*
 * vgaHWSave --
 *      save the current VGA state
 */

void
vgaHWSave(ScrnInfoPtr scrninfp, vgaRegPtr save, int flags)
{
    if (save == NULL)
	return;

   if (flags & VGA_SR_CMAP)
	vgaHWSaveColormap(scrninfp, save);

   if (flags & VGA_SR_MODE)
	vgaHWSaveMode(scrninfp, save);

   if (flags & VGA_SR_FONTS)
	vgaHWSaveFonts(scrninfp, save);
}


/*
 * vgaHWInit --
 *      Handle the initialization, etc. of a screen.
 *      Return FALSE on failure.
 */

Bool
vgaHWInit(ScrnInfoPtr scrninfp, DisplayModePtr mode)
{
    unsigned int i;
    int fixSync;
    vgaHWPtr hwp;
    vgaRegPtr regp;
    int depth = scrninfp->depth;

    /*
     * make sure the vgaHWRec is allocated
     */
    if (!vgaHWGetHWRec(scrninfp))
	return FALSE;
    hwp = VGAHWPTR(scrninfp);
    regp = &hwp->ModeReg;

    if (hwp->Flags & VGA_FIX_SYNC_PULSES)
	fixSync = 1;
    else
	fixSync = 0;
    
    /*
     * compute correct Hsync & Vsync polarity 
     */
    if ((mode->Flags & (V_PHSYNC | V_NHSYNC))
        && (mode->Flags & (V_PVSYNC | V_NVSYNC)))
    {
        regp->MiscOutReg = 0x23;
        if (mode->Flags & V_NHSYNC) regp->MiscOutReg |= 0x40;
        if (mode->Flags & V_NVSYNC) regp->MiscOutReg |= 0x80;
    }
    else
    {
        int VDisplay = mode->VDisplay;
        if (mode->Flags & V_DBLSCAN)
            VDisplay *= 2;
        if (mode->VScan > 1)
            VDisplay *= mode->VScan;
        if      (VDisplay < 400)
            regp->MiscOutReg = 0xA3;		/* +hsync -vsync */
        else if (VDisplay < 480)
            regp->MiscOutReg = 0x63;		/* -hsync +vsync */
        else if (VDisplay < 768)
            regp->MiscOutReg = 0xE3;		/* -hsync -vsync */
        else
            regp->MiscOutReg = 0x23;		/* +hsync +vsync */
    }
    
    regp->MiscOutReg |= (mode->ClockIndex & 0x03) << 2;

    /*
     * Time Sequencer
     */
    if (depth == 4)
        regp->Sequencer[0] = 0x02;
    else
        regp->Sequencer[0] = 0x00;
    if (mode->Flags & V_CLKDIV2) 
        regp->Sequencer[1] = 0x09;
    else
        regp->Sequencer[1] = 0x01;
    if (depth == 1)
        regp->Sequencer[2] = 1 << BIT_PLANE;
    else
        regp->Sequencer[2] = 0x0F;
    regp->Sequencer[3] = 0x00;                             /* Font select */
    if (depth < 8)
        regp->Sequencer[4] = 0x06;                             /* Misc */
    else
        regp->Sequencer[4] = 0x0E;                             /* Misc */

    /*
     * CRTC Controller
     */
    regp->CRTC[0]  = (mode->CrtcHTotal >> 3) - 5;
    regp->CRTC[1]  = (mode->CrtcHDisplay >> 3) - 1;
    regp->CRTC[2]  = (mode->CrtcHBlankStart >> 3) - 1;
    regp->CRTC[3]  = (((mode->CrtcHBlankEnd >> 3) - 1) & 0x1F) | 0x80;
    i = (((mode->CrtcHSkew << 2) + 0x10) & ~0x1F);
    if (i < 0x80)
	regp->CRTC[3] |= i;
    regp->CRTC[4]  = (mode->CrtcHSyncStart >> 3) - fixSync;
    regp->CRTC[5]  = ((((mode->CrtcHBlankEnd >> 3) - 1) & 0x20) << 2)
	| (((mode->CrtcHSyncEnd >> 3) - fixSync) & 0x1F);
    regp->CRTC[6]  = (mode->CrtcVTotal - 2) & 0xFF;
    regp->CRTC[7]  = (((mode->CrtcVTotal - 2) & 0x100) >> 8)
	| (((mode->CrtcVDisplay - 1) & 0x100) >> 7)
	| (((mode->CrtcVSyncStart - fixSync) & 0x100) >> 6)
	| (((mode->CrtcVBlankStart - 1) & 0x100) >> 5)
	| 0x10
	| (((mode->CrtcVTotal - 2) & 0x200)   >> 4)
	| (((mode->CrtcVDisplay - 1) & 0x200) >> 3)
	| (((mode->CrtcVSyncStart - fixSync) & 0x200) >> 2);
    regp->CRTC[8]  = 0x00;
    regp->CRTC[9]  = (((mode->CrtcVBlankStart - 1) & 0x200) >> 4) | 0x40;
    if (mode->Flags & V_DBLSCAN)
	regp->CRTC[9] |= 0x80;
    if (mode->VScan >= 32)
	regp->CRTC[9] |= 0x1F;
    else if (mode->VScan > 1)
	regp->CRTC[9] |= mode->VScan - 1;
    regp->CRTC[10] = 0x00;
    regp->CRTC[11] = 0x00;
    regp->CRTC[12] = 0x00;
    regp->CRTC[13] = 0x00;
    regp->CRTC[14] = 0x00;
    regp->CRTC[15] = 0x00;
    regp->CRTC[16] = (mode->CrtcVSyncStart - fixSync) & 0xFF;
    regp->CRTC[17] = ((mode->CrtcVSyncEnd - fixSync) & 0x0F) | 0x20;
    regp->CRTC[18] = (mode->CrtcVDisplay - 1) & 0xFF;
    regp->CRTC[19] = scrninfp->displayWidth >> 4;  /* just a guess */
    regp->CRTC[20] = 0x00;
    regp->CRTC[21] = (mode->CrtcVBlankStart - 1) & 0xFF; 
    regp->CRTC[22] = (mode->CrtcVBlankEnd - 1) & 0xFF;
    if (depth < 8)
	regp->CRTC[23] = 0xE3;
    else
	regp->CRTC[23] = 0xC3;
    regp->CRTC[24] = 0xFF;

    vgaHWHBlankKGA(mode, regp, 0, KGA_FIX_OVERSCAN | KGA_ENABLE_ON_ZERO);
    vgaHWVBlankKGA(mode, regp, 0, KGA_FIX_OVERSCAN | KGA_ENABLE_ON_ZERO);

    /*
     * Theory resumes here....
     */

    /*
     * Graphics Display Controller
     */
    regp->Graphics[0] = 0x00;
    regp->Graphics[1] = 0x00;
    regp->Graphics[2] = 0x00;
    regp->Graphics[3] = 0x00;
    if (depth == 1) {
        regp->Graphics[4] = BIT_PLANE;
        regp->Graphics[5] = 0x00;
    } else {
        regp->Graphics[4] = 0x00;
        if (depth == 4)
            regp->Graphics[5] = 0x02;
        else
            regp->Graphics[5] = 0x40;
    }
    regp->Graphics[6] = 0x05;   /* only map 64k VGA memory !!!! */
    regp->Graphics[7] = 0x0F;
    regp->Graphics[8] = 0xFF;
  
    if (depth == 1) {
        /* Initialise the Mono map according to which bit-plane gets used */

	Bool flipPixels = xf86GetFlipPixels();

        for (i=0; i<16; i++)
            if (((i & (1 << BIT_PLANE)) != 0) != flipPixels)
                regp->Attribute[i] = WHITE_VALUE;
            else
                regp->Attribute[i] = BLACK_VALUE;

        regp->Attribute[16] = 0x01;  /* -VGA2- */ /* wrong for the ET4000 */
	if (!hwp->ShowOverscan)
            regp->Attribute[OVERSCAN] = OVERSCAN_VALUE;  /* -VGA2- */
    } else {
        regp->Attribute[0]  = 0x00; /* standard colormap translation */
        regp->Attribute[1]  = 0x01;
        regp->Attribute[2]  = 0x02;
        regp->Attribute[3]  = 0x03;
        regp->Attribute[4]  = 0x04;
        regp->Attribute[5]  = 0x05;
        regp->Attribute[6]  = 0x06;
        regp->Attribute[7]  = 0x07;
        regp->Attribute[8]  = 0x08;
        regp->Attribute[9]  = 0x09;
        regp->Attribute[10] = 0x0A;
        regp->Attribute[11] = 0x0B;
        regp->Attribute[12] = 0x0C;
        regp->Attribute[13] = 0x0D;
        regp->Attribute[14] = 0x0E;
        regp->Attribute[15] = 0x0F;
        if (depth == 4)
            regp->Attribute[16] = 0x81; /* wrong for the ET4000 */
        else
            regp->Attribute[16] = 0x41; /* wrong for the ET4000 */
        /* Attribute[17] (overscan) initialised in vgaHWGetHWRec() */
    }
    regp->Attribute[18] = 0x0F;
    regp->Attribute[19] = 0x00;
    regp->Attribute[20] = 0x00;

    return(TRUE);
}

    /*
     * OK, so much for theory.  Now, let's deal with the >real< world...
     *
     * Aside from the VGA_FIX_SYNC_PULSES glitch, the above CRTC settings are
     * precise in theory, except that many, if not most, VGA clones fail to
     * reset the blanking signal when the character or line counter reaches
     * [HV]Total.  In this case, the signal is only unblanked when the counter
     * reaches [HV]BlankEnd (mod 64, 128 or 256 as the case may be) at the
     * start of the >next< scanline or frame, which means only part of the
     * screen shows.  This affects how null overscans are to be implemented on
     * such adapters.
     *
     * Henceforth, VGA cores that implement this broken, but unfortunately
     * common, behaviour are to be designated as KGA's, in honour of Koen
     * Gadeyne, whose zeal to eliminate overscans (read: fury) set in motion
     * a series of events that led to the discovery of this problem.
     *
     * Some VGA's are KGA's only in the horizontal, or only in the vertical,
     * some in both, others in neither.  Don't let anyone tell you there is
     * such a thing as a VGA "standard"...  And, thank the Creator for the fact
     * that Hilbert spaces are not yet implemented in this industry.
     *
     * The following implements a trick suggested by David Dawes.  This sets
     * [HV]BlankEnd to zero if the blanking interval does not already contain a
     * 0-point, and decrements it by one otherwise.  In the latter case, this
     * will produce a left and/or top overscan which the colourmap code will
     * (still) need to ensure is as close to black as possible.  This will make
     * the behaviour consistent across all chipsets, while allowing all
     * chipsets to display the entire screen.  Non-KGA drivers can ignore the
     * following in their own copy of this code.
     *
     * --  TSI @ UQV,  1998.08.21
     */

CARD32
vgaHWHBlankKGA(DisplayModePtr mode, vgaRegPtr regp, int nBits, 
	       unsigned int Flags)
{
    int nExtBits = (nBits < 6) ? 0 : nBits - 6;
    CARD32 ExtBits;
    CARD32 ExtBitMask = ((1 << nExtBits) - 1) << 6;

    regp->CRTC[3]  = (regp->CRTC[3] & ~0x1F) 
                     | (((mode->CrtcHBlankEnd >> 3) - 1) & 0x1F);
    regp->CRTC[5]  = (regp->CRTC[5] & ~0x80) 
                     | ((((mode->CrtcHBlankEnd >> 3) - 1) & 0x20) << 2);
    ExtBits        = ((mode->CrtcHBlankEnd >> 3) - 1) & ExtBitMask;

    /* First the horizontal case */
    if ((Flags & KGA_FIX_OVERSCAN)
	&& ((mode->CrtcHBlankEnd >> 3) == (mode->CrtcHTotal >> 3)))
    {
	int i = (regp->CRTC[3] & 0x1F) 
	    | ((regp->CRTC[5] & 0x80) >> 2)
	    | ExtBits;
	if (Flags & KGA_ENABLE_ON_ZERO) {
	    if ((i-- > (((mode->CrtcHBlankStart >> 3) - 1) 
		       & (0x3F | ExtBitMask)))
	    && (mode->CrtcHBlankEnd == mode->CrtcHTotal))
	    i = 0;
	} else if (Flags & KGA_BE_TOT_DEC)
	    i--;
	regp->CRTC[3] = (regp->CRTC[3] & ~0x1F) | (i & 0x1F);
	regp->CRTC[5] = (regp->CRTC[5] & ~0x80) | ((i << 2) & 0x80);
	ExtBits = i & ExtBitMask;
    }
    return ExtBits >> 6;
}

    /*
     * The vertical case is a little trickier.  Some VGA's ignore bit 0x80 of
     * CRTC[22].  Also, in some cases, a zero CRTC[22] will still blank the
     * very first scanline in a double- or multi-scanned mode.  This last case
     * needs further investigation.
     */
CARD32
vgaHWVBlankKGA(DisplayModePtr mode, vgaRegPtr regp, int nBits, 
	       unsigned int Flags)
{
    CARD32 ExtBits;
    CARD32 nExtBits = (nBits < 8) ? 0 : (nBits - 8);
    CARD32 ExtBitMask = ((1 << nExtBits) - 1) << 8;
    /* If width is not known nBits should be 0. In this 
     * case BitMask is set to 0 so we can check for it. */
    CARD32 BitMask = (nBits < 7) ? 0 : ((1 << nExtBits) - 1);
    int VBlankStart = (mode->CrtcVBlankStart - 1) & 0xFF; 
    regp->CRTC[22] = (mode->CrtcVBlankEnd - 1) & 0xFF;
    ExtBits        = (mode->CrtcVBlankEnd - 1) & ExtBitMask;

    if ((Flags & KGA_FIX_OVERSCAN) 
	&& (mode->CrtcVBlankEnd == mode->CrtcVTotal))
      /* Null top overscan */
    {
	int i = regp->CRTC[22] | ExtBits;
	if (Flags & KGA_ENABLE_ON_ZERO) {
	    if (((BitMask && ((i & BitMask) > (VBlankStart & BitMask)))
	     || ((i > VBlankStart)  &&  		/* 8-bit case */
	    ((i & 0x7F) > (VBlankStart & 0x7F)))) &&	/* 7-bit case */
	    !(regp->CRTC[9] & 0x9F))			/* 1 scanline/row */
	    i = 0;
	else
	    i = (i - 1);
	} else if (Flags & KGA_BE_TOT_DEC)
	    i = (i - 1);

	regp->CRTC[22] = i & 0xFF;
	ExtBits = i & 0xFF00;
    }
    return ExtBits >> 8;
}

/*
 * these are some more hardware specific helpers, formerly in vga.c
 */
static void
vgaHWGetHWRecPrivate(void)
{
    if (vgaHWPrivateIndex < 0)
	vgaHWPrivateIndex = xf86AllocateScrnInfoPrivateIndex();
    return;
}


static void
vgaHWFreeRegs(vgaRegPtr regp)
{
    if (regp->CRTC)
    	xfree (regp->CRTC);

    regp->CRTC =
    regp->Sequencer =
    regp->Graphics =
    regp->Attribute = NULL;

    regp->numCRTC =
    regp->numSequencer =
    regp->numGraphics =
    regp->numAttribute = 0;
}



static Bool
vgaHWAllocRegs(vgaRegPtr regp)
{
    unsigned char *buf;

    if ((regp->numCRTC + regp->numSequencer + regp->numGraphics +
         regp->numAttribute) == 0)
        return FALSE;

    buf = xcalloc(regp->numCRTC +
    		  regp->numSequencer +
		  regp->numGraphics +
		  regp->numAttribute, 1);
    if (!buf)
    	return FALSE;

    regp->CRTC = buf;
    regp->Sequencer = regp->CRTC + regp->numCRTC;
    regp->Graphics = regp->Sequencer + regp->numSequencer;
    regp->Attribute = regp->Graphics + regp->numGraphics;

    return TRUE;
}


Bool
vgaHWAllocDefaultRegs(vgaRegPtr regp)
{
    regp->numCRTC = VGA_NUM_CRTC;
    regp->numSequencer = VGA_NUM_SEQ;
    regp->numGraphics = VGA_NUM_GFX;
    regp->numAttribute = VGA_NUM_ATTR;

    return vgaHWAllocRegs(regp);
}


Bool
vgaHWSetRegCounts(ScrnInfoPtr scrp, int numCRTC, int numSequencer,
		  int numGraphics, int numAttribute)
{
#define VGAHWMINNUM(regtype) \
	((newMode.num##regtype < regp->num##regtype) ? \
	 (newMode.num##regtype) : (regp->num##regtype))
#define VGAHWCOPYREGSET(regtype) \
	memcpy (newMode.regtype, regp->regtype, VGAHWMINNUM(regtype))

    vgaRegRec newMode, newSaved;
    vgaRegPtr regp;

    regp = &VGAHWPTR(scrp)->ModeReg;
    memcpy (&newMode, regp, sizeof(vgaRegRec));

    /* allocate space for new registers */

    regp = &newMode;
    regp->numCRTC = numCRTC;
    regp->numSequencer = numSequencer;
    regp->numGraphics = numGraphics;
    regp->numAttribute = numAttribute;
    if (!vgaHWAllocRegs(regp))
    	return FALSE;

    regp = &VGAHWPTR(scrp)->SavedReg;
    memcpy (&newSaved, regp, sizeof(vgaRegRec));

    regp = &newSaved;
    regp->numCRTC = numCRTC;
    regp->numSequencer = numSequencer;
    regp->numGraphics = numGraphics;
    regp->numAttribute = numAttribute;
    if (!vgaHWAllocRegs(regp)) {
        vgaHWFreeRegs(&newMode);
    	return FALSE;
    }

    /* allocations succeeded, copy register data into new space */

    regp = &VGAHWPTR(scrp)->ModeReg;
    VGAHWCOPYREGSET(CRTC);
    VGAHWCOPYREGSET(Sequencer);
    VGAHWCOPYREGSET(Graphics);
    VGAHWCOPYREGSET(Attribute);

    regp = &VGAHWPTR(scrp)->SavedReg;
    VGAHWCOPYREGSET(CRTC);
    VGAHWCOPYREGSET(Sequencer);
    VGAHWCOPYREGSET(Graphics);
    VGAHWCOPYREGSET(Attribute);

    /* free old register arrays */

    regp = &VGAHWPTR(scrp)->ModeReg;
    vgaHWFreeRegs(regp);
    memcpy(regp, &newMode, sizeof(vgaRegRec));

    regp = &VGAHWPTR(scrp)->SavedReg;
    vgaHWFreeRegs(regp);
    memcpy(regp, &newSaved, sizeof(vgaRegRec));

    return TRUE;

#undef VGAHWMINNUM
#undef VGAHWCOPYREGSET
}


Bool
vgaHWCopyReg(vgaRegPtr dst, vgaRegPtr src)
{
    vgaHWFreeRegs(dst);

    memcpy(dst, src, sizeof(vgaRegRec));

    if (!vgaHWAllocRegs(dst))
	return FALSE;

    memcpy(dst->CRTC, src->CRTC, src->numCRTC);
    memcpy(dst->Sequencer, src->Sequencer, src->numSequencer);
    memcpy(dst->Graphics, src->Graphics, src->numGraphics);
    memcpy(dst->Attribute, src->Attribute, src->numAttribute);

    return TRUE;
}


Bool
vgaHWGetHWRec(ScrnInfoPtr scrp)
{
    vgaRegPtr regp;
    vgaHWPtr hwp;
    pciVideoPtr pvp;
    int i;
    
    /*
     * Let's make sure that the private exists and allocate one.
     */
    vgaHWGetHWRecPrivate();
    /*
     * New privates are always set to NULL, so we can check if the allocation
     * has already been done.
     */
    if (VGAHWPTR(scrp))
	return TRUE;
    hwp = VGAHWPTRLVAL(scrp) = xnfcalloc(sizeof(vgaHWRec), 1);
    regp = &VGAHWPTR(scrp)->ModeReg;

    if ((!vgaHWAllocDefaultRegs(&VGAHWPTR(scrp)->SavedReg)) ||
    	(!vgaHWAllocDefaultRegs(&VGAHWPTR(scrp)->ModeReg))) {
        xfree(hwp);
	return FALSE;
    }

    if (scrp->bitsPerPixel == 1) {
	rgb blackColour = scrp->display->blackColour,
	    whiteColour = scrp->display->whiteColour;

	if (blackColour.red   > 0x3F) blackColour.red   = 0x3F;
	if (blackColour.green > 0x3F) blackColour.green = 0x3F;
	if (blackColour.blue  > 0x3F) blackColour.blue  = 0x3F;

	if (whiteColour.red   > 0x3F) whiteColour.red   = 0x3F;
	if (whiteColour.green > 0x3F) whiteColour.green = 0x3F;
	if (whiteColour.blue  > 0x3F) whiteColour.blue  = 0x3F;

	if ((blackColour.red   == whiteColour.red  ) &&
	    (blackColour.green == whiteColour.green) &&
	    (blackColour.blue  == whiteColour.blue )) {
	    blackColour.red   ^= 0x3F;
	    blackColour.green ^= 0x3F;
	    blackColour.blue  ^= 0x3F;
	}

        /*
         * initialize default colormap for monochrome
         */
        for (i=0; i<3;   i++) regp->DAC[i] = 0x00;
        for (i=3; i<768; i++) regp->DAC[i] = 0x3F;
        i = BLACK_VALUE * 3;
        regp->DAC[i++] = blackColour.red;
        regp->DAC[i++] = blackColour.green;
        regp->DAC[i] = blackColour.blue;
        i = WHITE_VALUE * 3;
        regp->DAC[i++] = whiteColour.red;
        regp->DAC[i++] = whiteColour.green;
        regp->DAC[i] = whiteColour.blue;
        i = OVERSCAN_VALUE * 3;
        regp->DAC[i++] = 0x00;
        regp->DAC[i++] = 0x00;
        regp->DAC[i] = 0x00;
    } else {
	/* Set all colours to black */
        for (i=0; i<768; i++) regp->DAC[i] = 0x00;
        /* ... and the overscan */
        if (scrp->depth >= 4)
            regp->Attribute[OVERSCAN] = 0xFF;
    }
    if (xf86FindOption(scrp->confScreen->options, "ShowOverscan")) {
	xf86MarkOptionUsedByName(scrp->confScreen->options, "ShowOverscan");
	xf86DrvMsg(scrp->scrnIndex, X_CONFIG, "Showing overscan area\n");
	regp->DAC[765] = 0x3F; 
	regp->DAC[766] = 0x00; 
	regp->DAC[767] = 0x3F; 
	regp->Attribute[OVERSCAN] = 0xFF;
	hwp->ShowOverscan = TRUE;
    } else
	hwp->ShowOverscan = FALSE;

    hwp->paletteEnabled = FALSE;
    hwp->cmapSaved = FALSE;
    hwp->MapSize = 0;
    hwp->pScrn = scrp;

    /* Initialise the function pointers with the standard VGA versions */
    vgaHWSetStdFuncs(hwp);

    hwp->PIOOffset = scrp->domainIOBase;
    if ((pvp = xf86GetPciInfoForEntity(scrp->entityList[0])))
	hwp->Tag = pciTag(pvp->bus, pvp->device, pvp->func);

    return TRUE;
}


void
vgaHWFreeHWRec(ScrnInfoPtr scrp)
{
    if (vgaHWPrivateIndex >= 0) {
	vgaHWPtr hwp = VGAHWPTR(scrp);

	if (!hwp)
	    return;

	xfree(hwp->FontInfo1);
	xfree(hwp->FontInfo2);
	xfree(hwp->TextInfo);

	vgaHWFreeRegs (&hwp->ModeReg);
	vgaHWFreeRegs (&hwp->SavedReg);

	xfree(hwp);
	VGAHWPTRLVAL(scrp) = NULL;
    }
}


Bool
vgaHWMapMem(ScrnInfoPtr scrp)
{
    vgaHWPtr hwp = VGAHWPTR(scrp);
    int scr_index = scrp->scrnIndex;
    
    if (hwp->Base)
	return TRUE;

    /* If not set, initialise with the defaults */
    if (hwp->MapSize == 0)
	hwp->MapSize = VGA_DEFAULT_MEM_SIZE;
    if (hwp->MapPhys == 0)
	hwp->MapPhys = VGA_DEFAULT_PHYS_ADDR;

    /*
     * Map as VIDMEM_MMIO_32BIT because WC
     * is bad when there is page flipping.
     * XXX This is not correct but we do it
     * for now.
     */
#ifdef DEBUG
    ErrorF("Mapping VGAMem\n");
#endif
    hwp->Base = xf86MapDomainMemory(scr_index, VIDMEM_MMIO_32BIT, hwp->Tag,
				    hwp->MapPhys, hwp->MapSize);
    return hwp->Base != NULL;
}


void
vgaHWUnmapMem(ScrnInfoPtr scrp)
{
    vgaHWPtr hwp = VGAHWPTR(scrp);
    int scr_index = scrp->scrnIndex;

    if (hwp->Base == NULL)
	return;
    
#ifdef DEBUG
    ErrorF("Unmapping VGAMem\n");
#endif
    xf86UnMapVidMem(scr_index, hwp->Base, hwp->MapSize);
    hwp->Base = NULL;
}

int
vgaHWGetIndex()
{
    return vgaHWPrivateIndex;
}


void
vgaHWGetIOBase(vgaHWPtr hwp)
{
    hwp->IOBase = (hwp->readMiscOut(hwp) & 0x01) ?
				VGA_IOBASE_COLOR : VGA_IOBASE_MONO;
    xf86DrvMsgVerb(hwp->pScrn->scrnIndex, X_INFO, 3,
	"vgaHWGetIOBase: hwp->IOBase is 0x%04x, hwp->PIOOffset is 0x%04lx\n",
	hwp->IOBase, hwp->PIOOffset);
}


void
vgaHWLock(vgaHWPtr hwp)
{
    /* Protect CRTC[0-7] */
    hwp->writeCrtc(hwp, 0x11, hwp->readCrtc(hwp, 0x11) | 0x80);
}

void
vgaHWUnlock(vgaHWPtr hwp)
{
    /* Unprotect CRTC[0-7] */
     hwp->writeCrtc(hwp, 0x11, hwp->readCrtc(hwp, 0x11) & ~0x80);
}


void
vgaHWEnable(vgaHWPtr hwp)
{
    hwp->writeEnable(hwp, hwp->readEnable(hwp) | 0x01);
}


void
vgaHWDisable(vgaHWPtr hwp)
{
    hwp->writeEnable(hwp, hwp->readEnable(hwp) & ~0x01);
}


static void
vgaHWLoadPalette(ScrnInfoPtr pScrn, int numColors, int *indices, LOCO *colors,
		 VisualPtr pVisual)
{
    vgaHWPtr hwp = VGAHWPTR(pScrn);
    int i, index;

    for (i = 0; i < numColors; i++) {
	index = indices[i];
	hwp->writeDacWriteAddr(hwp, index);
	DACDelay(hwp);
	hwp->writeDacData(hwp, colors[index].red);
	DACDelay(hwp);
	hwp->writeDacData(hwp, colors[index].green);
	DACDelay(hwp);
	hwp->writeDacData(hwp, colors[index].blue);
	DACDelay(hwp);
    }

    /* This shouldn't be necessary, but we'll play safe. */
    hwp->disablePalette(hwp);
}


static void
vgaHWSetOverscan(ScrnInfoPtr pScrn, int overscan)
{
    vgaHWPtr hwp = VGAHWPTR(pScrn);

    if (overscan < 0 || overscan > 255)
	return;

    hwp->enablePalette(hwp);
    hwp->writeAttr(hwp, OVERSCAN, overscan);

#ifdef DEBUGOVERSCAN
    {
	int ov = hwp->readAttr(hwp, OVERSCAN);
	int red, green, blue;

	hwp->writeDacReadAddr(hwp, ov);
	red = hwp->readDacData(hwp);
	green = hwp->readDacData(hwp);
	blue = hwp->readDacData(hwp);
	ErrorF("Overscan index is 0x%02x, colours are #%02x%02x%02x\n",
		ov, red, green, blue);
    }
#endif

    hwp->disablePalette(hwp);
}


Bool
vgaHWHandleColormaps(ScreenPtr pScreen)
{
    ScrnInfoPtr pScrn = xf86Screens[pScreen->myNum];

    if (pScrn->depth > 1 && pScrn->depth <= 8) {
	return xf86HandleColormaps(pScreen, 1 << pScrn->depth,
				   pScrn->rgbBits, vgaHWLoadPalette,
				   pScrn->depth > 4 ? vgaHWSetOverscan : NULL,
				   CMAP_RELOAD_ON_MODE_SWITCH);
    }
    return TRUE;
}

/* ----------------------- DDC support ------------------------*/
/* 
 * Adjust v_active, v_blank, v_sync, v_sync_end, v_blank_end, v_total
 * to read out EDID at a faster rate. Allowed maximum is 25kHz with
 * 20 usec v_sync active. Set positive v_sync polarity, turn off lightpen
 * readback, enable access to cr00-cr07.
 */

/* vertical timings */
#define DISPLAY_END 0x04
#define BLANK_START DISPLAY_END
#define SYNC_START BLANK_START
#define SYNC_END 0x09
#define BLANK_END SYNC_END
#define V_TOTAL BLANK_END
/* this function doesn't have to be reentrant for our purposes */
struct _vgaDdcSave {
    unsigned char cr03;
    unsigned char cr06;
    unsigned char cr07;
    unsigned char cr09;
    unsigned char cr10;
    unsigned char cr11;
    unsigned char cr12;
    unsigned char cr15;
    unsigned char cr16;
    unsigned char msr;
};

void
vgaHWddc1SetSpeed(ScrnInfoPtr pScrn, xf86ddcSpeed speed)
{
    vgaHWPtr hwp = VGAHWPTR(pScrn);
    unsigned char tmp;
    struct _vgaDdcSave* save;
    switch (speed) {
    case DDC_FAST:
        
        if (hwp->ddc != NULL) break;
        hwp->ddc = xnfcalloc(sizeof(struct _vgaDdcSave),1);
	save = (struct _vgaDdcSave *)hwp->ddc;
      /* Lightpen register disable - allow access to cr10 & 11; just in case */
	save->cr03 = hwp->readCrtc(hwp, 0x03); 
	hwp->writeCrtc(hwp,0x03,(save->cr03 |0x80));
	save->cr12 = hwp->readCrtc(hwp, 0x12); 
	hwp->writeCrtc(hwp,0x12,DISPLAY_END);
	save->cr15 = hwp->readCrtc(hwp, 0x15); 
	hwp->writeCrtc(hwp,0x15,BLANK_START);
	save->cr10 = hwp->readCrtc(hwp, 0x10); 
	hwp->writeCrtc(hwp,0x10,SYNC_START);
	save->cr11 = hwp->readCrtc(hwp, 0x11); 
	/* unprotect group 1 registers; just in case ...*/
	hwp->writeCrtc(hwp,0x11,((save->cr11 & 0x70) | SYNC_END));
	save->cr16 = hwp->readCrtc(hwp, 0x16); 
	hwp->writeCrtc(hwp,0x16,BLANK_END);
	save->cr06 = hwp->readCrtc(hwp, 0x06); 
	hwp->writeCrtc(hwp,0x06,V_TOTAL);
	/* all values have less than 8 bit - mask out 9th and 10th bits */
	save->cr09 = hwp->readCrtc(hwp, 0x09); 
	hwp->writeCrtc(hwp,0x09,(save->cr09 &0xDF));
	save->cr07 = hwp->readCrtc(hwp, 0x07); 
	hwp->writeCrtc(hwp,0x07,(save->cr07 &0x10));
	/* vsync polarity negativ & ensure a 25MHz clock */
	save->msr = hwp->readMiscOut(hwp); 
	hwp->writeMiscOut(hwp,((save->msr & 0xF3) | 0x80));
	break;
    case DDC_SLOW:
        if (hwp->ddc == NULL) break;
	save = (struct _vgaDdcSave *)hwp->ddc;
	hwp->writeMiscOut(hwp,save->msr);
	hwp->writeCrtc(hwp,0x07,save->cr07);
	tmp = hwp->readCrtc(hwp, 0x09);
	hwp->writeCrtc(hwp,0x09,((save->cr09 & 0x20) | (tmp & 0xDF)));
	hwp->writeCrtc(hwp,0x06,save->cr06);
	hwp->writeCrtc(hwp,0x16,save->cr16);
	hwp->writeCrtc(hwp,0x11,save->cr11);
	hwp->writeCrtc(hwp,0x10,save->cr10);
	hwp->writeCrtc(hwp,0x15,save->cr15);
	hwp->writeCrtc(hwp,0x12,save->cr12);
	hwp->writeCrtc(hwp,0x03,save->cr03);
	xfree(save);
	hwp->ddc = NULL;
	break;
    default:
	break;
    }
}
