# $MirOS$
# $OpenBSD: Makefile,v 1.19 2010/11/15 00:22:45 espie Exp $

COMMENT=		library for reading and writing streaming archives

DISTNAME=		libarchive-2.8.4
DASH_VER=		0
CATEGORIES=		archivers
HOMEPAGE=		http://code.google.com/p/libarchive/
MASTER_SITES=		http://libarchive.googlecode.com/files/

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS+=		bz2::archivers/bzip2
LIB_DEPENDS+=		lzma::archivers/xz

CONFIGURE_STYLE=	autogen
AUTOCONF_NEW=		Yes
AUTOMAKE_VERSION=	1.9
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--without-lzmadec	# old LZMA utils
CONFIGURE_ARGS+=	--without-xml2		# expat suffices

.include <bsd.port.mk>
