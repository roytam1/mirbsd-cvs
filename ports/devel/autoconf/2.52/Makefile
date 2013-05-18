# $MirOS: ports/devel/autoconf/2.52/Makefile,v 1.4 2006/09/14 00:08:02 tg Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2003/02/15 14:03:28 espie Exp $

COMMENT=		automatically configure source code on many Un*x platforms
VERSION=		2.52
DASH_VER=		1
DISTNAME=		autoconf-${VERSION}
CATEGORIES=		devel
MASTER_SITES=		${MASTER_SITE_GNU:=autoconf/}
HOMEPAGE=		http://www.gnu.org/software/autoconf/

# GPL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

SUFFIX=			-${VERSION}
MODULES+=		m4
B_R_DEPENDS+=		${MODM4_DEPENDS}
CONFIGURE_ARGS+=	--program-suffix=${SUFFIX}
CONFIGURE_STYLE=	gnu
CONFIGURE_ENV+=		M4=${M4:Q}
CONFIGURE_ENV+=		AWK=${AWK:Q}
MAKE_FLAGS=pkgdatadir=${PREFIX}/share/autoconf${SUFFIX}
FAKE_FLAGS=${MAKE_FLAGS} DESTDIR=${WRKINST}
SUBST_VARS=SUFFIX

post-install:
	cd ${PREFIX}/info && mv autoconf.info autoconf${SUFFIX}.info && rm standards.info

.include <bsd.port.mk>
