# $MirOS: ports/graphics/icon-naming-utils/Makefile,v 1.1 2007/06/21 17:47:10 bsiegert Exp $

COMMENT=		icon naming utilities from Tango project

VERSION=		0.8.2
DASH_VER=		1
DISTNAME=		icon-naming-utils-${VERSION}
CATEGORIES=		x11 x11/gnome

HOMEPAGE=		http://tango.freedesktop.org/Tango_Icon_Library
MASTER_SITES=		http://tango-project.org/releases/


# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

B_R_DEPENDS+=		::textproc/p5-XML-Simple

MODULES=		devel/pkgconfig

CONFIGURE_STYLE= 	gnu
USE_GMAKE=		Yes

.include <bsd.port.mk>
