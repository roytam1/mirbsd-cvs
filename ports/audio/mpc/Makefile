# $MirOS: ports/audio/mpc/Makefile,v 1.2 2005/05/21 02:00:46 bsiegert Exp $

COMMENT=			client for Music Play Daemon
CATEGORIES=		audio multimedia net
DISTNAME=		mpc-0.11.2
HOMEPAGE=		http://www.musicpd.org/
MASTER_SITES=		http://mercury.chem.pitt.edu/~shank/

# GNU GPLv2
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--disable-iconv

.include <bsd.port.mk>
