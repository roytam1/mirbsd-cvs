# $MirOS: src/lib/libc/Makefile,v 1.35 2010/01/10 20:18:50 tg Exp $
# $OpenBSD: Makefile,v 1.23 2005/06/29 14:05:08 mickey Exp $
#
# All library objects contain sccsid strings by default; they may be
# excluded as a space-saving measure.  To produce a library that does
# not contain these strings, delete -DLIBC_SCCS and -DSYSLIBC_SCCS
# from CFLAGS below.  To remove these strings from just the system call
# stubs, remove just -DSYSLIBC_SCCS from CFLAGS in Makefile.inc.

.include <bsd.own.mk>

#XXX next major: rm crypt/arc4pushk.c, optu8to16vis
#XXX make new conversion: 0‥1F→2400, 80‥9F,EF80‥EF9F vis, EFA0‥EFFF lat1
SHLIB_VERSION?=		41.8	# note: If changes were made to the file
#				# src/lib/libc/include/thread_private.h or
#				# system calls have been added/changed,
#				# libpthread must also be updated.
LIB=			c
LINTFLAGS+=		-z

LIBCSRCDIR=		${.CURDIR}
KERNNOGCC=		#defined
KERNISUSR=		#defined
KERNBASE?=		${.CURDIR}/../../kern
.include "${LIBCSRCDIR}/Makefile.inc"
.include "${KERNBASE}/c/Makefile.inc"

SRCS+=			csuhlpr.c

.include <bsd.lib.mk>
