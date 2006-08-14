# $MirOS: ports/www/lynx/Makefile,v 1.2 2006/08/10 22:27:10 tg Exp $

COMMENT=			standard text-mode world wide web browser
CATEGORIES=			www essentials
VERSION=			2.8.6dev.18
DISTNAME=			lynx${VERSION
PKGNAME=			lynx-${VERSION}-1
HOMEPAGE=			http://lynx.browser.org/
RESPONSIBLE=			Thorsten Glaser <tg@mirbsd.de>
MASTER_SITES=			http://lynx.isc.org/current/

# GNU GPL Version 2 or later
PERMIT_DISTFILES_CDROM=		Yes
PERMIT_DISTFILES_FTP=		Yes
PERMIT_PACKAGE_CDROM=		Yes
PERMIT_PACKAGE_FTP=		Yes

WRKDIST=			${WRKDIR}/lynx2-8-6
MAKE_FILE=			makefile
INSTALL_TARGET=			install-full

MODULES=			converters/libiconv
CONFIGURE_STYLE=		gnu
CONFIGURE_ARGS+=		--with-ssl --with-zlib --enable-japanese-utf8 \
				--libdir=${SYSCONFDIR} \
		--enable-addrlist-page --enable-charset-choice \
		--enable-color-style --disable-full-paths --enable-warnings \
		--enable-internal-links --enable-kbd-layout --enable-ipv6 \
		--enable-nested-tables --disable-nls --enable-nsl-fork \
		--with-screen=ncurses --disable-scrollbar --enable-cjk \
		--enable-underlines --enable-vertrace --without-bzlib
.if ${OStype} == "Interix"
CONFIGURE_ARGS+=		--disable-ipv6
.endif
.if ${OStype} == "Darwin"
CONFIGURE_ARGS+=		--disable-prettysrc
.endif
EXTRA_XAKE_FLAGS+=		docdir=${PREFIX}/share/doc/lynx_doc \
				helpdir=${PREFIX}/share/doc/lynx_help

post-install:
	mv -f ${WRKINST}${SYSCONFDIR}/lynx.{cfg,lss} \
	    ${PREFIX}/share/doc/lynx_doc/samples/

.include <bsd.port.mk>
