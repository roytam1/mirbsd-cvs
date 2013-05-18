# $MirOS: ports/devel/libdsk/Makefile,v 1.3 2006/09/14 00:08:20 tg Exp $
# $OpenBSD: Makefile,v 1.3 2003/10/17 06:23:44 grange Exp $

COMMENT=			library for accessing disks and disk image files

DISTNAME=		libdsk-1.0.0
CATEGORIES=		devel

HOMEPAGE=		http://www.seasip.demon.co.uk/Unix/LibDsk/

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://www.seasip.demon.co.uk/Unix/LibDsk/

LIB_DEPENDS=		bz2.10::archivers/bzip2

USE_GMAKE=		Yes

CONFIGURE_STYLE=	autoconf
CONFIGURE_ARGS=		${CONFIGURE_SHARED}
MODGNU_RECURSE_DIRS=	${WRKSRC}/config ${WRKSRC}

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/libdsk
	${INSTALL_DATA} ${WRKSRC}/doc/libdsk.txt ${PREFIX}/share/doc/libdsk
	${INSTALL_DATA} ${WRKSRC}/doc/libdsk.pdf ${PREFIX}/share/doc/libdsk

.include <bsd.port.mk>
