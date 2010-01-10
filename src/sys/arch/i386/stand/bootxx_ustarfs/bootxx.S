/*-
 * Copyright (c) 2009, 2010
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

	.intel_syntax noprefix
	.section .comment
	.ascii	"$MirOS: src/sys/arch/i386/stand/bootxx/bootxx.S,v 1.25 2009/06/29 20:50:59 tg Exp $"
	.ascii	" +t:MBSD"
	.ascii	" +s:TAR"
	.byte	0

	.code16
	.text

	/* ustar header begins here */

LHD_USTAR_name:
	.globl	_start
	.type	_start,@function
_start:	/* bootxx entry point 07C00 */
	.byte	0x34, 0x00	/* XOR AL,00h ; this is a NOP */
	/* end of string (filename) for ustar */

	/* code to load the rest of the bootsector */
	xor	ecx,ecx
	mov	ss,cx
	mov	sp,0x7BFC
	push	ecx
	popfd

	/**
	 * We now have a sane environment, stack set up, interrupts
	 * disabled. We are loaded at 0x07C00 absolute (so much, we
	 * can assume, but not segment:offset). We ignore a possib-
	 * ly loaded partition table (ustarfs is intended for flop-
	 * pies), load sector #1 (assuming the bootsector is indeed
	 * sector #0) and jump there. It fits nice with ustar.
	 */

	mov	ds,cx
	mov	si,0x7C00 + offset LHD_USTAR_magic - offset _start
	call	4f
	mov	ax,0x0E20
	int	0x10

	mov	ax,SA_LINKSEG
	mov	ds,ax
	mov	es,ax
	push	ax
	push	offset Lmain
	mov	bx,0xFE00
	/* we assume CHS loading works here */
	mov	ax,0x0201
	mov	cx,2
	mov	dh,0
1:	pusha
	stc
	int	0x13
	popa
	jnc	2f
	pusha
	xor	ax,ax
	int	0x13
	popa
	jmp	1b
2:	lret

3:	mov	ah,0x0E
	mov	bx,7
	int	0x10
4:	lodsb
	or	al,al
	jnz	3b
	ret

	/* ustar padding */
	. = LHD_USTAR_name + 98
	.byte	0x90, 0
LHD_USTAR_mode:
	.asciz	"0100600"
LHD_USTAR_uid:
	.asciz	"0000000"
LHD_USTAR_gid:
	.asciz	"0000003"
LHD_USTAR_size:
	.asciz	"00000001000"		/* 512 in octal */
LHD_USTAR_mtime:
	.asciz	"11322205736"		/* time_t */
LHD_USTAR_chksum:
	.asciz	"cheksum"		/* filled in post-build */
LHD_USTAR_typeflag:
	.byte	0x30
LHD_USTAR_linkname:
	. = LHD_USTAR_linkname + 100
LHD_USTAR_magic:
	.asciz	"ustar"
LHD_USTAR_version:
	.ascii	"00"
LHD_USTAR_uname:
	.asciz	"root"
	. = LHD_USTAR_uname + 32
LHD_USTAR_gname:
	.asciz	"sys"
	. = LHD_USTAR_gname + 32
LHD_USTAR_devmajor:
	.long	0, 0
LHD_USTAR_devminor:
	.long	0, 0
LHD_USTAR_prefix:
	. = LHD_USTAR_prefix + 155
	/* ustar header ends here */
L_ustar_padding:
	.long	0, 0, 0xDEADBEEF

	. = _start + 512
L_code_start:

	/* LBA parameter block */
Lpblk:	.word	0x10		/* size */
	.word	0		/* number of sectors */
	.long	0		/* seg:ofs xfer buffer */
	.long	0, 0		/* LBA address */

	/* disc access data */
geomh:	.word	0		/* tracks per cylinder */
geoms:	.word	0		/* sectors per track */
Lload:	.word	LsLBA
Ldrv:	.byte	0		/* BIOS drive number */

Lemsg:	.ascii	__BOOT_VER
	.asciz	" Loading "
Lmmsg:	.ascii	"bad magic"
Lfmsg:	.ascii	" error"
Lbmsg:	.asciz	"\r\n"
Lname:	.asciz	"boot"
	Lnmsz = . - Lname

	/* output NUL-terminated string from ds:si */
Lotxt0:	mov	ah,0x0E
	mov	bx,7
	int	0x10
Lotxt:	lodsb
	or	al,al
	jnz	Lotxt0
	ret

Lmain:	sti
	/**
	 * Sane environment, flags cleared, interrupts enabled. We
	 * have been loaded at SA_LINKSEG:FE00h (from L_code_start
	 * to L_code_end) by the code placed in the ustar filename
	 * buffer past the NUL. CS = DS = ES = SA_LINKSEG = 4000h;
	 * SS:SP = 0000:7BFCh; DL = drive.
	 * The rest of the state is pretty much undefined.
	 */
	mov	[Ldrv],dl
	mov	si,offset Lemsg
	cmp	dl,0x80
	jb	Lbarf		/* floppy: only try CHS */
	call	Lotxt
	/* FALLTHROUGH */

Lretr:	xor	bx,bx			/* load offset (begin) */
	push	bx			/* return address */
	mov	ebp,2			/* load sector (begin) */

Lscan:	/* load first/next sector */
	call	Lread
	inc	ebp
	xor	si,si
	mov	di,offset Lname		/* "boot\0" */
	mov	cx,5
	repe	cmpsb
	jne	Lscan
	/* found, now load FE00h bytes of second-stage bootloader */
	/* note: BX is 0000h here... */
Lloop:	/* load next sector */
	call	Lread
	inc	ebp
	add	bh,2
	cmp	bh,0xFE
	jb	Lloop
	/* loaded 0000..FDFFh into memory */

	/* check bootloader magic */
	mov	eax,ds:[4]	/* location of magic in /boot */
	cmp	eax,0x696D4F00
	mov	si,offset Lmmsg
	jne	Lbarf
	mov	si,offset Lbmsg
	call	Lotxt
	mov	si,offset _start
	ret

Lbarf:	call	Lotxt
	mov	ax,offset LsCHS
	xchg	ax,[Lload]
	cmp	ax,offset LsCHS
	jne	Lretr
	xor	ax,ax
	int	0x16
	jmp	0xF000,0xFFF0

Lread:	/* load sector [EBP] to CS:BX */
	push	ebp
	push	bx
	/* create LBA parameter block */
	mov	di,offset Lpblk
	mov	ax,0x0010
	stosw
	mov	al,1
	stosw
	mov	ax,bx
	stosw
	mov	ax,cs
	stosw
	mov	eax,ebp
	stosd
	xor	eax,eax
	stosd

	mov	si,offset Lpblk
	call	[Lload]
	mov	bp,4		/* number of retries */
	mov	dl,[Ldrv]
Lldlp:	pusha
	stc
	int	0x13
	pushf
	mov	ax,0x0E2E	/* "dot" as progress meter */
	mov	bx,7
	int	0x10
	popf
	sti
	popa
	jnc	Lldok
	dec	bp
	pusha
	pushf
	xor	ax,ax		/* reset drive */
	int	0x13
	popf
	mov	si,offset Lfmsg
	jz	Lbarf
	mov	ax,0x0E30	/* number as fail meter */
	add	ax,bp
	mov	bx,7
	int	0x10
	popa
	jmp	Lldlp
Lldok:	pop	bx
	pop	ebp
	ret

	/* obtain drive geometry */
Lgeom:	pusha
	push	es
#if 0
	/*
	 * According to RBIL, this is needed to guard against
	 * BIOS bugs, but we don’t read out the table anyway.
	 */
	xor	di,di
	mov	es,di
#endif
	mov	ah,8
	mov	dl,[Ldrv]
	stc
	int	0x13
	sti
	pop	es
	mov	si,offset Lfmsg
	jc	Lbarf
	/* process returned values */
	and	cl,0x3F		/* number of sectors per track */
	mov	[geoms],cl	/* high byte is 0 anyway */
	movzx	ax,dh
	inc	ax		/* maximum index -> number of heads */
	mov	[geomh],ax
	popa
	/* FALLTHROUGH */

LsCHS:	mov	cx,[geoms]
	jcxz	Lgeom
	mov	ax,8[si]
	mov	dx,10[si]
	div	cx
	inc	dx		/* remainder: sector */
	xor	cx,cx
	xchg	cx,dx
	div	word ptr [geomh]
	shl	ah,6		/* quotient: cylinder */
	xchg	ah,al
	or	cx,ax
	mov	dh,dl		/* remainder: head */
	mov	ax,0x0201
	ret

LsLBA:	mov	ah,0x42
	ret

	. = L_code_start + 508
	.long	0x20355604	/* just so I know */
L_code_end:
