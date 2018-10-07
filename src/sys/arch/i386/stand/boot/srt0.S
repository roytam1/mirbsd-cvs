/* $MirOS: src/sys/arch/i386/stand/boot/srt0.S,v 1.85 2012/09/02 22:08:48 tg Exp $ */

/*-
 * Copyright (c) 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2012
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
	.globl	real_to_prot
	.globl	prot_to_real
	.globl	boot
	.globl	_edata
	.globl	_end
	.globl	_rtt
#ifdef USE_PXE
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
	.globl	pxecall_addr
	.globl	lmbm_num
	.globl	lmbm_ofs

_start:	cli
	call	Linit
Lrval:	.p2align 2
	. = _start + 4
	/*	  ffffddpp	(f)lags user(p)artype (d)rive */
Ldrvi:	.long	0x696D4F00	/* drive information and magic */
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
	. = _start + 8
pxe_bang:
	.size	pxe_bang,4
	.long	0		/* address of !PXE structure */
	. = _start + 12
pxe_plus:
	.size	pxe_plus,4
	.long	0		/* address of PXENV+ structure */
	. = _start + 16
bios_bootpte:
	.size	bios_bootpte,16
	.long	0, 0, 0, 0	/* 16 bytes from initial DS:SI */
	. = _start + 32
pxecall_addr:
	.size	pxecall_addr,4
	.long	0		/* PXE RM entry point (FAR pointer) */
lmbm_num:
	.size	lmbm_num,4
	.long	0		/* number of Loadable MultiBoot Modules */
lmbm_ofs:
	.size	lmbm_ofs,4
	.long	0		/* address of LMBM table, if loaded */

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

	/* pointer to ldbsd.com command line or 1 (DOS/COMBOOT PSP) */
Largp:	.long	0

Linit:	/* qemu sucks, int3 doesn’t work */
	push	ds
	push	si
	xor	si,si
	mov	ds,si
	mov	cl,0xCB
	xchg	ds:[si],cl
	/* set a “b *0” to stop at this point */
	lcall	0x0000,0x0000
	xchg	ds:[si],cl
	pop	si
	pop	ds

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

#ifdef SMALL_BOOT
	xor	eax,eax
	mov	ah,dl
	mov	al,ds:[ebx + offset Ldrvi - offset _start]
	mov	ds:[ebx + offset Ldrvi - offset _start],eax
#else
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
3:	/* find out if we're a DOS or SYSLINUX COMBOOT program */
	cmp	bx,0x0100
	jne	Lnocom
	cmp	word ptr ds:[0],0x20CD
	jne	Lnocom

	/* store magic flag to Largp for using the command line */
	inc	byte ptr ds:[ebx + offset Largp - offset _start]

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
	mov	dh,4		/* probably PXE :) but do not scan */
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
	/* subtract 128 for DOS/COMBOOT PSP command line */
	sub	bx,(128/16)
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
	/* subtract 128 for DOS/COMBOOT PSP command line */
	sub	ax,(128/16)
	mov	es,ax
	xor	di,di
	mov	eax,offset LdoRel - offset _start
	push	ax
	push	es
	push	di
	/* min. 0xFF00 max. code size + 0x80 PSP cmdline */
	mov	cx,0xFFF0
	rep	movsb
	pop	si
	pop	ds
	lret

LdoRel:	mov	ax,0x3000
	mov	ss,ax
	mov	esp,0x0000FF7C
	cmp	ebp,SA_LINKADDR
	je	LisRel

	/* subtract 128 for DOS/COMBOOT PSP command line */
	mov	ax,(SA_LINKSEG - (128/16))
	mov	es,ax
	xor	di,di
	/* same as above */
	mov	cx,0xFFF0
	rep	movsb

	/* assumes flags=0, SS:ESP set up to 3000:0000FF7Ch */
LisRel:	mov	ax,SA_LINKSEG
	mov	ds,ax
	mov	es,ax
	push	ax
	mov	eax,offset Lstart - offset _start
	push	ax
	lret

	/* whew, we're relocated */
Lstart:
	/* check for presence of command line */
	mov	esi,offset Largp - offset _start
	mov	eax,[si]
	or	eax,eax
	jz	Lnocmd
#ifdef BOOTSELECT_HOOK
	xor	ebx,ebx
#endif
	cmp	eax,1		/* magic */
	jne	Liscmd
	/* we have a DOS/COMBOOT PSP, analyse it */
	mov	ax,ds
	push	ax
	sub	ax,(128/16)
	mov	ds,ax
	xor	cx,cx
	mov	cl,byte ptr ds:[0]
	mov	si,1
1:	or	cx,cx
	jz	Lpspno
	lodsb
	cmp	al,0x09		/* tab */
	je	2f
	cmp	al,0x0D		/* CR */
	je	2f
	cmp	al,0x20		/* space */
	jne	3f
2:	dec	cx
	jmp	1b
3:	dec	si
	mov	di,si
	add	di,cx
	dec	di
4:	mov	al,[di]
	cmp	al,0x09		/* tab */
	je	5f
	cmp	al,0x0D		/* CR */
	je	5f
	cmp	al,0x20		/* space */
	jne	6f
5:	dec	cx
	jz	Lpspno
	dec	di
	jmp	4b
6:	inc	di
	xor	eax,eax
	mov	[di],al		/* convert to NUL-terminated */
	/* DS:SI now points to NUL-terminated argv (SI < 0x80) */
	mov	ax,ds
	shl	eax,4
	add	ax,si
	pop	ds
	/* store flat pointer to NUL-terminated argv into Largp */
	mov	esi,offset Largp - offset _start
	mov	[si],eax
#ifdef BOOTSELECT_HOOK
	xor	ebx,ebx
#endif
	jmp	Liscmd

Lpspno:	pop	ds
	xor	eax,eax
	mov	esi,offset Largp - offset _start
	mov	[si],eax
Lnocmd:	/* no command line found */
#ifdef BOOTSELECT_HOOK
	sti
	.globl	Lhook
	call	Lhook
	mov	ebx,eax
#endif
Liscmd:	/* a command line was found */

	call	real_to_prot
Lsta32:	.code32
	/* ensure stack is 32-bit aligned */
	mov	esp,0x0003FF7C
	/* zero out .bss section */
	xor	eax,eax
	push	eax
	popfd
	mov	ecx,offset _end
	mov	edi,offset _edata
	sub	ecx,edi
	rep	stosb

	/* zero out stack segment lower parts */
	mov	edi,offset ssbss_beg
	mov	ecx,offset ssbss_end - offset ssbss_beg
	rep	stosb

#ifdef BOOTSELECT_HOOK
	/* store user choice */
	mov	[hook_value],ebx
#endif

	/* store command line, if any */
	mov	esi,[Largp]
	or	esi,esi
	jz	1f
	mov	ecx,(CMD_BUFF_SIZE - 1)
	mov	edi,offset cmd_buf
	rep	movsb
	/* NUL-terminate potentially too long multiboot cmdline */
	mov	al,0
	stosb
1:

	movzx	eax,byte ptr [i386_biosdev]
	push	eax
	call	boot
	jmp	_rtt

#ifndef SMALL_BOOT
	/* Multiboot entry point */
	.p2align 4,0x90
Lmbrun:	mov	esp,0x0003FF7C
	xor	eax,eax
	push	eax
	popfd

	/* set a “b *0” to stop at this point */
	push	[eax]
	mov	byte ptr [eax],0xC3
	call	eax
	pop	[eax]

	mov	esi,0x00100000
	mov	edi,SA_LINKADDR
	mov	ecx,0x4000
	rep	movsd
	mov	eax,offset Lmb2rm
	jmp	eax
	/* relocated */
Lmb2rm:	mov	edi,offset Ldrvi
	mov	edx,[ebx+12]		/* boot_device */
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
#ifdef USE_PXE
	mov	[have_pxe],eax	/* do not even try */
#endif

	mov	eax,[ebx]
	and	eax,(1 << 2)	/* do we have command line? */
	jz	1f		/* nope */
	mov	esi,[ebx+16]	/* pointer */
	/*
	 * annoyingly enough, the first word on the command line
	 * is our own pathname, so we must skip it
	 */
4:	lodsb
	or	al,al		/* NUL */
	jz	1f
	cmp	al,0x09		/* tab */
	je	2f
	cmp	al,0x0A		/* LF */
	je	2f
	cmp	al,0x0D		/* CR */
	je	2f
	cmp	al,0x20		/* space */
	jne	4b
2:	lodsb
	or	al,al		/* NUL */
	jz	1f
	cmp	al,0x09		/* tab */
	je	2b
	cmp	al,0x0A		/* LF */
	je	2b
	cmp	al,0x0D		/* CR */
	je	2b
	cmp	al,0x20		/* space */
	je	2b
	dec	esi
	mov	edi,esi
	mov	ecx,CMD_BUFF_SIZE
	xor	eax,eax
	repne	scasb
3:	dec	edi
	mov	al,[edi]
	cmp	al,0x09		/* tab */
	je	3b
	cmp	al,0x0A		/* LF */
	je	3b
	cmp	al,0x0D		/* CR */
	je	3b
	cmp	al,0x20		/* space */
	je	3b

	/* got a non-empty command line */
	mov	byte ptr [edi+1],0
	mov	[Largp],esi

	/* got no command line */
1:	mov	eax,[ebx]
	and	eax,(1 << 3)	/* do we have modules? */
	jz	Lnombm		/* nope */
	mov	eax,[ebx+20]	/* how many? */
	mov	[lmbm_num],eax
	mov	eax,[ebx+24]	/* module information */
	mov	[lmbm_ofs],eax
Lnombm:

	lgdt	Gdtr
	call	prot_to_real	/* converts stack */
	.code16
	jmp	LisRel
#endif

#ifdef USE_PXE
	.code32
	.globl	pxecall_bang
pxecall_bang:
	push	ebp
	mov	ebp,esp
	pushfd
	push	ebx
	push	esi
	push	edi

	mov	ebx,[ebp+8]
	mov	edi,offset pxe_command_buf - offset bounce_buf

	call	prot_to_real
	.code16
	sti

	push	ss
	push	di
	push	bx
	lcall	ds:[32]		/* pxecall_addr */
	add	sp,6
	movzx	ebx,ax

	call	real_to_prot
	.code32

	mov	eax,ebx
	pop	edi
	pop	esi
	pop	ebx
	popfd
	pop	ebp
	ret

	.globl	pxecall_plus
pxecall_plus:
	push	ebp
	mov	ebp,esp
	pushfd
	push	ebx
	push	esi
	push	edi

	mov	ebx,[ebp+8]
	mov	edi,offset pxe_command_buf - offset bounce_buf

	call	prot_to_real
	.code16
	sti

	push	ss
	pop	es
	lcall	ds:[32]		/* pxecall_addr */
	movzx	ebx,ax

	call	real_to_prot
	.code32

	mov	eax,ebx
	pop	edi
	pop	esi
	pop	ebx
	popfd
	pop	ebp
	ret
#endif


	bounce_buf = 0x30000
	.globl	bounce_buf
	.size	bounce_buf, 4096

	crc_table = bounce_buf + 4096
	.globl	crc_table
	.size	crc_table, 1024

	pxe_command_buf = crc_table + 1024
	.globl	pxe_command_buf
	.size	pxe_command_buf, 256

	sa_fixed_table = pxe_command_buf + 256
	.globl	sa_fixed_table
	.size	sa_fixed_table, 2176

	biosdev_lba_buf = sa_fixed_table + 2176
	.globl	biosdev_lba_buf
	.size	biosdev_lba_buf, 16

	cmd_buf = biosdev_lba_buf + 16
	.globl	cmd_buf
	.size	cmd_buf, CMD_BUFF_SIZE

	/* last; size unknown (<0x1000) */
	cmd = cmd_buf + CMD_BUFF_SIZE
	.globl	cmd
	.size	cmd, CMD_STRUCT_SIZE

	ssbss_beg = bounce_buf
	ssbss_end = cmd + 0x0900
