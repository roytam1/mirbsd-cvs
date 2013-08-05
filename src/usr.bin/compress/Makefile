# $MirOS: src/usr.bin/compress/Makefile,v 1.9 2009/10/27 19:27:15 tg Exp $
# $OpenBSD: Makefile,v 1.21 2007/05/20 00:27:27 jsg Exp $

PROG=	compress
SRCS=	main.c zopen.c gzopen.c nullopen.c
MAN=	compress.1 gzip.1
LINKS=	${BINDIR}/compress ${BINDIR}/uncompress \
	${BINDIR}/compress ${BINDIR}/zcat \
	${BINDIR}/compress ${BINDIR}/gzip \
	${BINDIR}/compress ${BINDIR}/gunzip \
	${BINDIR}/compress ${BINDIR}/gzcat

MLINKS+=compress.1 uncompress.1 compress.1 zcat.1
MLINKS+=gzip.1 gunzip.1 gzip.1 gzcat.1

LDADD=		-lz
DPADD=		${LIBZ}
CPPFLAGS+=	-DZLIB_CONST

LDSTATIC=	-static

.include <bsd.prog.mk>
