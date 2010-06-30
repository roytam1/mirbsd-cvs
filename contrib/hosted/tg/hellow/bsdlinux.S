/*-
 * Copyright (c) 2010
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
 *-
 * Compile commands:
 * - (on MirBSD use -DI_BSD or -DI_LINUX to add a PT_NOTE section)
 *	mgcc -nostdlib -o hello bsdlinux.S -DI_BSD
 * - (on GNU/Linux; the Linux kernel does not care about ABI tags)
 *	gcc -nostdlib -o hello bsdlinux.S
 * - (on kFreeBSD/MidnightBSD add an EI_OSABI as it ignores NOTEs)
 *	brandelf -f {3|9} hello  # 3=Linux, 9=kFreeBSD/MidnightBSD
 * Observations:
 * - MirBSD honours NOTEs first, EI_OSABI second; default to Linux
 * - kLinux ignores NOTEs and EI_OSABI, apparently
 * - kFreeBSD refuses binaries without EI_OSABI set manually
 * - FreeBSD patches their libbfd to add them automatically
 * Implications:
 * => When creating either Linux (bare), GNU/Linux, MirLinux, etc.
 *    binaries on MirOS, we put in a PT_NOTE just like for MirBSD,
 *    and kFreeBSD users need to run brandelf as they’re used to.
 */

	.intel_syntax noprefix

	.section .comment
	.ascii	"@(""#)rcsid: "
	.asciz	"$MirOS: src/share/misc/licence.template,v 1.28 2008/11/14 15:33:44 tg Rel $"

#if defined(I_BSD) || defined(I_LINUX)
	.section .note.miros.ident,"a",@progbits
	.p2align 2
	.long	2f-1f
	.long	4f-3f
	.long	1
#ifdef I_BSD
1:	.asciz	"MirOS BSD"
#else
1:	.asciz	"MirOS Linux"
#endif
2:	.p2align 2
3:	.long	0
4:	.p2align 2
#endif

	.data
LmsgB:	.ascii	"Hello from BSD!\n"
	ZmsgB = . - LmsgB
LmsgL:	.ascii	"Hello from Linux!\n"
	ZmsgL = . - LmsgL

	.text

	.globl	_start
_start:
	mov	eax,4			/* A write syscall */
	mov	ecx,offset LmsgB
	mov	edx,ZmsgB
	mov	ebx,1			/* L file descriptor */
	push	edx			/* B message size */
	push	ecx			/* B message offset */
	push	ebx			/* B file descriptor */
	mov	ecx,offset LmsgL	/* L message offset */
	mov	edx,ZmsgL		/* L message size */
	call	Lkrnl			/* A do the syscall */
	add	esp,12			/* clean stack */
	xor	ebx,ebx			/* L return code */
	push	ebx			/* B return code */
	mov	eax,1			/* A exit syscall */
	call	Lkrnl
	/* NOTREACHED */

Lkrnl:	int	0x80			/* kernel call */
	ret
