# $MirOS: ports/devel/libsigc++/Makefile,v 1.6 2006/10/07 03:03:45 tg Exp $
# $OpenBSD: Makefile,v 1.13 2003/11/27 02:22:20 pvalchev Exp $

COMMENT=		callback framework for C++
COMMENT-docs=		HTML documentation for libsigc++
V=			2.0.17
PL=			2
DISTNAME=		libsigc++-${V}
PKGNAME=		libsigc++-${V}-${PL}
PKGNAME-docs=		libsigc++-docs-${V}-${PL}
CATEGORIES=		devel
HOMEPAGE=		http://libsigc.sourceforge.net/
MASTER_SITES=		${MASTER_SITE_GNOME:=sources/libsigc++/2.0/}

# LGPL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MULTI_PACKAGES=		-docs
SUBPACKAGE?=

.if ${SUBPACKAGE} == "-docs"
DESCR=			${PKGDIR}/DESCR
.endif

USE_CXX=		yes
MODULES+=		devel/pkgconfig
CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--enable-static

pre-install:
	${INSTALL_DATA_DIR} ${PREFIX}/include/sigc++-2.0/sigc++/{,functors,adaptors{,/lambda}}/macros

.include <bsd.port.mk>
