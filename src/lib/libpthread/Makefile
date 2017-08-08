# $MirOS: src/lib/libpthread/Makefile,v 1.8 2007/06/21 14:40:21 tg Exp $
# $OpenBSD: Makefile,v 1.22 2004/01/18 23:54:20 marc Exp $
#
# The pthread library is formed from the FreeBSD uthread sources of 
# libc_r, and exploits weak symbols in libc.

SRCDIR=		${.CURDIR}
LIBCSRCDIR=	${.CURDIR}/../libc

SHLIB_VERSION?=	11.1
LIB=		pthread
LINTFLAGS=	-z
CPPFLAGS+=	-DPTHREAD_KERNEL -D_POSIX_THREADS -D_THREAD_SAFE -DLIBC_SCCS
CFLAGS+=	-Wall -Wpointer-arith -Wwrite-strings -Wstrict-prototypes
CFLAGS+=	-Wmissing-prototypes -Wsign-compare
CPPFLAGS+=	-I${SRCDIR}/uthread
CPPFLAGS+=	-I${SRCDIR}/include
CPPFLAGS+=	-I${LIBCSRCDIR}/include
AINC+=		-I${SRCDIR}/uthread

# Uncomment this if you want libpthread to contain debug information for
# thread locking.
CPPFLAGS+=	-D_LOCK_DEBUG
#DEBUG=		-g

# enable extra internal consistency checks
CPPFLAGS+=	-D_PTHREADS_INVARIANTS

# for now. gcc 3.4.4 is too strict, and I don't know its inline asm
CFLAGS__atomic_lock.o = -Wno-error

.include "${SRCDIR}/include/Makefile.inc"
.include "${SRCDIR}/sys/Makefile.inc"
.include "${SRCDIR}/thread/Makefile.inc"
.include "${SRCDIR}/uthread/Makefile.inc"
.include "${SRCDIR}/man/Makefile.inc"

.include <bsd.lib.mk>
