# $MirOS$

# for gajim-0.14.1
#IGNORE+=		'dependency py-gtk2 too old (need 2.16.0)'
#IGNORE+=		'py-gtk2=2.16.0 depends on gtk+2 2.16.0 we have 2.12'

COMMENT=		jabber client written in pygtk
CATEGORIES=		net x11/gnome
DISTNAME=		gajim-0.13.4
HOMEPAGE=		http://gajim.org/

# GNU GPLv3-only
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		${HOMEPAGE}/downloads/0.13/

USE_GMAKE=		Yes

MODULES+=		lang/python
MODPY_USE_DISTUTILS=	No

# mostly for its dependencies
MODULES+=		devel/pkgconfig

BUILD_DEPENDS+=		:intltool->=0.35.0:textproc/intltool
B_R_DEPENDS+=		::security/py-crypto
B_R_DEPENDS+=		:py-openssl->=0.9:security/py-openssl
B_R_DEPENDS+=		:py-gtk2->=2.12.0:x11/py-gtk

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
AUTOCONF_VERSION=	2.62
CONFIGURE_ARGS+=	--disable-nls

.include <bsd.port.mk>
