# $MirOS: src/sys/arch/sparc/stand/libz/Makefile,v 1.3 2006/06/11 00:15:12 tg Exp $

.include <bsd.own.mk>

# This is needed for libz in the boot loader
S=		${.CURDIR}/../../../..
CFLAGS+=	${SACFLAGS} ${DEBUGFLAGS}
CPPFLAGS+=	-I${S}/lib/libsa

# This is used to build a small libz
CPPFLAGS+=	-DSLOW -DSMALL -DNOBYFOUR -DNO_GZIP
CPPFLAGS+=	-DDYNAMIC_CRC_TABLE -DBUILDFIXED

LIB=		z
SRCS=		adler32s.c crc32.c infback.c inffast.c inflate.c inftrees.c
.PATH: ${BSDSRCDIR}/lib/libz ${S}/lib/libsa

NOPIC=		Yes
DEBUGLIBS=	No

install:

.include <bsd.lib.mk>
