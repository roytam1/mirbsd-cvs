# $MirOS: src/usr.bin/xmlwf/Makefile,v 1.1 2005/03/06 16:46:48 tg Exp $

.include <bsd.own.mk>
EXPAT_DIR=	${BSDSRCDIR}/lib/libexpat

PROG=		xmlwf
.PATH: ${EXPAT_DIR}/doc
.PATH: ${EXPAT_DIR}/xmlwf
SRCS=		codepage.c unixfilemap.c xmlfile.c xmlmime.c xmlwf.c

CFLAGS+=	-Wall
CPPFLAGS+=	-I${EXPAT_DIR} -DHAVE_EXPAT_CONFIG_H
DPADD=		${LIBEXPAT}
LDADD=		-lexpat

.include <bsd.prog.mk>
