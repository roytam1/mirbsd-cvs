# $MirOS: ports/devel/pkgconfig-bsd/Makefile,v 1.1 2007/02/23 20:14:07 bsiegert Exp $

COMMENT=		pkg-config clone in Perl
CATEGORIES=		devel
CVS_DISTREPO=		anoncvs@anoncvs.ca.openbsd.org:/cvs
CVS_DISTDATE=		2007/02/23
CVS_DISTMODS=		src/usr.bin/pkg-config src/usr.sbin/pkg_add/OpenBSD
CVS_DISTFILE=		pkgconfig-bsd
PKGNAME=		pkgconfig-${CVS_DISTDATE:S!/!!g}-${DASH_VER}-bsd
RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

WRKDIST=		${WRKDIR}/src/usr.bin/pkg-config
SUBST_VARS+=		P5ARCH

# BSD
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

do-configure:
	cd ${WRKSRC} && ${MAKE} obj

pre-build:
	cd ${WRKBUILD} && exec ${SETENV} ${MAKE_ENV} \
	    ${MAKE_PROGRAM} ${MAKE_FLAGS} -f ${MAKE_FILE} depend

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/${P5ARCH}/OpenBSD
	${INSTALL_DATA} ${WRKDIR}/src/usr.sbin/pkg_add/OpenBSD/PkgConfig.pm ${PREFIX}/${P5ARCH}/OpenBSD/

.include <bsd.port.mk>
