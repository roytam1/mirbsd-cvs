# $MirOS: ports/x11/goggles/Makefile,v 1.3 2006/02/09 11:15:50 tg Exp $
# $OpenBSD: Makefile,v 1.2 2004/02/12 02:19:39 espie Exp $

COMMENT=			gui for ogle

CATEGORIES=		x11
VERSION=		0.7.2
DASH_VER=		-0
DISTNAME=		Goggles-${VERSION}
PKGNAME=		goggles-${VERSION}${DASH_VER}
WRKDIST=		${WRKDIR}/${DISTNAME:L}
MASTER_SITES=		http://www.fifthplanet.net/files/
HOMEPAGE=		http://www.fifthplanet.net/goggles.html

# GPL
PERMIT_DISTFILES_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes

LIB_DEPENDS=		FOX-1.1.41.0::devel/fox \
			dvdcontrol,msgevents::x11/ogle

USE_CXX=		Yes
USE_X11=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--with-dvdcontrol=${LOCALBASE} \
			--with-fox=${LOCALBASE}

.include <bsd.port.mk>
