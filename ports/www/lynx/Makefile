# $MirOS: ports/www/lynx/Makefile,v 1.29 2009/09/06 14:17:03 tg Exp $

COMMENT=		standard text-mode world wide web browser
CATEGORIES=		www essentials
VSN=			2.8.7rel.1
DASH_VER=		2		# in sync with MirOS-0AAA rev.
DISTNAME=		lynx${VSN:C/[a-z]$//}
.if ${VSN} != ${VSN:C/[a-z]$//}
PATCHFILES=		lynx${VSN}.patch.gz:0
.endif
PKGNAME=		lynx-${VSN}-${DASH_VER}
HOMEPAGE=		http://lynx.isc.org/
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.org>
MASTER_SITES=		http://lynx.isc.org/current/
MASTER_SITES0=		ftp://invisible-island.net/temp/
PATCH_DIST_STRIP=	-p1

# GNU GPLv2
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

.include <mirports.sys.mk>

FLAVOURS=		wide
FLAVOUR?=		wide

WRKDIST=		${WRKDIR}/lynx2-8-7
MAKE_FILE=		makefile
CPPFLAGS+=		-DLYNX_VERSION=\"${VSN}-MirPorts-${DASH_VER}\"
INSTALL_TARGET=		install-full
NO_REGRESS=		Yes

MODULES+=		converters/libiconv
CONFIGURE_STYLE=	autoconf no-autoheader
CONFIGURE_ARGS+=	--enable-vertrace \
			--enable-warnings \
			--disable-nls \
			--disable-full-paths \
			--with-ssl \
			--without-gnutls \
			--without-socks \
			--without-socks5 \
			--without-pkg-config \
			--enable-ipv6 \
			--with-screen=ncursesw \
			--enable-widec \
			--disable-htmlized-cfg \
			--enable-locale-charset \
			--enable-addrlist-page \
			--enable-ascii-ctypes \
			--enable-charset-choice \
			--enable-cjk \
			--enable-japanese-utf8 \
			--enable-color-style \
			--disable-default-colors \
			--enable-kbd-layout \
			--enable-nested-tables \
			--enable-progressbar \
			--disable-scrollbar \
			--disable-sessions \
			--disable-session-cache \
			--enable-justify-elts \
			--enable-internal-links \
			--enable-nsl-fork \
			--enable-underlines \
			--without-bzlib \
			--with-zlib \
			--without-x
# do not hardcode paths; do not scan for ports stuff
# bzip2 is special and must always be disabled, otherwise
# it tries to handle it internally as if linking with the
# bzlib even if bzip2 isn’t there; setting the bzip2 path
# in lynx.cfg doesn’t have this issue
CONFIGURE_ENV+=		ac_cv_path_TELNET=telnet \
			ac_cv_path_TN3270=tn3270 \
			ac_cv_path_RLOGIN=rlogin \
			ac_cv_path_MV=mv \
			ac_cv_path_GZIP=gzip \
			ac_cv_path_UNCOMPRESS=gunzip \
			ac_cv_path_UNZIP=unzip \
			ac_cv_path_BZIP2= \
			ac_cv_path_TAR=tar \
			ac_cv_path_COMPRESS=compress \
			ac_cv_path_RM=rm \
			ac_cv_path_UUDECODE=uudecode \
			ac_cv_path_ZCAT=zcat \
			ac_cv_path_ZIP=zip \
			ac_cv_path_PKG_CONFIG=none
CONFIGURE_ENV+=		YACC=yacc

.if ${MACHINE_OS} == "Interix"
CONFIGURE_ARGS+=	--disable-ipv6
.endif

.if ${OStype} == "OpenBSD"
CONFIGURE_ARGS+=	--disable-locale-charset
.endif

.if ${FLAVOUR:Mwide}
MODULES+=		devel/libncursesw
.else
CONFIGURE_ARGS+=	--with-screen=ncurses \
			--disable-widec
.endif

post-install:
	${INSTALL_SCRIPT} ${WRKSRC}/samples/oldlynx ${PREFIX}/bin/

.include <bsd.port.mk>

# fix up paths, must come after gnu module
EXTRA_FAKE_FLAGS+=	SYSCONFDIR=${WRKINST:Q}${TRUEPREFIX:Q}/share/examples/lynx
CONFIGURE_ARGS+=	--datadir=${PREFIX:Q}/share/doc/lynx
