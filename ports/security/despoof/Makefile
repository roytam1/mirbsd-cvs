# $OpenBSD: Makefile,v 1.6 2002/12/29 20:31:40 fgsch Exp $

COMMENT=			command-line anti-spoofing detection utility

DISTNAME=	despoof-0.9
CATEGORIES=	security
MASTER_SITES=	http://razor.bindview.com/tools/files/ \
		${MASTER_SITE_PACKETSTORM:=UNIX/misc/}
EXTRACT_SUFX=	.tgz

HOMEPAGE=	http://razor.bindview.com/tools/desc/despoof_readme.html


PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS=	net::net/libnet

MAKE_FLAGS+=	DEFS='-I${LOCALBASE}/include `libnet-config --defines`' \
		LIBS='-L${LOCALBASE}/lib -lnet -lpcap'

NO_REGRESS=	Yes

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/despoof ${PREFIX}/bin
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/despoof
	${INSTALL_DATA} ${WRKSRC}/README ${PREFIX}/share/doc/despoof
	${INSTALL_DATA} ${WRKSRC}/LICENSE ${PREFIX}/share/doc/despoof

.include <bsd.port.mk>
