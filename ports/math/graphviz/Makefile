# $MirOS: ports/math/graphviz/Makefile,v 1.3 2006/02/09 11:12:04 tg Exp $
# $OpenBSD: Makefile,v 1.10 2004/03/04 01:48:02 naddy Exp $

IGNORE=		"might be broken, used to use Libtool"

CATEGORIES=	math devel graphics
COMMENT=			graph drawing software
PKGNAME=	graphviz-1.7.6-0
DISTFILES=	gviz176.tgz
DISTNAME=	gv1.7.6
HOMEPAGE=	http://www.research.att.com/sw/tools/graphviz/
MASTER_SITES=	${HOMEPAGE}dist/

# As long as the licence is shown, everything is fine
PERMIT_DISTFILES_FTP=	No
PERMIT_DISTFILES_CDROM=	No
PERMIT_PACKAGE_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes

CONFIGURE_STYLE=	gnu
CONFIGURE_ENV=TCLCONFIG=${LOCALBASE}/lib/tcl8.4/tclConfig.sh \
	TKCONFIG=${LOCALBASE}/lib/tk8.4/tkConfig.sh \
	LIBS=-lz
CPPFLAGS+=		-I${LOCALBASE}/include/tcl8.4 -I${LOCALBASE}/include/tk8.4

CONFIGURE_ARGS=	--with-freetypeincludedir=${X11BASE}/include/freetype2 \
		--with-pngincludedir=${LOCALBASE}/include/libpng
CONFIGURE_SCRIPT=autogen.sh
CONFIGURE_ENV+=AUTOCONF_VERSION=${AUTOCONF_VERSION}
USE_GMAKE=	Yes
USE_X11=	Yes

.include <bsd.own.mk>

ACCEPT_GRAPHVIZ_LICENSE?=No
.if ${ACCEPT_GRAPHVIZ_LICENSE:L} == "no"
post-extract:
	@echo "You must read ${WRKDIST}/COPYING first"
	@echo "To accept the license, restart the build with"
	@echo "ACCEPT_GRAPHVIZ_LICENSE=Yes"
	@exit 1
.endif

LIB_DEPENDS=	tcl84.::lang/tcl/8.4 \
		tk84.::x11/tk/8.4 \
		jpeg.62::graphics/jpeg
MODULES+=		graphics/png

BUILD_DEPENDS=	::devel/autoconf/${AUTOCONF_VERSION} \
		::devel/metaauto \
		::devel/automake

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/graphviz
	${INSTALL_DATA} ${WRKDIST}/{COPYING,MINTERMS.txt,FAQ.txt} ${PREFIX}/share/doc/graphviz

SUBST_VARS=PKGNAME

.include <bsd.port.mk>
