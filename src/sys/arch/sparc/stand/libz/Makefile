# $MirOS: src/sys/arch/sparc/stand/libz/Makefile,v 1.5 2007/03/02 03:13:27 tg Exp $

.include <bsd.own.mk>

# This is needed for libz in the boot loader
S=		${.CURDIR}/../../../..
CFLAGS+=	${SACFLAGS} ${DEBUGFLAGS}
CPPFLAGS+=	-I${S}/lib/libsa
CPPFLAGS+=	-DZCONST=const

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
