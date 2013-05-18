# $MirOS: ports/net/centericq/Makefile,v 1.23 2006/10/06 21:24:18 tg Exp $
# $OpenBSD: Makefile,v 1.24 2004/02/03 08:37:55 brad Exp $

# bus error on start
NOT_FOR_PLATFORM+=	Darwin:*:*

COMMENT=		curses-based multiprotocol IM client implementation
DISTNAME=		centericq-${V}
PKGNAME=		${DISTNAME}-${PL}
V=			4.21.0
PL=			7
CATEGORIES=		net
PATCHFILES=		centericq-${V}.msn.patch:0
PATCH_DIST_STRIP=	-p1
MASTER_SITES=		http://konst.org.ua/download/ \
			http://konst.home.welcomehome.org/ \
			http://centericq.de/archive/source/releases/
MASTER_SITES0=		http://unkie.org/tmp/ \
			http://centericq.de/archive/contrib/patches/
HOMEPAGE=		http://konst.org.ua/en/centericq
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>

# GNU GPLv2
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

FLAVORS=		no_msn gnupg
FLAVOR?=

GCC_VERSION!=		${CC} -v 2>&1 | fgrep "cc version" | sed 's!^.*cc version \([0-9\.]*\).*$!\1!'
.if ${GCC_VERSION:M3.2*} || ${GCC_VERSION:M3.3*}
FLAVOR+=		no_msn	# needs gcc 3.4+
.endif

MODULES+=		converters/libiconv
LIB_DEPENDS+=		curl::net/curl
LIB_DEPENDS+=		jpeg::graphics/jpeg
USE_GMAKE=		Yes
USE_CXX=		Yes

CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--disable-dependency-tracking \
			--enable-locales-fix \
			--disable-nls \
			--without-fribidi \
			--with-openssl \
			--with-libjpeg
CPPFLAGS+=		-DPORT_VERSION=\"${V}-${PL}\"

.if ${FLAVOR:L:Mno_msn}
CONFIGURE_ARGS+=	--disable-msn
.endif

.if ${FLAVOR:L:Mgnupg}
CONFIGURE_ARGS+=	--with-gpgme=${LOCALBASE:Q}
LIB_DEPENDS+=		gpgme::security/gpgme
.else
CONFIGURE_ARGS+=	--without-gpgme
.endif

MODGNU_CONFIG_GUESS_DIRS= ${WRKSRC} ${WRKSRC}/connwrap-0.1 \
			${WRKSRC}/firetalk-0.1 ${WRKSRC}/kkconsui-0.1 \
			${WRKSRC}/kkstrtext-0.1 ${WRKSRC}/kksystr-0.1 \
			${WRKSRC}/libgadu-0.1 ${WRKSRC}/libicq2000-0.1 \
			${WRKSRC}/libjabber-0.1 ${WRKSRC}/libmsn-3.2 \
			${WRKSRC}/libyahoo2-0.1

DOCS=			ChangeLog FAQ README

pre-patch:
	for dpatch in ${.CURDIR}/dpatch/*.dpatch.diff; do \
		${PATCH} ${PATCH_DIST_ARGS} <$$dpatch; \
	done
	for dpatch in ${.CURDIR}/dpatch/zzfix-*; do \
		${PATCH} ${PATCH_DIST_ARGS} <$$dpatch; \
	done
	for dpatch in ${WRKSRC}/debian/patches/*.dpatch; do \
		${PATCH} ${PATCH_DIST_ARGS} -l <$$dpatch; \
	done

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/centericq
	cd ${WRKSRC} && ${INSTALL_DATA} ${DOCS} ${PREFIX}/share/doc/centericq/
	${INSTALL_DATA} ${WRKSRC}/centericq.1 ${PREFIX}/man/man1/

.include <bsd.port.mk>

MODGNU_post-patch+=	( cd ${WRKSRC}; echo Running \
			    "autoheader-${AUTOCONF_VERSION} in ${WRKSRC}"; \
			${_SYSTRACE_CMD} ${SETENV} ${AUTOCONF_ENV} \
			    ${AUTOHEADER} );
