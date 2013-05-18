/* $MirOS: src/sys/arch/i386/stand/boot/srt0.S,v 1.48 2009/01/10 14:30:44 tg Exp $ */

/*-
 * Copyright (c) 2003, 2004, 2005, 2006, 2007, 2008, 2009
 *	Thorsten Glaser <tg@mirbsd.de>
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
 *-
 * Initialisation code for second-stage or stand-alone boot loader.
 *
 * This code is responsible for:
 * - setting up a known environment, with no knowledge about current
 *   CPU state (except that we are in real mode and DL is the BIOS
 *   boot device)
 * - relocate ourselves to a known sane location (4000:0000h)
 * - checking if we're called from an El Torito bootable CD-ROM via
 *   the BIOS, or from a PBR, or from within MS-DOS, and take
 *   appropiate set-up action
 * - for El Torito, load in the full boot code again, as we cannot
 *   guarantee that faulty BIOSes load more than the first 2048 bytes
 * - set up some variables, load GDT, set up protected mode and
 *   jump into C code
 */

#include <machine/asm.h>
#include <assym.h>
#include "stand/boot/cmd.h"

	.intel_syntax noprefix
	.text
	.code16

/* It's hard to fight vs. broken BIOSes */
#ifdef	UTEST
#ifdef	UHARD
/* XXX does not work on Intel Mac with broken BIOS.EFI app */
#define	UD(x)	push bp; mov bp,(0x4040 + x); \
		gs mov [(0x0C80 + (2 * x))], bp; pop bp; \
		push ax; xor ax,ax; int 0x16; pop ax
#ifdef	UANAL
#define	UDX(x)	push bp; mov bp,(0x0940 + x); \
		gs mov [0x0C80], bp; pop bp; \
		push ax; xor ax,ax; int 0x16; pop ax
#else	/* UTEST, UHARD, not UANAL */
#define	UDX(x)	/* nothing */
#endif	/* UTEST, UHARD, not UANAL */
#else	/* UTEST, not UHARD */
#define	UD(x)	push bp; mov bp,(0x4040 + x); \
		gs mov [(0x0C80 + (2 * x))], bp; pop bp
#ifdef	UANAL
#define	UDX(x)	push bp; mov bp,(0x0940 + x); \
		gs mov [0x0C80], bp; pop bp
#else	/* UTEST, not UHARD, not UANAL */
#define	UDX(x)	/* nothing */
#endif	/* UTEST, not UHARD, not UANAL */
#endif	/* UTEST, not UHARD */
#define	UD32(x)	mov ebx,(0xB8A00 + (2 * x)); \
		mov word ptr [ebx],(0x4040 + x)
#else	/* not UTEST */
#define	UD(x)	/* nothing */
#define	UD32(x)	/* nothing */
#define	UDX(x)	/* nothing */
#endif	/* not UTEST */

	.globl	Gdtr
	.globl	_C_LABEL(_rtt)
	.globl	_rval
	.globl	_start
	.globl	_C_LABEL(bios_bootdev)
	.globl	_C_LABEL(bios_bootpte)
#ifndef SMALL_BOOT
	.globl	_C_LABEL(i386_toridev)
#endif
	.globl	_C_LABEL(boot)
	.globl	_C_LABEL(edata)
	.globl	_C_LABEL(end)
	.globl	idt_init
	.globl	real_to_prot
#ifndef SMALL_BOOT
	.globl	prot_to_real
#endif

_start:	cli
	jmp	Lstart
	. = _start + 0x08	/* "EL TORITO BOOT INFO TABLE" */
	.long	0		/* #no longer# filled in by mkisofs: */
	.long	0xcafebabe	/* LBA address of boot file */
	.p2align 4
_C_LABEL(bios_bootpte):
	.long	0, 0, 0, 0
	.p2align 4
Ltblk:	.long	0x13,0,0,0	/* El Torito parameter block */
	.byte	0,0,0
	. = _start + 0x4C
Lstart:	cld
	call	Linit
_rval:	.long	0x6A6D4F00	/* _start + 0x50 */
Linit:	pop	di
	mov	ax,0xB800
	mov	gs,ax		/* for UD() */
	UD(0)			/** @: we're here */
#ifndef SMALL_BOOT
	cmp	di,0x0150	/* test for .COM offset */
	jne	Ldxok
	mov	dl,0x80		/* fake HDD boot on DOS */
	/* begin SYSLINUX tests */
	cmp	word ptr cs:[0],0x20CD
	jne	Ldxok		/* no DOS PSP */
	push	gs
	push	di
	push	dx
	mov	eax,0x00003000	/* AH=30h: get DOS version */
	int	0x21
	cmp	eax,0x59530000
	jne	Lnolx
	cmp	ecx,0x4E490000
	jne	Lnolx
	cmp	edx,0x58550000
	jne	Lnolx
	cmp	ebx,0x4C530000
	jne	Lnolx
	mov	ax,0x0005	/* SYSLINUX: force text mode */
	int	0x22
	mov	ax,0x000A	/* SYSLINUX: get information */
	xor	cx,cx		/* ISOLINUX >= 3.73: emulation */
	int	0x22
	xor	di,di		/* for later: 0=HD 1=CD 2=emul */
	cmp	al,0x31		/* 31h: SYSLINUX */
	jb	Llxok
	je	Llxdx
	cmp	al,0x34		/* 34h: EXTLINUX */
	ja	Llxok
	je	Llxdx
	cmp	al,0x33		/* 33h: ISOLINUX */
	jb	Llxok		/* 32h: PXELINUX (no drive in DL) */
	inc	di
	or	ch,ch
	jz	Llxdx		/* El Torito no emulation */
	inc	di		/* El Torito FDD/HDD emulation */
Llxdx:	pop	ax		/* we have a drive in DL */
	push	dx
	or	di,di
	jnz	Llxok		/* CD have no MBR entry */
	/* copy boot partition entry */
	mov	eax,es:[bx]
	mov	cs:[0x0150+_C_LABEL(bios_bootpte)-_rval],eax
	mov	eax,es:[bx+4]
	mov	cs:[0x0150+_C_LABEL(bios_bootpte)-_rval+4],eax
	mov	eax,es:[bx+8]
	mov	cs:[0x0150+_C_LABEL(bios_bootpte)-_rval+8],eax
	mov	eax,es:[bx+12]
	mov	cs:[0x0150+_C_LABEL(bios_bootpte)-_rval+12],eax
Llxok:	push	di
	mov	ax,0x000C	/* SYSLINUX: final cleanup */
	xor	dx,dx		/* clean up everything */
	int	0x22
	pop	cx
	cmp	cl,2
	jne	Lnolx		/* HDD or El Torito no emulation */
	push	cs
	pop	ds
	mov	ax,0x4B00	/* BIOS: terminate emulation */
	mov	dl,0x7F		/* ... on all drives */
	mov	si,0x0150+Ltblk-_rval
	int	0x13
Lnolx:	pop	dx
	pop	di
	pop	gs
	/* end SYSLINUX tests */
#endif
Ldxok:	xor	eax,eax
	push	eax
	popfd
	UD(1)			/** A: flags set */
	mov	ax,di
	test	al,0x0F		/* test for alignment */
Lirrf:	jnz	Lirrf		/* forever loop */
	shr	ax,4
	mov	cx,cs
	add	ax,cx		/* ax:0000 is now _start+0x50 */
	mov	ecx,offset _rval - SA_LINKADDR
	shr	ecx,4
	sub	ax,cx		/* source */
	mov	ss,ax
	mov	esp,offset cmd_buf - SA_LINKADDR + CMD_BUFF_SIZE - 4
	cmp	ax,SA_LINKSEG
	je	LisRel
	UD(2)			/** B: relocation needed */
	cmp	ax,SA_LINKSEG - 0x1000		/* lower boundry */
	jb	Lrel2		/* below target area, relocate once */
	cmp	ax,SA_LINKSEG + 0x1000		/* upper boundary */
	ja	Lrel2		/* above target area, relocate once */
	/* within target area, relocate twice */
	UD(3)			/** C: relocate twice */
	mov	bx,SA_LINKSEG + 0x2000
	mov	es,bx		/* safe target: above */
	mov	ds,ax		/* original source */
	xor	si,si
	xor	di,di
	mov	cx,0x4000
	rep	movsd
	push	es
	mov	eax,offset Lrel1 - SA_LINKADDR
	push	ax
	mov	ax,es		/* target -> new source */
	lret
Lrel1:	mov	ss,ax
	mov	esp,offset cmd_buf - SA_LINKADDR + CMD_BUFF_SIZE - 4
Lrel2:	mov	ds,ax		/* source (original or above) */
	UD(4)			/** D: relocate once */
	mov	ax,SA_LINKSEG
	mov	es,ax		/* new target: final destination */
	xor	si,si
	xor	di,di
	mov	cx,0x4000
	rep	movsd

LisRel:	UD(5)			/** E: done reloc, or not needed */
	mov	ax,SA_LINKSEG
	push	ax
	mov	eax,offset Lmain - SA_LINKADDR
	push	ax
	lret

/*
 * Code which can assume sane location
 */

Lmain:	UD(6)			/** F: jump successful */
	mov	ax,0x3000
	mov	ss,ax
	mov	esp,0x0000FFFC
	mov	ax,cs
	mov	ds,ax
	mov	es,ax
	push	dx
	call	idt_init
	sti

	/* check if drive is a CD */
	xor	ax,ax
	push	ax
#ifndef SMALL_BOOT
	cmp	dl,0x88
	jae	1f
	push	dx
	mov	ah,0x41
	mov	bx,0x55aa
	int	0x13
	pop	dx
	jc	LnoCD
	cmp	bx,0xaa55
	jne	LnoCD
	or	ah,ah
	jz	LnoCD
1:	/* this may be a CD */
	mov	esi,offset Ltblk - SA_LINKADDR
	mov	byte ptr [si],0x13
	push	dx
	mov	ax,0x4B01
	int	0x13
	pop	dx
	jc	LnoCD
	cmp	byte ptr [si+2],dl
	jne	LnoCD
	test	byte ptr [si+1],0x0F
	jnz	LnoCD
	/* we have a CD in no emulation mode */
	pop	ax
	inc	ax
	push	ax
#endif

LnoCD:
#ifdef BOOTSELECT_HOOK
	UD(37)			/** e: calling the hook */
	call	Lhook
	mov	esi,eax
#endif
	UD(14)			/** N: preparing 32-bit */
	pop	dx
	shl	edx,16
	pop	dx
	mov	ebx,offset _rval - SA_LINKADDR
	mov	dh,[bx]		/* carry this over to VPAM */
	cli
	call	real_to_prot
	.code32
	mov	ax,ds
	mov	fs,ax
	mov	gs,ax
	push	edx
#ifdef BOOTSELECT_HOOK
	push	esi
#endif
	UD32(15)		/** O: 32-bit reached */
	UD32(16)		/** P: PMM initialised */
	/* zero out .bss section */
	xor	eax,eax
	mov	ecx,offset _C_LABEL(end)
	mov	edi,offset _C_LABEL(edata)
	sub	ecx,edi
	rep	stosb
	mov	edi,offset cmd_buf
	mov	ecx,CMD_BUFF_SIZE
	rep	stosb
#ifdef BOOTSELECT_HOOK
	/* store saved hook value */
	pop	ecx
	mov	[_C_LABEL(hook_value)],ecx
#endif
	/* store saved BIOS boot device */
	pop	eax
	mov	[_C_LABEL(userpt)],ah
	xor	edx,edx
	mov	dl,al
	push	edx
	mov	[_C_LABEL(bios_bootdev)],edx
#ifndef SMALL_BOOT
	shr	eax,16
	test	al,1
	jz	1f
	mov	[_C_LABEL(i386_toridev)],edx
1:
#endif
	UD32(17)		/** Q: jump into C code */
	/* jump into boot loader C code */
	call	_C_LABEL(boot)
	UD32(35)		/** c: return from C code */
	jmp	_C_LABEL(_rtt)

#ifndef SMALL_BOOT
	/*
	 * Multiboot header and entry point
	 */
	.p2align 4
Lmbhdr:	.long	0x1BADB002		/* magic */
	.long	0x00010000		/* flags */
	.long	-0x1BADB002-0x00010000	/* checksum */
	/* the addresses are all bounced to 1 MiB */
	.long	Lmbhdr - SA_LINKADDR + 0x00100000	/* header_addr */
	.long	0x00100000				/* load_addr */
	.long	0					/* load_end_addr */
	.long	0					/* bss_end_addr */
	.long	Lmbrun - SA_LINKADDR + 0x00100000	/* entry_addr */

Lmbrun:	mov	edx,[ebx+12]		/* boot_device */
	shr	edx,24
	mov	esp,offset cmd_buf + CMD_BUFF_SIZE - 4
	and	esp,0xFFFFFFFC
	/* relocate */
	xor	eax,eax
	push	eax
	popfd
	/* Note: GRUB does not support loading below 1 MiB */
	mov	esi,0x00100000
	mov	edi,SA_LINKADDR
	mov	ecx,0x4000		/* 64 KiB in dwords */
	rep	movsd
	mov	eax,offset Lmb2rm
	jmp	eax
	/* relocated */
Lmb2rm:	lgdt	Gdtr
	call	prot_to_real
	.code16
	mov	ax,0xB800
	mov	gs,ax
	mov	bx,SA_LINKSEG
	push	dx
	mov	ax,bx
	add	ah,0x10
	push	ax
	xor	eax,eax
	push	eax
	popfd
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
