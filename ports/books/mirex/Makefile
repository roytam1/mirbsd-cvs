# $MirOS$

COMMENT=		"MirOS sample files, keys and info"
CATEGORIES=		books
DISTNAME=		mirex-5
EXTRACT_SUFX=		.cpio.gz
RESPONSIBLE=		Thorsten Glaser <tg@${_DOMAIN_DU_JOUR}>
HOMEPAGE=		http://mirbsd.de/

# MirOS licence
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${_MASTER_SITE_MIRBSD}
WRKDIST=		${WRKDIR}/samples

pre-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/mirex

.include <bsd.port.mk>
