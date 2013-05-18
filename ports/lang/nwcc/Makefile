# $MirOS: ports/lang/nwcc/Makefile,v 1.2 2009/04/17 14:54:37 tg Exp $

COMMENT=		Nils R. Weller’s C Compiler
DISTNAME=		nwcc_0.8
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
CONFIGURE_ARGS+=	--installprefix=${TRUEPREFIX:Q}
CONFIGURE_ARGS+=	--nocpp
REGRESS_TARGET=		test

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/nwcc
	cd ${WRKSRC} && ${INSTALL_DATA} COPYING CREDITS CROSSCOMP NEWS \
	    README.first USAGE news* oldnews/* ${PREFIX}/share/doc/nwcc/
	cd ${PREFIX}/share/doc/nwcc; for x in news*; do \
		mv $$x NEWS$${x#news}; \
	done

.include <bsd.port.mk>
