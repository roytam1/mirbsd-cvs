/*	$OpenBSD: rindex.S,v 1.3 2005/08/07 11:30:38 espie Exp $ */
/*
 * Written by J.T. Conklin <jtc@netbsd.org>.
 * Public domain.
 */

#include <machine/asm.h>

	.section .comment
	.asciz	"$MirOS: src/lib/libc/arch/i386/string/rindex.S,v 1.4 2005/09/22 20:06:18 tg Exp $"

	.text

NENTRY(strrchr)
ENTRY(rindex)
	pushl	%ebx
	movl	8(%esp),%edx
	movb	12(%esp),%cl
	xorl	%eax,%eax		/* init pointer to null */
	.align 2,0x90
L1:
	movb	(%edx),%bl
	cmpb	%bl,%cl
	jne	L2
	movl	%edx,%eax
L2:
	incl	%edx
	testb	%bl,%bl			/* null terminator??? */
	jnz	L1
	popl	%ebx
	ret
