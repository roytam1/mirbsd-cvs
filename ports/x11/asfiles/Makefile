# $MirOS$
# $OpenBSD: Makefile,v 1.7 2003/10/08 17:13:15 sturm Exp $

COMMENT=		X11 file manager. Dockable in Window Maker

DISTNAME=		ASFiles-1.0
PKGNAME=		${DISTNAME:L}-0
CATEGORIES=		x11 x11/windowmaker


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_AFTERSTEP:=apps/ASFiles/}

LIB_DEPENDS=		Dnd::x11/libdnd

FAKE_FLAGS=		NORMAL_INSTALL=""

USE_CXX=		Yes # depends on libdnd, which uses CXX
USE_X11=		Yes
NO_REGRESS=		Yes
CONFIGURE_STYLE=	gnu

post-configure:
.for d in . src src/bitmaps src/pixmaps src/external src/regexp pixmaps bitmaps
	@perl -pi -e 's|^(prefix[ \t]*=).*$$|\1 \$${PREFIX}|' ${WRKSRC}/${d}/Makefile
.endfor

post-install:
	${INSTALL_DATA} ${WRKSRC}/src/Files.ad ${PREFIX}/lib/X11/app-defaults/Files

.include <bsd.port.mk>
