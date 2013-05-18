# $MirOS: ports/devel/autoconf/2.13-o/Makefile,v 1.3 2006/02/09 09:35:43 tg Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2003/02/15 14:02:54 espie Exp $

COMMENT=			automatically configure source code on many Un*x platforms
VERSION=	2.13
DISTNAME=	autoconf-${VERSION}
PKGNAME=	autoconf-${VERSION}-2-o
CATEGORIES=	devel
MASTER_SITES=	${MASTER_SITE_GNU:=autoconf/}
HOMEPAGE=	http://www.gnu.org/software/autoconf/

# GPL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

SUFFIX=-${VERSION}-o
CONFIGURE_ARGS+=	--program-suffix=${SUFFIX}
CONFIGURE_STYLE= gnu dest
CONFIGURE_ENV=	M4=/usr/bin/m4

MAKE_FLAGS=acdatadir=${PREFIX}/share/autoconf${SUFFIX}
FAKE_FLAGS=DESTDIR=${WRKINST} acdatadir=${WRKINST}${PREFIX}/share/autoconf${SUFFIX}
SUBST_VARS=SUFFIX

post-install:
	cd ${PREFIX}/info && mv autoconf.info autoconf${SUFFIX}.info && rm standards.info

REGRESS_DEPENDS=:dejagnu-*:devel/dejagnu

.include <bsd.port.mk>
