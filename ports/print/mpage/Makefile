# $OpenBSD: Makefile,v 1.21 2004/05/04 04:49:51 jolan Exp $

COMMENT=			print multiple pages per sheet on PostScript printer

DISTNAME=	mpage-2.5.3
CATEGORIES=	print

PERMIT_PACKAGE_CDROM=	"incomplete license"
PERMIT_PACKAGE_FTP=	"incomplete license"
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	ftp://ftp.mesa.nl/pub/mpage/
EXTRACT_SUFX=	.tgz

FLAVOURS=	letter legal a4
FLAVOUR?=	a4

ALL_TARGET=	default
MAKE_FLAGS=	CC=${_PASS_CC:T:Q} CFLAGS='${CFLAGS} $${DEFS}' PREFIX='${PREFIX}'

.if   ${FLAVOUR:L} == "letter"
MAKE_FLAGS+=	PAGESIZE=Letter
.elif ${FLAVOUR:L} == "legal"
MAKE_FLAGS+=	PAGESIZE=Legal
.elif ${FLAVOUR:L} == "a4"
MAKE_FLAGS+=	PAGESIZE=A4
.else
ERRORS+=	"Fatal: You must set exactly ONE flavour: ${FLAVOURS}"
.endif

NO_REGRESS=	Yes

do-install:
	${INSTALL_PROGRAM} ${WRKBUILD}/mpage ${PREFIX}/bin
	${INSTALL_DATA} ${WRKSRC}/mpage.1 ${PREFIX}/man/man1
	${INSTALL_DATA_DIR} ${PREFIX}/share/mpage
	${INSTALL_DATA} ${WRKSRC}/Encodings/* ${PREFIX}/share/mpage

.include <bsd.port.mk>
