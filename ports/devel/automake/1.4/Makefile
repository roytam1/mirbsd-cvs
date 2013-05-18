# $MirOS: ports/devel/automake/1.4/Makefile,v 1.6 2006/09/14 00:08:04 tg Exp $
# $OpenBSD: Makefile,v 1.27 2002/11/27 07:50:28 ish Exp $

COMMENT=		GNU Standards-compliant Makefile generator
VERSION=		1.4-p6
DASH_VER=		5
DISTNAME=		automake-${VERSION}
MPVERSION=		${VERSION:S/-//}-MirPorts-${DASH_VER}
PKGNAME=		automake-${VERSION:S/-//}-${DASH_VER}
SUFFIX=			-1.4
CATEGORIES=		devel
MASTER_SITES=		${MASTER_SITE_GNU:=automake/}
HOMEPAGE=		http://www.gnu.org/software/automake/

# GNU GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	gnu
SUBST_VARS+=		SUFFIX

RUN_DEPENDS=		:metaauto->=0.2:devel/metaauto
REGRESS_DEPENDS=	:gmake-*:devel/gmake

do-regress:
	cd ${WRKBUILD} && exec ${SETENV} ${MAKE_ENV} MAKE=gmake gmake -f \
	    ${MAKE_FILE} ${REGRESS_FLAGS} ${REGRESS_TARGET}

post-build:
.for _f in aclocal automake
	print '%g/@MPVERSION@/s//${MPVERSION}/g\nwq' | ed -s ${WRKSRC}/${_f}
.endfor

post-install:
	cd ${PREFIX}/info && mv automake.info automake${SUFFIX}.info
	-rm -f ${PREFIX}/bin/{aclocal,automake}

.include <bsd.port.mk>
