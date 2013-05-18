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

	/* extern */
	.globl	bounce_buf

/* *bounce_buf = ASCIZ filename; returns effff e=error f=flags */
/* uint32_t dosfs__stat(void); */

	.globl	dosfs__stat
dosfs__stat:
	push	ebp
	mov	ebp,esp
	pushfd
	push	ebx
	push	esi
	push	edi
	/* assert: bounce_buf is PARA aligned */
	mov	ebx,offset bounce_buf
	xor	edx,edx
	shr	ebx,4

	/** state:
	 * ELF i386 ABI registers saved
	 * bx:edx = seg:ofs bounce_buf
	 */

	call	prot_to_real
	.code16
	sti

	mov	ds,bx
	mov	ax,0x4300
	xor	bx,bx
	push	bx
	int	0x21
	pop	bx
	/** state:
	 * bx = 0000
	 * CY = error?
	 * ax = error code (if CY)
	 * cx = attributes (if NC)
	 */
	jnc	1f
	inc	bx
	mov	cx,ax
1:	shl	ebx,16
	mov	bx,cx

	/** state:
	 * ebx = 000evvvv
	 * + e = 1 if error, 0 otherwise
	 * + v = error code if error, attributes otherwise
	 */

	call	real_to_prot
	.code32

	mov	eax,ebx
	pop	edi
	pop	esi
	pop	ebx
	popfd
	pop	ebp
	ret


/* *bounce_buf = ASCIZ filename; returns ehhhh e=error h=handle */
/* uint32_t dosfs__open(void); */

	.globl	dosfs__open
dosfs__open:
	push	ebp
	mov	ebp,esp
	pushfd
	push	ebx
	push	esi
	push	edi
	/* assert: bounce_buf is PARA aligned */
	mov	ebx,offset bounce_buf
	xor	edx,edx
	shr	ebx,4

	/** state:
	 * ELF i386 ABI registers saved
	 * bx:edx = seg:ofs bounce_buf
	 */

	call	prot_to_real
	.code16
	sti

	mov	ds,bx
	mov	ax,0x3D00
	xor	cx,cx
	push	cx
	int	0x21
	pop	bx
	/** state:
	 * bx = 0000
	 * CY = error?
	 * ax = handle (if NC) or error code (if CY)
	 */
	adc	bx,0		/* add 0 + CF to bx */
	shl	ebx,16
	mov	bx,ax

	/** state:
	 * ebx = 000evvvv
	 * + e = 1 if error, 0 otherwise
	 * + v = error code if error, handle otherwise
	 */

	call	real_to_prot
	.code32

	mov	eax,ebx
	pop	edi
	pop	esi
	pop	ebx
	popfd
	pop	ebp
	ret


/* void dosfs__close(uint32_t handle); */

	.globl	dosfs__close
dosfs__close:
	push	ebp
	mov	ebp,esp
	pushfd
	pushad
	mov	ebx,[ebp+8]

	/** state:
	 * all registers saved
	 * bx = handle
	 */

	call	prot_to_real
	.code16
	sti

	mov	ah,0x3E
	int	0x21

	call	real_to_prot
	.code32

	popad
	popfd
	pop	ebp
	ret


/* uint32_t dosfs__read(uint32_t handle, void *buf, uint32_t n); */

	.globl	dosfs__read
dosfs__read:
	push	ebp
	mov	ebp,esp
	pushfd
	push	ebx
	push	esi
	push	edi
	mov	ebx,[ebp+8]
	mov	edx,[ebp+12]
	mov	ecx,[ebp+16]

	/** state:
	 * ELF i386 ABI registers saved
	 * bx = handle
	 * cx = count
	 * edx = flat offset buf
	 */

	call	prot_to_real
	.code16
	sti

	push	dx
	shr	edx,4
	mov	ds,dx
	pop	dx
	and	dx,0x000F
	/** state:
	 * bx = handle
	 * cx = count
	 * ds = seg buf
	 * edx = ofs buf (bit 4..31 cleared)
	 */
	mov	ah,0x3F
	int	0x21
	jnc	1f
	xor	ax,ax
	dec	ax
1:	movzx	ebx,ax

	/** state:
	 * ebx = 0x0000FFFF (error) or count
	 */

	call	real_to_prot
	.code32

	mov	eax,ebx
	pop	edi
	pop	esi
	pop	ebx
	popfd
	pop	ebp
	ret


/* int32_t dosfs__seek(uint32_t handle, uint32_t whence, int32_t ofs); */

	.globl	dosfs__seek
dosfs__seek:
	push	ebp
	mov	ebp,esp
	pushfd
	push	ebx
	push	esi
	push	edi
	mov	ebx,[ebp+8]
	mov	ecx,[ebp+12]
	mov	edx,[ebp+16]

	/** state:
	 * ELF i386 ABI registers saved
	 * bx = handle
	 * ecx = signed 32-bit file offset
	 * dx = whence
	 */

	call	prot_to_real
	.code16
	sti

	mov	ah,0x42
	mov	al,dl
	mov	dx,cx
	shr	ecx,16
	/** state:
	 * al = whence
	 * bx = handle
	 * cx:dx = signed 16+16 bit file offset
	 */
	int	0x21
	jnc	1f
	xor	ax,ax
	dec	ax
	mov	dx,ax
1:	shl	edx,16
	mov	dx,ax

	/** state:
	 * edx = signed 32-bit file offset, or (-1) on error
	 */

	call	real_to_prot
	.code32

	mov	eax,edx
	pop	edi
	pop	esi
	pop	ebx
	popfd
	pop	ebp
	ret
