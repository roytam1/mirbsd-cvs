# $MirOS: ports/devel/libgtop/Makefile,v 1.6 2007/06/26 21:23:29 bsiegert Exp $
# $OpenBSD: Makefile,v 1.14 2004/12/11 17:41:52 marcm Exp $

COMMENT=		portable library for obtaining system information

VSN=			2.14.6
DISTNAME=		libgtop-${VSN}
PKGNAME=		libgtop2-${VSN}-${DASH_VER}
CATEGORIES=		devel x11/gnome

HOMEPAGE=		http://www.gnome.org
MASTER_SITES=		${MASTER_SITE_GNOME:=sources/libgtop/2.14/}
EXTRACT_SUFX=		.tar.bz2

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES=		devel/gettext devel/pkgconfig
LIB_DEPENDS=		glib-2.0.0.0::devel/glib \
			popt::devel/popt

USE_GMAKE=		Yes
USE_CXX=		Yes
CONFIGURE_STYLE= 	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+= 	${CONFIGURE_SHARED}

post-install:
	@chgrp kmem ${PREFIX}/bin/libgtop_server2
	@chmod 2555 ${PREFIX}/bin/libgtop_server2

.include <bsd.port.mk>
