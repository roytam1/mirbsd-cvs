/**	$MirOS: src/sys/arch/i386/include/asm.h,v 1.10 2008/08/03 21:02:03 tg Exp $ */
/*	$OpenBSD: asm.h,v 1.7 2003/06/02 23:27:47 millert Exp $	*/
/*	$NetBSD: asm.h,v 1.7 1994/10/27 04:15:56 cgd Exp $	*/

/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)asm.h	5.5 (Berkeley) 5/7/91
 */

#ifndef _I386_ASM_H_
#define _I386_ASM_H_

#ifdef PIC
#ifdef __ELF__
#define PIC_PROLOGUE	\
	pushl	%ebx;	\
	call	666f;	\
666:			\
	popl	%ebx;	\
	addl	$_GLOBAL_OFFSET_TABLE_+[.-666b], %ebx
#else
#define PIC_PROLOGUE	\
	pushl	%ebx;	\
	call	666f;	\
666:			\
	popl	%ebx;	\
	addl	$__GLOBAL_OFFSET_TABLE_+[.-666b], %ebx
#endif
#define PIC_EPILOGUE	\
	popl	%ebx
#define PIC_PLT(x)	x@PLT
#define PIC_GOT(x)	x@GOT(%ebx)
#define PIC_GOTOFF(x)	x@GOTOFF(%ebx)
#else
#define PIC_PROLOGUE
#define PIC_EPILOGUE
#define PIC_PLT(x)	x
#define PIC_GOT(x)	x
#define PIC_GOTOFF(x)	x
#endif

#ifdef __ELF__
#define _C_LABEL(name)		name
#else
#ifdef __STDC__
#define _C_LABEL(name)		_ ## name
#else
#define _C_LABEL(name)		_/**/name
#endif
#endif
#define	_ASM_LABEL(x)	x

/*
 * WEAK_ALIAS: create a weak alias (ELF only)
 */
#ifdef __ELF__
#define WEAK_ALIAS(alias,sym)		\
	.weak alias;			\
	alias = sym
#endif

/*
 * WARN_REFERENCES: create a warning if the specified symbol is referenced
 * (ELF only).
 */
#ifdef __ELF__
#define WARN_REFERENCES(_sym,_msg)	\
	.section .gnu.warning. ## _sym ; .ascii "REF! " _msg ; .previous
#endif /* __ELF__ */

/* let kernels and others override entrypoint alignment */
#ifndef _ALIGN_TEXT
#ifdef SMALL
#define _ALIGN_TEXT		/* nothing */
#else
#define _ALIGN_TEXT		.p2align 2, 0x90
#endif
#endif

#define FTYPE(x)		.type x,@function
#define OTYPE(x)		.type x,@object

#define	_ENTRY(name) \
	.text; _ALIGN_TEXT; .globl name; FTYPE(name); name:

/* no profiling */
#define _PROF_PROLOGUE

#define ENTRY(name)		_ENTRY(_C_LABEL(name)); _PROF_PROLOGUE
#define NENTRY(name)		_ENTRY(_C_LABEL(name))
#define	ASENTRY(name)		_ENTRY(_ASM_LABEL(name)); _PROF_PROLOGUE

#define ALTENTRY(name) \
	.globl _C_LABEL(name); FTYPE(_C_LABEL(name)); _C_LABEL(name):
#define DENTRY(name) \
	.globl _C_LABEL(name); OTYPE(_C_LABEL(name)); _C_LABEL(name):

#define ASMSTR			.asciz

#define RCSID(x)		.section .comment; \
				.ascii "@(""#)rcsid: "; \
				.asciz x; \
				.previous

#endif /* !_I386_ASM_H_ */
