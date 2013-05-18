# $MirOS: ports/net/ctorrent/Makefile,v 1.1 2006/02/07 23:54:46 tg Exp $
# $NetBSD: Makefile,v 1.5 2005/04/11 21:46:45 tv Exp $

CATEGORIES=		net
COMMENT=			BitTorrent client for the console
DISTNAME=		ctorrent-1.3.4
HOMEPAGE=		http://ctorrent.sourceforge.net/
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=ctorrent/}
EXTRACT_SUFX=		.tar.bz2
RESPONSIBLE=		Thomas E. Spanjaard <tgen@netphreax.net>

# GPLv2
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

USE_CXX=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes

.include <bsd.port.mk>
