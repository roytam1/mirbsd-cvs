# $MirOS: src/usr.bin/compress/Makefile,v 1.7 2008/03/27 14:53:24 tg Exp $
# $OpenBSD: Makefile,v 1.20 2007/01/24 10:53:43 jmc Exp $

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
CPPFLAGS+=	-DZCONST=const

LDSTATIC=	-static

.include <bsd.prog.mk>
