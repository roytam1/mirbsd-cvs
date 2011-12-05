/* $XFree86: xc/programs/Xserver/hw/xfree86/os-support/int10Defines.h,v 1.5 2004/02/13 23:58:46 dawes Exp $ */
/*
 * Copyright (c) 2000-2001 by The XFree86 Project, Inc.
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

#ifndef _INT10DEFINES_H_
#define _INT10DEFINES_H_ 1

#ifdef _VM86_LINUX

#include <asm/vm86.h>

#define CPU_R(type,name,num) \
	(((type *)&(((struct vm86_struct *)REG->cpuRegs)->regs.name))[num])
#define CPU_RD(name,num) CPU_R(CARD32,name,num)
#define CPU_RW(name,num) CPU_R(CARD16,name,num)
#define CPU_RB(name,num) CPU_R(CARD8,name,num)

#define X86_EAX CPU_RD(eax,0)
#define X86_EBX CPU_RD(ebx,0)
#define X86_ECX CPU_RD(ecx,0)
#define X86_EDX CPU_RD(edx,0)
#define X86_ESI CPU_RD(esi,0)
#define X86_EDI CPU_RD(edi,0)
#define X86_EBP CPU_RD(ebp,0)
#define X86_EIP CPU_RD(eip,0)
#define X86_ESP CPU_RD(esp,0)
#define X86_EFLAGS CPU_RD(eflags,0)

#define X86_FLAGS CPU_RW(eflags,0)
#define X86_AX CPU_RW(eax,0)
#define X86_BX CPU_RW(ebx,0)
#define X86_CX CPU_RW(ecx,0)
#define X86_DX CPU_RW(edx,0)
#define X86_SI CPU_RW(esi,0)
#define X86_DI CPU_RW(edi,0)
#define X86_BP CPU_RW(ebp,0)
#define X86_IP CPU_RW(eip,0)
#define X86_SP CPU_RW(esp,0)
#define X86_CS CPU_RW(cs,0)
#define X86_DS CPU_RW(ds,0)
#define X86_ES CPU_RW(es,0)
#define X86_SS CPU_RW(ss,0)
#define X86_FS CPU_RW(fs,0)
#define X86_GS CPU_RW(gs,0)

#define X86_AL CPU_RB(eax,0)
#define X86_BL CPU_RB(ebx,0)
#define X86_CL CPU_RB(ecx,0)
#define X86_DL CPU_RB(edx,0)

#define X86_AH CPU_RB(eax,1)
#define X86_BH CPU_RB(ebx,1)
#define X86_CH CPU_RB(ecx,1)
#define X86_DH CPU_RB(edx,1)

#elif defined(_X86EMU)

#include "xf86x86emu.h"

#endif

#endif
