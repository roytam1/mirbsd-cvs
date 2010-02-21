# $MirOS: ports/www/dillo/v2/Makefile,v 1.3 2009/08/24 16:54:22 tg Exp $
# $OpenBSD: Makefile,v 1.18 2004/02/26 13:43:26 couderc Exp $

COMMENT=		Fast and lightweight web browser
VERSION=		2.2
DISTNAME=		dillo-${VERSION}
DASH_VER=		0
CATEGORIES=     	www
HOMEPAGE=		http://www.dillo.org/
RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

# GPL license
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${HOMEPAGE}download/

EXTRACT_SUFX=		.tar.bz2

LIB_DEPENDS+=		fltk2,fltk2_images::x11/fltk2
RUN_DEPENDS+=		::net/wget

#USE_GMAKE=		Yes
USE_X11=		Yes
USE_CXX=		Yes
#CONFIGURE_STYLE=	autogen
CONFIGURE_STYLE=	autoconf
AUTOCONF_VERSION=	2.62
#AUTOMAKE_VERSION=	1.9

CONFIGURE_ARGS+=	--enable-cookies
CONFIGURE_ARGS+=	--enable-ipv6
CONFIGURE_ARGS+=	--disable-threaded-dns
CONFIGURE_ARGS+=	--enable-ssl

post-install:
	mv ${WRKINST:Q}/${SYSCONFDIR:Q}/dillo ${PREFIX:Q}/share/examples/

.include <bsd.port.mk>
