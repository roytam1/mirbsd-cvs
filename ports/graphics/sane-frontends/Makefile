# $MirOS: ports/graphics/sane-frontends/Makefile,v 1.3 2006/02/09 11:11:52 tg Exp $
# Original from: Antoine Jacoutot <ajacoutot@lphp.org>

COMMENT=			API for accessing scanners, frontends

DISTNAME=	sane-frontends-1.0.12
CATEGORIES=	graphics

MASTER_SITES=	ftp://ftp.sane-project.org/pub/sane/${DISTNAME}/ \
		http://gd.tuwien.ac.at/hci/sane/${DISTNAME}/ \
		ftp://gd.tuwien.ac.at/hci/sane/${DISTNAME}/

HOMEPAGE=	http://www.sane-project.org/

# GPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES=	devel/gettext
LIB_DEPENDS=	gtk.1.2,gdk.1.2::x11/gtk+1

USE_X11=		Yes
USE_GMAKE=		Yes
AUTOCONF_NEW=	Yes
CONFIGURE_STYLE=autoconf

CONFIGURE_ARGS+=	--disable-gtk2
CONFIGURE_ARGS+=	--disable-gimp

.include <bsd.port.mk>
