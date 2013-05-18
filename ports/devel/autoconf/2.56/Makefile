# $MirOS: ports/devel/autoconf/2.56/Makefile,v 1.2 2006/09/14 00:08:03 tg Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2003/06/24 23:03:54 espie Exp $

COMMENT=		automatically configure source code on many Un*x platforms
DISTNAME=		autoconf-2.56
CATEGORIES=		devel
MASTER_SITES=		${MASTER_SITE_GNU:=autoconf/}
HOMEPAGE=		http://www.gnu.org/software/autoconf/

# GPL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

BUILD_DEPENDS=		:help2man-*:devel/help2man

SUFFIX=			-2.56
MODULES+=		m4
B_R_DEPENDS+=		${MODM4_DEPENDS}
CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	--program-suffix=${SUFFIX} \
			--without-lispdir
CONFIGURE_ENV+=		M4=${M4:Q}
CONFIGURE_ENV+=		AWK=${AWK:Q}
MAKE_FLAGS=		pkgdatadir=${PREFIX}/share/autoconf${SUFFIX}
FAKE_FLAGS=		${MAKE_FLAGS} DESTDIR=${WRKINST} lispdir=
SUBST_VARS=		SUFFIX

NO_REGRESS=		Yes

.include <bsd.port.mk>
