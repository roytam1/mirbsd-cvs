# $MirOS: ports/archivers/unarj/Makefile,v 1.2 2005/07/07 21:17:03 bsiegert Exp $
# $OpenBSD: Makefile,v 1.17 2003/05/24 02:40:42 jolan Exp $
# $FreeBSD: Makefile,v 1.12 1999/02/17 22:25:36 ache Exp $

COMMENT=	"extract files from ARJ archives"

DISTNAME=	unarj-2.43
PKGNAME=	unarj-2.43-1
CATEGORIES=	archivers
MASTER_SITES=	ftp://ftp.kiarchive.ru/pub/unix/arcers/
EXTRACT_SUFX=	.tgz

# Restrictive
PERMIT_PACKAGE_CDROM=	No
PERMIT_PACKAGE_FTP=	No
PERMIT_DISTFILES_CDROM=	No
PERMIT_DISTFILES_FTP=	No

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/unarj
	cd ${WRKSRC}; ${INSTALL_PROGRAM} unarj ${PREFIX}/bin
	cd ${WRKSRC}; ${INSTALL_DATA} unarj.doc technote.doc ${PREFIX}/share/doc/unarj

NO_REGRESS=	Yes

.include <bsd.port.mk>
