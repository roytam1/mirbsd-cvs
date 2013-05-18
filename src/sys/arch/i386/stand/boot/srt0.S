/* $MirOS: src/sys/arch/i386/stand/boot/srt0.S,v 1.59 2009/01/11 19:49:19 tg Exp $ */

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
#ifndef SMALL_BOOT
	.globl	have_pxe
#endif
	/* global */
	.globl	_start
	.globl	bios_bootpte
	.globl	i386_userpt
	.globl	i386_biosdev
	.globl	i386_biosflags
	.globl	i386_dosdev
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
		/*-
		 * 01101101 = flags invalid
		 * xxxxxx00 = nothing special about drives
		 * xxxxxx01 = i386_dosdev valid, DOS interface
		 * xxxxxx10 = pxelinux or invalid FOOlinux
		 * xxxxxx11 = syslinux/extlinux/isolinux
		 * xxxxx1xx = probably booted via PXE
		 */
	i386_dosdev = Ldrvi + 3
		/*-
		 * if PXE: 0 = do not scan, 1 = do scan
		 */
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

#ifndef SMALL_BOOT
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
#endif

Linit:
#ifndef SMALL_BOOT
	mov	cx,es
	shl	ecx,16
	mov	cx,bx		/* ECX: PXENV+ */
	mov	bp,sp
	mov	edi,[bp+6]	/* EDI: !PXE */
	rol	esi,16
	mov	si,ds		/* ESI: SI:DS */
#endif

	xor	ebp,ebp
	push	ebp
	popfd
	pop	bp

	/* make cs:(e)bx = offset _start */
	lea	ebx,[ebp + offset _start - offset Lrval]
	/* make ebp = flat offset _start */
	mov	bp,cs
	shl	ebp,4
	add	ebp,ebx
	/* make ax = _start + 64K (approx.) */
	mov	eax,ebp
	shr	eax,4
	add	ax,0x1000
	/* set up initial stack */
	mov	ss,ax
	mov	esp,0x00003FEC

	/* first stage: before relocation */

	/* set up segment registers */
	mov	ax,cs
	mov	ds,ax
	mov	es,ax

#ifndef SMALL_BOOT
	/* store away structure pointers */
	mov	ds:[ebx + offset pxe_plus - offset _start],ecx
	mov	ds:[ebx + offset pxe_bang - offset _start],edi
	cmp	byte ptr ds:[ebx + offset i386_biosflags - offset _start],0x6D
	je	1f
	mov	ds,si
	rol	esi,16
	lea	di,[ebx + offset bios_bootpte - offset _start]
	movsd
	movsd
	movsd
	movsd
	mov	ax,cs
	mov	ds,ax
	jmp	3f
1:	xor	eax,eax
	mov	ah,dl
	cmp	ebp,0x00007C00
	jne	2f
	or	eax,0x01040000		/* PXE, do scan */
2:	mov	al,ds:[ebx + offset Ldrvi - offset _start]
	mov	ds:[ebx + offset Ldrvi - offset _start],eax
3:	/* find out if we're a DOS or SYSLINUX COMBOOT programme */
	cmp	bx,0x0100
	jne	Lnocom
	cmp	word ptr ds:[0],0x20CD
	jne	Lnocom

	push	ebp
	push	ebx

	xor	eax,eax
	/* from DOS or SYSLINUX: no PXE or bootpte */
	lea	edi,[ebx + offset pxe_bang - offset _start]
	mov	cx,6
	rep	stosd

	mov	ah,0x30		/* get DOS version */
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
	push	cs
	pop	ds
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
	mov	ds:[ecx + offset pxe_bang - offset _start],eax
	mov	ds:[ecx + offset pxe_plus - offset _start],eax
	xor	edx,edx
	mov	ah,4		/* probably PXE :) but do not scan */
	mov	bx,3		/* clean up but retain PXE and UNDI */
	jmp	Lislx

Lsyslinux:
Lextlinux:
	mov	eax,es:[bx]
	mov	ds:[ecx + offset bios_bootpte - offset _start],eax
	mov	eax,es:[bx+4]
	mov	ds:[ecx + offset bios_bootpte - offset _start + 4],eax
	mov	eax,es:[bx+8]
	mov	ds:[ecx + offset bios_bootpte - offset _start + 8],eax
	mov	eax,es:[bx+12]
	mov	ds:[ecx + offset bios_bootpte - offset _start + 12],eax
Lisolinux:
Linvlinux:
	and	edx,0xFF
	mov	dh,1
	xor	bx,bx		/* clean up everything */
Lislx:	or	dh,2
	shl	edx,8
	mov	dl,ds:[ecx + offset Ldrvi - offset _start]
	mov	ds:[ecx + offset Ldrvi - offset _start],edx

	mov	ax,0x000C	/* SYSLINUX: final cleanup */
	mov	dx,bx		/* see above */
	int	0x22
	jmp	Liscom

Lnolx:	/* DOS */
	mov	ah,0x19
	int	0x21
	push	cs
	pop	ds
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
	mov	al,ds:[bx]	/* dosdrv flag biosdrv partp */
	mov	ds:[bx],eax

Liscom:	pop	ebp
	xor	eax,eax
	push	eax
	popfd
Lnocom:	/* flags are (already) okay */
#endif

	/* load source address (_start) normalised */
	mov	ebx,ebp
	shr	ebx,4
	mov	ds,bx
	mov	si,bp
	and	si,0x000F

	/* check if we need to relocate */
	cmp	ebp,SA_LINKADDR
	je	LdoRel		/* to set up the stack */
	cmp	ebp,0x1C000
	jbe	LdoRel		/* way below target */
	cmp	ebp,0x50000
	jae	LdoRel		/* somewhat above target */

	/* eek, relocate twice */
	mov	ax,0x7000
	mov	ss,ax
	mov	sp,0x3FFC
	mov	ax,0x6000
	push	ax
	mov	es,ax
	xor	di,di
	mov	eax,offset LdoRel - offset _start
	push	ax
	push	es
	push	di
	mov	cx,0xFFF0
	rep	movsb
	pop	si
	pop	ds
	lret

LdoRel:	mov	ax,0x3000
	mov	ss,ax
	mov	esp,0x0000FFFC
	cmp	ebp,SA_LINKADDR
	je	LisRel

	mov	ax,SA_LINKSEG
	mov	es,ax
	xor	di,di
	mov	cx,0xFFF0
	rep	movsb

	/* assumes flags=0, SS:ESP set up to 3000:0000FFFCh */
LisRel:	mov	ax,SA_LINKSEG
	mov	ds,ax
	mov	es,ax
	push	ax
	mov	eax,offset Lstart - offset _start
	push	ax
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
Lsta32:	.code32
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

#ifndef SMALL_BOOT
	/* Multiboot entry point */
	.p2align 4,0x90
Lmbrun:	mov	edx,[ebx+12]		/* boot_device */
	mov	esp,0x0003FFFC
	xor	eax,eax
	push	eax
	popfd
	mov	esi,0x00100000
	mov	edi,SA_LINKADDR
	mov	ecx,0x4000
	rep	movsd
	mov	eax,offset Lmb2rm
	jmp	eax
	/* relocated */
Lmb2rm:	mov	edi,offset Ldrvi
	shr	edx,16
	mov	eax,edx
	mov	al,[edi]	/* user partition type */
	stosd			/* drive information */
	xor	eax,eax
	stosd			/* pxe_bang */
	stosd			/* pxe_plus */
	stosd			/* partition */
	stosd			/* partition */
	stosd			/* partition */
	stosd			/* partition */
	mov	[have_pxe],eax	/* do not even try */

	lgdt	Gdtr
	call	prot_to_real	/* converts stack */
	.code16
	jmp	LisRel
#endif

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

	pxe_command_buf = bounce_buf + 4096
	.globl	pxe_command_buf
	.size	pxe_command_buf, 256

	biosdev_lba_buf = pxe_command_buf + 256
	.globl	biosdev_lba_buf
	.size	biosdev_lba_buf, 16
