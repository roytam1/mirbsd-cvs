# $MirOS$

COMMENT=			standard text-mode world wide web browser
CATEGORIES=			www essentials
VERSION=			2.8.6dev.18
DISTNAME=			lynx${VERSION
PKGNAME=			lynx-${VERSION}-0
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
		--enable-internal-links --enable-kbd-layout \
		--enable-nested-tables --disable-nls --enable-nsl-fork \
		--with-screen=ncurses --disable-scrollbar --enable-cjk \
		--enable-underlines --enable-vertrace --without-bzlib
.if ${OStype} == "Interix"
CONFIGURE_ARGS+=		--disable-ipv6
.else
CONFIGURE_ARGS+=		--enable-ipv6
.endif
EXTRA_XAKE_FLAGS+=		docdir=${PREFIX}/share/doc/lynx_doc \
				helpdir=${PREFIX}/share/doc/lynx_help

post-install:
	mv -f ${PREFIX}/etc/lynx.* ${PREFIX}/share/doc/lynx_doc/samples/

.include <bsd.port.mk>
