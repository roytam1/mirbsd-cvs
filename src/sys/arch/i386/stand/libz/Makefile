# $MirOS: src/sys/arch/i386/stand/libz/Makefile,v 1.6 2006/10/15 01:35:54 tg Exp $

.include <bsd.own.mk>

# This is needed for libz in the boot loader
S=		${.CURDIR}/../../../..
CPPFLAGS+=	${SACFLAGS:M-[DI]*} -I${S}/lib/libsa
COPTS+=		${SACFLAGS:N-[DI]*} ${DEBUGFLAGS}

# This is used to build a small libz
CPPFLAGS+=	-DSLOW -DSMALL -DNOBYFOUR -DNO_GZIP
CPPFLAGS+=	-DDYNAMIC_CRC_TABLE -DBUILDFIXED

LIB=		z
SRCS=		crc32.c infback.c inffast.c inflate.c inftrees.c
.PATH: ${BSDSRCDIR}/lib/libz

NOPIC=		Yes
DEBUGLIBS=	No

install:

.include <bsd.lib.mk>
