# $MirOS: ports/devel/libdockapp/Makefile,v 1.1.7.1 2005/03/18 15:44:50 tg Exp $
# $OpenBSD: Makefile,v 1.9 2002/09/17 14:35:03 wilfried Exp $

COMMENT=		'dockapp-making standard library for Window Maker'
DISTNAME=		libdockapp-0.4.0
CATEGORIES=		devel

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		ftp://shadowmere.student.utwente.nl/pub/WindowMaker/

USE_X11=		Yes
NO_REGRESS=		Yes
CONFIGURE_STYLE=	autoconf
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} --enable-static

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/libdockapp
	${INSTALL_DATA} ${WRKSRC}/COPYING ${PREFIX}/share/doc/libdockapp

.include <bsd.port.mk>
