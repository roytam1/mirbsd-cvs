# $MirOS: ports/devel/libreadline/Makefile,v 1.10 2008/08/26 13:53:02 tg Exp $

COMMENT=		history and line editing library similar to libedit
CATEGORIES=		devel
DASH_VER=		4
DISTNAME=		readline-5.2
HOMEPAGE=		http://cnswww.cns.cwru.edu/php/chet/readline/rltop.html

# Code: GNU GPLv2 or later
# Docs: GNU FDL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNU:=readline/}
MASTER_SITES0=		${MASTER_SITE_GNU:=readline/${DISTNAME}-patches/}

.ifndef rl_patches
rl_patches!=		jot -w%03d - 1 12 1
.MAKEFLAGS:=		${.MAKEFLAGS} rl_patches=${rl_patches:Q}
.endif
.for _p in ${rl_patches}
PATCHFILES+=		${DISTNAME:S/-//:S/.//}-${_p}:0
.endfor

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
