# $MirOS: ports/devel/pwlib/Makefile,v 1.1.7.1 2005/03/18 15:45:24 tg Exp $

COMMENT=		"cross platform C++ socket and stuff library"
VERSION=		1.6.3
DISTNAME=		pwlib-${VERSION}
CATEGORIES=		net
HOMEPAGE=		http://www.openh323.org/

# MPL 
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://www.gnomemeeting.org/admin/downloads/latest/sources/sources/ 

WRKDIST=        	${WRKDIR}/pwlib

BUILD_DEPENDS=		::devel/bison \
			::textproc/expat

#			::databases/openldap \
#			::devel/sdl \

USE_GMAKE=		Yes
USE_CXX=		Yes
AUTOCONF_NEW=		Yes
CONFIGURE_STYLE=	autoconf
CONFIGURE_ENV=		STDCCFLAGS="-I${LOCALBASE}/include/ptlib/unix"
CONFIGURE_ARGS+=	--enable-internalregex
CONFIGURE_ARGS+=	--disable-openssl		# broken for now
CONFIGURE_ARGS+=	--disable-sdl --disable-openldap
MAKE_ENV=		PWLIBDIR=${WRKDIST}
ALL_TARGET=		optshared

NO_REGRESS=     	Yes

pre-build:
	@mkdir -p ${WRKDIST}/share/pwlib
	@ln -sf ${WRKDIST}/make ${WRKDIST}/share/pwlib

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/include/ptclib
	${INSTALL_DATA_DIR} ${PREFIX}/include/ptlib/unix/ptlib
	${INSTALL_DATA_DIR} ${PREFIX}/share/pwlib/make
	${INSTALL_DATA} ${WRKDIST}/include/ptlib/unix/ptlib/*.{h,inl} ${PREFIX}/include/ptlib/unix/ptlib
	${INSTALL_DATA} ${WRKDIST}/include/ptclib/*.h ${PREFIX}/include/ptclib
	${INSTALL_DATA} ${WRKDIST}/include/ptlib/*.{h,inl} ${PREFIX}/include/ptlib
	${INSTALL_DATA} ${WRKDIST}/include/*.h ${PREFIX}/include
	${INSTALL_DATA} ${WRKDIST}/lib/libpt.so.${VERSION} \
	    ${PREFIX}/lib/libpt.so.${VERSION:C/\.[^.]*$//}
	${INSTALL_DATA} ${WRKDIST}/lib/libpt.a ${PREFIX}/lib
	${INSTALL_DATA} ${WRKDIST}/make/*.mak ${PREFIX}/share/pwlib/make
	${INSTALL_PROGRAM} ${WRKDIST}/tools/asnparser/obj_OpenBSD_*/asnparser ${PREFIX}/bin/asnparser
	${INSTALL_SCRIPT} ${WRKDIST}/make/ptlib-config ${PREFIX}/bin
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/pwlib
	${INSTALL_DATA} ${WRKDIST}/ReadMe.txt ${PREFIX}/share/doc/pwlib

.include <bsd.port.mk>
