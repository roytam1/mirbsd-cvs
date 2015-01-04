# $MirOS: ports/www/dillo/v2/Makefile,v 1.4 2010/02/21 20:08:41 bsiegert Exp $
# $OpenBSD: Makefile,v 1.18 2004/02/26 13:43:26 couderc Exp $

COMMENT=		Fast and lightweight web browser
DISTNAME=		dillo-2.1.1
DASH_VER=		1
CATEGORIES=     	www
HOMEPAGE=		http://www.dillo.org/
RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

# GPL
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
AUTOCONF_NEW=		Yes
#AUTOMAKE_VERSION=	1.9

CONFIGURE_ARGS+=	--enable-cookies
CONFIGURE_ARGS+=	--enable-ipv6
CONFIGURE_ARGS+=	--disable-threaded-dns
CONFIGURE_ARGS+=	--enable-ssl

post-install:
	mv ${WRKINST:Q}/${SYSCONFDIR:Q}/dillo ${PREFIX:Q}/share/examples/

.include <bsd.port.mk>
