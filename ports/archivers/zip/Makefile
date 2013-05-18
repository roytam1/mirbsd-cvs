# $MirOS: ports/archivers/zip/Makefile,v 1.3 2006/02/09 11:11:01 tg Exp $
# $OpenBSD: Makefile,v 1.30 2003/05/24 02:40:42 jolan Exp $
# $FreeBSD: Makefile,v 1.11 1997/11/25 20:45:45 ache Exp $

COMMENT=	"create/update ZIP files compatible with PKZip(tm)"

DISTNAME=	zip231
PKGNAME=	zip-2.31-0
CATEGORIES=	archivers
MASTER_SITES=	ftp://ftp.info-zip.org/pub/infozip/src/ \
		ftp://mirror.switch.ch/ftp/mirror/infozip/src/ \
		http://www.mirrorservice.org/sites/ftp.info-zip.org/pub/infozip/src/ \
		${MASTER_SITE_SOURCEFORGE:=infozip/}



DISTFILES=	zip231.tar.gz zcrypt29.zip

HOMEPAGE=	http://www.ctan.org/tex-archive/tools/zip/info-zip/Zip.html

# Conditional
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

EXTRA_FAKE_FLAGS=	prefix="${WRKINST}${PREFIX}"

MAKE_FILE=	unix/Makefile

ALL_TARGET=	generic

WRKDIST=	${WRKDIR}/zip-2.31

DOCS=	README WHERE

post-extract:
	@mv -f ${WRKDIR}/{crypt.c,crypt.h} ${WRKSRC}

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/zip
	cd ${WRKSRC}; ${INSTALL_DATA} ${DOCS} ${PREFIX}/share/doc/zip

NO_REGRESS=	Yes

.include <bsd.port.mk>
