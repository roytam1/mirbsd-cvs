# $MirOS: ports/graphics/glitz/Makefile,v 1.5 2007/03/31 22:02:00 tg Exp $

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

.include <mirports.sys.mk>

.if ${MACHINE_OS} == "Darwin"
PSEUDO_FLAVOURS=		agl
FLAVOUR?=		agl
.endif

.include <bsd.port.mk>
