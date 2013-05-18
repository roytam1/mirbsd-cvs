# $OpenBSD: Makefile,v 1.5 2002/12/29 20:08:46 fgsch Exp $

COMMENT=	"MPEG and VCD video playback in XMMS"

VERSION=	0.3.5
DISTNAME=	smpeg-xmms-${VERSION}
PKGNAME=	xmms-smpeg-${VERSION}-0
CATEGORIES=	graphics
HOMEPAGE=	http://www.xmms.org/files/plugins/smpeg-xmms/


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${HOMEPAGE} \
		http://mirror.csoft.org/smpeg-xmms/

LIB_DEPENDS=	xmms.2::audio/xmms \
		smpeg.1.3::devel/smpeg

USE_X11=	Yes
USE_CXX=	Yes

CONFIGURE_STYLE= gnu
CONFIGURE_ARGS=	${CONFIGURE_SHARED} \
		--with-glib-prefix=${LOCALBASE} \
		--with-gtk-prefix=${LOCALBASE} \
		--with-sdl-prefix=${LOCALBASE} \
		--with-xmms-prefix=${LOCALBASE}

.include <bsd.port.mk>
