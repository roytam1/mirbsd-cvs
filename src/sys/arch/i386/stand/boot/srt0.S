/* $MirOS: src/sys/arch/i386/stand/boot/srt0.S,v 1.7 2006/04/10 20:54:46 tg Exp $ */

/*-
 * Copyright (c) 2003, 2004, 2005, 2006
 *	Thorsten Glaser <tg@mirbsd.de>
 *
 * Licensee is hereby permitted to deal in this work without restric-
 * tion, including unlimited rights to use, publicly perform, modify,
 * merge, distribute, sell, give away or sublicence, provided all co-
 * pyright notices above, these terms and the disclaimer are retained
 * in all redistributions or reproduced in accompanying documentation
 * or other materials provided with binary redistributions.
 *
 * All advertising materials mentioning features or use of this soft-
 * ware must display the following acknowledgement:
 *	This product includes material provided by Thorsten Glaser.
 *
 * Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
 * express, or implied, to the maximum extent permitted by applicable
 * law, without malicious intent or gross negligence; in no event may
 * licensor, an author or contributor be held liable for any indirect
 * or other damage, or direct damage except proven a consequence of a
 * direct error of said person and intended use of this work, loss or
 * other issues arising in any way out of its use, even if advised of
 * the possibility of such damage or existence of a nontrivial bug.
 *-
 * Initialisation code for second-stage or stand-alone boot loader.
 *
 * This code is responsible for:
 * - setting up a known environment, with no knowledge about current
 *   CPU state (except that we are in real mode and DL is the BIOS
 *   boot device)
 * - relocate ourselfes to a known sane location (0x4000:0x0120)
 * - checking if we're called from an El Torito bootable CD-ROM via
 *   the BIOS, or from a PBR, or from within MS-DOS, and take
 *   appropiate set-up action
 * - for El Torito, load in the full boot code again, as we cannot
 *   guarantee that faulty BIOSes load more than the first 2048 bytes
 * - if faulty BIOS makes problems, use the table which can be written
 *   with 'mkisofs -no-emul-boot -boot-load-size 4 -boot-info-table'
 *   into the image to locate start of the boot file; always load 64K
 * - set up some variables, load GDT, set up protected mode and
 *   jump into C code
 */

#include <machine/asm.h>
#include <assym.h>

	.intel_syntax noprefix
	.text
	.code16

/* It's hard to fight vs. broken BIOSes */
#ifdef	UTEST
#ifdef	UHARD
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
	.globl	_C_LABEL(boot)
	.globl	_C_LABEL(edata)
	.globl	_C_LABEL(end)
	.globl	_ASM_LABEL(pmm_init)
#ifndef FFS_ONLY
	.globl	_C_LABEL(tori_bootflag)
	.globl	_C_LABEL(tori_pblk)
#endif

_start:	cli
	jmp	_star2
	. = _start + 0x08	/* "EL TORITO BOOT INFO TABLE" */
	.long	0		/* filled in by mkisofs: */
Lbofs:	.long	0xcafebabe	/* LBA address of boot file */
	. = _start + 0x40
_star2:	mov	bx,SA_LOADSEG
	mov	ss,bx
	mov	esp,0xC0
	sti
	push	dx
	call	Linit
_rval:	.long	0x6A6D4F00	/* _start + 0x50 */
Linit:	pop	di
	mov	ax,0xB800
	mov	gs,ax		/* for UD() */
	UD(0)			/** @: we're here */
	mov	ax,bx
	add	ah,0x10		/* add 64K (apparent max. code size) */
	push	ax		/* future SS */
	add	ah,0x10		/* add that 64K for a safe buffer */
	mov	fs,ax		/* for buffer I/O */
	xor	eax,eax
	push	eax
	popfd
	UD(1)			/** A: flags set */
	mov	ax,di
	and	ax,0x000F	/* test for alignment */
Lirrf:	jnz	Lirrf		/* forever loop */
	mov	ax,di
	shr	ax,4
	mov	cx,cs
	add	ax,cx		/* ax:0000 is now _start+0x50 */
	mov	cx,ax
	sub	cx,RL_VAL
	cld
	xor	si,si
	UD(2)			/** B: alignment okay */
	cmp	cx,bx		/* bx is still SA_LOADSEG */
	je	LisRel		/* already relocated */
	jnb	LdoRel		/* loaded above target address */
	UD(3)			/** C: below target */
	std
	dec	si		/* loaded below target addr, go backwards */
LdoRel:	UD(4)			/** D: doing reloc */
	xor	cx,cx
	dec	cx
	mov	di,si
	sub	ax,5		/* make up for stuff above _rval */
	mov	ds,ax
	add	bx,RL_VAL
	sub	bx,5		/* dito */
	mov	es,bx
	rep	movsb
LisRel:	UD(5)			/** E: done reloc, or not needed */
	cld
	jmp	SA_LOADSEG,offset Lstart

/*
 * Stuff which MUST NOT be placed in the .bss section
 */

#ifndef FFS_ONLY
_C_LABEL(tori_bootflag):
	.long	0
_C_LABEL(tori_pblk):
Ltblk:	.long	0x13,0,0,0	/* El Torito parameter block */
	.byte	0,0,0
Lbdev:	.byte	0		/* local copy of BIOS boot device */
Llba:	.word	0x0010		/* LBA parameter block */
	.word	0x0001
	.long	0,0,0
#else
Lbdev:	.byte	0		/* local copy of BIOS boot device */
#endif

/*
 * Code which can assume sane location
 */

Lstart:	UD(6)			/** F: jump successful */
	pop	ax		/* saved future stack base */
	pop	dx		/* saved BIOS drive */
	mov	ss,ax
	mov	sp,0xFFFC	/* another nearly-64K for stack */
	mov	ax,cs
	mov	ds,ax
	mov	es,ax
	mov	[Lbdev],dl
#ifdef	EXTRALOUD
	call	L..e1
	.asciz	"00 at DL\r\n"
L..e1:	mov	al,dl
	pop	si
	mov	di,si
	call	LpBY
	call	Lotxt
#endif
#ifdef	LOUD
	mov	si,offset Lsrt0
	call	Lotxt
#endif
#ifdef	DEBUG_OFS
	mov	[Lofsd],esi
#endif

#ifdef FFS_ONLY
	jmp	L..12
#else
#ifdef	WANT_ELTORITO_CHECK
	/* check for El Torito */
	mov	ax,0x4B01
	mov	si,offset Ltblk
	int	0x13
#ifdef	EXTRALOUD
	pushf
	pusha
	pushf
	call	L..e2
	.ascii	"Load SPEC returned, DL = "
L..e21:	.ascii	"00; CF="
L..e22:	.ascii	"00; [SI+2]="
L..e23:	.asciz	"00\r\n"
L..e2:	xor	ax,ax
	pop	bp
	popf
	adc	al,0
	mov	di,offset L..e22
	call	LpBY
	mov	al,dl
	mov	di,offset L..e21
	call	LpBY
	mov	al,[si+2]
	mov	di,offset L..e23
	call	LpBY
	mov	si,bp
	call	Lotxt
	popa
	popf
#endif
	jc	LnoCD
	UD(7)			/** G: El Torito found */
	xor	eax,eax
	dec	eax
	mov	al,dl
	mov	[_C_LABEL(tori_bootflag)],eax

	/*
	 * now we have to find out where on the CD-ROM the bootable
	 * image is located (looking for "default" image)
	 */

	/* get boot record */
	mov	eax,0x11
	call	LcdLDS		/* loads to FS:0x0000 */
	UD(8)			/** H: boot record loaded */
	fs mov	eax,[0]
	cmp	eax,0x30444300	/* '\0CD001' magic */
	jne	LbmCD		/* bad magic CD */

	/* get boot catalogue */
	fs mov	eax,[0x47]
	call	LcdLDS
	UD(9)			/** I: boot catalogue loaded */
	fs mov	ax,[0]
	dec	ax
	jne	LbmCD
	fs mov	ax,[0x1E]
	cmp	ax,0xAA55
	jne	LbmCD
	fs mov	ax,[0x20]
	cmp	ax,0x0088	/* no emulation, default entry */
	jne	LbmCD
	fs mov	eax,[0x28]	/* address */
	UD(10)			/** J: boot image found, no fake */
#else	/* not WANT_ELTORITO_CHECK */
	jmp	LnoCD
#endif	/* not def WANT_ELTORITO_CHECK */

LisCD:	mov	bx,SA_LINKSEG	/* target segment */
	inc	eax		/* don't load the first sector again */
	add	bx,0x80		/* 2048 bytes in paragraphs */
	UDX(2)
	mov	byte ptr [2+Llba],31	/* we don't load more anyways */
	push	fs
	mov	fs,bx
	call	LcdLDS
	UDX(3)
	pop	fs
	UD(11)			/** K: boot image loaded */
#ifdef	DEBUG_OFS
	mov	eax,[Lofsd]
	cmp	eax,0xfeedcafe
	je	L..37
	UD(37)			/** e: magic check failed */
#ifdef	LOUD
	call	L..37a
	.asciz	"Load magic failed!\r\nPress a key to reboot..."
L..37a:	pop	si
	call	Lotxt
#endif
	xor	ax,ax
	int	0x16
	jmp	0xF000,0xFFF0
#endif
L..37:	jmp	LpreCD		/* prepare boot from CD */
#endif /* !FFS_ONLY */

#ifdef	LOUD
Lotxt:	lodsb
	or	al,al
	je	Lretn
	mov	ah,0x0E
	mov	bx,7
	int	0x10
	jmp	Lotxt

Lsrt0:	.ascii	"MirOS boot v"
	.ascii	__BOOT_VER
	.asciz	" srt0 initialising\r\n"
#endif

#ifndef FFS_ONLY
LcdLDS:	pusha
	push	eax
	UDX(4)
#ifdef	EXTRALOUD
	pusha
	call	L..e3
	.ascii	"called LDS at LBA="
L..e31:	.ascii	"00000000 DL="
L..e32:	.ascii	"00 #="
L..e33:	.asciz	"0000 "
L..e3:	mov	di,offset L..e31
	call	LpDW
	mov	al,dl
	pop	si
	mov	di,offset L..e32
	call	LpBY
	mov	di,offset L..e33
	mov	ax,[2+Llba]
	call	LpWO
	call	Lotxt
	popa
	pop	eax
	push	eax
#endif
	xor	bp,bp
	mov	[8+Llba],eax	/* block number */
	mov	ax,fs
	mov	[6+Llba],ax	/* transfer address */
LcdLD0:	mov	ah,0x42
	mov	si,offset Llba
	int	0x13
#ifdef	UANAL
	pushf
	UDX(5)
	popf
#endif
	jc	LcdLD1
	UDX(6)
	pop	eax
	popa
Lretn:	ret
LcdLD1:	pusha
	UDX(33)
	xor	ah,ah
	int	0x13
	mov	ax,0x0E40
	mov	bx,7
	int	0x10
	popa
	inc	bp
	cmp	bp,5
	jb	LcdLD0
	UDX(34)
	UD(33)			/** a: CD read failed */
	/* FALL-THROUGH */

LbmCD:	UD(34)			/** b: CD bad magic */
#ifdef	LOUD
	call	L..34
	.asciz	"Bad Magic reading from CD\r\n"
L..34:	pop	si
	call	Lotxt
#endif
	xor	eax,eax		/* reset to default floppy boot */
	mov	[_C_LABEL(tori_bootflag)],eax
	/* FALL-THROUGH */

LnoCD:	mov	ebp,0xcafebabe	/* kludge! */
	mov	eax,ebp
	xchg	eax,[Lbofs]	/* only once */
	cmp	eax,ebp
	je	L..12
	push	eax
	UD(36)			/** d: attention fake torito */
#ifdef	LOUD
	call	L..36
	.asciz	"Attention: faking El Torito boot!\r\n"
L..36:	pop	si
	call	Lotxt
#endif
	UDX(1)
	mov	dl,[Lbdev]
	xor	eax,eax
	dec	eax
	mov	al,dl
	mov	[_C_LABEL(tori_bootflag)],eax
	mov	[2+Ltblk],al
	mov	ax,0x07C0
	mov	[12+Ltblk],ax
	mov	ax,32
	mov	[14+Ltblk],ax
	pop	eax
	mov	[4+Ltblk],eax
	jmp	LisCD		/* and be it the devil */
#endif /* !FFS_ONLY */

	/* "real" floppy boot */
L..12:	UD(12)			/** L: floppy boot */
#ifdef	LOUD
	call	LdebFD		/* debug msgs */
#endif
	jmp	LpreFD

#ifndef FFS_ONLY
LpreCD:	UD(13)			/** M: cd-rom boot */
#ifdef	LOUD
	call	LdebCD		/* debug msgs */
#endif
	/* FALL-THROUGH */
#endif

LpreFD:	/* prepare booting */
#ifdef BOOTSELECT_HOOK
	UD(37)			/** e: calling the hook */
	call	Lhook
	push	eax
#endif
	UD(14)			/** N: preparing 32-bit */
	xor	edx,edx
	mov	dl,[Lbdev]	/* carry this over to VPAM */
	mov	dh,[_rval]
#ifdef BOOTSELECT_HOOK
	pop	esi
#endif
	cli
	addr32 data32 lgdt (Gdtr - SA_LOADADDR)
	mov	ax,1
	lmsw	ax		/* switch to protected mode */
	data32 jmp 8,offset Lpmode

#ifdef	LOUD
	/*
	 * debugging routines for LOUD mode
	 */
LiscdM:	.ascii	"CD Drive "			/* drive no */
Liscd0:	.ascii	"00 on "			/* load seg */
Liscd1:	.ascii	"0000:0000, "			/* sectors  */
Liscd2:	.ascii	"0000 sectors starting at "	/* img offs */
Liscd3:	.asciz	"00000000 LBA\r\n"
LisfdM:	.ascii	"BIOS Drive "			/* bootdev */
Lisfd0:	.asciz	"00 initialized.\r\n"

LdebFD:	/* debug message for floppy/hdd boot */
	mov	al,[Lbdev]
	mov	di,offset Lisfd0
	call	LpBY
	mov	si,offset LisfdM
	jmp	Lotxt

#ifndef FFS_ONLY
LdebCD:	/* debug message for El Torito boot */
	mov	di,offset Liscd0
	mov	al,[Lbdev]
	call	LpBY
	mov	di,offset Liscd1
	mov	ax,[12+Ltblk]
	call	LpWO
	mov	di,offset Liscd2
	mov	ax,[14+Ltblk]
	call	LpWO
	mov	di,offset Liscd3
	mov	eax,[4+Ltblk]
	call	LpDW
	mov	si,offset LiscdM
	jmp	Lotxt
#endif

/* the formatting routines */

LpDW:	push	eax
	shr	eax,16
	call	LpWO
	pop	eax
	/* fall-through */
LpWO:	push	ax
	xchg	ah,al
	call	LpBY
	pop	ax
	/* fall-through */
LpBY:	mov	ah,al
	and	ah,0x0F
	shr	al,4
	add	ax,0x3030
	cmp	al,0x39
	jna	4f
	add	al,7
4:	cmp	ah,0x39
	jna	5f
	add	ah,7
5:	stosw
	ret
#endif

	/*
	 * 32-bit code in 16-bit code segment
	 * attention when adding code fragments below!
	 */

	.code32
Lpmode:	mov	eax,0x10
	mov	ss,ax
	mov	esp,0x0000FFFC
	mov	es,ax
	mov	ds,ax
	mov	fs,ax
	mov	gs,ax
	push	edx
#ifdef BOOTSELECT_HOOK
	push	esi
#endif
	UD32(15)		/** O: 32-bit reached */
	call	_ASM_LABEL(pmm_init)
	UD32(16)		/** P: PMM initialised */
	/* zero out .bss section */
	xor	eax,eax
	mov	ecx,offset _C_LABEL(end)
	mov	edi,offset _C_LABEL(edata)
	sub	ecx,edi
	push	ecx
	shr	ecx,2
	cld
	rep	stosd
	pop	ecx
	and	ecx,0x00000003
	rep	stosb
#ifdef BOOTSELECT_HOOK
	/* store saved hook value */
	pop	ecx
	mov	[_C_LABEL(hook_value)],ecx
#endif
	/* store saved BIOS boot device */
	pop	edx
	mov	[_C_LABEL(userpt)],dh
	mov	dh,0
	push	edx
	mov	[_C_LABEL(bios_bootdev)],edx
	UD32(17)		/** Q: jump into C code */
	/* jump into boot loader C code */
	call	_C_LABEL(boot)
	UD32(35)		/** c: return from C code */
	jmp	_C_LABEL(_rtt)

#ifdef	DEBUG_OFS
	. = _start + 0x0900
Lofsd:	.long	0xfeedcafe	/* just another bad magic */
#endif

	/*
	 * End of File. Attention, 32-bit mode!
	 */
