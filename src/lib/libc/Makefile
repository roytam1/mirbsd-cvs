# $MirOS: src/lib/libc/Makefile,v 1.31 2008/12/27 21:17:53 tg Exp $
# $OpenBSD: Makefile,v 1.23 2005/06/29 14:05:08 mickey Exp $
#
# All library objects contain sccsid strings by default; they may be
# excluded as a space-saving measure.  To produce a library that does
# not contain these strings, delete -DLIBC_SCCS and -DSYSLIBC_SCCS
# from CFLAGS below.  To remove these strings from just the system call
# stubs, remove just -DSYSLIBC_SCCS from CFLAGS in Makefile.inc.

.include <bsd.own.mk>

#XXX next major: rm crypt/arc4pushk.c
SHLIB_VERSION?=		41.6	# note: If changes were made to the file
#				# src/lib/libc/include/thread_private.h or
#				# system calls have been added/changed,
#				# libpthread must also be updated.
LIB=			c
LINTFLAGS+=		-z

LIBCSRCDIR=		${.CURDIR}
KERNNOGCC=		#defined
KERNBASE?=		${.CURDIR}/../../kern
.include "${LIBCSRCDIR}/Makefile.inc"
.include "${KERNBASE}/c/Makefile.inc"

SRCS+=			csuhlpr.c

.include <bsd.lib.mk>
