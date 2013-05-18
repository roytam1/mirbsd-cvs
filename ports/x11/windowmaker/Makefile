# $MirOS: ports/x11/windowmaker/Makefile,v 1.8 2006/03/06 23:19:04 tg Exp $
# $OpenBSD: Makefile,v 1.57 2003/08/16 19:06:07 tedu Exp $

COMMENT=		'window manager that emulates NEXTSTEP(tm)'
COMMENT-lang=		"language subpackage for Window Maker"

V=			0.92.0
PL=			1
DISTNAME=		WindowMaker-${V}
PKGNAME=		${DISTNAME:L}-${PL}
CATEGORIES=		x11 x11/windowmaker
HOMEPAGE=		http://www.windowmaker.org/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_WINDOWMAKER:=source/release/}
EXTRACT_SUFX=		.tar.bz2

NO_REGRESS=		Yes
USE_X11=		Yes
CONFIGURE_STYLE=	autogen
AUTOMAKE_VERSION=	1.4
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--enable-static \
			--with-pixmapdir="${PREFIX}/share/WindowMaker/Pixmaps" \
			--with-nlsdir="${LOCALBASE}/share/locale" \
			--disable-dependency-tracking \
			--enable-gnome \
			--enable-kde
CONFIGURE_ENV=		LINGUAS='bg cs da de el es et fi fr gl hr hu it ja ko ms nl no pl pt ro ru sk sv tr zh_CN zh_TW'

MULTI_PACKAGES= 	-lang

.for i in ${MULTI_PACKAGES}
PKGNAME$i=      	windowmaker${i}-${V}-${PL}
.endfor

SUBPACKAGE?=

.if defined(PACKAGING) && !empty(SUBPACKAGE)
RUN_DEPENDS=		:windowmaker->=0.90.0:x11/windowmaker
.else
MODULES=		devel/gettext graphics/png
LIB_DEPENDS=		jpeg::graphics/jpeg \
			tiff::graphics/tiff \
			ungif::graphics/libungif
USE_CXX=		Yes
.endif

post-patch:
	@perl -pi -e "s|%%%PREFIX%%%|${PREFIX}|g" \
		${WRKSRC}/WINGs/wapplication.c \
		${WRKSRC}/WPrefs.app/Menu.c \
		${WRKSRC}/WPrefs.app/Paths.c
# Rename wrongly named locale files
	@mv ${WRKSRC}/WindowMaker/menu.cz ${WRKSRC}/WindowMaker/menu.cs
	@mv ${WRKSRC}/WindowMaker/menu.se ${WRKSRC}/WindowMaker/menu.sv

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/WindowMaker/Sounds
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples
	mv ${WRKINST}/etc/WindowMaker ${PREFIX}/share/examples

.include <bsd.port.mk>
