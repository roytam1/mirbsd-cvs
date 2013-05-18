# $MirOS: ports/devel/autoconf/2.13/Makefile,v 1.4 2005/07/07 21:18:53 bsiegert Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2003/02/15 14:02:54 espie Exp $

COMMENT=	"automatically configure source code on many Un*x platforms"
SUFFIX=		-2.13
DISTNAME=	autoconf${SUFFIX}
PKGNAME=	autoconf${SUFFIX}.20050228-1
CATEGORIES=	devel
MASTER_SITES=	${MASTER_SITE_GNU:=autoconf/}
HOMEPAGE=	http://dickey.his.com/autoconf/autoconf.html

# GNU GPLv2
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

CONFIGURE_ARGS+=--program-suffix=${SUFFIX}
CONFIGURE_STYLE=gnu dest
CONFIGURE_ENV=	M4=/usr/bin/m4

MAKE_FLAGS+=	acdatadir=${PREFIX}/share/autoconf${SUFFIX}
FAKE_FLAGS+=	DESTDIR=${WRKINST} \
		acdatadir=${WRKINST}${PREFIX}/share/autoconf${SUFFIX}
SUBST_VARS+=	SUFFIX

post-install:
	cd ${PREFIX}/info && mv autoconf.info autoconf${SUFFIX}.info

REGRESS_DEPENDS+=	:dejagnu-*:devel/dejagnu

.include <bsd.port.mk>
