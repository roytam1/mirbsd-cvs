# $MirOS$

COMMENT=		Nils R. Weller’s C Compiler
DISTNAME=		nwcc_0.7.6
CATEGORIES=		lang devel
HOMEPAGE=		http://nwcc.sourceforge.net/

# BSD
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

PKGNAME=		${DISTNAME:S/_/-/}-${DASH_VER}
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=nwcc/}

CONFIGURE_STYLE=	simple
CONFIGURE_ARGS+=	--installprefix=${WRKINST:Q}${TRUEPREFIX:Q}
ALL_TARGET=		nwcc

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/nwcc/
	cd ${WRKSRC} && ${INSTALL_DATA} COPYING CREDITS CROSSCOMP NEWS \
	    README.first USAGE ${PREFIX}/share/doc/nwcc/

.include <bsd.port.mk>
