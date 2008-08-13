# $MirOS$

CATEGORIES=		devel
COMMENT=		Python bindings for ombiORB
DISTNAME=		omniORBpy-3.2
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

#BINOWN!=		id -un
#BINGRP!=		id -gn
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=omniorb/}
MAKE_FILE=		GNUmakefile
USE_GMAKE=		Yes
USE_CXX=		Yes
CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes
#CONFIGURE_ENV+=		PYTHON=${LOCALBASE:Q}/bin/python${MODPY_VERSION}
CONFIGURE_ARGS+=	--with-openssl=/usr
#CONFIGURE_ARGS+=	--with-omniORB-config=${SYSCONFDIR:Q}/omniORB.cfg
#EXTRA_XAKE_FLAGS+=	CDEBUGFLAGS=${CFLAGS:Q} CXXDEBUGFLAGS=${CXXFLAGS:Q}

.include <bsd.port.mk>
