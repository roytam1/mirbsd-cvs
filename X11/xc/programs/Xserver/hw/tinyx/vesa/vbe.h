/* 
Copyright (c) 2000 by Juliusz Chroboczek
 
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
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
/* $XFree86: xc/programs/Xserver/hw/tinyx/vesa/vbe.h,v 1.1 2004/06/02 22:43:03 dawes Exp $ */
/*
 * Copyright (c) 2004 by The XFree86 Project, Inc.
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

#ifndef _VBE_H
#define _VBE_H

#define VBE_WINDOW_RELOCATE 1
#define VBE_WINDOW_READ 2
#define VBE_WINDOW_WRITE 4

typedef struct _VbeInfoBlock {
    U8 VbeSignature[4];         /* VBE Signature */
    U16 VbeVersion;             /* VBE Version */
    U32 OemStringPtr;           /* Pointer to OEM String */
    U8 Capabilities[4];         /* Capabilities of graphics controller */
    U32 VideoModePtr;           /* Pointer to VideoModeList */
    U16 TotalMemory;            /* Number of 64kb memory blocks */
/* Added for VBE 2.0 */
    U16 OemSoftwareRev;         /* VBE implementation Software revision */
    U32 OemVendorNamePtr;       /* Pointer to Vendor Name String */
    U32 OemProductNamePtr;	/* Pointer to Product Name String */
    U32 OemProductRevPtr;       /* Pointer to Product Revision String */
    U8 Reserved[222];           /* Reserved for VBE implementation */
    U8 OemData[256];            /* Data Area for OEM Strings*/
} __attribute__((packed)) VbeInfoBlock;

typedef struct _VbeModeInfoBlock {
/* Mandatory information for all VBE revisions */
    U16 ModeAttributes;         /* mode attributes */
    U8 WinAAttributes;          /* window A attributes */
    U8 WinBAttributes;          /* window B attributes */
    U16 WinGranularity;         /* window granularity */
    U16 WinSize;                /* window size */
    U16 WinASegment;            /* window A start segment */
    U16 WinBSegment;            /* window B start segment */
    U32 WinFuncPtr;             /* pointer to window function */
    U16 BytesPerScanLine;       /* bytes per scan line */
/* Mandatory information for VBE 1.2 and above */
    U16 XResolution;            /* horizontal resolution */
    U16 YResolution;            /* vertical resolution */
    U8 XCharSize;               /* character cell width in pixels */
    U8 YCharSize;               /* character cell height in pixels */
    U8 NumberOfPlanes;          /* number of memory planes */
    U8 BitsPerPixel;            /* bits per pixel */
    U8 NumberOfBanks;           /* number of banks */
    U8 MemoryModel;             /* memory model type */
    U8 BankSize;                /* bank size in KB */
    U8 NumberOfImagePages;      /* number of images */
    U8 Reserved;                /* reserved for page function */
/* Direct Color fields (required for direct/6 and YUV/7 memory models) */
    U8 RedMaskSize;             /* size of direct color red mask in bits */
    U8 RedFieldPosition;        /* bit position of lsb of red mask */
    U8 GreenMaskSize;           /* size of direct color green mask in bits */
    U8 GreenFieldPosition;      /* bit position of lsb of green mask */
    U8 BlueMaskSize;            /* size of direct color blue mask in bits */
    U8 BlueFieldPosition;       /* bit position of lsb of blue mask */
    U8 RsvdMaskSize;            /* size of direct color reserved mask bits*/
    U8 RsvdFieldPosition;       /* bit position of lsb of reserved mask */
    U8 DirectColorModeInfo;     /* direct color mode attributes */
/* Mandatory information for VBE 2.0 and above */
    U32 PhysBasePtr;            /* physical address for flat memory fb */
    U32 OffScreenMemOffset;     /* pointer to start of off screen memory */
    U16 OffScreenMemSize;       /* amount of off screen memory in 1k units */
    U8 Reserved2[206];          /* remainder of ModeInfoBlock */
} __attribute__((packed)) VbeModeInfoBlock;

typedef struct _VbeInfoRec {
    U8			palette_format;
    int			palette_wait;
    int			windowA_offset;
    int			windowB_offset;
    int			window_size;
    int			last_window;
    VbeModeInfoBlock	vmib;
} VbeInfoRec, *VbeInfoPtr;

typedef struct _SupVbeInfoBlock {
    U8 SupVbeSignature[7];      /* Supplemental VBE Signature */
    U16 SupVbeVersion;          /* Supplemental VBE Version*/
    U8 SupVbeSubFunc[8];	/* Bitfield of supported subfunctions */
    U16 OemSoftwareRev;         /* OEM Software revision */
    U32 OemVendorNamePtr;       /* Pointer to Vendor Name String */
    U32 OemProductNamePtr;	/* Pointer to Product Name String */
    U32 OemProductRevPtr;       /* Pointer to Product Revision String */
    U32 OemStringPtr;           /* Pointer to OEM String */
    U8 Reserved[221];           /* Reserved */
} __attribute__((packed)) SupVbeInfoBlock;

int
VbeGetVib (Vm86InfoPtr vi, VbeInfoBlock *vib);

int
VbeGetVmib (Vm86InfoPtr vi, int mode, VbeModeInfoBlock *vmib);

void
VbeReportInfo (Vm86InfoPtr vi);

int
VbeGetNmode (Vm86InfoPtr vi);

int
VbeGetModes (Vm86InfoPtr vi, VesaModePtr modes, int nmode);

int
VbeGetModeInfo(Vm86InfoPtr vi, int m, VesaModePtr mode);

VbeInfoPtr
VbeInit (Vm86InfoPtr vi);

int
VbeSetMode (Vm86InfoPtr vi, VbeInfoPtr vbe, int mode, int linear, int direct);

int 
VbeGetMode(Vm86InfoPtr vi, int *mode);

void *
VbeMapFramebuffer(Vm86InfoPtr vi, VbeInfoPtr vbe, int mode, int *size, CARD32 *phys);

void
VbeUnmapFramebuffer(Vm86InfoPtr vi, VbeInfoPtr vbe, int mode, void *fb);

int 
VbeSetPalette(Vm86InfoPtr vi, VbeInfoPtr vbe, int first, int number, U8 *entries);
        
int 
VbeGetPalette(Vm86InfoPtr vi, VbeInfoPtr vbe, int first, int number, U8 *entries);
        
int 
VbeSetPaletteOptions(Vm86InfoPtr vi, VbeInfoPtr vbe, U8 bits, int wait);

void *
VbeSetWindow(Vm86InfoPtr vi, VbeInfoPtr vbe, int offset, int purpose, int *size_return);

int 
VbeReportVib(Vm86InfoPtr vi, VbeInfoBlock *vib);

int 
VbeReportModeInfo(Vm86InfoPtr vi, U16 mode, VbeModeInfoBlock *vmib);

int
VbeDoInterrupt10(Vm86InfoPtr vi);
    
Bool
VbeDPMS(Vm86InfoPtr vi, int mode);

void
VbeCleanup (Vm86InfoPtr vi, VbeInfoPtr vbe);


#endif
