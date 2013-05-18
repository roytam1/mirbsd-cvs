# $MirOS: ports/math/galculator/Makefile,v 1.5 2006/09/14 00:10:55 tg Exp $
# $OpenBSD: Makefile,v 1.6 2004/05/27 20:10:19 naddy Exp $

COMMENT=	GTK2-based scientific calculator

DISTNAME=	galculator-1.3.1
CATEGORIES=	math
HOMEPAGE=	http://galculator.sourceforge.net/


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=galculator/}

LIB_DEPENDS=	glade-2.0.0.0::devel/libglade
BUILD_DEPENDS=	::textproc/intltool
MODULES=	devel/pkgconfig

USE_GMAKE=	Yes
USE_CXX=	Yes
USE_X11=	Yes
CONFIGURE_STYLE=autoconf
AUTOCONF_NEW=	Yes

.include <bsd.port.mk>
