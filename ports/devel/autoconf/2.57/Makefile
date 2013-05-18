# $MirOS: ports/devel/autoconf/2.57/Makefile,v 1.1.7.1 2005/03/18 15:44:26 tg Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2003/06/09 12:04:15 espie Exp $

COMMENT=			automatically configure source code on many Un*x platforms
DISTNAME=	autoconf-2.57
CATEGORIES=	devel
MASTER_SITES=	${MASTER_SITE_GNU:=autoconf/}
HOMEPAGE=	http://www.gnu.org/software/autoconf/

# GPL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

BUILD_DEPENDS=		:help2man-*:devel/help2man

SUFFIX=			-2.57
CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	--program-suffix=${SUFFIX} \
			--without-lispdir
CONFIGURE_ENV+=		M4="/usr/bin/m4"
CONFIGURE_ENV+=		AWK="${AWK}"
MAKE_FLAGS=		pkgdatadir=${PREFIX}/share/autoconf${SUFFIX}
FAKE_FLAGS=		${MAKE_FLAGS} DESTDIR=${WRKINST} lispdir=
#USE_GMAKE=		Yes
SUBST_VARS=		SUFFIX

NO_REGRESS=		Yes

.include <bsd.port.mk>
