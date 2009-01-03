# Copyright (c) 2009
#	Thorsten Glaser <tg@mirbsd.org>
#
# Provided that these terms and disclaimer and all copyright notices
# are retained or reproduced in an accompanying document, permission
# is granted to deal in this work without restriction, including un-
# limited rights to use, publicly perform, distribute, sell, modify,
# merge, give away, or sublicence.
#
# This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
# the utmost extent permitted by applicable law, neither express nor
# implied; without malicious intent or gross negligence. In no event
# may a licensor, author or contributor be held liable for indirect,
# direct, other damage, loss, or other issues arising in any way out
# of dealing in the work, even if advised of the possibility of such
# damage or existence of a defect, except proven that it results out
# of said person's immediate fault when using the work as intended.

	.intel_syntax noprefix

	.section .comment
.asciz	"@(#)rcsid: $MirOS: src/share/misc/licence.template,v 1.28 2008/11/14 15:33:44 tg Rel $"

	.text

	.globl	gent_proc
gent_proc:
	push	ebp
	mov	ebp,esp
	push	edi
	mov	edi,[ebp+8]
	cld
#if 1
	/* asm size: 79 */
	gent_beg = .
	mov	ax,0xFF00
	stosw
	mov	ecx,16
1:	inc	eax
	stosb
	loop	1b
	mov	al,0xE8
	mov	cl,8
2:	stosb
	inc	eax
	loop	2b
	mov	al,0x8F
	mov	cl,0x40
3:	stosb
	dec	eax
	loop	3b
	mov	al,0xC0
	mov	cl,16
4:	stosb
	inc	eax
	loop	4b
	mov	al,0x4F
	mov	cl,0x3F
5:	stosb
	dec	eax
	loop	5b
	mov	al,0xB0
	mov	cl,16
6:	stosb
	inc	eax
	loop	6b
	mov	al,0xFE
	mov	cl,15
7:	stosb
	dec	eax
	loop	7b
	mov	al,0xE7
	mov	cl,24
8:	stosb
	dec	eax
	loop	8b
	mov	al,0xAF
	mov	cl,0x20
9:	stosb
	dec	eax
	loop	9b
#else
	/* asm size: 97 */
	jmp	gent_do
	gent_beg = .
Lsfw:	stosb
	inc	eax
	loop	Lsfw
	ret
Lsbk:	stosb
	dec	eax
	loop	Lsbk
	ret
gent_do:
	mov	ax,0xFF00
	stosw
	mov	ecx,16
1:	inc	eax
	stosb
	loop	1b
	mov	al,0xE8
	mov	cl,8
	call	Lsfw
	mov	al,0x8F
	mov	cl,0x40
	call	Lsbk
	mov	al,0xC0
	mov	cl,16
	call	Lsfw
	mov	al,0x4F
	mov	cl,0x3F
	call	Lsbk
	mov	al,0xB0
	mov	cl,16
	call	Lsfw
	mov	al,0xFE
	mov	cl,15
	call	Lsbk
	mov	al,0xE7
	mov	cl,24
	call	Lsbk
	mov	al,0xAF
	mov	cl,0x20
	call	Lsbk
#endif
	gent_end = .
	pop	edi
	pop	ebp
	ret

	.data

	.globl	gent_sz
gent_sz:
	.long	gent_end - gent_beg
