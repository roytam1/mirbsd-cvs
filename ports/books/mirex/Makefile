# $MirOS: ports/books/mirex/Makefile,v 1.1.7.1 2005/03/18 15:43:29 tg Exp $

COMMENT=		"MirOS sample files, keys and information"
CATEGORIES=		books
DISTNAME=		mirex-6
EXTRACT_SUFX=		.cpio.gz
RESPONSIBLE=		Thorsten Glaser <tg@${_DOMAIN_DU_JOUR}>
HOMEPAGE=		http://MirBSD.org/

# MirOS licence
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		${_MASTER_SITE_MIRBSD}
WRKDIST=		${WRKDIR}/samples

pre-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/mirex

.include <bsd.port.mk>
