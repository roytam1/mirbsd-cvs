# $OpenBSD: Makefile,v 1.3 2004/04/18 00:41:03 jolan Exp $

COMMENT=	"free MPEG-2 video stream decoder"
DISTNAME=	mpeg2dec-0.4.0b
PKGNAME=	${DISTNAME:S/mpeg2dec/libmpeg2/}-0
CATEGORIES=	graphics x11
MASTER_SITES=	${HOMEPAGE}files/

HOMEPAGE=	http://libmpeg2.sourceforge.net/


# GPL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

USE_X11=	Yes
MODULES+=		devel/pkgconfig

WRKDIST=${WRKDIR}/mpeg2dec-0.4.0

CONFIGURE_STYLE=gnu
CONFIGURE_ENV=	LIBS="-lX11 -lXext -lXv"
CONFIGURE_ARGS+=${CONFIGURE_SHARED} --disable-sdl

.include <bsd.port.mk>
