# $MirOS: ports/devel/libreadline/Makefile,v 1.7 2008/04/22 17:24:18 bsiegert Exp $

COMMENT=		history and line editing library similar to libedit
CATEGORIES=		devel
DASH_VER=		2
DISTNAME=		readline-5.2
MASTER_SITES=		${MASTER_SITE_GNU:=readline/}
HOMEPAGE=		http://cnswww.cns.cwru.edu/php/chet/readline/rltop.html

# Code: GNU GPLv2 or later
# Docs: GNU FDL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--enable-multibyte \
			--enable-static
EXTRA_XAKE_FLAGS+=	MAKE_SHELL=${MKSH:Q}
NO_REGRESS=		Yes

# To avoid clashing with native libreadline (Darwin), libedit
CONFIGURE_ARGS+=	--libdir=${PREFIX}/pkgview/libreadline/lib \
			--includedir=${PREFIX}/pkgview/libreadline/include

.include <bsd.port.mk>
