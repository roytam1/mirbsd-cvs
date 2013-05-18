# $MirOS$
# $OpenBSD: Makefile,v 1.6 2002/12/29 19:43:50 fgsch Exp $

NOT_FOR_PLATFORM= MirBSD:*:* # needs a Fortran compiler

COMMENT=	high-level language for numerical computations
VERSION=	2.0.16
DISTNAME=	octave-${VERSION}
CATEGORIES=    	math

HOMEPAGE=	http://www.che.wisc.edu/octave/


# Licensing:  GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNU:=octave/}

REGRESS_DEPENDS=::devel/dejagnu

USE_GMAKE=	Yes
USE_CXX=	Yes

CONFIGURE_STYLE=	gnu dest
MODGNU_RECURSE_DIRS=	${WRKSRC}/kpathsea ${WRKSRC}/readline \
			${WRKSRC}/readline/support ${WRKSRC}
CONFIGURE_ARGS=		${CONFIGURE_SHARED} ${GCCARCH}
CONFIGURE_ENV= 		FFLAGS="${FFLAGS}" SOREV="${SHLIB_VER}"

# need shared library version for machines which support shared libraries.
SHLIB_VER=	1.0
GCCARCH=	${MACHINE_ARCH}-unknown-openbsd${OPSYS_VER}
SUBST_VARS=	GCCARCH VERSION SHLIB_VER

pre-build:
	@rm -f ${WRKSRC}/doc/liboctave/liboctave.info*

# fix ls-R
post-install:
	@cd ${PREFIX}/share/octave && \
	    sed -e "s,${PREFIX},${TRUEPREFIX}," ls-R > ls-R.new && \
	    mv -f ls-R.new ls-R
	@cd ${PREFIX}/libexec/octave && \
	    sed -e "s,${PREFIX},${TRUEPREFIX}," ls-R > ls-R.new && \
	    mv -f ls-R.new ls-R

.include <bsd.port.mk>

# if we can use shared libraries, make octave use modules.
.if !defined (NO_SHARED_LIBS)
CONFIGURE_ARGS+=	--enable-lite-kernel
.endif
