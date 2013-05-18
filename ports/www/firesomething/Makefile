# $MirOS: ports/www/firesomething/Makefile,v 1.28 2008/05/26 05:45:51 bsiegert Exp $
# $OpenBSD: Makefile,v 1.41 2005/11/15 09:21:52 wilfried Exp $

ONLY_FOR_PLATFORM=	*:*:alpha *:*:i386 *:*:sparc *:*:sparc64 *:*:amd64 *:*:powerpc
COMMENT=		one of the successors to the Netscape browser engine
VER=			2.0.0.14
DASH_VER=		0
DISTNAME=		mozilla
PKGNAME=		firesomething-${VER}-${DASH_VER}
CATEGORIES=		www
HOMEPAGE=		http://www.mozilla.org/projects/firefox/

# mozilla public license
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

.include <mirports.sys.mk>

MASTER_SITES=		ftp://archive.mozilla.org/pub/mozilla.org/firefox/releases/${VER}/source/ \
			http://ftp.eu.mozilla.org/pub/mozilla.org/firefox/releases/${VER}/source/ \
			http://ftp.mozilla.org/pub/mozilla.org/firefox/releases/${VER}/source/
#MASTER_SITES=		${_MASTER_SITE_MIRBSD}
DISTFILES=		firefox-${VER}-source.tar.bz2
SO_VERSION=		9.0

MODULES+=		devel/gettext devel/pkgconfig
RUN_DEPENDS+=		:esound-*:audio/esound
BUILD_DEPENDS+=		:libIDL-*:devel/libIDL \
			:zip->=2.3:archivers/zip \
			:pkgconfig-*:devel/pkgconfig
LIB_DEPENDS+=		gdk-x11-2.0.0.0,gdk_pixbuf-2.0.0.0,gtk-x11-2.0.0.0::x11/gtk+

VMEM_WARNING=		Yes
USE_CXX=		Yes
USE_X11=		Yes
USE_GMAKE=		Yes
# Regression tests are too hard to adapt to run here
NO_REGRESS=		Yes
SUBST_VARS=		LOCALBASE SO_EXTENSION SO_VERSION VER
SO_EXTENSION=		.${SO_VERSION}

MODGNU_RECURSE_DIRS=	${WRKSRC}/nsprpub ${WRKSRC}/directory/c-sdk ${WRKSRC}
CONFIGURE_STYLE=	autoconf no-autoheader
CONFIGURE_ARGS+=	--with-system-jpeg=${LOCALBASE}	\
			--with-system-png=${PNG_BASE}	\
			--with-system-zlib=/usr/lib	\
			--with-pthreads			\
			--without-system-nspr		\
			--enable-xft			\
			--enable-optimize=-Os		\
			--enable-default-toolkit=gtk2	\
			--disable-debug			\
			--disable-tests			\
			--disable-pedantic		\
			--disable-installer		\
			--disable-updater		\
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

post-patch:
.for dir in security/coreconf directory/c-sdk/config
	cd ${WRKSRC}/${dir} && \
	    ln -sf FreeBSD.mk MidnightBSD.mk && \
	    ln -sf OpenBSD.mk MirBSD.mk
.endfor

pre-configure:
	@perl -pi -e 's|_LOCALBASE_|${LOCALBASE}|g; s|_X11BASE_|${X11BASE}|g' \
		${WRKSRC}/browser/app/mozilla.in
	@perl -pi -e 's|_SO_VERSION_|${SO_VERSION}|g' \
		${WRKSRC}/nsprpub/pr/include/md/_openbsd.h \
		${WRKSRC}/xpcom/components/nsNativeComponentLoader.cpp

post-install:
	cd ${PREFIX} && \
	    mv -f bin/firefox bin/firesomething && \
	    mv -f firesomething/firefox-bin firesomething/firesomething-bin

.include <bsd.port.mk>
