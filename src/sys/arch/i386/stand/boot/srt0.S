/* $MirOS: src/share/misc/licence.template,v 1.28 2008/11/14 15:33:44 tg Rel $ */

/*-
 * Copyright (c) 2003, 2004, 2005, 2006, 2007, 2008, 2009
 *	Thorsten Glaser <tg@mirbsd.org>
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un-
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
 *
 * This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
 * the utmost extent permitted by applicable law, neither express nor
 * implied; without malicious intent or gross negligence. In no event
 * may a licensor, author or contributor be held liable for indirect,
 * direct, other damage, loss, or other issues arising in any way out
 * of dealing in the work, even if advised of the possibility of such
 * damage or existence of a defect, except proven that it results out
 * of said person's immediate fault when using the work as intended.
 */

#include "stand/boot/cmd.h"

	.intel_syntax noprefix
	.text
	.code16

	/* extern */
	.globl	idt_init
	.globl	real_to_prot
	.globl	prot_to_real
	.globl	boot
	.globl	_edata
	.globl	_end
	.globl	_rtt
	/* global */
	.globl	_start
	.globl	bios_bootpte
	.globl	i386_userpt
	.globl	pxe_bang
	.globl	pxe_plus

_start:	cli
	call	Linit
Lrval:	.p2align 2
	. = _start + 4
	/*	  ffffddpp	(f)lags user(p)artype (d)rive */
Ldrvi:	.long	0x6A6D4F00	/* drive information */
	i386_userpt = Ldrvi
	i386_biosdev = Ldrvi + 1
	i386_biosflags = Ldrvi + 2
	i386_dosdev = Ldrvi + 3
	.size	i386_userpt,1
	.size	i386_biosdev,1
	.size	i386_biosflags,1
	.size	i386_dosdev,1
pxe_bang:
	.size	pxe_bang,4
	.long	0		/* address of !PXE structure */
pxe_plus:
	.size	pxe_plus,4
	.long	0		/* address of PXENV+ structure */
bios_bootpte:
	.size	bios_bootpte,16
	.long	0, 0, 0, 0	/* 16 bytes from initial DS:SI */

	/* Multiboot header */
	.p2align 2
Lmbhdr:	.long	0x1BADB002		/* magic */
	.long	0x00010000		/* flags */
	.long	-0x1BADB002-0x00010000	/* checksum */
	/* the addresses are all bounced to 1 MiB */
	.long	Lmbhdr - SA_LINKADDR + 0x00100000	/* header_addr */
	.long	0x00100000				/* load_addr */
	.long	0					/* load_end_addr */
	.long	0					/* bss_end_addr */
	.long	Lmbrun - SA_LINKADDR + 0x00100000	/* entry_addr */

Linit:	xor	eax,eax
	push	eax
	popfd
	pop	dx

#ifndef SMALL_BOOT
	mov	bp,sp		/* for later (!PXE pointer) */
#endif

	/* find out current position in memory */
	sub	dx,offset Lrval - offset _start
	movzx	ecx,dx		/* CS:ECX = far ptr of _start noreloc */
	mov	ax,cs
	shl	eax,4
	add	ax,dx
	mov	edx,eax		/* EDX = linear address of _start noreloc */

#ifndef SMALL_BOOT
	/* store away the partition and two PXE structures */
	rol	ebx,16
	mov	bx,es
	rol	ebx,16
	mov	cs:[ecx + offset pxe_plus - offset _start],ebx
	mov	ebx,ss:[bp+4]
	mov	cs:[ecx + offset pxe_bang - offset _start],ebx
	cmp	byte ptr cs:[ecx + offset i386_biosflags - offset _start],0x6D
	je	1f
	push	cs
	pop	es
	lea	di,[ecx + offset bios_bootpte - offset _start]
	movsd
	movsd
	movsd
	movsd
1:
#endif

	/* set up initial stack */
	add	eax,offset cmd_buf + CMD_BUFF_SIZE - 4 - offset _start
	mov	ebx,eax
	shr	ebx,4
	and	bx,0xF000	/* BX:AX = far ptr initial stack */
	and	ax,0xFFFC
	mov	ss,bx
	movzx	esp,ax

	/* set up segments */
	mov	ax,cs
	mov	ds,ax
	mov	es,ax
	mov	fs,ax
	mov	gs,ax

	/*-
	 * DS = ES = FS = GS	== CS
	 * CS:(E)CX = flat:EDX	== _start (noreloc)
	 * SS:ESP		== initial stack
	 * EFLAGS		== 0
	 */

#ifndef SMALL_BOOT
	/* find out if we're a DOS or SYSLINUX programme */
	cmp	cx,0x0100
	jne	Lnocom
	cmp	word ptr ds:[0],0x20CD
	jne	Lnocom

	push	edx
	push	ecx

	mov	ah,0x30		/* DOS/SYSLINUX: get DOS version */
	int	0x21
	cmp	eax,0x59530000
	jne	Lnolx
	cmp	ecx,0x4E490000
	jne	Lnolx
	cmp	edx,0x58550000
	jne	Lnolx
	cmp	ebx,0x4C530000
	jne	Lnolx

	/* SYSLINUX */
	mov	ax,0x0005	/* SYSLINUX: force text mode */
	int	0x22
	mov	ax,0x000A	/* SYSLINUX: get information */
	int	0x22
	pop	ecx
	cmp	al,0x31
	jb	Linvlinux
	je	Lsyslinux
	cmp	al,0x34
	ja	Linvlinux
	je	Lextlinux
	cmp	al,0x33
	je	Lisolinux

Lpxelinux:
	mov	ax,es
	shl	eax,16
	mov	ax,bx
	mov	cs:[ecx + offset pxe_bang - offset _start],eax
	mov	cs:[ecx + offset pxe_plus - offset _start],eax
	xor	edx,edx
	mov	bx,3		/* clean up but retain PXE and UNDI */
	jmp	Loklx

Lsyslinux:
Lextlinux:
	mov	eax,es:[bx]
	mov	cs:[ecx + offset bios_bootpte - offset _start],eax
	mov	eax,es:[bx+4]
	mov	cs:[ecx + offset bios_bootpte - offset _start + 4],eax
	mov	eax,es:[bx+8]
	mov	cs:[ecx + offset bios_bootpte - offset _start + 8],eax
	mov	eax,es:[bx+12]
	mov	cs:[ecx + offset bios_bootpte - offset _start + 12],eax
Lisolinux:
Linvlinux:
	and	edx,0xFF
	mov	dh,1
	xor	bx,bx		/* clean up everything */
Loklx:	or	dh,2
	shl	edx,8
	or	cs:[ecx + offset Ldrvi - offset _start],edx

	mov	ax,0x000C	/* SYSLINUX: final cleanup */
	mov	dx,bx		/* see above */
	int	0x22
	jmp	Lokcom		/* we're done */

Lnolx:	/* DOS */
	mov	ah,0x19
	int	0x21
	pop	ecx
	lea	ebx,[ecx + offset Ldrvi - offset _start]
	mov	ah,al		/* ign ign dosdrv dosdrv */
	cmp	al,2
	jb	1f		/* floppy (BIOS 00h, 01h) for DOS A:, B: */
	mov	al,0x80		/* fake BIOS 80h for DOS C:, D:, E:, ... */
1:	shl	eax,8		/* ign dosdrv biosdrv zero */
	inc	ax		/* 01 = flag: DOS drive valid */
	xchg	ah,al		/* ign dosdrv flag=1 biosdrv */
	shl	eax,8		/* dosdrv flag biosdrv zero */
	mov	al,cs:[bx]	/* dosdrv flag biosdrv partp */
	mov	cs:[bx],eax

Lokcom:
	xor	eax,eax
	push	eax
	popfd

	pop	edx
Lnocom:
#endif

	/*-
	 * CS:(E)CX = flat:EDX	== _start (noreloc)
	 * SS:ESP		== valid, initial stack
	 * EFLAGS		== valid, sane
	 */

	cmp	edx,SA_LINKADDR
	je	LisRel

	mov	si,dx
	and	si,0x000F
	mov	eax,edx
	shr	eax,4
	mov	ds,ax		/* DS:SI = _start (noreloc) min. */

	cmp	edx,0x30000
	jb	LdoRel
	cmp	edx,0x4FFFF
	ja	LdoRel

	/* relocate twice, ugh */
	mov	ax,0x6000
	mov	es,ax
	xor	di,di
	mov	cx,0xFFF0
	rep	movsb

	mov	ax,es
	mov	ds,ax
	mov	ss,ax
	mov	esp,offset cmd_buf + CMD_BUFF_SIZE - 4 - offset _start
	push	ax
	mov	eax,offset LdoRel
	push	ax
	xor	si,si
	lret

LdoRel:	mov	ax,SA_LINKSEG
	mov	es,ax
	xor	di,di
	mov	cx,0xFFF0
	rep	movsb

LisRel:	mov	ax,0x3000
	mov	ss,ax
	mov	esp,0x0000FFFC

	mov	ax,SA_LINKSEG
	mov	ds,ax
	mov	es,ax
Lmb16e:	mov	fs,ax
	mov	gs,ax
	push	ax
	mov	eax,offset Lstart
	push	ax

	xor	eax,eax
	push	eax
	popfd
	lret

	/* whew, we're relocated */
Lstart:	call	idt_init
#ifdef BOOTSELECT_HOOK
	sti
	.globl	Lhook
	call	Lhook
	push	eax
#endif

	cli
	call	real_to_prot
	.code32
	mov	ax,ds
	mov	fs,ax
	mov	gs,ax

	/* zero out .bss section */
	xor	eax,eax
	mov	ecx,offset _end
	mov	edi,offset _edata
	sub	ecx,edi
	rep	stosb
	/* zero out temporary stack */
	mov	edi,offset cmd_buf
	mov	ecx,CMD_BUFF_SIZE
	rep	stosb

#ifdef BOOTSELECT_HOOK
	/* store user choice */
	pop	dword ptr [hook_value]
#endif

	movzx	eax,byte ptr [i386_biosdev]
	push	eax
	call	boot
	jmp	_rtt

	/* Multiboot entry point */
	.p2align 4,0x90
Lmbrun:	mov	edx,[ebx+12]		/* boot_device */
	cld
	mov	esi,0x00100000
	mov	edi,SA_LINKADDR
	mov	ecx,0x4000
	rep	movsd
	mov	eax,offset Lmb2rm
	jmp	eax
	/* relocated */
Lmb2rm:	mov	esp,0x0003FFFC
	xor	eax,eax
	push	eax
	popfd

	mov	edi,offset Ldrvi
	shr	edx,16
	mov	eax,edx
	lodsb			/* user partition type */
	stosd			/* drive information */
	xor	eax,eax
	stosd			/* pxe_bang */
	stosd			/* pxe_plus */
	stosd			/* partition */
	stosd			/* partition */
	stosd			/* partition */
	stosd			/* partition */

	lgdt	Gdtr
	call	prot_to_real
	.code16
	mov	ax,SA_LINKSEG
	jmp	Lmb16e

	.p2align 4
	.globl	cmd_buf
	.size	cmd_buf, CMD_BUFF_SIZE
cmd_buf:
	.long	0xDEADBEEF
	. = cmd_buf + CMD_BUFF_SIZE - 4
	.long	0xCAFEBABE

	bounce_buf = 0x30000
	.globl	bounce_buf
	.size	bounce_buf, 4096
