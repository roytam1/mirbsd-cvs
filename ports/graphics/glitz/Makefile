# $MirOS: ports/graphics/glitz/Makefile,v 1.3 2006/08/26 23:34:12 tg Exp $

COMMENT=			OpenGL image compositing library

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
MODULES+=		devel/pkgconfig

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes

.include <bsd.own.mk>

.if ${MACHINE_OS} == "Darwin"
PSEUDO_FLAVORS=		agl
FLAVOR?=		agl
.endif

.include <bsd.port.mk>
