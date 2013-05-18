# $MirOS: ports/devel/automake/1.9/Makefile,v 1.13 2009/12/06 15:23:07 tg Exp $
# $OpenBSD: Makefile,v 1.27 2002/11/27 07:50:28 ish Exp $

COMMENT=		experimental GNU automatic Makefile generator
VERSION=		1.9.6
DASH_VER=		6
DISTNAME=		automake-${VERSION}
SUFFIX=			-1.9
CATEGORIES=		devel
MASTER_SITES=		${MASTER_SITE_GNU:=automake/}
HOMEPAGE=		http://www.gnu.org/software/automake/

# GNU GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes
EXTRA_FAKE_FLAGS=	${DESTDIRNAME}=${WRKINST:Q}
MPVERSION=		${VERSION}-MirPorts-${DASH_VER}
SUBST_VARS+=		SUFFIX

RUN_DEPENDS=		:metaauto->=0.2:devel/metaauto
REGRESS_DEPENDS=	:gmake-*:devel/gmake

do-regress:
	cd ${WRKBUILD} && exec ${SETENV} ${MAKE_ENV} MAKE=${GMAKE} \
	    ${GMAKE} -f ${MAKE_FILE} ${REGRESS_FLAGS} ${REGRESS_TARGET}

post-build:
	chmod u+w ${WRKSRC}/lib/Automake/Config.pm
	print ',g/@MPVERSION@/s//${MPVERSION}/g\nwq' \
	    | ed -s ${WRKSRC}/lib/Automake/Config.pm
	chmod u-w ${WRKSRC}/lib/Automake/Config.pm

post-install:
	cd ${PREFIX}/info && mv automake.info automake${SUFFIX}.info
	-rm -f ${PREFIX}/bin/{aclocal,automake}

.include <bsd.port.mk>
