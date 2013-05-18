# $MirOS$
# $OpenBSD: Makefile,v 1.19 2008/10/26 23:05:41 naddy Exp $

COMMENT=		library for arbitrary precision arithmetic
DISTNAME=		gmp-4.2.4
CATEGORIES=		devel math
HOMEPAGE=		http://gmplib.org/

# GNU LGPLv3
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		ftp://ftp.gmplib.org/pub/ \
			${MASTER_SITE_GNU:=gmp/}

USE_CXX=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--enable-cxx \
			--without-readline

post-extract:
	-rm -f ${WRKSRC}/doc/*.info{,-*}

.include <bsd.port.mk>
