# $MirOS: ports/devel/autoconf/2.58/Makefile,v 1.3 2009/11/21 16:52:11 tg Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2004/02/10 00:27:01 espie Exp $

COMMENT=		automatically configure source code on many Un*x platforms
DISTNAME=		autoconf-2.58
CATEGORIES=		devel
MASTER_SITES=		${MASTER_SITE_GNU:=autoconf/}
HOMEPAGE=		http://www.gnu.org/software/autoconf/

# GPL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

BUILD_DEPENDS=		:help2man-*:devel/help2man
USE_M4=			bsd
MODULES+=		m4
B_R_DEPENDS+=		${MODM4_DEPENDS}

SUFFIX=			-2.58
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
