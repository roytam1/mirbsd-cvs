# $MirOS: ports/net/tor/Makefile,v 1.5 2008/03/04 02:24:14 tg Exp $
# $NetBSD: Makefile,v 1.41 2007/04/26 20:04:37 tv Exp $

COMMENT=		Anonymising overlay network for TCP
CATEGORIES=		net security
DISTNAME=		tor-0.1.2.19
DASH_VER=		1
HOMEPAGE=		http://tor.eff.org/

# 3-clause UCB-style
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		${HOMEPAGE}dist/
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--enable-eventdns \
			--enable-threads \
			--with-tor-user=_tor \
			--with-tor-group=_tor \
			--disable-gcc-warnings
# enable gcc warnings will set -Werror, this might be bad
EXTRA_XAKE_FLAGS+=	confdir=${PREFIX}/share/examples/tor

.include <bsd.port.mk>
