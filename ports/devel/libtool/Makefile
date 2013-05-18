# $MirOS: ports/devel/libtool/Makefile,v 1.15 2008/12/07 18:57:51 tg Exp $

COMMENT=		complete GNU libtool with MirLibtool patches added
CATEGORIES=		devel
DASH_VER=		3
MCZ_FETCH=		Yes
CVS_DISTREPO=		:pserver:anonymous@cvs.sv.gnu.org:/sources/libtool
CVS_DISTDATE=		2008/05/03
CVS_DISTTAGS=		branch-1-5
CVS_DISTMODS=		libtool
_DATE=			${CVS_DISTDATE:C![/:]!!g:Q:S!\\ !!}
PKGNAME=		libtool-1.5.27a.${_DATE}-${DASH_VER}
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

CONFIGURE_ARGS+=	CC=${_ORIG_CC:Q} CXX=${_ORIG_CXX:Q}

FLAVOURS=		no_cxx
FLAVOUR?=

.if !${FLAVOUR:Mno_cxx}
USE_CXX=		Yes
REGRESS_TARGET=		check
.else
NO_REGRESS=		Yes
.endif

post-configure:
	rm -f ${WRKSRC}/{,libltdl/}ltmain.sh
	cp ${PORTSDIR}/infrastructure/db/ltmain.sh ${WRKSRC}/
	cp ${PORTSDIR}/infrastructure/db/ltmain.sh ${WRKSRC}/libltdl/

regress-v: ${_BUILD_COOKIE}
	cd ${.CURDIR} && exec ${MAKE} \
	    regress REGRESS_TARGET="VERBOSE=x check" 2>&1 | tee $@

.include <bsd.port.mk>
