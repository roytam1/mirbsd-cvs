# $MirOS: ports/math/mpfr/Makefile,v 1.1 2008/11/10 05:15:34 tg Exp $
# $OpenBSD: Makefile,v 1.5 2008/10/27 20:45:54 naddy Exp $

COMMENT=		library for multiple-precision floating-point computations
DISTNAME=		mpfr-2.4.2
CATEGORIES=		devel math
HOMEPAGE=		http://www.mpfr.org/

# GNU (L)GPL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

DIST_SUBDIR=		${DISTNAME}
PATCHFILES+=		patch01 patch02 patch03
PATCHFILES+=		454393:0
PATCH_DIST_STRIP=	-p1
EXTRACT_SUFX=		.tar.xz
MASTER_SITES=		${HOMEPAGE}${DISTNAME}/
MASTER_SITES0=		https://bugzilla.redhat.com/attachment.cgi?id=

# no interlibrary dependency, though
LIB_DEPENDS+=		gmp:gmp->=4.2.3:devel/gmp

CONFIGURE_STYLE=	autogen
AUTOCONF_NEW=		Yes
AUTOMAKE_VERSION=	1.9
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--with-gmp=${LOCALBASE:Q}

post-install:
	mv ${PREFIX:Q}/share/doc/mpfr/examples \
	    ${PREFIX:Q}/share/examples/mpfr

.include <bsd.port.mk>
