# $MirOS: ports/security/uvscan/Makefile,v 1.4 2005/07/07 21:26:27 bsiegert Exp $
# $OpenBSD: Makefile,v 1.14 2004/01/14 19:20:39 jakob Exp $
# $NetBSD: Makefile,v 1.1.1.1 2000/06/05 12:01:24 rh Exp $

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386
EMUL=			linux

COMMENT=			evaluation version of a DOS/Windows file virus scanner
VERSION=	4.16.0
DISTNAME=	vlnx416e
PKGNAME=	uvscan-${VERSION}-0
CATEGORIES=	security
HOMEPAGE=	http://www.networkassociates.com/us/downloads/evals/

MASTER_SITES=	http://download.nai.com/products/evaluation/virusscan/english/cmdline/linux/version_4.16/

EXTRACT_SUFX=	.tar.Z

PERMIT_PACKAGE_CDROM=	"Commercial software"
PERMIT_PACKAGE_FTP=	"Commercial software"
PERMIT_DISTFILES_CDROM=	"Commercial software"
PERMIT_DISTFILES_FTP=	"Commercial software"

RUN_DEPENDS=	:redhat_base-*:emulators/redhat/base \
		:uvscan_dat-*:security/uvscan_dat

NO_BUILD=	Yes
NO_REGRESS=	Yes
WRKDIST=	${WRKDIR}

do-configure:
	sed -e 's:@@PREFIX@@:${PREFIX}:g' \
		<${FILESDIR}/uvscan.sh >${WRKDIR}/uvscan.sh

do-install:
	${INSTALL_SCRIPT} ${WRKSRC}/uvscan.sh ${PREFIX}/bin/uvscan
	${INSTALL_MAN} ${WRKSRC}/uvscan.1 ${PREFIX}/man/man1
	${INSTALL_DATA_DIR} ${PREFIX}/libexec/uvscan
	${INSTALL_SCRIPT} ${WRKSRC}/uvscan ${PREFIX}/libexec/uvscan
	${INSTALL_SCRIPT} ${WRKSRC}/liblnxfv.so.4 ${PREFIX}/libexec/uvscan
	ln -s liblnxfv.so.4 ${PREFIX}/libexec/uvscan/liblnxfv.so
.for file in clean.dat license.dat messages.dat names.dat
	${INSTALL_DATA} ${WRKSRC}/${file} ${PREFIX}/libexec/uvscan
.endfor
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/uvscan
.for file in unxadmin.pdf license.txt readme.txt
	${INSTALL_DATA} ${WRKSRC}/${file} ${PREFIX}/share/doc/uvscan
.endfor

.include <bsd.port.mk>
