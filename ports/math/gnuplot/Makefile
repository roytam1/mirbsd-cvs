# $MirOS: ports/math/gnuplot/Makefile,v 1.3 2006/09/14 00:10:55 tg Exp $
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

FLAVORS=	no_x11
FLAVOR?=

MODULES+=		graphics/png

CONFIGURE_STYLE= gnu
CONFIGURE_ARGS+=	--without-linux-vga
CONFIGURE_ARGS+=	--without-gd
CONFIGURE_ARGS+=	--with-png
CONFIGURE_ARGS+=	--with-gnu-readline
CONFIGURE_ARGS+=	--with-lasergnu
CONFIGURE_ARGS+=	--disable-wxwidgets
NO_REGRESS=	Yes

.if ${FLAVOR:L:Mno_x11}
CONFIGURE_ARGS+= --without-x
.else
USE_X11=	Yes
CONFIGURE_ARGS+= --with-x
.endif

.include <bsd.port.mk>
