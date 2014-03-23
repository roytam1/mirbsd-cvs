/* $MirOS: src/lib/libc/arch/i386/string/strcpy.S,v 1.5 2005/10/21 10:53:23 tg Exp $ */
/*
 * Written by J.T. Conklin <jtc@netbsd.org>.
 * Public domain.
 */

#include <machine/asm.h>

WARN_REFERENCES(strcpy, "strcpy() is almost always misused, consider using strlcpy()")

	.section .comment
	.asciz	"$MirOS: src/lib/libc/arch/i386/string/strcpy.S,v 1.5 2005/10/21 10:53:23 tg Exp $"

	.text

/*
 * NOTE: I've unrolled the loop eight times: large enough to make a
 * significant difference, and small enough not to totally trash the
 * cache.
 */

ENTRY(strcpy)
	movl	4(%esp),%ecx		/* dst address */
	movl	8(%esp),%edx		/* src address */
	pushl	%ecx			/* push dst address */

	.align 2,0x90
L1:	movb	(%edx),%al		/* unroll loop, but not too much */
	movb	%al,(%ecx)
	testb	%al,%al
	jz	L2
	movb	1(%edx),%al
	movb	%al,1(%ecx)
	testb	%al,%al
	jz	L2
	movb	2(%edx),%al
	movb	%al,2(%ecx)
	testb	%al,%al
	jz	L2
	movb	3(%edx),%al
	movb	%al,3(%ecx)
	testb	%al,%al
	jz	L2
	movb	4(%edx),%al
	movb	%al,4(%ecx)
	testb	%al,%al
	jz	L2
	movb	5(%edx),%al
	movb	%al,5(%ecx)
	testb	%al,%al
	jz	L2
	movb	6(%edx),%al
	movb	%al,6(%ecx)
	testb	%al,%al
	jz	L2
	movb	7(%edx),%al
	movb	%al,7(%ecx)
	addl	$8,%edx
	addl	$8,%ecx
	testb	%al,%al
	jnz	L1
L2:	popl	%eax			/* pop dst address */
	ret
