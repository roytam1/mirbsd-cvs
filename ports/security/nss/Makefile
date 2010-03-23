# $MirOS: ports/devel/nspr/Makefile,v 1.6 2010/02/02 20:36:19 bsiegert Exp $

COMMENT=		Network Security Services from the Mozilla project
VERSION=		3.12.4
V=			${VERSION:S/./_/g}
DISTNAME=		nss-${VERSION}
CATEGORIES=		security devel
HOMEPAGE=		http://www.mozilla.org/projects/security/pki/nss/

# MPL - Mozilla Public License
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://ftp.mozilla.org/pub/mozilla.org/security/nss/releases/NSS_${V}_RTM/src/

USE_CXX=		Yes
USE_GMAKE=		Yes

WRKDIST=		${WRKDIR}/${DISTNAME}/mozilla
WRKSRC=			${WRKDIST}/security/nss

LIB_DEPENDS+=		nspr4,plc4,plds4::devel/nspr
LIB_DEPENDS+=		sqlite3::databases/sqlite

SO_VERSION=		10.0
SUBST_VARS+=		SO_VERSION
MAKE_ENV+=		SO_VERSION=${SO_VERSION}
MAKE_ENV+=		BUILD_OPT=1
MAKE_ENV+=		NS_USE_GCC=1
MAKE_ENV+=		NO_MDUPDATE=1
MAKE_ENV+=		NSS_USE_SYSTEM_SQLITE=1

ALL_TARGET=		build_coreconf build_dbm all
CPPFLAGS+=		-I${LOCALBASE}/include/nspr

post-extract:
	cd ${WRKSRC}/lib/ckfw/builtins/ && \
	    cp ${FILESDIR}/certdata.{c,txt} . && \
	    touch certdata.txt && sleep 1 && touch certdata.c
	cd ${WRKDIST}/security/coreconf && \
	    cp FreeBSD.mk MidnightBSD.mk && \
	    ln -sf OpenBSD.mk MirBSD.mk

do-regress:
	cd ${WRKSRC}/tests && env ${MAKE_ENV} sh ./all.sh

post-install:
	cd ${WRKDIST}/dist/*.OBJ && pax -rw -L . ${PREFIX}
	cd ${WRKDIST}/dist/public && pax -rw -L . ${PREFIX}/include

.include <bsd.port.mk>
