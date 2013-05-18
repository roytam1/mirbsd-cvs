# $MirOS$
# $OpenBSD: Makefile,v 1.4 2010/11/08 20:11:13 naddy Exp $

COMMENT=		LZMA compression and decompression tools
DISTNAME=		xz-5.0.0
CATEGORIES=		archivers
HOMEPAGE=		http://tukaani.org/xz/
MASTER_SITES=		${HOMEPAGE}

# GPLv2+
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES=		devel/gettext

CONFIGURE_STYLE=	autogen
AUTOCONF_NEW=		Yes
AUTOMAKE_VERSION=	1.9
CONFIGURE_ARGS=		${CONFIGURE_SHARED} \
			--disable-threads

post-extract:
	rm -f ${WRKSRC}/m4/lt*.m4 ${WRKSRC}/m4/libtool.m4

.include <bsd.port.mk>
