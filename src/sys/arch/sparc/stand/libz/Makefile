# $MirOS: src/sys/arch/sparc/stand/libz/Makefile,v 1.4 2006/10/07 21:36:21 tg Exp $

.include <bsd.own.mk>

# This is needed for libz in the boot loader
S=		${.CURDIR}/../../../..
CFLAGS+=	${SACFLAGS} ${DEBUGFLAGS}
CPPFLAGS+=	-I${S}/lib/libsa

# This is used to build a small libz
CPPFLAGS+=	-DSLOW -DSMALL -DNOBYFOUR -DNO_GZIP
CPPFLAGS+=	-DDYNAMIC_CRC_TABLE -DBUILDFIXED

LIB=		z
SRCS=		crc32.c infback.c inffast.c inflate.c inftrees.c
.PATH: ${BSDSRCDIR}/lib/libz ${S}/lib/libsa

NOPIC=		Yes
DEBUGLIBS=	No

install:

.include <bsd.lib.mk>
