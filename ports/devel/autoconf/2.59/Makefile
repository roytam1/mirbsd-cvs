# $MirOS: ports/devel/autoconf/2.59/Makefile,v 1.7 2009/11/21 16:52:11 tg Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2004/02/10 00:00:14 espie Exp $

COMMENT=		automatically configure source code on many Un*x platforms
SUFFIX=			-2.59
DISTNAME=		autoconf${SUFFIX}
DASH_VER=		4
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
CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	--program-suffix=${SUFFIX} --without-lispdir
CONFIGURE_ENV+=		M4=${M4:Q}
CONFIGURE_ENV+=		AWK=${AWK:Q}
EXTRA_XAKE_FLAGS+=	pkgdatadir=${PREFIX}/share/autoconf${SUFFIX}
EXTRA_FAKE_FLAGS+=	DESTDIR=${WRKINST} lispdir=
SUBST_VARS=		SUFFIX
NO_REGRESS=		Yes

.include <bsd.port.mk>
