# $MirOS: ports/devel/libreadline/Makefile,v 1.5 2006/10/17 22:17:05 tg Exp $

COMMENT=		history and line editing library similar to libedit
COMMENT-docs=		documentation for libreadline
CATEGORIES=		devel
V=			5.2
DISTNAME=		readline-${V}
PKGNAME-docs=		readline-docs-${V}-0
MASTER_SITES=		${MASTER_SITE_GNU:=readline/}
HOMEPAGE=		http://cnswww.cns.cwru.edu/php/chet/readline/rltop.html

MULTI_PACKAGES=		-docs
SUBPACKAGE?=

# Code: GNU GPLv2 or later
# Docs: GNU FDL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

.if ${SUBPACKAGE} == "-docs"
PERMIT_PACKAGE_CDROM=	"GNU FDL"
PERMIT_PACKAGE_FTP=	"texinfo output is considered opaque by GNU FDL"
.else
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
.endif

CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--enable-multibyte \
			--enable-static
EXTRA_XAKE_FLAGS+=	MAKE_SHELL=${MKSH:Q}
NO_REGRESS=		Yes

.include <bsd.port.mk>
