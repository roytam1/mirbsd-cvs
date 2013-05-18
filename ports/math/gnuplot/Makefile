# $MirOS: ports/math/gnuplot/Makefile,v 1.4 2007/10/31 21:21:16 bsiegert Exp $
# $OpenBSD: Makefile,v 1.25 2004/02/04 15:02:09 xsa Exp $

COMMENT=	command-driven interactive function plotting program

DISTNAME=	gnuplot-4.2.2
CATEGORIES=	math graphics
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=gnuplot/}

HOMEPAGE=	http://www.gnuplot.info/

PERMIT_PACKAGE_CDROM=	"no modify"
PERMIT_PACKAGE_FTP=	"no modify"
PERMIT_DISTFILES_CDROM=	"no modify"
PERMIT_DISTFILES_FTP=	Yes

FLAVOURS=	no_x11
FLAVOUR?=

MODULES+=		graphics/png

CONFIGURE_STYLE= gnu
CONFIGURE_ARGS+=	--without-linux-vga
CONFIGURE_ARGS+=	--without-gd
CONFIGURE_ARGS+=	--with-png
CONFIGURE_ARGS+=	--with-gnu-readline
CONFIGURE_ARGS+=	--with-lasergnu
CONFIGURE_ARGS+=	--disable-wxwidgets
NO_REGRESS=	Yes

.if ${FLAVOUR:L:Mno_x11}
CONFIGURE_ARGS+= --without-x
.else
USE_X11=	Yes
CONFIGURE_ARGS+= --with-x
.endif

.include <bsd.port.mk>
