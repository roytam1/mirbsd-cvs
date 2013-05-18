# $MirOS: ports/converters/rpm2cpio/Makefile,v 1.2 2006/09/14 00:07:47 tg Exp $
# $OpenBSD: Makefile,v 1.8 2004/02/03 07:28:12 sturm Exp $

COMMENT=		rpm2cpio, simple perl converter
DISTNAME=		rpm2cpio-1.2
DASH_VER=		1
CATEGORIES=		converters archivers
MASTER_SITES=		http://www.iagora.com/~espel/
HOMEPAGE=		http://www.iagora.com/~espel/hacks.html

# BSD
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

# In case other versions are released
DIST_SUBDIR=	${DISTNAME}
DISTFILES=	rpm2cpio

NO_BUILD=	Yes
NO_REGRESS=	Yes
PKG_ARCH=	*

do-extract:
	@mkdir -p ${WRKSRC}
	@cp ${FULLDISTDIR}/${DISTFILES} ${WRKSRC}/

do-install:
	${INSTALL_SCRIPT} ${WRKSRC}/rpm2cpio ${PREFIX}/bin

.include <bsd.port.mk>
