# $MirOS: src/distrib/special/pax/Makefile,v 1.1 2016/03/12 12:53:29 tg Exp $

.include <bsd.own.mk>

SRC_PATH=	${BSDSRCDIR}/bin/pax

.include "${SRC_PATH}/Makefile"

SRCDIR=		${SRC_PATH}
SRCS:=		${SRCS:Nar.c}
SAFE_PATH=	/bin:/usr/bin
CPPFLAGS+=	-DSMALL
