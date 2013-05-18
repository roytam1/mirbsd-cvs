# $MirOS: ports/www/firesomething/Makefile,v 1.51 2010/02/21 09:36:57 bsiegert Exp $
# $OpenBSD: Makefile,v 1.41 2005/11/15 09:21:52 wilfried Exp $

# mnbsd/amd64, mnbsd/sparc64 missing
# darwin extremely difficult, interix impossible
ONLY_FOR_PLATFORM=	MidnightBSD:*:i386 \
			MirBSD:*:i386 MirBSD:*:sparc \
			OpenBSD:*:alpha OpenBSD:*:amd64 OpenBSD:*:i386 \
			OpenBSD:*:powerpc OpenBSD:*:sparc OpenBSD:*:sparc64

COMMENT=		one of the successors to the Netscape browser engine
COMMENT-nssckbi=	CA certificate bundle for NSS (Mirzilla Firetapir)
VER=			3.0.18
DISTNAME=		mozilla
PKGNAME=		firesomething-${VER}-${DASH_VER}
FULLPKGNAME-nssckbi=	nssckbi-1.75-3
CATEGORIES=		www
HOMEPAGE=		http://www.mozilla.org/projects/firefox/

# mozilla public license
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

.include <mirports.sys.mk>

MASTER_SITES=		http://ftp.eu.mozilla.org/pub/mozilla.org/firefox/releases/${VER}/source/ \
			http://ftp.mozilla.org/pub/mozilla.org/firefox/releases/${VER}/source/ \
			ftp://releases.mozilla.org/pub/mozilla.org/firefox/releases/${VER}/source/ \
			ftp://archive.mozilla.org/pub/mozilla.org/firefox/releases/${VER}/source/
DISTFILES=		firefox-${VER}-source.tar.bz2
SO_VERSION=		10.0

MULTI_PACKAGES=		-nssckbi #-nspr
SUBPACKAGE?=
PREFER_SUBPKG_INSTALL=	No	# firesomething depends on nssckbi already

MODULES+=		devel/gettext devel/pkgconfig
RUN_DEPENDS+=		:esound-*:audio/esound
BUILD_DEPENDS+=		:libIDL-*:devel/libIDL
BUILD_DEPENDS+=		:zip->=2.3:archivers/zip
BUILD_DEPENDS+=		:python->=2.5.2-7:lang/python/2.5
LIB_DEPENDS+=		cairo:cairo->=1.6:graphics/cairo
LIB_DEPENDS+=		gdk-x11-2.0.0.0,gdk_pixbuf-2.0.0.0,gtk-x11-2.0.0.0::x11/gtk+
LIB_DEPENDS+=		dbus-glib-1::sysutils/dbus-glib

VMEM_WARNING=		Yes
USE_CXX=		Yes
USE_X11=		Yes
USE_GMAKE=		Yes
# Regression tests are too hard to adapt to run here
NO_REGRESS=		Yes
SUBST_VARS=		LOCALBASE SO_EXTENSION SO_VERSION VER

.if ${OStype} == "MidnightBSD"
SO_EXTENSION=
.else
SO_EXTENSION=		.${SO_VERSION}
.endif

.if defined(PACKAGING)
.  if ${SUBPACKAGE} == "-nssckbi"
MODULES:=
LIB_DEPENDS:=
B_R_DEPENDS:=
RUN_DEPENDS:=
.  else
RUN_DEPENDS+=		:nssckbi-*:www/firesomething,-nssckbi
.  endif
.endif

MODGNU_RECURSE_DIRS=	${WRKSRC}/nsprpub ${WRKSRC}
CONFIGURE_STYLE=	autoconf no-autoheader
CONFIGURE_ARGS+=	--with-system-jpeg=${LOCALBASE}	\
			--with-system-png=${PNG_BASE}	\
			--with-system-zlib=/usr/lib	\
			--with-system-sqlite		\
			--with-pthreads			\
			--without-system-nspr		\
			--enable-xft			\
			--enable-optimize=-Os		\
			--enable-default-toolkit=cairo-gtk2	\
			--disable-debug			\
			--disable-tests			\
			--disable-pedantic		\
			--disable-installer		\
			--disable-updater		\
			--disable-crashreporter		\
			--disable-gnomeui		\
			--disable-gnomevfs		\
			--enable-xinerama		\
			--enable-svg			\
			--enable-svg-renderer=cairo	\
			--enable-system-cairo		\
			--enable-canvas

# from browser/config/mozconfig
CONFIGURE_ARGS+=	--enable-application=browser

MAKE_ENV=		MOZ_CO_PROJECT=browser \
			LD_LIBRARY_PATH=${WRKSRC:Q}/dist/bin \
			SO_VERSION=${SO_VERSION:Q}
CONFIGURE_ENV=		${MAKE_ENV}

post-extract:
	@cp ${FILESDIR}/xptc* ${WRKSRC}/xpcom/reflect/xptcall/src/md/unix/
	cd ${WRKSRC}/security/nss/lib/ckfw/builtins/ && \
	    cp ${FILESDIR}/certdata.{c,txt} . && \
	    touch certdata.txt && sleep 1 && touch certdata.c
	cd ${WRKSRC}/security/coreconf && \
	    cp FreeBSD.mk MidnightBSD.mk && \
	    ln -sf OpenBSD.mk MirBSD.mk

pre-configure:
	@perl -pi -e 's|_LOCALBASE_|${LOCALBASE}|g; s|_X11BASE_|${X11BASE}|g' \
		${WRKSRC}/browser/app/mozilla.in
	@perl -pi -e 's|_SO_VERSION_|${SO_VERSION}|g' \
		${WRKSRC}/nsprpub/pr/include/md/_openbsd.h \
		${WRKSRC}/xpcom/components/nsNativeComponentLoader.cpp
	@perl -pi -e 's|_SO_EXTENSION_|${SO_EXTENSION}|g' \
		${WRKSRC}/browser/installer/unix/packages-static

post-install:
	cd ${PREFIX} && \
	    mv -f firesomething/firefox firesomething/firesomething && \
	    mv -f firesomething/firefox-bin firesomething/firesomething-bin
	cd ${PREFIX}/bin && ln -sf ../firesomething/firesomething firesomething

.include <bsd.port.mk>
