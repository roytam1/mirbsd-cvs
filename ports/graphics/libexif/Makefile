# $MirOS$
# $OpenBSD: Makefile,v 1.3 2003/01/21 02:21:59 naddy Exp $

COMMENT=	"extract digital camera info tags from JPEG images"
DISTNAME=	libexif-0.6.12
CATEGORIES=	graphics
HOMEPAGE=	http://sourceforge.net/projects/libexif/

# GNU LGPL
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=libexif/}

SEPARATE_BUILD=		concurrent
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
RUN_DEPENDS=		::devel/pkgconfig
BUILD_DEPENDS=		${RUN_DEPENDS}
MODULES=		devel/gettext

.include <bsd.port.mk>
