# $MirOS: ports/devel/autoconf/2.59/Makefile,v 1.4 2006/02/09 11:11:18 tg Exp $

COMMENT=		automatically configure source code on many Un*x platforms
SUFFIX=			-2.60
DISTNAME=		autoconf${SUFFIX}
CATEGORIES=		devel
MASTER_SITES=		${MASTER_SITE_GNU:=autoconf/}
HOMEPAGE=		http://www.gnu.org/software/autoconf/

# GPL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

BUILD_DEPENDS=		:help2man-*:devel/help2man

CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	--program-suffix=${SUFFIX} \
			--infodir=${PREFIX}/info \
			--mandir=${PREFIX}/man \
			--without-lispdir
CONFIGURE_ENV+=		M4=${M4:Q} AWK=${AWK:Q}
EXTRA_XAKE_FLAGS+=	pkgdatadir=${PREFIX}/share/autoconf${SUFFIX}
EXTRA_FAKE_FLAGS+=	DESTDIR=${WRKINST} lispdir=
SUBST_VARS=		SUFFIX

NO_REGRESS=		Yes

.include <bsd.port.mk>
