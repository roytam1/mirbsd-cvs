# $MirOS: ports/emulators/wine/winesetup/Makefile,v 1.2 2005/07/07 21:20:54 bsiegert Exp $

BROKEN=			have to port itcl and itk first

COMMENT=			TK-based setup for wine
V=			0-73
DISTNAME=		winesetuptk-${V}
EXTRACT_SUFX=		.tar.bz2
PKGNAME=		winesetup-${V:C/-/./}-0
CATEGORIES=		emulators x11
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=wine/}

# GNU GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

BUILD_DEPENDS+=		::x11/tk/8.4

WRKDIST=		${WRKDIR}/winesetuptk${V:C/-/./}/winesetuptk-${V:C/-/./}

CONFIGURE_STYLE=	autoconf
CONFIGURE_ARGS+=	--with-tcltk=${PREFIX}/.. \
			--with-doc=${PREFIX}/share/doc/winesetup

.include <bsd.port.mk>
