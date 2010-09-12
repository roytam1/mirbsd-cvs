# $MirOS: ports/print/ttf-anonymous-pro/Makefile,v 1.3 2010/09/02 09:44:25 tg Exp $

COMMENT=		fixed width sans designed especially for coders
CATEGORIES=		print graphics textproc productivity x11
VERSION=		1.001
DASH_VER=		2
DISTNAME=		AnonymousPro
PKGNAME=		ttf-anonymous-pro-${VERSION}-${DASH_VER}
HOMEPAGE=		http://www.ms-studio.com/FontSales/anonymouspro.html

# SIL Open Font License (DFSG free)
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		http://www.ms-studio.com/FontSales/
DIST_SUBDIR=		ttf-anonymous-pro-${VERSION}
EXTRACT_SUFX=		.zip

FONTDIR=		${PREFIX}/lib/X11/fonts/${DISTNAME}
USE_X11=		Yes
NO_BUILD=		Yes
NO_REGRESS=		Yes

DOCS=			FONTLOG.txt OFL.txt OFL-FAQ.txt README.txt
FONTS=			Anonymous\ Pro.ttf Anonymous\ Pro\ B.ttf Anonymous\ Pro\ I.ttf Anonymous\ Pro\ BI.ttf

do-install:
	@-rm -rf ${FONTDIR}
	${INSTALL_DATA_DIR} ${FONTDIR}
	cd ${WRKSRC} && ${INSTALL_DATA} ${FONTS} ${FONTDIR}/
	cd ${FONTDIR} && \
	    ${X11BASE}/bin/mkfontscale . && \
	    ${X11BASE}/bin/mkfontdir .
	cd ${WRKSRC} && ${INSTALL_DATA} ${DOCS} ${FONTDIR}/

.include <bsd.port.mk>
