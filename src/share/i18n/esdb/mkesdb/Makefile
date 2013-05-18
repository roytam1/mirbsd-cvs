# $MirOS: src/share/i18n/esdb/mkesdb/Makefile,v 1.4 2006/01/31 19:13:45 tg Exp $
# $NetBSD: Makefile,v 1.3 2003/10/27 00:14:59 lukem Exp $

.include <bsd.own.mk>
.include "${BSDSRCDIR}/lib/libcitrus_iconv/Makefile.inc"

.PATH: ${BSDSRCDIR}/lib/libcitrus_iconv/libc/citrus

PROG=		mkesdb
SRCS=		yacc.y lex.l \
		citrus_bcs.c citrus_db_factory.c citrus_db_hash.c \
		citrus_lookup_factory.c
CPPFLAGS+=	-I. -I${.CURDIR} -I${NETBSDSRCDIR}/lib/libc \
		-I${BSDSRCDIR}/lib/libcitrus_iconv/libc/citrus \
		-DHOSTPROG -DLIBC_SCCS
NOMAN=		Yes

install:

.include <bsd.prog.mk>
