# $MirOS: ports/archivers/unzip/Makefile,v 1.5 2006/06/23 14:34:35 bsiegert Exp $
# $OpenBSD: Makefile,v 1.32 2003/08/17 23:48:40 brad Exp $

COMMENT=			extract, list & test files in a ZIP archive
VERSION=	5.52
DISTNAME=	unzip${VERSION:S/.//}
PKGNAME=	unzip-${VERSION}-0
CATEGORIES=	archivers
MASTER_SITES=	ftp://ftp.info-zip.org/pub/infozip/src/ \
		ftp://mirror.switch.ch/ftp/mirror/infozip/src/ \
		http://www.mirrorservice.org/sites/ftp.info-zip.org/pub/infozip/src/ \
		${MASTER_SITE_SOURCEFORGE:=infozip/}
HOMEPAGE=	http://www.ctan.org/tex-archive/tools/zip/info-zip/UnZip.html

# Conditional
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

EXTRA_MAKE_FLAGS=	LD="${CC}" CF='-I. $$(LOC)' \
		LOC="${CFLAGS} -DUSE_UNSHRINK -DUNIX -DBSD4_4"
FAKE_FLAGS=	prefix="${WRKINST}${PREFIX}"
MAKE_FILE=	unix/Makefile
ALL_TARGET=	bsd
WRKDIST=	${WRKDIR}/unzip-${VERSION}
DOCS=		COPYING.OLD LICENSE README WHERE

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/unzip
	cd ${WRKSRC}; ${INSTALL_DATA} ${DOCS} ${PREFIX}/share/doc/unzip

do-regress:
	cd ${WRKBUILD} && ./unzip -x -a -o testmake.zip
	cmp -s ${WRKBUILD}/notes files/notes

.include <bsd.port.mk>
