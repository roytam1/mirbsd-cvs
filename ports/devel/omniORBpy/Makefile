# $MirOS: ports/devel/omniORBpy/Makefile,v 1.2 2008/08/26 16:34:27 tg Exp $

CATEGORIES=		devel
COMMENT=		Python bindings for ombiORB
DISTNAME=		omniORBpy-3.3
HOMEPAGE=		http://omniorb.sourceforge.net/

# GNU LGPLv2.1
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MODULES+=		lang/python
MODPY_USE_DISTUTILS=	No

MODULES+=		devel/pkgconfig
LIB_DEPENDS+=		omniORB4::devel/omniORB

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=omniorb/}
MAKE_FILE=		GNUmakefile
USE_GMAKE=		Yes
USE_CXX=		Yes
CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--with-openssl=/usr

.include <bsd.port.mk>
