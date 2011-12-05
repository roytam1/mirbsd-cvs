# $MirOS: src/bin/md5/Makefile,v 1.6 2006/05/26 11:55:15 tg Exp $
# $OpenBSD: Makefile,v 1.10 2005/05/24 21:57:47 millert Exp $

PROG=		cksum
SRCS=		adler32.c crc.c md5.c suma.c
.if ${MACHINE_ARCH} == "i386"
SRCS+=		ad32-x86.S suma-x86.S
CPPFLAGS+=	-DUSE_ASM
.else
SRCS+=		suma-mi.c
DPADD+=		${LIBZ}
LDADD+=		-lz
.endif

MAN=	cksum.1 md5.1 sha1.1 rmd160.1
LINKS=	${BINDIR}/cksum ${BINDIR}/sha1 \
	${BINDIR}/cksum ${BINDIR}/rmd160 \
	${BINDIR}/cksum ${BINDIR}/md5 \
	${BINDIR}/cksum ${BINDIR}/sum
MLINKS= cksum.1 sum.1

.include <bsd.own.mk>

COPTS+=	-Wall -Wconversion -Wmissing-prototypes

.if ${OStype} != "MirBSD"
CPPFLAGS+=	-D_MIRMAKE_DEFNS
LDADD+=		-L${.SYSMK} -lmirmake
.endif

.include <bsd.prog.mk>
