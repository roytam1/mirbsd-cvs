/*
 * Written by J.T. Conklin <jtc@netbsd.org>.
 * Public domain.
 */

#include <machine/asm.h>

	.section .comment
	.asciz	"$MirOS$"

	.text
#if 0
	.asciz "$OpenBSD: rindex.S,v 1.2 1996/08/19 08:13:10 tholo Exp $"
#endif

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
