/* $MirOS: src/share/misc/licence.template,v 1.28 2008/11/14 15:33:44 tg Rel $ */

/*-
 * Copyright (c) 2009
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
	.text
	.code32

	.globl	prot_to_real
	.globl	real_to_prot

/* int biosdev_lbaprobe(int drive); */
	.globl	biosdev_lbaprobe
biosdev_lbaprobe:
	push	ebp
	mov	ebp,esp
	push	ebx
	push	esi
	push	edi
	xor	edx,edx
	mov	dl,[ebp+8]
	call	prot_to_real
	.code16
	push	edx
	mov	ah,0x41
	mov	bx,0x55AA
	int	0x13
	pop	edx
	jc	LnoLBA
	cmp	bx,0xAA55
	jne	LnoLBA
	or	ah,ah
	jne	LnoCD
	cmp	dl,0x88
	jb	LnoCD
	push	edx
	push	ds
	push	ss
	pop	ds
	xor	si,si
	xor	eax,eax
	mov	byte ptr ds:[0],19
	mov	ds:[1],eax
	mov	ds:[5],eax
	mov	ds:[9],eax
	mov	ds:[13],eax
	mov	ds:[17],eax
	mov	ax,0x4B01
	int	0x13
	pop	edx
	jc	LnoCD
	cmp	byte ptr [2],dl
	jne	LnoCD
	test	byte ptr [1],0x0F
	jne	LnoCD
	or	dh,2
LnoCD:	or	dh,1
LnoLBA:	call	real_to_prot
	.code32
	pop	edi
	pop	esi
	pop	ebx
	mov	eax,edx
	shr	eax,8
	pop	ebp
	ret
