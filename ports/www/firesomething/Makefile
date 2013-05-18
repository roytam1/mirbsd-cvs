# $MirOS: ports/www/firesomething/Makefile,v 1.11 2006/07/30 15:07:23 bsiegert Exp $
# $OpenBSD: Makefile,v 1.41 2005/11/15 09:21:52 wilfried Exp $

ONLY_FOR_PLATFORM=	*:*:alpha *:*:i386 *:*:sparc *:*:sparc64 *:*:amd64 *:*:powerpc
COMMENT=			one of the successors to the Netscape browser engine
VER=			1.5.0.5
DASH_VER=		-0
DISTNAME=		mozilla
PKGNAME=		firesomething-${VER}${DASH_VER}
CATEGORIES=		www
HOMEPAGE=		http://www.mozilla.org/projects/firefox/

SO_VERSION=		8.0

# mozilla public license
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://releases.mozilla.org/pub/mozilla.org/firefox/releases/${VER}/source/ \
			http://ftp.eu.mozilla.org/pub/mozilla.org/firefox/releases/${VER}/source/ \
			http://ftp.mozilla.org/pub/mozilla.org/firefox/releases/${VER}/source/
DISTFILES=		firefox-${VER}-source.tar.bz2

MODULES+=		devel/gettext devel/pkgconfig
RUN_DEPENDS=		:esound-*:audio/esound
BUILD_DEPENDS=		:libIDL-*:devel/libIDL \
			:zip->=2.3:archivers/zip \
			:pkgconfig-*:devel/pkgconfig
LIB_DEPENDS=		gdk-x11-2.0.0.0,gdk_pixbuf-2.0.0.0,gtk-x11-2.0.0.0::x11/gtk+

VMEM_WARNING=		Yes
USE_CXX=		Yes
USE_X11=		Yes
USE_GMAKE=		Yes
# Regression tests are too hard to adapt to run here
NO_REGRESS=		Yes
SUBST_VARS=		LOCALBASE SO_VERSION

MODGNU_CONFIG_GUESS_DIRS=	${WRKSRC} \
				${WRKSRC}/nsprpub

CONFIGURE_STYLE=	autoconf no-autoheader
CONFIGURE_ARGS=		--with-system-jpeg=${LOCALBASE}	\
			--with-system-png=${LOCALBASE}	\
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
			LD_LIBRARY_PATH="${WRKSRC}/dist/bin" \
			SO_VERSION="${SO_VERSION}"
CONFIGURE_ENV=		${MAKE_ENV}

MOB=			${WRKSRC}/dist/bin
MOZ=			${PREFIX}/firesomething

post-extract:
	@cp ${FILESDIR}/xptc* ${WRKSRC}/xpcom/reflect/xptcall/src/md/unix/

post-patch:
.for dir in security/coreconf directory/c-sdk/config
	cd ${WRKSRC}/${dir} && ln -s OpenBSD.mk MirBSD.mk
.endfor

pre-configure:
	@perl -pi -e 's|_LOCALBASE_|${LOCALBASE}|g; s|_X11BASE_|${X11BASE}|g' \
		${WRKSRC}/browser/app/mozilla.in
	@perl -pi -e 's|_SO_VERSION_|${SO_VERSION}|g' \
		${WRKSRC}/nsprpub/pr/include/md/_openbsd.h \
		${WRKSRC}/xpcom/components/nsNativeComponentLoader.cpp

do-install:
.for dir in chrome components defaults extensions greprefs res searchplugins
	${INSTALL_DATA_DIR} ${MOZ}/${dir}
	cd ${MOB} && ${TAR} -chf - ${dir} | \
		${TAR} -xf - -C ${MOZ}
.endfor
	cd ${MOB} && ${TAR} -chf - *.so.?.? | \
		${TAR} -xf - -C ${MOZ}
	chmod 444 ${MOZ}/*.so.?.? ${MOZ}/components/*.so.?.? ${MOZ}/components/*.js
	${INSTALL_DATA} ${WRKSRC}/LICENSE ${MOZ}

	${INSTALL_DATA} ${WRKSRC}/browser/app/mozicon16.xpm ${WRKSRC}/browser/app/mozicon50.xpm ${MOZ}
	${INSTALL_SCRIPT} ${MOB}/firefox ${PREFIX}/bin/firesomething
	${INSTALL_SCRIPT} ${MOB}/firefox-config ${PREFIX}/bin/
	ln -f ${PREFIX}/bin/firesomething ${PREFIX}/bin/firefox
	${INSTALL_SCRIPT} ${MOB}/run-mozilla.sh ${MOZ}
	${INSTALL_PROGRAM} ${MOB}/regxpcom ${MOB}/mozilla-xremote-client ${MOZ}
	${INSTALL_PROGRAM} ${MOB}/firefox-bin ${MOZ}/firesomething-bin
	ln -f ${MOZ}/firesomething-bin ${MOZ}/firefox-bin

.include <bsd.port.mk>
