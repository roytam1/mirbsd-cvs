# $MirOS: ports/devel/autoconf/2.13-o/Makefile,v 1.5 2009/11/21 16:52:07 tg Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2003/02/15 14:02:54 espie Exp $

COMMENT=		automatically configure source code on many Un*x platforms
VERSION=		2.13
DASH_VER=		2
DISTNAME=		autoconf-${VERSION}
PKGNAME=		autoconf-${VERSION}-${DASH_VER}-o
CATEGORIES=		devel
MASTER_SITES=		${MASTER_SITE_GNU:=autoconf/}
HOMEPAGE=		http://www.gnu.org/software/autoconf/

# GPL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

SUFFIX=			-${VERSION}-o
USE_M4=			bsd
MODULES+=		m4
B_R_DEPENDS+=		${MODM4_DEPENDS}
CONFIGURE_ARGS+=	--program-suffix=${SUFFIX}
CONFIGURE_STYLE=	gnu dest
CONFIGURE_ENV+=		M4=${M4:Q}
CONFIGURE_ENV+=		AWK=${AWK:Q}

MAKE_FLAGS=acdatadir=${PREFIX}/share/autoconf${SUFFIX}
FAKE_FLAGS=DESTDIR=${WRKINST} acdatadir=${WRKINST}${PREFIX}/share/autoconf${SUFFIX}
SUBST_VARS=SUFFIX

post-install:
	cd ${PREFIX}/info && mv autoconf.info autoconf${SUFFIX}.info && rm standards.info

REGRESS_DEPENDS=:dejagnu-*:devel/dejagnu

.include <bsd.port.mk>
