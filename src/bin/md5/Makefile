# $MirOS: src/bin/md5/Makefile,v 1.8 2006/09/17 19:28:57 tg Exp $
# $OpenBSD: Makefile,v 1.10 2005/05/24 21:57:47 millert Exp $

PROG=		cksum
SRCS=		crc.c md5.c sfv.c suma.c
.if ${MACHINE_ARCH} == "i386"
SRCS+=		suma-x86.S
.else
SRCS+=		suma-mi.c
.endif

MAN=	cksum.1 md5.1 sha1.1 rmd160.1
LINKS=	${BINDIR}/cksum ${BINDIR}/sha1 \
	${BINDIR}/cksum ${BINDIR}/rmd160 \
	${BINDIR}/cksum ${BINDIR}/md5 \
	${BINDIR}/cksum ${BINDIR}/sum
MLINKS= cksum.1 sum.1

.include <bsd.own.mk>

COPTS+=		-Wall -Wconversion -Wmissing-prototypes

.if ${OStype} != "MirBSD"
CPPFLAGS+=	-D_MIRMAKE_DEFNS
LDADD+=		-L${.SYSMK} -lmirmake
DPADD+=		${LIBZ}
LDADD+=		-lz
.else
SMALL=		#defined
KERNBASE?=	${BSDSRCDIR}/kern
.  include "${KERNBASE}/z/Makefile.adler32"
.endif

.include <bsd.prog.mk>
