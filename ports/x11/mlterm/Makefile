# $MirOS: ports/x11/mlterm/Makefile,v 1.4 2005/04/11 15:57:36 tg Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2004/06/04 17:13:26 naddy Exp $

NOT_FOR_PLATFORM=	*:*:vax

COMMENT=			color terminal emulator with transparency and unicode support
DISTNAME=	mlterm-2.8.0
CATEGORIES=	x11

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

HOMEPAGE=	http://mlterm.sourceforge.net/
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=mlterm/}
PATCHFILES=	${DISTNAME}pl1.tar.gz

USE_X11=	Yes
#MODULES=	gettext		# links statically (lib-link.m4 bug)

LIB_DEPENDS=	gtk.1.2::x11/gtk+1

MODGNU_CONFIG_GUESS_DIRS= ${WRKSRC} ${WRKSRC}/kiklib ${WRKSRC}/mkf
CONFIGURE_STYLE=autoconf no-autoheader
CONFIGURE_ARGS=	${CONFIGURE_SHARED} --enable-anti-alias --enable-utmp
CONFIGURE_ARGS+=--disable-nls

CPPFLAGS+=	-I${X11BASE}/include/freetype2

.if defined(NO_SHARED_LIBS)
CONFIGURE_ENV+=	"X_EXTRA_LIBS=\"/usr/X11R6/lib/libXft.a \
		/usr/X11R6/lib/libXfont.a \
                /usr/X11R6/lib/libfontconfig.a /usr/X11R6/lib/libX11.a \
                /usr/X11R6/lib/libfreetype.a /usr/X11R6/lib/libexpat.a \
                /usr/X11R6/lib/libXrender.a /usr/X11R6/lib/libXext.a\""
.endif

NO_REGRESS=	Yes

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/mlterm
	${INSTALL_DATA} ${WRKSRC}/etc/[a-z]* ${PREFIX}/share/examples/mlterm

.include <bsd.port.mk>
