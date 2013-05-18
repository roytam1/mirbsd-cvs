# $MirOS: ports/www/firesomething/Makefile,v 1.6 2005/07/06 19:21:37 bsiegert Exp $
# $OpenBSD: Makefile,v 1.10 2004/08/08 17:19:36 robert Exp $

BROKEN=			Kaput. I suggest ports/www/opera (BSD), K-Meleon (Win), Safari (Mac)

ONLY_FOR_PLATFORM=	*:*:alpha *:*:i386 *:*:sparc *:*:sparc64 *:*:amd64 *:*:powerpc
COMMENT=		"one of the successors to the Netscape browser engine"
VERSION=		0.8
DASH_VER=		-1
DISTNAME=		mozilla
PKGNAME=		firesomething-${VERSION}${DASH_VER}
CATEGORIES=		www
HOMEPAGE=		http://www.mozilla.org/projects/firefox/

# MPL; strange Trademark licence policy
PERMIT_PACKAGE_CDROM=	"trademark licencing issues"
PERMIT_PACKAGE_FTP=	"http://mozilla.org/foundation/licensing.html"
PERMIT_DISTFILES_CDROM=	"unsure of licencing implications"
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://ftp.eu.mozilla.org/pub/mozilla.org/firefox/releases/${VERSION}/ \
			http://ftp.mozilla.org/pub/firefox/releases/${VERSION}/
DISTFILES=		firefox-source-${VERSION}.tar.bz2

BUILD_DEPENDS=		:zip->=2.3:archivers/zip \
			:pkgconfig-*:devel/pkgconfig
LIB_DEPENDS=		gtk.1,gdk.1::x11/gtk+1 \
			glib.1,gmodule.1::devel/glib1 \
			IDL.4::devel/ORBit \
			jpeg.62::graphics/jpeg \
			png.3::graphics/png

VMEM_WARNING=		Yes
USE_CXX=		Yes
USE_X11=		Yes
USE_GMAKE=		Yes
# Regression tests are too hard to adapt to run here
NO_REGRESS=		Yes

MODGNU_CONFIG_GUESS_DIRS=	${WRKSRC}/build/autoconf \
				${WRKSRC}/nsprpub/build/autoconf \
				${WRKSRC}/directory/c-sdk/config/autoconf

CONFIGURE_STYLE=	autoconf no-autoheader
CONFIGURE_ARGS=		--with-system-jpeg=${LOCALBASE}	\
			--with-system-png=${LOCALBASE}	\
			--with-system-zlib=/usr/lib	\
			--with-pthreads			\
			--enable-xft			\
			--enable-optimize=-Os		\
			--disable-debug			\
			--disable-tests			\
			--disable-pedantic		\
			--disable-installer
# from browser/config/mozconfig
CONFIGURE_ARGS+=	--disable-ldap			\
			--disable-mailnews		\
			--enable-extensions=cookie,xml-rpc,xmlextras,p3p,pref,transformiix,universalchardet,typeaheadfind,webservices \
			--enable-crypto			\
			--disable-composer

# There is no problem with the propolice-enabled gcc3 on amd64 and sparc64,
# but it is reported to still be broken on others. XXX test that!
.if ${MACHINE_ARCH} != "amd64" && ${MACHINE_ARCH} != "sparc64"
CFLAGS+=		-fno-stack-protector
.endif

CONFIGURE_ENV=		MOZ_PHOENIX=1 \
			PKG_CONFIG_PATH="${LOCALBASE}/lib/pkgconfig:${X11BASE}/lib/pkgconfig"
MAKE_ENV=		MOZ_PHOENIX=1 \
			LD_LIBRARY_PATH="${WRKSRC}/dist/bin"

MOB=			${WRKSRC}/dist/bin
MOZ=			${PREFIX}/firesomething

post-extract:
	@cp ${FILESDIR}/xptc* ${WRKSRC}/xpcom/reflect/xptcall/src/md/unix/

post-patch:
.for dir in security/coreconf directory/c-sdk/config
	cd ${WRKSRC}/${dir} && ln -s OpenBSD.mk MirBSD.mk
.endfor

pre-configure:
.for dir in / nsprpub directory/c-sdk
	@cd ${WRKSRC}/${dir} && ${SETENV} ${AUTOCONF_ENV} ${AUTOCONF}
.endfor
	@perl -pi -e 's|_LOCALBASE_|${LOCALBASE}|g; s|_X11BASE_|${X11BASE}|g' \
		${WRKSRC}/browser/app/mozilla.in

do-install:
	${INSTALL_DATA_DIR} ${MOZ}
.for dir in chrome components defaults res searchplugins
	@cd ${MOB} && ${TAR} -chf - ${dir} | \
		${TAR} -xf - -C ${MOZ}
.endfor
	@cd ${MOB} && ${TAR} -chf - *.so.1.0 | \
		${TAR} -xf - -C ${MOZ}
	@chmod 444 ${MOZ}/*.so.1.0 ${MOZ}/components/*.so.1.0
	${INSTALL_SCRIPT} ${MOB}/firefox ${PREFIX}/bin/firesomething
	${INSTALL_SCRIPT} ${MOB}/run-mozilla.sh ${MOB}/mozilla-config ${MOZ}
	${INSTALL_PROGRAM} ${MOB}/regchrome ${MOB}/regxpcom ${MOB}/firefox-bin ${MOZ}

.include <bsd.port.mk>
