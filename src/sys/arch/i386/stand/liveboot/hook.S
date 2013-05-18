/* $MirOS: src/share/misc/licence.template,v 1.14 2006/08/09 19:35:23 tg Rel $ */

/*-
 * Copyright (c) 2006
 *	Thorsten Glaser <tg@mirbsd.de>
 *
 * Licensee is hereby permitted to deal in this work without restric-
 * tion, including unlimited rights to use, publicly perform, modify,
 * merge, distribute, sell, give away or sublicence, provided all co-
 * pyright notices above, these terms and the disclaimer are retained
 * in all redistributions or reproduced in accompanying documentation
 * or other materials provided with binary redistributions.
 *
 * Advertising materials mentioning features or use of this work must
 * display the following acknowledgement:
 *	This product includes material provided by Thorsten Glaser.
 *
 * Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
 * express, or implied, to the maximum extent permitted by applicable
 * law, without malicious intent or gross negligence; in no event may
 * licensor, an author or contributor be held liable for any indirect
 * or other damage, or direct damage except proven a consequence of a
 * direct error of said person and intended use of this work, loss or
 * other issues arising in any way out of its use, even if advised of
 * the possibility of such damage or existence of a defect.
 */

	.intel_syntax noprefix
	.code16

	.data
lbl_mayskip:
	.ascii	"\n\rHold down SHIFT to skip the coloured menu"
	.asciz	" and go directly to the bootloader..."
lbl_title:
	.asciz	"MirOS #9-current Setup/Live CD"
lbl_menus:
	.byte	4
	.word	lbl_menu0
	.word	lbl_menu1
	.word	lbl_menu2
	.word	lbl_menu3
lbl_menu0:
	.asciz	"Continue to normal /boot\n"
lbl_menu1:
	.asciz	"Boot into the Live-CD\n"
lbl_menu2:
	.asciz	"Boot the Live-CD dd(1)d onto hard disc\n"
lbl_menu3:
	.asciz	"Boot the MirOS installer\n"
lbl_ask:
	.ascii	"\nUse the cursor up/down keys to navigate\n"
	.ascii	"and press return to activate the selected item\n"
	.asciz	"or enter the number of the entry to boot: "
lbl_widmung:
	.ascii	"This MirOS Setup/Live-CD ISO image is proudly presented by\n"
	.asciz	"Thorsten Glaser and Benny Siegert, and their contributors."

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
	mov	si,offset s; \
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
	mov	si,offset lbl_mayskip
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
	mov	ax,7
	int	0x10
	mov	ax,3
	int	0x10
	/* print banner */
	LOCATE(20,0)
	OUTS(lbl_widmung,4)
	GET_XY
	push	dx
	LOCATE(0,0)
	OUTCH(201,15)
	mov	si,offset lbl_title
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
	mov	[Ltick],ecx
Lmlp0:	/* display the menu */
	call	Ldspm
Lmlp1:	/* read keypress (if any) */
	mov	ah,1
	int	0x16
	jnz	Lmlp2
	/* checking time? */
	mov	ebp,[Ltick]
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
	mov	dword ptr [Ltick],0
	/* check which key */
	xor	ax,ax
	int	0x16
Lmlp3:	cmp	ax,0x4800	/* cursor up */
	jne	Lmlp4
	mov	al,[lbl_menus]
	dec	ax
	xchg	al,[Lmenu]
	or	al,al
	je	Lmlp0
	dec	al
	mov	[Lmenu],al
	jmp	Lmlp0
Lmlp4:	cmp	ax,0x5000	/* cursor down */
	jne	Lmlp5
	xchg	al,[Lmenu]
	inc	ax
	cmp	al,[lbl_menus]
	jnb	Lmlp0
	mov	[Lmenu],al
	jmp	Lmlp0
Lmlp5:	sub	al,13		/* return */
	jb	Lmlp1		/* <13: illegal */
	je	Ldone
	sub	al,0x30-13	/* '0' */
	jb	Lmlp1
	cmp	al,[lbl_menus]
	jae	Lmlp1
	mov	[Lmenu],al
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
	mov	al,[Lmenu]
	ret

Ldspm:	/* lines 0, 1, 2 = banner, 3 = empty, start at 4 */
	LOCATE(4,0)
	mov	si,offset lbl_menus
	xor	ax,ax
	lodsb
	mov	bp,ax	/* count left */
	xor	di,di	/* which item */
Ldspm0:	mov	ax,[Lmenu]
	mov	bx,7
	cmp	ax,di
	jne	Ldspm1
	mov	bl,0x70
Ldspm1:	lodsw
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
