# $MirOS: ports/www/lynx/Makefile,v 1.8 2006/10/02 23:22:06 tg Exp $

COMMENT=			standard text-mode world wide web browser
CATEGORIES=			www essentials
VERSION=			2.8.7dev.1
PL=				0
DISTNAME=			lynx${VERSION:C/[a-z]$//}
.if ${VERSION} != ${VERSION:C/[a-z]$//}
PATCHFILES=			lynx${VERSION}.patch.gz:0
.endif
PKGNAME=			lynx-${VERSION}-${PL}
HOMEPAGE=			http://lynx.browser.org/
RESPONSIBLE=			Thorsten Glaser <tg@mirbsd.de>
MASTER_SITES=			http://lynx.isc.org/current/
MASTER_SITES0=			ftp://invisible-island.net/temp/
PATCH_DIST_STRIP=		-p1

# GNU GPL Version 2 or later
PERMIT_DISTFILES_CDROM=		Yes
PERMIT_DISTFILES_FTP=		Yes
PERMIT_PACKAGE_CDROM=		Yes
PERMIT_PACKAGE_FTP=		Yes

WRKDIST=			${WRKDIR}/lynx2-8-7
MAKE_FILE=			makefile
INSTALL_TARGET=			install-full
NO_REGRESS=			Yes

MODULES=			converters/libiconv
CONFIGURE_STYLE=		gnu
CONFIGURE_ARGS+=		--with-ssl --with-zlib --enable-japanese-utf8 \
		--enable-addrlist-page --enable-charset-choice \
		--enable-color-style --disable-full-paths --enable-warnings \
		--enable-internal-links --enable-kbd-layout --enable-ipv6 \
		--enable-nested-tables --disable-nls --enable-nsl-fork \
		--with-screen=ncurses --disable-scrollbar --enable-cjk \
		--enable-underlines --enable-vertrace --without-bzlib
.if ${MACHINE_OS} == "Interix"
CONFIGURE_ARGS+=		--disable-ipv6
.endif
CPPFLAGS+=			-DLYNX_VERSION=\"${VERSION}-MirPorts-${PL}\"

post-install:
	${INSTALL_SCRIPT} ${WRKSRC}/samples/oldlynx ${PREFIX}/bin/
	mv -f ${WRKINST}${SYSCONFDIR}/lynx.{cfg,lss} \
	    ${PREFIX}/share/lynx_doc/samples/
	-rm -rf ${WRKINST}${SYSCONFDIR}

.include <bsd.port.mk>
