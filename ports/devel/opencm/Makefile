# $MirOS: ports/devel/opencm/Makefile,v 1.6 2008/03/09 17:22:31 tg Exp $
# $OpenBSD: Makefile,v 1.18 2004/02/04 07:39:18 sturm Exp $

COMMENT=		OpenCM change management system
COMMENT-docs=		OpenCM Documentation

V=			0.1.2alpha7pl1
sV=			-1
DASH_VER=		1
DISTNAME=		opencm-${V}${sV}-src
PKGNAME=		opencm-${V}-${DASH_VER}
FULLPKGNAME-docs=	opencm-docs-${V}-${DASH_VER}
CATEGORIES=		devel

HOMEPAGE=		http://www.opencm.org


# BSD/(GPL for diff3)
PERMIT_PACKAGE_CDROM=	dependency devel/boehm-gc is not allowed for CDROM
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=	Yes

# where the source files and patches can be fetched
#
MASTER_SITES=		http://www.opencm.org/releases/
EXTRACT_SUFX=		.tgz

USE_GMAKE=		Yes
USE_CXX=		Yes
MODGNU_CONFIG_GUESS_DIRS= ${WRKSRC}
CONFIGURE_STYLE=	autoconf
CPPFLAGS+=		-DUSE_SYSTEM_ZLIB
CONFIGURE_ENV=		vl_cv_lib_kerberos=1

NO_REGRESS=	Yes

PSEUDO_FLAVOURS=	no_docs
FLAVOUR?=		no_docs

MULTI_PACKAGES=

.if ${FLAVOUR:L:Mno_docs}
MAKE_FLAGS+=		TEXI2DVI=: DVIPS=:
FAKE_FLAGS+=		TEXI2DVI=: DVIPS=:
.else
BUILD_DEPENDS+= :teTeX_base-*:print/teTeX/base
MULTI_PACKAGES+= -docs

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/opencm
	${INSTALL_DATA} ${WRKSRC}/doc/opencm.html ${PREFIX}/share/doc/opencm
	${INSTALL_DATA} ${WRKSRC}/doc/opencm.ps ${PREFIX}/share/doc/opencm

.endif
.if defined(PACKAGING) && ${SUBPACKAGE} == "-docs"
PKG_ARCH=	*
.endif

MAKE_FLAGS+= LIBZ=-lz USOURCE_SUBDIRS="libgdiff src"
FAKE_FLAGS+= LIBZ=-lz USOURCE_SUBDIRS="libgdiff src"

MAKE_FLAGS+= LIBGC=
FAKE_FLAGS+= LIBGC=
LDFLAGS+= -L/usr/local/lib -lgc
LIB_DEPENDS=		gc.1:boehm-gc->=6.2:devel/boehm-gc

PLIST=			${PKGDIR}/PLIST${SUBPACKAGE}

WRKDIST=		${WRKDIR}/opencm-${V}
WRKSRC=			${WRKDIST}/base

.include <bsd.port.mk>
