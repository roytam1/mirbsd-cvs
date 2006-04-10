/* $MirOS: src/sys/arch/i386/stand/liveboot/hook.S,v 1.2 2006/04/10 17:33:03 tg Exp $ */

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
 */

	.intel_syntax noprefix
	.code16

	.data
lbl_title:
	.asciz	"MirOS #8-current Setup/Live CD"
lbl_menus:
	.byte	3
	.word	lbl_menu0
	.word	lbl_menu1
	.word	lbl_menu2
lbl_menu0:
	.asciz	"Continue to normal /boot"
lbl_menu1:
	.asciz	"Boot into the Live-CD"
lbl_menu2:
	.asciz	"Boot the MirOS installer"
lbl_ask:
	.ascii	"Use the cursor up/down keys to navigate\r\n"
	.ascii	"and press return to activate the selected item\r\n"
	.asciz	"or enter the number of the entry to boot: "

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
	mov	ax,0x0E00 | ((ch) & 0xFF); \
	mov	bx,((col) & 0xFF); \
	int	0x10

#define OUTS(s,col) \
	mov	si,offset s; \
	mov	bx,((col) & 0xFF); \
	call	Louts

Louts:	lodsb
	or	al,al
	je	Louts1
	mov	ah,0x0E
	int	0x10
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
	;...
#endif

Lhook:
	/* clear screen */
	mov	ax,7
	int	0x10
	mov	ax,3
	int	0x10
	/* print banner */
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

	.data
Ltick:	.long	0
Lmenu:	.byte	0

#define GETTICK(a) \
	xor	ax,ax; \
	int	0x1A; \
	add	dx,(a); \
	adc	cl,0; \
	shl	ecx,16; \
	mov	cx,dx

	.text
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
Ldspm0:	xor	ax,ax
	mov	al,[Lmenu]
	mov	bx,7
	cmp	ax,di
	jne	Ldspm1
	mov	bl,15
Ldspm1:	lodsw
	push	si
	push	di
	push	bp
	mov	si,ax
	mov	ax,0x0E30
	add	ax,di
	int	0x10
	mov	ax,0x0E29	/* ')' */
	int	0x10
	mov	ax,0x0E20
	int	0x10
	call	Louts
	mov	ax,0x0E0D
	mov	bx,7
	int	0x10
	mov	ax,0x0E0A
	int	0x10
	pop	bp
	pop	di
	pop	si
	inc	di
	dec	bp
	jne	Ldspm0
	mov	ax,0x0E0D
	int	0x10
	mov	ax,0x0E0A
	int	0x10
	OUTS(lbl_ask,7)
	ret
