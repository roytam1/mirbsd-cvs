# $MirOS: ports/math/gnuplot/Makefile,v 1.5 2008/03/09 17:23:10 tg Exp $
# $OpenBSD: Makefile,v 1.25 2004/02/04 15:02:09 xsa Exp $

COMMENT=		command-driven interactive function plotting program
DISTNAME=		gnuplot-4.2.2
DASH_VER=		1
CATEGORIES=		math graphics
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=gnuplot/}
HOMEPAGE=		http://www.gnuplot.info/

PERMIT_PACKAGE_CDROM=	"no modify"
PERMIT_PACKAGE_FTP=	"no modify"
PERMIT_DISTFILES_CDROM=	"no modify"
PERMIT_DISTFILES_FTP=	Yes

FLAVOURS=		no_x11
FLAVOUR?=

MODULES+=		graphics/png
MODULES+=		devel/libreadline

CONFIGURE_STYLE=	autoconf detectheader
AUTOCONF_NEW=		Yes
MODGNU_RECURSE_DIRS=	${WRKSRC} ${WRKSRC}/lisp
CONFIGURE_ARGS+=	--without-linux-vga
CONFIGURE_ARGS+=	--without-gd
CONFIGURE_ARGS+=	--with-png
CONFIGURE_ARGS+=	--with-gnu-readline
CONFIGURE_ARGS+=	--with-lasergnu
CONFIGURE_ARGS+=	--disable-wxwidgets
NO_REGRESS=		Yes

.if ${FLAVOUR:L:Mno_x11}
CONFIGURE_ARGS+=	--without-x
.else
USE_X11=		Yes
CONFIGURE_ARGS+=	--with-x
.endif

.include <bsd.port.mk>
