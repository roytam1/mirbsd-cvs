# $MirOS: ports/audio/ncmpc/Makefile,v 1.1 2005/05/21 03:09:15 bsiegert Exp $

COMMENT=			ncurses client for Music Play Daemon
CATEGORIES=		audio multimedia net
DISTNAME=		ncmpc-0.11.1
HOMEPAGE=		http://www.musicpd.org/
MASTER_SITES=		http://hem.bredband.net/kaw/ncmpc/files/

# GNU GPLv2
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

LIB_DEPENDS=		glib-2.0.0.0::devel/glib
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
MODULES=		devel/gettext

.include <bsd.port.mk>
