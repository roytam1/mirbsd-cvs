# $OpenBSD: Makefile,v 1.19 2002/12/29 20:08:46 fgsch Exp $

COMMENT=			creating & editing GIF images and animations

DISTNAME=	gifsicle-1.30
CATEGORIES=    	graphics


PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

HOMEPAGE=	http://www.lcdf.org/gifsicle/

MASTER_SITES=	${HOMEPAGE}/ \
		ftp://ftp.lcdf.org/pub/ \
		ftp://ftp.lcdf.org/pub/OLD-VERSIONS/

FLAVOURS=	no_x11
FLAVOUR?=

CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS=		--enable-gifdiff


.if ${FLAVOUR:L:Mno_x11}
CONFIGURE_ARGS+=	--disable-gifview
.else
USE_X11=	Yes
.endif

.include <bsd.port.mk>
