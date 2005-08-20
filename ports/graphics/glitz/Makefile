# $MirOS$

COMMENT=		"OpenGL image compositing library"

DISTNAME=		glitz-0.4.3
CATEGORIES=		graphics

HOMEPAGE=		http://www.freedesktop.org/Software/glitz

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://cairographics.org/snapshots/

USE_X11=		Yes

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes

BUILD_DEPENDS+=		::devel/pkgconfig

.include <bsd.own.mk>

.if ${OStype} == "Darwin"
PSEUDO_FLAVORS=		agl
FLAVOR?=		agl
.endif

.include <bsd.port.mk>
