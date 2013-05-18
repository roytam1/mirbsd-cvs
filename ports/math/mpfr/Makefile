# $MirOS$
# $OpenBSD: Makefile,v 1.5 2008/10/27 20:45:54 naddy Exp $

COMMENT=		library for multiple-precision floating-point computations
DISTNAME=		mpfr-2.3.2
CATEGORIES=		devel math
HOMEPAGE=		http://www.mpfr.org/

# GNU (L)GPL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

EXTRACT_SUFX=		.tar.lzma
MASTER_SITES=		${HOMEPAGE}${DISTNAME}/ \
			http://www.buraphalinux.org/download/bls1.1/dvd/source/libs/mpfr/

# no interlibrary dependency, though
LIB_DEPENDS+=		gmp:gmp->=4.2.0:devel/gmp

CONFIGURE_STYLE=	autogen
AUTOCONF_NEW=		Yes
AUTOMAKE_VERSION=	1.9
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--with-gmp=${LOCALBASE:Q}

.include <bsd.port.mk>
