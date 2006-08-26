# $MirOS$

COMMENT=			systrace userland virtualisation
CATEGORIES=			security sysutils
DISTNAME=			sysjail-1.0.0
HOMEPAGE=			http://sysjail.bsd.lv/
MASTER_SITES=			${HOMEPAGE}dist/

# 2/3-clause BSD, Beer-Ware, ISC
PERMIT_DISTFILES_CDROM=		Yes
PERMIT_DISTFILES_FTP=		Yes
PERMIT_PACKAGE_CDROM=		Yes
PERMIT_PACKAGE_FTP=		Yes

CONFIGURE_STYLE=		autogen
AUTOCONF_NEW=			Yes
AUTOMAKE_VERSION=		1.9
CONFIGURE_ARGS+=		--disable-dependency-tracking \
				--disable-doxygen-doc \
				--disable-doxygen-dot

.include <bsd.port.mk>
