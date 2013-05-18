# $MirOS: ports/security/dsniff/Makefile,v 1.2 2006/09/14 00:12:57 tg Exp $
# $OpenBSD: Makefile,v 1.32 2004/05/07 15:28:31 naddy Exp $

COMMENT=			sniffing tools for penetration testing
DISTNAME=		dsniff-2.3
CATEGORIES=		security
MASTER_SITES=		http://monkey.org/~dugsong/dsniff/
HOMEPAGE=		http://www.monkey.org/~dugsong/dsniff/
BUILD_DEPENDS=		::net/libnids
LIB_DEPENDS=		net::net/libnet

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	autoconf

FLAVOURS=		no_x11
FLAVOUR?=

.if ${FLAVOUR:L} == "no_x11"
CONFIGURE_ARGS+=	--without-x
.else
USE_X11=		Yes
.endif

NO_REGRESS=		Yes

FAKE_FLAGS=		install_prefix="${WRKINST}"

.include <bsd.port.mk>
