# $MirOS: ports/archivers/unzip/Makefile,v 1.7 2007/02/23 11:04:31 bsiegert Exp $
# $OpenBSD: Makefile,v 1.32 2003/08/17 23:48:40 brad Exp $

COMMENT=		extract, list & test files in a ZIP archive
VERSION=		5.52
DASH_VER=		1
DISTNAME=		unzip${VERSION:S/.//}
PKGNAME=		unzip-${VERSION}-${DASH_VER}
CATEGORIES=		archivers
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=infozip/}
HOMEPAGE=		http://www.info-zip.org/UnZip.html

# BSD-style
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

WRKDIST=		${WRKDIR}/unzip-${VERSION}
EXTRA_XAKE_FLAGS+=	WRKSRC=${WRKSRC:Q}

post-extract:
	cd ${FILESDIR} && pax -rw . ${WRKBUILD}/

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/unzip
	cd ${WRKSRC}; ${INSTALL_DATA} LICENSE README ${PREFIX}/share/doc/unzip/

do-regress:
	cd ${WRKBUILD}/unzip && ./unzip -x -a -o ../testmake.zip
	cmp -s ${WRKBUILD}/unzip/notes ${FILESDIR}/notes

.include <bsd.port.mk>
