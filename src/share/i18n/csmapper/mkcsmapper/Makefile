# $MirOS: src/share/i18n/csmapper/mkcsmapper/Makefile,v 1.3 2006/01/31 15:59:31 tg Exp $
# $NetBSD: Makefile,v 1.3 2003/10/27 00:14:59 lukem Exp $

.ifndef HOSTPROG
.include <bsd.own.mk>
.endif
.include "${BSDSRCDIR}/lib/libcitrus_iconv/Makefile.inc"

.PATH: ${BSDSRCDIR}/lib/libcitrus_iconv/libc/citrus

WARNS?=	2
PROG=		mkcsmapper
SRCS=		yacc.y lex.l \
		citrus_db_factory.c citrus_bcs.c citrus_db_hash.c \
		citrus_lookup_factory.c citrus_pivot_factory.c
CPPFLAGS+=	-I. -I${.CURDIR} -I${BSDSRCDIR}/lib/libc \
		-I${BSDSRCDIR}/lib/libcitrus_iconv/libc/citrus \
		-I${BSDSRCDIR}/lib/libcitrus_iconv/libc/citrus/modules \
		-DHOSTPROG -DLIBC_SCCS
YHEADER=	1
CLEANFILES+=	y.tab.h
NOMAN=		Yes

install:

.ifndef HOSTPROG
.include <bsd.prog.mk>
.endif
