# $MirOS: ports/archivers/libarchive/Makefile,v 1.1 2010/11/20 17:18:33 bsiegert Exp $
# $OpenBSD: Makefile,v 1.25 2013/04/04 16:03:55 brad Exp $

COMMENT=		multi-format archive and compression library
DISTNAME=		libarchive-3.0.4
CATEGORIES=		archivers
HOMEPAGE=		http://libarchive.github.com/

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		https://github.com/downloads/libarchive/libarchive/

MODULES+=		converters/libiconv
LIB_DEPENDS+=		bz2::archivers/bzip2
LIB_DEPENDS+=		lzma::archivers/xz

CONFIGURE_STYLE=	autogen
AUTOCONF_NEW=		Yes
AUTOCONF_VERSION=	2.62
AUTOMAKE_VERSION=	1.9
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--without-lzmadec	# old LZMA utils
CONFIGURE_ARGS+=	--without-nettle	# prefer OpenSSL
CONFIGURE_ARGS+=	--without-xml2		# expat suffices

.include <bsd.port.mk>

_CIPHERS+=		sha256
