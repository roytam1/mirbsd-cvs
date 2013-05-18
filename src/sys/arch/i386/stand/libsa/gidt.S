/*	$MirOS: src/sys/arch/i386/stand/libsa/gidt.S,v 1.29 2009/03/15 18:16:13 tg Exp $ */
/*	$OpenBSD: gidt.S,v 1.32 2006/12/26 19:30:44 tom Exp $	*/

/*
 * Copyright (c) 2008, 2009 Thorsten Glaser
 * Copyright (c) 1997 Michael Shalayeff
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR 
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

	.file "gidt.S"

#include <machine/asm.h>
#define _LOCORE
#include <machine/trap.h>
#include <debug_md.h>
#undef _LOCORE
#include <assym.h>

#include "gidt.h"

	.globl	_C_LABEL(BIOS_regs)

	.text
	.code32

	.globl	_C_LABEL(_rtt)
ENTRY(_rtt)
#ifdef GIDT_DEBUG
	movl	$0xb8000, %ebx
	movl	$0x4f514f51, (%ebx)
#endif
	movw	$0x1234, %ax
	movw	%ax, 0x472	/* warm boot */

	/* Try to use the KBD to reboot system */
	movb	$0xfe, %al
	outb	%al, $0x64

	movl	$0x5000, %ecx
1:	inb	$0x84, %al
	loop	1b

	movb	$0xfe, %al
	outb	%al, $0x64

#ifdef GIDT_DEBUG
	movl	$0xb8000, %ebx
	movl	$0x07310731, (%ebx)
#endif

	/* Try to cause a triple fault... */
	lidt    Idtr_reset
	xorl	%eax, %eax
	divl	%eax, %eax

	/* Again... */
	int $0x8

	/* Again... */
	movl	$0, %esp	/* segment violation */
	ret

	/*
	 * set up the protected mode Interrupt Descriptor Table
	 */

#ifdef __STDC__
#define IPROC(n)	X##n
#define IEMU(n)		IPROC(emu##n)
#define idtb(b)		idte(emu##b)
#else
#define IPROC(n)	X/**/n
#define IEMU(n)		IPROC(emu/**/n)
#define idtb(b)		idte(emu/**/b)
#endif

#define idte(e) \
	.long	IPROC(e), ((S32TEXT) << 16) | ((0x80 | SDT_SYS386TGT) << 8)

	.p2align 4
	.globl	idt_for_fixup
idt_for_fixup:
	idte(de); idte(db); idte(nmi); idte(bp); idte(of); idte(br)
	idte(ud); idte(nm); idte(df);  idte(fo); idte(ts); idte(np)
	idte(ss); idte(gp); idte(pf);  idte(xx); idte(mf); idte(ac)
	idte(mc)
	idte(xx); idte(xx); idte(xx);  idte(xx); idte(xx); idte(xx)
	idte(xx); idte(xx); idte(xx);  idte(xx); idte(xx); idte(xx)
	idte(xx) 
		/* Maskable interrupts (32-255) */
		/* BIOS entry points (32-63) */
		/* DOS entry points (64-80) */
	idtb(0);  idtb(1);  idtb(2);  idtb(3);  idtb(4);  idtb(5)
	idtb(6);  idtb(7);  idtb(8);  idtb(9);  idtb(10); idtb(11)
	idtb(12); idtb(13); idtb(14); idtb(15); idtb(16); idtb(17)
	idtb(18); idtb(19); idtb(20); idtb(21); idtb(22); idtb(23)
	idtb(24); idtb(25); idtb(26); idtb(27); idtb(28); idtb(29)
	idtb(30); idtb(31); idtb(32); idtb(33); idtb(34); idtb(35)
	idtb(36); idtb(37); idtb(38); idtb(39); idtb(40); idtb(41)
	idtb(42); idtb(43); idtb(44); idtb(45); idtb(46); idtb(47)
	.globl	idt_fixup_end
idt_fixup_end:

	.balign 8
	.globl	Idtr
Idtr:	.word	idt_fixup_end - idt_for_fixup - 1
	.long	idt_for_fixup
	.word	0

	.balign	8
	.globl	Idtr_real
Idtr_real:	.word	1023
		.long	0
		.word	0

	.balign	8
Idtr_reset:	.long	0, 0

	.balign	8
gdt:
		/* 0x00 : null */
	.space	8
		/* 0x08 : flat code */
	.word	0xFFFF			# lolimit
	.word	0			# lobase
	.byte	0			# midbase
	.byte	SDT_MEMERAC | 0 | 0x80	# RXAC, dpl = 0, present
	.byte	0xf | 0 | 0x40 | 0x80	# hilimit, xx, 32bit, 4k granularity
	.byte	0			# hibase
		/* 0x10 : flat data */
	.word	0xFFFF			# lolimit
	.word	0			# lobase
	.byte	0			# midbase
	.byte	SDT_MEMRWA | 0 | 0x80	# RWA, dpl = 0, present
	.byte	0xf | 0 | 0x40 | 0x80	# hilimit, xx, 32bit, 4k granularity
	.byte	0			# hibase
		/* 0x18 : 16 bit code */
	.word	0xFFFF				# lolimit
	.word	(SA_LINKADDR & 0xffff)		# lobase
	.byte	(SA_LINKADDR >> 16) & 0xff	# midbase
	.byte	SDT_MEMERAC | 0 | 0x80		# RXAC, dpl = 0, present
	.byte	0x0 | 0 | 0 | 0		# hilimit, xx, 16bit, byte granularity
	.byte	(SA_LINKADDR >> 20) & 0xff	# hibase
		/* 0x20 : 16 bit data */
	.word	0xFFFF				# lolimit
	.word	(SA_LINKADDR & 0xffff)		# lobase
	.byte	(SA_LINKADDR >> 16) & 0xff	# midbase
	.byte	SDT_MEMRWA | 0 | 0x80		# RWA, dpl = 0, present
	.byte	0x0 | 0 | 0 | 0		# hilimit, xx, 16bit, byte granularity
	.byte	(SA_LINKADDR >> 20) & 0xff	# hibase

.globl Gdtr
Gdtr:	.word	. - gdt - 1
	.long	gdt
	.word	0

#define IENTRY(name,type) \
IPROC(name): \
	pushl	$type ; \
	jmp	1f
#define IENTRY_ERR(name,err,type) \
IPROC(name): \
	pushl	$err ; \
	pushl	$type ; \
	jmp	1f

IPROC(xx):
	pushl	$1
	pushl	$T_RESERVED
	jmp	1f

IENTRY_ERR(de,0,T_DIVIDE)	/* #DE divide by zero */
IENTRY_ERR(db,0,T_TRCTRAP)	/* #DB debug */
IENTRY_ERR(nmi,0,T_NMI)		/* NMI */
IENTRY_ERR(bp,0,T_BPTFLT)	/* #BP breakpoint */
IENTRY_ERR(of,0,T_OFLOW)	/* #OF overflow */
IENTRY_ERR(br,0,T_BOUND)	/* #BR BOUND range exceeded */
IENTRY_ERR(ud,0,T_PRIVINFLT)	/* #UD invalid opcode */
IENTRY_ERR(nm,0,T_DNA)		/* #NM device not available */
IENTRY(df,T_DOUBLEFLT)		/* #DF double fault */
IENTRY_ERR(fo,0,T_FPOPFLT)	/* #FO coprocessor segment overrun */
IENTRY(ts,T_TSSFLT)		/* #TS invalid TSS */
IENTRY(np,T_SEGNPFLT)		/* #NP segment not present */
IENTRY(ss,T_STKFLT)		/* #SS stack fault */
IENTRY(gp,T_PROTFLT)		/* #GP general protection */
IENTRY(pf,T_PAGEFLT)		/* #PF page fault */
IENTRY_ERR(mf,0,T_ARITHTRAP)	/* #MF floating point error */
IENTRY(ac,T_ALIGNFLT)		/* #AC alignment check */
IENTRY(mc,T_MACHK)		/* #MC machine check */

	.globl	alltraps
1:	/* save on jumps */
	jmp	alltraps

#define	IEMUENT(n)	IEMU(n): pushl $n; jmp 1f

IEMUENT(0);  IEMUENT(1);  IEMUENT(2);  IEMUENT(3)
IEMUENT(4);  IEMUENT(5);  IEMUENT(6);  IEMUENT(7)
IEMUENT(8);  IEMUENT(9);  IEMUENT(10); IEMUENT(11)
IEMUENT(12); IEMUENT(13); IEMUENT(14); IEMUENT(15)
IEMUENT(16); IEMUENT(17); IEMUENT(18); IEMUENT(19)
IEMUENT(20); IEMUENT(21); IEMUENT(22); IEMUENT(23)
IEMUENT(24); IEMUENT(25); IEMUENT(26); IEMUENT(27)
IEMUENT(28); IEMUENT(29); IEMUENT(30); IEMUENT(31)
1:	jmp	EMUh	/* redirect for short jumps */
IEMUENT(32); IEMUENT(33); IEMUENT(34); IEMUENT(35)
IEMUENT(36); IEMUENT(37); IEMUENT(38); IEMUENT(39)
IEMUENT(40); IEMUENT(41); IEMUENT(42); IEMUENT(43)
IEMUENT(44); IEMUENT(45); IEMUENT(46); IEMUENT(47)
1:	jmp	EMUh

/*
 * entry point for BIOS real-mode interface
 * all the magic for real-prot mode switching is here
 *
 * Call:	%eax, %ecx, %edx, %ebx, %ebp, %esi, %edi, %es, %ds
 * Return:	%eax, %edx, %ecx, %eflags (as returned from BIOS)
 *
 */
	.globl	EMUh
	.balign	8, 0x90
	.intel_syntax noprefix
EMUh:
	xchg	[esp],eax
	mov	[LemuNR],al
	pop	eax

	push	ebx
	push	ebp
	push	esi
	push	edi
	push	ds
	push	es
	push	fs
	push	gs

	push	eax
	mov	eax,[BIOS_regs + BIOSR_DS]
	push	eax
	mov	eax,[BIOS_regs + BIOSR_ES]
	push	eax

	call	prot_to_real
	.code16

	pop	eax
	mov	es,ax
	pop	eax
	mov	ds,ax
	pop	eax

	sti
	int	0
	LemuNR = . - 1
	cli

	push	eax
	lahf
	push	eax
	xor	eax,eax
	mov	ax,es
	push	eax

	call	real_to_prot
	.code32

	mov	[BIOS_regs + BIOSR_CX],ecx
	mov	[BIOS_regs + BIOSR_DX],edx
	mov	[BIOS_regs + BIOSR_BX],ebx
	mov	[BIOS_regs + BIOSR_BP],ebp
	mov	[BIOS_regs + BIOSR_SI],esi
	mov	[BIOS_regs + BIOSR_DI],edi
	pop	eax
	mov	[BIOS_regs + BIOSR_ES],eax
	pop	ebx
	pop	eax
	mov	[BIOS_regs + BIOSR_AX],eax

	pushfd
	pop	ebp
	and	ebp,0xFFFFBFFF		/* clear NT flag */
	push	ebp
	popfd

	pop	gs
	pop	fs
	pop	es
	pop	ds
	pop	edi
	pop	esi
	pop	ebp
	mov	[esp+12],bh
	pop	ebx
	iret

#ifndef SMALL_BOOT
/* Call buffer at 07c0:0000 in real mode to simulate a BIOS boot */
ENTRY(bootbuf)
	pop	eax		/* Don't need return address */
	pop	esi		/* Buffer Source (linear) */
	pop	ecx		/* Size */
	pop	ebp		/* Buffer Target (ES:DI) */
	pop	ebx		/* Device and flags */
	pop	edi		/* Initial CS:IP */

	xor	edx,edx
	dec	edx		/* EDX = 0xFFFFFFFF */
	mov	dl,bl		/* EDX = 0xFFFFFFzz (z = device) */

	call	prot_to_real
	.code16

	/* set up flags, real mode stack */
	xor	eax,eax
	mov	ss,ax
	mov	esp,0x000006F0
	push	eax
	popf

	/*-
	 * Now the machine status is as follows:
	 * - CS = DS = ES = 4000h = (SA_LINKSEG)
	 * - SS:SP = 0000:06F0h (to make room for !PXE ptr)
	 * - EFLAGS = 0
	 * - ESI = linear address of source buffer (must be para aligned)
	 * - ECX = source buffer size (up to 64 KiB)
	 * - EBP = target address as ES:DI (FAR pointer)
	 * - EDI = initial CS:IP (FAR pointer)
	 * - EBX = bootbuf flags, currently unused
	 * - EDX = drive
	 * - _C_LABEL(bios_bootpte) = future DS:SI contents (16by)
	 * - 0000:0600h .. 0000:07FFh are available to put the boot
	 *   partition table entry in, according to SYSLINUX docs;
	 *   we also move certain relocation code there, and our
	 *   stack is also positioned in there
	 * - we assume ECX > (“ES”<<4)|“DI” [EBP]
	 * - “DI” is almost certainly 0 and should be
	 */

	mov	eax,edi
	shr	eax,16
	push	ax		/* future CS */
	push	di		/* future IP */
	mov	eax,ds:[8]
	push	eax		/* !PXE structure RM address */
	mov	eax,ds:[12]
	push	eax		/* PXENV+ structure RM address */
	push	edx		/* future DL (drive) */
	push	ecx		/* source buffer size */
	shr	esi,4
	push	si		/* source buffer segment */
	mov	eax,ebp
	shr	eax,16
	push	ax		/* buffer ES */
	push	bp		/* buffer DI */
	xor	ecx,ecx
	mov	es,cx
	mov	edi,0x0600
	mov	esi,offset _C_LABEL(bios_bootpte) - SA_LINKADDR
	mov	cx,4
	rep	movsd
	push	es		/* temporary CS */
	push	di		/* temporary IP */
	call	Ltcend
Ltcbeg:	/* temporary relocation code, copied to 0000:0610h */
	pop	di		/* buffer target (DI) */
	pop	es		/* buffer target (ES) */
	pop	ds		/* source buffer segment */
Ltcbig:	pop	ecx		/* source buffer size */
	xor	si,si		/* source buffer offset */
	cmp	ecx,0x00010000
	jb	Ltcseg
	/* copy 64 KiB, reduce, retry */
	sub	ecx,0x00010000
	push	ecx
	mov	ecx,0x4000	/* 64 KiB in dwords */
	push	di
	rep	movsd
	pop	di
	mov	ax,ds
	add	ax,0x1000
	mov	ds,ax
	mov	ax,es
	add	ax,0x1000
	mov	es,ax
	jmp	Ltcbig
Ltcseg:	rep	movsb
Ltcrun:	xor	ax,ax
	mov	ds,ax
	mov	si,0x0600
	pop	edx		/* drive */
	pop	bx		/* PXENV+ offset */
	pop	es		/* PXENV+ segment */
	pop	edi		/* !PXE */
	mov	bp,sp
	mov	[bp+8],edi
	lret			/* future CS:IP on stack */
Ltcend:	pop	si		/* offset Ltcbeg */
	mov	cx,offset Ltcend - offset Ltcbeg
	rep	movsb
	lret			/* temporary CS:IP (0000:0610h) on stack */
#endif

/*-
 * Switch from protected mode to real mode.
 * Registers trashed: EAX 
 * CS = DS = ES = SA_LINKSEG
 * SS:SP = old flat:ESP
 */
	.code32
	.globl	prot_to_real
prot_to_real:
	cli
	/* switch to 16 bit code size */
	ljmp	S16TEXT,offset Lp2r32 - SA_LINKADDR
Lp2r32:	.code16
	mov	ax,S16DATA
	mov	ds,ax
	mov	es,ax
	mov	fs,ax
	mov	gs,ax
	mov	ss,ax
	/* disable protected mode */
	mov	eax,cr0
	and	eax,~CR0_PE
	mov	cr0,eax
	/* switch to 16 bit data size */
	data32 ljmp SA_LINKSEG,offset Lp2r16 - SA_LINKADDR
Lp2r16:	/* convert ESP to SS:SP */
	mov	eax,esp
	shr	eax,4
	and	ax,0xF000
	mov	ss,ax
	and	esp,0x0000FFFF
	/* load real mode segments */
	mov	ax,cs
	mov	ds,ax
	mov	es,ax
	mov	fs,ax
	mov	gs,ax
	/* load real mode IDT */
	data32 addr32 lidt (Idtr_real - SA_LINKADDR)
	/* fix up return address */
	pop	eax
	sub	eax,SA_LINKADDR
	push	ax
	ret

/*-
 * Switch from real mode to protected mode.
 * Registers trashed: EAX 
 * CS = S32TEXT
 * DS = ES = SS = S32DATA
 * ESP = flat, old (SS<<4)|SP
 */
	.code16
	.globl	real_to_prot
real_to_prot:
	cli
	/* fix up return address */
	xor	eax,eax
	pop	ax
	add	eax,SA_LINKADDR
	push	eax
	/* load GDT via data segment */
	mov	ax,SA_LINKSEG
	mov	ds,ax
	data32 addr32 lgdt (Gdtr - SA_LINKADDR)
	/* convert SS:SP to ESP */
	xor	eax,eax
	mov	ax,ss
	shl	eax,4
	and	esp,0x0000FFFF
	add	esp,eax
	/* enter protected mode */
	mov	eax,cr0
	or	eax,CR0_PE
	mov	cr0,eax
	/* switch to 32 bit */
	data32 ljmp S32TEXT,offset Lr2p32
Lr2p32:	.code32
	mov	eax,S32DATA
	mov	ds,ax
	mov	es,ax
	mov	fs,ax
	mov	gs,ax
	mov	ss,ax
	/* load protected mode IDT */
	lidt	Idtr
	ret
