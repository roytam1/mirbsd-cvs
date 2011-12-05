# $MirOS: src/bin/md5/Makefile,v 1.4 2005/04/12 19:50:21 tg Exp $
# $OpenBSD: Makefile,v 1.10 2005/05/24 21:57:47 millert Exp $

PROG=	md5
SRCS=	crc.c md5.c suma.c
.if ${MACHINE_ARCH} == "i386"
SRCS+=	suma-x86.S
.else
SRCS+=	suma-mi.c
.endif

MAN=	cksum.1 md5.1 sha1.1 rmd160.1
LINKS=	${BINDIR}/md5 ${BINDIR}/sha1 \
	${BINDIR}/md5 ${BINDIR}/rmd160 \
	${BINDIR}/md5 ${BINDIR}/cksum \
	${BINDIR}/md5 ${BINDIR}/sum
MLINKS= cksum.1 sum.1

.include <bsd.own.mk>

COPTS+=	-Wall -Wconversion -Wmissing-prototypes

.include <bsd.prog.mk>
