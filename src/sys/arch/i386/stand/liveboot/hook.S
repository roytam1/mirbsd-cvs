/* $MirOS: src/sys/arch/i386/stand/liveboot/hook.S,v 1.26 2009/02/01 10:44:17 tg Exp $ */

/*-
 * Copyright (c) 2006, 2007, 2009
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
	.code16

	.data
lbl_mayskip:
	.ascii	"\n\rHold down SHIFT to skip the coloured menu"
	.ascii	" and go directly to the bootloader...\n\r"
#ifdef FORGRML
	.ascii	"On a WRAP/Soekris, press 4"
#else
	.ascii	"On a WRAP/Soekris, press 4 (Live) or 7 (Setup)"
#endif
	.asciz	" for serial console @38k4,8N1.\n\r"
lbl_title:
	.ascii	"MirOS #"
	.ascii	mbsd_major
	.ascii	mbsd_type
#ifndef HAVE_DUALIVE
	.ascii	"/i386"
#endif
#ifdef FORGRML
	.asciz	" Rescue CD for grml.org"
#else
	.ascii	" Setup/Rescue/"
#ifndef HAVE_DUALIVE
#ifndef HAVE_GRML
	.ascii	"Live"
#else
	.ascii	"Live/GRML"
#endif
#else
#ifndef HAVE_GRML
	.ascii	"DuaLive"
#else
	.ascii	"Triforce"
#endif
#endif
	.asciz	" CD"
#endif
lbl_menus:
#if defined(FORGRML)
#if defined(NOGRUB)
	.byte	6
#else
	.byte	7
#endif
#elif defined(HAVE_GRML)
	.byte	10
#else
	.byte	9
#endif
	.long	lbl_menu0 - SA_LINKADDR
	.long	lbl_menu1 - SA_LINKADDR
	.long	lbl_menu2 - SA_LINKADDR
	.long	lbl_menu3 - SA_LINKADDR
	.long	lbl_menu4 - SA_LINKADDR
	.long	lbl_menu5 - SA_LINKADDR
#if !defined(FORGRML) || !defined(NOGRUB)
	.long	lbl_menu6 - SA_LINKADDR
#endif
#ifndef FORGRML
	.long	lbl_menu7 - SA_LINKADDR
	.long	lbl_menu8 - SA_LINKADDR
#ifdef HAVE_GRML
	.long	lbl_menu9 - SA_LINKADDR
#endif
lbl_menu0:
	.asciz	"Continue to normal /boot installer/rescue\n"
lbl_menu1:
	.asciz	"Boot into the Live-CD\n"
lbl_menu2:
	.asciz	"Boot the Live-CD from 2nd CD drive or hard disc\n"
lbl_menu3:
	.asciz	"Live-CD, serial console at COM1:9600,8N1\n"
lbl_menu4:
	.asciz	"Live-CD, serial console at COM1:38400,8N1\n"
lbl_menu5:
	.asciz	"Live-CD, serial console at COM1:115200,8N1\n"
lbl_menu6:
	.asciz	"Installer, serial console at COM1:9600,8N1\n"
lbl_menu7:
	.asciz	"Installer, serial console at COM1:38400,8N1\n"
lbl_menu8:
	.asciz	"Installer, serial console at COM1:115200,8N1\n"
#ifdef HAVE_GRML
lbl_menu9:
	.asciz	"Switch to GNU GRUB for booting into grml\n"
#endif
#else /* FORGRML */
lbl_menu0:
	.asciz	"Continue to normal MirOS boot loader\n"
lbl_menu1:
	.asciz	"Boot the MirOS bsd4grml rescue system ramdisk kernel\n"
lbl_menu2:
	.asciz	"Boot the rescue system, entering UKC (userconf)\n"
lbl_menu3:
	.asciz	"Rescue system, serial console at COM1:9600,8N1\n"
lbl_menu4:
	.asciz	"Rescue system, serial console at COM1:38400,8N1\n"
lbl_menu5:
	.asciz	"Rescue system, serial console at COM1:115200,8N1\n"
#ifndef NOGRUB
lbl_menu6:
	.asciz	"Chain to GNU GRUB for booting into grml.org again\n"
#endif /* !NOGRUB */
#endif /* FORGRML */
lbl_ask:
	.ascii	"\nUse the cursor up/down keys to navigate\n"
	.ascii	"and press return to activate the selected item\n"
	.asciz	"or enter the number of the entry to boot: "
lbl_widmung:
#ifdef FORGRML
	.ascii	"MirBSD for grml.org is proudly presented to you by\n"
	.asciz	"Thorsten Glaser, Michael Prokop, and their contributors."
#else
	.ascii	"This MirBSD Setup/Rescue/Triforce/DuaLive-CD ISO image is proudly\n"
	.asciz	"presented by The MirOS Project developers and contributors."
#endif

Ltick:	.long	0	/* end tick for timeout */
Lmenu:	.word	0	/* which menu point has been chosen (MBZ) */

#define GETTICK(a) \
	xor	ax,ax; \
	int	0x1A; \
	add	dx,(a); \
	adc	cl,0; \
	shl	ecx,16; \
	mov	cx,dx

	.text
	.globl	Lhook

Llens:	mov	di,si
	xor	cx,cx
	dec	cx
	cld
	xor	al,al
	repne	scasb
	not	cx
	dec	cx
	ret

/* out: DH=Zeile DL=Spalte (0-based) */
#define GET_XY \
	mov	ah,3; \
	mov	bh,0; \
	int	0x10

/* in: z,s (0-based) */
#define	LOCATE(z,s) \
	mov	ah,2; \
	mov	bh,0; \
	mov	dx,(((z) & 0xFF) << 8) | ((s) & 0xFF); \
	int	0x10

#define OUTCH(ch,col) \
	mov	al,(ch); \
	mov	bx,((col) & 0xFF); \
	call	outchc

#define OUTS(s,col) \
	mov	esi,offset s - SA_LINKADDR; \
	mov	bx,((col) & 0xFF); \
	call	Louts

Louts:	lodsb
	or	al,al
	je	Louts1
	call	outchc
	jmp	Louts
#if 1
Louts1:	ret
#else

Lsinitlo:
	mov	ax,0xE3
	xor	dx,dx
	int	0x14
Louts1:	ret

Lsput:	mov	ah,1
	xor	dx,dx
	int	0x14
	ret

Lsget:
	XXX ...
#endif

Lhook:	/* if any shift key pressed, skip all of this, return 0 */
	mov	esi,offset lbl_mayskip - SA_LINKADDR
	lodsb
Lhookp:	mov	ah,0x0E
	mov	bx,7
	int	0x10
	lodsb
	or	al,al
	jnz	Lhookp
	GETTICK(32)
	mov	ebp,ecx
Lhooks:	mov	ah,2
	int	0x16
	and	al,3
	jnz	Lquit
	GETTICK(0)
	cmp	ecx,ebp
	jbe	Lhooks
Lhook0:	/* clear screen */
#if 0
	mov	ax,7
	int	0x10
	mov	ax,3
	int	0x10
#else
	push	es
	mov	ax,0xB000
	mov	es,ax
	cld
	xor	di,di
	mov	ax,0x0720
	mov	cx,0x8000
	rep	stosw
	pop	es
#endif
	/* print banner */
	LOCATE(20,0)
	OUTS(lbl_widmung,4)
	GET_XY
	push	dx
	OUTCH(32,7)		/* -> newline at Lquit has this colour */
	LOCATE(0,0)
	OUTCH(201,15)
	mov	esi,offset lbl_title - SA_LINKADDR
	call	Llens
	inc	cx
	inc	cx
	push	cx
Lhook1:	OUTCH(205,15)
	dec	cx
	jne	Lhook1
	OUTCH(187,15)
	LOCATE(1,0)
	OUTCH(186,15)
	OUTCH(32,7)
	OUTS(lbl_title,14)
	OUTCH(32,7)
	OUTCH(186,15)
	LOCATE(2,0)
	OUTCH(200,15)
	pop	cx
Lhook2:	OUTCH(205,15)
	dec	cx
	jne	Lhook2
	OUTCH(188,15)

	GETTICK(219 /* 12 * 18.2 */)
	mov	ebx,offset Ltick - SA_LINKADDR
	mov	[bx],ecx
Lmlp0:	/* display the menu */
	call	Ldspm
Lmlp1:	/* read keypress (if any) */
	mov	ah,1
	int	0x16
	jnz	Lmlp2
	/* checking time? */
	mov	ebx,offset Ltick - SA_LINKADDR
	mov	ebp,[bx]
	or	ebp,ebp
	jz	Lmlp1
	/* get current ticks */
	GETTICK(0)
	/* lower? */
	cmp	ecx,ebp
	jbe	Lmlp1
	/* fake "return" */
	mov	ax,13
	jmp	Lmlp3
Lmlp2:	/* we have a keypress event, disable timeout */
	mov	ebx,offset Ltick - SA_LINKADDR
	mov	dword ptr [bx],0
	/* check which key */
	xor	ax,ax
	int	0x16
Lmlp3:	cmp	ax,0x4800	/* cursor up */
	jne	Lmlp4
	mov	ebx,offset lbl_menus - SA_LINKADDR
	mov	al,[bx]
	dec	ax
	mov	ebx,offset Lmenu - SA_LINKADDR
	xchg	al,[bx]
	or	al,al
	je	Lmlp0
	dec	al
	mov	[bx],al
	jmp	Lmlp0
Lmlp4:	cmp	ax,0x5000	/* cursor down */
	jne	Lmlp5
	mov	ebx,offset Lmenu - SA_LINKADDR
	xchg	al,[bx]
	inc	ax
	mov	ebx,offset lbl_menus - SA_LINKADDR
	cmp	al,[bx]
	jnb	Lmlp0
	mov	ebx,offset Lmenu - SA_LINKADDR
	mov	[bx],al
	jmp	Lmlp0
Lmlp5:	sub	al,13		/* return */
	jb	Lmlp1		/* <13: illegal */
	je	Ldone
	sub	al,0x30-13	/* '0' */
	jb	Lmlp1
	mov	ebx,offset lbl_menus - SA_LINKADDR
	cmp	al,[bx]
	jae	Lmlp1
	mov	ebx,offset Lmenu - SA_LINKADDR
	mov	[bx],al
Ldone:	/* choice in [Lmenu] */
	mov	ah,2
	mov	bh,0
	pop	dx
	/* restore cursor position (after last text output) */
	int	0x10 
Lquit:	/* issue a newline (colour 7, because it's the final one) */
	mov	ax,0x0E0D
	mov	bx,7
	int	0x10
	mov	ax,0x0E0A
	int	0x10
	/* return choice */
	xor	eax,eax
	mov	ebx,offset Lmenu - SA_LINKADDR
	mov	al,[bx]
	ret

Ldspm:	/* lines 0, 1, 2 = banner, 3 = empty, start at 4 */
	LOCATE(4,0)
	mov	esi,offset lbl_menus - SA_LINKADDR
	xor	ax,ax
	lodsb
	mov	bp,ax	/* count left */
	xor	di,di	/* which item */
Ldspm0:	mov	ebx,offset Lmenu - SA_LINKADDR
	mov	ax,[bx]
	mov	bx,7
	cmp	ax,di
	jne	Ldspm1
	mov	bl,0x70
Ldspm1:	lodsd
	push	si
	push	di
	push	bp
	mov	si,ax
	mov	al,0x30
	add	ax,di
	call	outchc
	mov	al,')'
	call	outchc
	mov	al,' '
	call	outchc
	call	Louts
	pop	bp
	pop	di
	pop	si
	inc	di
	dec	bp
	jne	Ldspm0
	OUTS(lbl_ask,9)
	ret

/*
 * We cannot use INT 10h AH=09 or AH=0Eh functions for
 * outputting coloured text, use direct memory writes,
 * cover both HGC and CGA/EGA/VGA memory
 */
outchc:
	pusha
	/* special case: newline (never coloured, equals 0x0D 0x0A) */
	cmp	al,0x0a
	je	outnl
	mov	ah,bl
	push	ax	/* in correct form for video memory */
	mov	ah,3
	int	0x10
	mov	cl,160
	mov	al,dh
	mul	cl
	mov	dh,0
	shl	dx,1
	add	dx,ax	/* dx := offset in video memory */
	pop	ax
	push	es
	mov	bx,0xb800
	mov	es,bx
	mov	di,dx
	stosw
	cmp	ah,9
	jne	outct1
	mov	ah,7	/* tweak black/white */
outct1:	mov	bh,0xb0
	mov	es,bx
	mov	di,dx
	stosw
	pop	es
	mov	ah,3
	mov	bh,0
	int	0x10
	inc	dx	/* go forward by one char */
setcpos:
	mov	ah,2
	int	0x10
	popa
	ret
outnl:
	mov	ah,3
	mov	bh,0
	int	0x10
	inc	dh
	mov	dl,0
	jmp	setcpos
