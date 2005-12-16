# $MirOS: ports/devel/libtool/Makefile,v 1.1 2005/12/16 11:56:51 tg Exp $

COMMENT=		"complete GNU libtool with MirLibtool patches added"
CATEGORIES=		devel
CVS_DISTREPO=		:pserver:anonymous@cvs.sv.gnu.org:/sources/libtool
CVS_DISTDATE=		2005/12/16
CVS_DISTTAGS=		branch-1-5
CVS_DISTMODS=		libtool
PKGNAME=		libtool-1.5.21a.${CVS_DISTDATE:S!/!!g}-0
HOMEPAGE=		http://www.gnu.org/software/libtool/

# GNU GPLv2
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

CONFIGURE_STYLE=	autogen
AUTOGEN=		${WRKSRC}/bootstrap
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
AUTOCONF_NEW=		Yes
AUTOMAKE_VERSION=	1.9

REGRESS_TARGET=		check

post-configure:
	rm -f ${WRKSRC}/{,libltdl/}ltmain.sh
	cp ${PORTSDIR}/infrastructure/db/ltmain.sh ${WRKSRC}/
	cp ${PORTSDIR}/infrastructure/db/ltmain.sh ${WRKSRC}/libltdl/

regress-v: ${_BUILD_COOKIE}
	cd ${.CURDIR} && exec ${MAKE} \
	    regress REGRESS_TARGET="VERBOSE=x check" 2>&1 | tee $@

.include <bsd.port.mk>
