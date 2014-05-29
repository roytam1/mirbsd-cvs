# $MirOS: ports/devel/gmp/Makefile,v 1.7 2008/11/10 05:15:31 tg Exp $
# $OpenBSD: Makefile,v 1.19 2008/10/26 23:05:41 naddy Exp $

COMMENT=		library for arbitrary precision arithmetic
DISTNAME=		gmp-6.0.0
CATEGORIES=		devel math
HOMEPAGE=		https://gmplib.org/

# GNU LGPLv3 or GNU GPLv2
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

# 6.0.0a only doc changes
DISTFILES=		${DISTNAME}a${EXTRACT_SUFX}

EXTRACT_SUFX=		.tar.xz
MASTER_SITES=		https://gmplib.org/download/gmp/ \
			${MASTER_SITE_GNU:=gmp/}

CONFIGURE_STYLE=	autogen
AUTOCONF_NEW=		Yes
AUTOMAKE_VERSION=	1.9
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--disable-cxx \
			--without-readline
CC_FOR_BUILD=		${CC} ${CPPFLAGS} ${CFLAGS}
CONFIGURE_ENV+=		CC_FOR_BUILD=${CC_FOR_BUILD:Q}

post-extract:
	-rm -f ${WRKSRC}/doc/*.info{,-*}

.include <bsd.port.mk>
