# $MirOS: ports/security/nss/Makefile,v 1.2 2010/03/28 15:42:30 bsiegert Exp $

COMMENT=		Network Security Services from the Mozilla project
VERSION=		3.12.4
MAJOR_VERSION=		3
DASH_VER=		2
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

PC_SED=			sed -e "s,@prefix@,$(TRUEPREFIX)," \
			-e "s,@exec_prefix@,$(TRUEPREFIX)/bin," \
			-e "s,@libdir@,$(TRUEPREFIX)/lib," \
			-e "s,@includedir@,$(TRUEPREFIX)/include," \
			-e "s,@NSS_MAJOR_VERSION@,$(MAJOR_VERSION),g" \
			-e "s,@NSS_VERSION@,$(VERSION),g"

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
	mkdir -p ${PREFIX}/lib/pkgconfig
	${PC_SED} ${FILESDIR}/nss.pc.in > ${PREFIX}/lib/pkgconfig/nss.pc
	${PC_SED} ${FILESDIR}/nss-config.in > ${PREFIX}/bin/nss-config
	chmod +x ${PREFIX}/bin/nss-config

.include <bsd.port.mk>
