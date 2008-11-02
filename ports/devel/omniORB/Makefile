# $MirOS: ports/devel/omniORB/Makefile,v 1.2 2008/08/26 15:37:25 tg Exp $

CATEGORIES=		devel
COMMENT=		ORB implementing CORBA 2.6, with Python interface
DISTNAME=		omniORB-4.1.3
HOMEPAGE=		http://omniorb.sourceforge.net/

# GNU GPLv2
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MODULES+=		lang/python
MODPY_USE_DISTUTILS=	No

MODULES+=		devel/pkgconfig

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=omniorb/}
MAKE_FILE=		GNUmakefile
USE_GMAKE=		Yes
USE_CXX=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
MODSIMPLE_USE_INSTALL=	${INSTALL} -c
CONFIGURE_ENV+=		PYTHON=${LOCALBASE:Q}/bin/python${MODPY_VERSION}
CONFIGURE_ARGS+=	--with-openssl=/usr
CONFIGURE_ARGS+=	--with-omniORB-config=${SYSCONFDIR:Q}/omniORB.cfg
EXTRA_XAKE_FLAGS+=	CDEBUGFLAGS=${CFLAGS:Q} CXXDEBUGFLAGS=${CXXFLAGS:Q}

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/omniORB/
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/omniORB/
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/omniORB/omniORB
	${INSTALL_DATA} ${WRKSRC}/sample.cfg ${PREFIX}/share/examples/omniORB/
	${INSTALL_DATA} ${WRKSRC}/doc/*.html ${PREFIX}/share/doc/omniORB/
	${INSTALL_DATA} ${WRKSRC}/doc/*.pdf ${PREFIX}/share/doc/omniORB/
	${INSTALL_DATA} ${WRKSRC}/doc/*.ps ${PREFIX}/share/doc/omniORB/
	${INSTALL_DATA} ${WRKSRC}/doc/omniORB/* ${PREFIX}/share/doc/omniORB/omniORB/
	${INSTALL_MAN} ${WRKSRC}/man/man1/* ${PREFIX}/man/man1/

.include <bsd.port.mk>
