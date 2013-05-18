# $MirOS: src/usr.bin/compress/Makefile,v 1.6 2008/03/27 13:41:32 tg Exp $
# $OpenBSD: Makefile,v 1.20 2007/01/24 10:53:43 jmc Exp $

BINDIR?=/usr/dbin

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

.include <bsd.prog.mk>
