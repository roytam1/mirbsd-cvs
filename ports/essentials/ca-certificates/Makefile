# $MirOS$

COMMENT=		X.509 CA certificate collection
CATEGORIES=		essentials security
CVS_DISTREPO=		${_MIROS_ANONCVS}
CVS_DISTDATE=		2008/02/23
CVS_DISTMODS=		src/etc/ssl.certs.shar
CVS_DISTFILE=		ca-certificates
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>
HOMEPAGE=		http://MirBSD.de/

# copyright law not applicable
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

WRKDIST=		${WRKDIR}/src/etc

do-build:
	cd ${WRKSRC} && ${MKSH} ssl.certs.shar

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/ca-certificates
	${INSTALL_DATA} ${WRKSRC}/*.+([0-9]) ${PREFIX}/share/ca-certificates/

.include <bsd.port.mk>
