# $MirOS$
# $NetBSD: Makefile,v 1.3 2003/10/27 00:14:59 lukem Exp $

.ifndef HOSTPROG
.include <bsd.own.mk>
.endif

.PATH: ${BSDSRCDIR}/lib/libcitrus_iconv/libc/citrus

WARNS?=		2
PROG=		mkesdb
SRCS=		yacc.y lex.l \
		citrus_bcs.c citrus_db_factory.c citrus_db_hash.c \
		citrus_lookup_factory.c
CPPFLAGS+=	-I. -I${.CURDIR} -I${NETBSDSRCDIR}/lib/libc \
		-I${BSDSRCDIR}/lib/libcitrus_iconv/libc/citrus \
		-DHOSTPROG -DLIBC_SCCS
YHEADER=	1
NOMAN=		Yes

install:

.ifndef HOSTPROG
.include <bsd.prog.mk>
.endif
