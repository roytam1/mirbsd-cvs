/*	$OpenBSD: index.S,v 1.4 2005/08/07 11:30:38 espie Exp $ */
/*
 * Written by J.T. Conklin <jtc@netbsd.org>.
 * Public domain.
 */

#include <machine/asm.h>

	.section .comment
	.asciz	"$MirOS: src/lib/libc/arch/i386/string/index.S,v 1.4 2005/09/22 20:06:17 tg Exp $"

	.text

NENTRY(strchr)
ENTRY(index)
	movl	4(%esp),%eax
	movb	8(%esp),%cl
	.align 2,0x90
L1:
	movb	(%eax),%dl
	cmpb	%dl,%cl			/* found char??? */
	je 	L2
	incl	%eax
	testb	%dl,%dl			/* null terminator??? */
	jnz	L1
	xorl	%eax,%eax
L2:
	ret
