/* $MirOS: src/sys/arch/i386/stand/libsa/biosdev2.S,v 1.4 2009/01/11 17:08:30 tg Exp $ */

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
/*-
 * return value is a bitmask:
 * 01 = LBA disc access (42h-44h, 47h, 48h)
 * 02 = removable drv ctl (45h, 46h, 48h, 49h, INT 15h 52h)
 * 04 = LBA disc status (48h, 4Eh)
 * 08 = LBA installation check succeeded
 * 10 = is a CD-ROM in El Torito "no emulation" mode
 */
	.globl	biosdev_lbaprobe
	.code32
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
	sti
	push	edx
	mov	ah,0
	int	0x13
	pop	edx
	push	edx
	mov	ah,0x41
	mov	bx,0x55AA
	int	0x13
	pop	edx
	jc	LnoLBA
	cmp	bx,0xAA55
	jne	LnoLBA
	and	cl,7
	or	dh,cl
	or	ah,ah
	jz	LnoCD
	cmp	dl,0x88
	jb	LnoCD
	push	edx
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
	cmp	byte ptr ds:[2],dl
	jne	LnoCD
	test	byte ptr ds:[1],0x0F
	jne	LnoCD
	or	dh,16
LnoCD:	or	dh,8
LnoLBA:	call	real_to_prot
	.code32
	sti
	pop	edi
	pop	esi
	pop	ebx
	mov	eax,edx
	shr	eax,8
	pop	ebp
	ret

/* int biosdev_CHS(int ah, int dev, int cyl, int head, int sec, int nsec); */
/* ebp + …         +8      +12      +16      +20       +24      +28 */
	.globl	biosdev_CHS
	.code32
biosdev_CHS:
	push	ebp
	mov	ebp,esp
	push	ebx
	push	esi
	push	edi
	mov	ecx,[ebp+16]
	xchg	ch,cl
	shl	cl,6
	or	cl,[ebp+24]
	inc	ecx
	mov	dh,[ebp+20]
	mov	dl,[ebp+12]
	mov	bh,[ebp+8]
	mov	bl,[ebp+28]
	call	prot_to_real
	.code16
	sti
	mov	ax,bx
	mov	bx,0x3000
	mov	es,bx
	xor	bx,bx
	push	bx
biosdev_io:
	int	0x13
	pop	bx
	jnc	1f
	mov	bl,ah
1:	call	real_to_prot
	.code32
	sti
	xor	eax,eax
	mov	al,bl
	pop	edi
	pop	esi
	pop	ebx
	pop	ebp
	ret

/* int biosdev_LBA(int ah, int dev, u_int blk_lo, u_int blk_hi, int nsec); */
/* ebp + …         +8      +12      +16           +20           +24 */
	.globl	biosdev_LBA
	.code32
biosdev_LBA:
	push	ebp
	mov	ebp,esp
	push	ebx
	push	esi
	push	edi
	mov	edi,offset biosdev_lba_buf
	mov	eax,[ebp+24]
	shl	eax,16
	mov	al,16
	stosd
	mov	eax,0x30000000
	stosd
	lea	esi,[ebp+16]
	movsd
	movsd
	mov	edx,[ebp+12]
	mov	dh,[ebp+8]
	xor	ebx,ebx
	mov	esi,offset biosdev_lba_buf - 0x30000
	call	prot_to_real
	.code16
	sti
	push	bx
	mov	bx,0x3000
	mov	ds,bx
	mov	ah,dh
	jmp	biosdev_io
