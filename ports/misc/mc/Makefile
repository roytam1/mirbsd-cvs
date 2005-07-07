# $MirOS: ports/misc/mc/Makefile,v 1.2 2005/03/30 14:54:44 tg Exp $

COMMENT=		"free Norton Commander clone with many useful features"
DISTNAME=		mc-4.6.0
PKGNAME=		${DISTNAME}-3
CATEGORIES=		misc
HOMEPAGE=		http://www.ibiblio.org/mc/
MASTER_SITES=		http://www.ibiblio.org/pub/Linux/utils/file/managers/mc/
RESPONSIBLE=		Thorsten Glaser <tg@${_DOMAIN_DU_JOUR}>

# GNU General Public License, Version 2 or later
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

LIB_DEPENDS=		glib.1.2::devel/glib1

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--disable-nls --with-vfs --without-mcfs --without-x

.include <bsd.port.mk>
