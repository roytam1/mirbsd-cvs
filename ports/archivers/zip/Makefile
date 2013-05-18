# $MirOS: ports/archivers/zip/Makefile,v 1.7 2007/02/23 13:43:20 tg Exp $
# $OpenBSD: Makefile,v 1.30 2003/05/24 02:40:42 jolan Exp $
# $FreeBSD: Makefile,v 1.11 1997/11/25 20:45:45 ache Exp $

COMMENT=		create/update ZIP files compatible with PKZip(tm)
VERSION=		2.32
DASH_VER=		1
DISTNAME=		zip${VERSION:S/.//g}
PKGNAME=		zip-${VERSION}-${DASH_VER}
CATEGORIES=		archivers
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=infozip/}
EXTRACT_SUFX=		.zip
HOMEPAGE=		http://www.info-zip.org/Zip.html

# BSD-style
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

EXTRA_FAKE_FLAGS=	prefix=${WRKINST:Q}${PREFIX:Q}
MAKE_FILE=		unix/Makefile
ALL_TARGET=		generic_zlib
WRKDIST=		${WRKDIR}
NO_REGRESS=		Yes

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/zip
	cd ${WRKSRC} && ${INSTALL_DATA} LICENSE README WHATSNEW \
	    ${PREFIX}/share/doc/zip/

.include <bsd.port.mk>
