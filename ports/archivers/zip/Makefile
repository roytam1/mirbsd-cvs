# $MirOS: ports/archivers/zip/Makefile,v 1.5 2006/09/14 00:06:53 tg Exp $
# $OpenBSD: Makefile,v 1.30 2003/05/24 02:40:42 jolan Exp $
# $FreeBSD: Makefile,v 1.11 1997/11/25 20:45:45 ache Exp $

COMMENT=		create/update ZIP files compatible with PKZip(tm)

DISTNAME=	zip232
PKGNAME=	zip-2.32-0
CATEGORIES=	archivers
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=infozip/}

DISTFILES=	zip232.zip

HOMEPAGE=	http://www.ctan.org/tex-archive/tools/zip/info-zip/Zip.html

# Conditional
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

EXTRA_FAKE_FLAGS=	prefix="${WRKINST}${PREFIX}"

MAKE_FILE=	unix/Makefile

ALL_TARGET=	generic

WRKDIST=	${WRKDIR}

DOCS=	README WHERE

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/zip
	cd ${WRKSRC}; ${INSTALL_DATA} ${DOCS} ${PREFIX}/share/doc/zip

NO_REGRESS=	Yes

.include <bsd.port.mk>
