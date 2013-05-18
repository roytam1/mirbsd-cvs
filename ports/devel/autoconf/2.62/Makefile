# $MirOS: ports/devel/autoconf/2.62/Makefile,v 1.1 2009/11/18 20:48:06 bsiegert Exp $
# $OpenBSD: Makefile,v 1.2 2009/06/12 19:22:57 matthieu Exp $

COMMENT =	automatically configure source code on many Un*x platforms

DISTNAME =	autoconf-2.62
CATEGORIES =	devel
MASTER_SITES =	${MASTER_SITE_GNU:=autoconf/}

HOMEPAGE =	http://www.gnu.org/software/autoconf/

# GPL
PERMIT_DISTFILES_CDROM =Yes
PERMIT_DISTFILES_FTP =	Yes
PERMIT_PACKAGE_CDROM =	Yes
PERMIT_PACKAGE_FTP =	Yes

BUILD_DEPENDS =		:help2man-*:devel/help2man
RUN_DEPENDS =		::devel/metaauto
USE_M4=			new
MODULES+=		m4
B_R_DEPENDS+=		${MODM4_DEPENDS}

SUFFIX =		-2.62
CONFIGURE_STYLE =	gnu
CONFIGURE_ARGS +=	--program-suffix=${SUFFIX} \
			--without-lispdir \
			--mandir=${PREFIX}/man \
			--infodir=${PREFIX}/info
EXTRA_XAKE_FLAGS +=	pkgdatadir=${PREFIX}/share/autoconf${SUFFIX} EMACS=no lispdir=
CONFIGURE_ENV +=	${EXTRA_XAKE_FLAGS}
CONFIGURE_ENV+=		M4=${M4:Q}
CONFIGURE_ENV +=	AWK="${AWK}" ac_cv_sh_n_works=yes
MODGNU_CONFIG_GUESS_DIRS =${WRKSRC}/build-aux
SUBST_VARS =		SUFFIX
REGRESS_DEPENDS =	::devel/automake/1.9
REGRESS_FLAGS +=	AUTOMAKE_VERSION=1.9

.include <bsd.port.mk>
