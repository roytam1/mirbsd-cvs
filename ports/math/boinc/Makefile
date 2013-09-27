# $MirOS: ports/math/boinc/Makefile,v 1.2 2008/10/18 21:10:00 tg Exp $

COMMENT=		Berkeley Open Infrastructure for Network Computing client
VERSION=		5.10.45
DASH_VER=		1
DISTNAME=		boinc-core-release-${VERSION}
PKGNAME=		boinc-client-${VERSION}-${DASH_VER}
CATEGORIES=		math net
HOMEPAGE=		http://boinc.berkeley.edu/

# GNU LGPLv2.1
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

# SVN distfile: https://boinc.berkeley.edu/svn/tags/boinc_core_release_5_10_45
MASTER_SITES=		${_MASTER_SITE_MIRBSD}
EXTRACT_SUFX=		.mcz
WRKDIST=		${WRKDIR}/${DISTNAME:S/./_/g:S/-/_/g}

LIB_DEPENDS+=		curl:curl->=7.17.1:net/curl
LIB_DEPENDS+=		jpeg.62::graphics/jpeg
LIB_DEPENDS+=		glut::graphics/glut

CONFIGURE_STYLE=	autogen
AUTOMAKE_VERSION=	1.9
AUTOCONF_NEW=		Yes
USE_CXX=		Yes
USE_X11=		Yes
CONFIGURE_ENV+=		MYSQL_CONFIG=false
CONFIGURE_ARGS+=	--disable-server
CONFIGURE_ARGS+=	--enable-client \
			${CONFIGURE_SHARED} \
			--enable-static \
			--with-libcurl=${LOCALBASE:Q} \
			--with-ssl \
			--with-x \
			--without-apple-opengl-framework \
			--with-wxdir=junk \
			--with-wx-config=false \
			--enable-unicode \
			--disable-static-linkage

.if (${OStype} == "Darwin") || (${OStype} == "Interix")
ERRORS+=		"not yet ported to ${OStype}"
.elif ${MACHINE_ARCH} == "i386"
CONFIGURE_ARGS+=	--with-boinc-alt-platform=i686-pc-linux-gnu
.endif

.include <bsd.port.mk>
