# $MirOS$
# Original from: Antoine Jacoutot <ajacoutot@lphp.org>

COMMENT=	"API for accessing scanners, frontends"

DISTNAME=	sane-frontends-1.0.12
CATEGORIES=	graphics

MASTER_SITES=	ftp://ftp.sane-project.org/pub/sane/${DISTNAME}/ \
		http://gd.tuwien.ac.at/hci/sane/${DISTNAME}/ \
		ftp://gd.tuwien.ac.at/hci/sane/${DISTNAME}/

HOMEPAGE=	http://www.sane-project.org/

# GPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES=	devel/gettext
LIB_DEPENDS=	gtk.1.2,gdk.1.2::x11/gtk+

USE_X11=		Yes
USE_GMAKE=		Yes
AUTOCONF_NEW=	Yes
CONFIGURE_STYLE=autoconf

CONFIGURE_ARGS+=	--disable-gtk2

FLAVORS=	gimp
FLAVOR?=

.if ${FLAVOR:L} == "gimp"
LIB_DEPENDS+=		gimp::graphics/gimp/stable
CONFIGURE_ENV+=		CPPFLAGS="-I${LOCALBASE}/include -I${LOCALBASE}/include/gimp-1.2" \
			LDFLAGS="-L${LOCALBASE}/lib"
CONFIGURE_ARGS+=	--enable-gimp12
.else
CONFIGURE_ENV+=		CPPFLAGS="-I${LOCALBASE}/include" \
			LDFLAGS="-L${LOCALBASE}/lib"
CONFIGURE_ARGS+=	--disable-gimp
.endif

.include <bsd.port.mk>
