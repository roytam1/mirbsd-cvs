# $MirOS: ports/net/openvpn/Makefile,v 1.16 2010/09/21 21:23:56 tg Exp $
# $OpenBSD: Makefile,v 1.2 2003/12/30 21:29:53 sturm Exp $

COMMENT=		easy-to-use, robust, highly configurable VPN solution
DISTNAME=		openvpn-2.3.7
CATEGORIES=		net security
HOMEPAGE=		https://openvpn.net/index.php/open-source.html
MASTER_SITES=		http://swupdate.openvpn.org/community/releases/

# GNU GPLv2-only with OpenSSL exception
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=	Yes

FLAVOURS=		no_lzo static
FLAVOUR?=

.if !${FLAVOUR:L:Mno_lzo}
.  if !${FLAVOUR:L:Mstatic}
LIB_DEPENDS+=		lzo2::archivers/lzo
RUN_DEPENDS+=		:lzo->=2.*:archivers/lzo
.  endif
BUILD_DEPENDS+=		:lzo->=2.*:archivers/lzo
.endif

.if ${FLAVOUR:L:Mstatic}
LDSTATIC=		-static
.endif

USE_GMAKE=		Yes
CONFIGURE_STYLE=	autogen
AUTOCONF_NEW=		Yes
AUTOMAKE_VERSION=	1.9
.if ${FLAVOUR:L:Mno_lzo}
CONFIGURE_ARGS+=	--disable-lzo --enable-lzo-stub
.else
CONFIGURE_ARGS+=	--with-lzo-headers=${LOCALBASE:Q}/include \
			--with-lzo-lib=${LOCALBASE:Q}/lib
.endif
CONFIGURE_ARGS+=	--enable-password-save

post-extract:
	-rm -f ${WRKSRC:Q}/m4/{lt,libtool}*

.include <bsd.port.mk>
