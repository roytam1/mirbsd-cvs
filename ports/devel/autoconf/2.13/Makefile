# $MirOS: ports/devel/autoconf/2.13/Makefile,v 1.9 2008/04/05 18:03:27 tg Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2003/02/15 14:02:54 espie Exp $

COMMENT=		automatically configure source code on many Un*x platforms
SUFFIX=			-2.13
DASH_VER=		20080405
DISTNAME=		autoconf${SUFFIX}
CATEGORIES=		devel
MASTER_SITES=		${MASTER_SITE_GNU:=autoconf/}
HOMEPAGE=		http://dickey.his.com/autoconf/autoconf.html

# GNU GPLv2
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MODULES+=		m4
B_R_DEPENDS+=		${MODM4_DEPENDS}
CONFIGURE_ARGS+=	--program-suffix=${SUFFIX}
CONFIGURE_STYLE=	gnu dest
CONFIGURE_ENV+=		M4=${M4:Q}
CONFIGURE_ENV+=		AWK=${AWK:Q}

MAKE_FLAGS+=		acdatadir=${PREFIX}/share/autoconf${SUFFIX}
FAKE_FLAGS+=		DESTDIR=${WRKINST} \
			acdatadir=${WRKINST}${PREFIX}/share/autoconf${SUFFIX}
SUBST_VARS+=		SUFFIX

pre-build:
	print '/@MIRPORTS_DASHVER@/s//${DASH_VER}/\nwq' | \
	    ed -s ${WRKSRC}/acgeneral.m4

post-install:
	cd ${PREFIX}/info && mv autoconf.info autoconf${SUFFIX}.info

REGRESS_DEPENDS+=	:dejagnu-*:devel/dejagnu

.include <bsd.port.mk>
