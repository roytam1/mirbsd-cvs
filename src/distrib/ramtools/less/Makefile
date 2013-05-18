# $MirOS: src/distrib/ramtools/less/Makefile,v 1.1 2006/05/15 19:20:16 tg Exp $

.include <bsd.own.mk>

SRC_PATH=	${BSDSRCDIR}/usr.bin/less
.PATH: ${SRC_PATH}

CPPFLAGS+=	-DSMALL=1 -I${SRC_PATH}

.include "${SRC_PATH}/less/Makefile"
