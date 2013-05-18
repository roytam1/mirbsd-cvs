# $MirOS: ports/net/centericq/Makefile,v 1.37 2009/08/16 17:18:16 tg Exp $
# $OpenBSD: Makefile,v 1.24 2004/02/03 08:37:55 brad Exp $

# bus error on start
NOT_FOR_PLATFORM+=	Darwin:*:*

COMMENT=		curses-based multiprotocol IM client implementation
DISTNAME=		centericq-${VSN}
VSN=			4.21.0
DASH_VER=		15
CATEGORIES=		net
PATCHFILES=		centericq-${VSN}.msn.patch:0
PATCH_DIST_STRIP=	-p1
MASTER_SITES=		http://konst.org.ua/download/ \
			http://konst.home.welcomehome.org/ \
			http://centericq.de/archive/source/releases/
# unfetchable
#MASTER_SITES0=		http://unkie.org/tmp/ \
#			http://centericq.de/archive/contrib/patches/
MASTER_SITES0=		${_MASTER_SITE_MIRBSD}
HOMEPAGE=		http://konst.org.ua/en/centericq
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>

# GNU GPLv2
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

FLAVOURS=		no_msn
FLAVOUR?=

.ifndef GCC_VERSION
GCC_VERSION!=		${_ORIG_CC} -v 2>&1 | fgrep "cc version" | sed 's!^.*cc version \([0-9\.]*\).*$!\1!'
.MAKEFLAGS:=		${.MAKEFLAGS} GCC_VERSION=${GCC_VERSION:Q}
.endif
.if ${GCC_VERSION:M3.2*} || ${GCC_VERSION:M3.3*}
FLAVOUR+=		no_msn	# needs gcc 3.4+
.endif

MODULES+=		converters/libiconv
LIB_DEPENDS+=		curl::net/curl
LIB_DEPENDS+=		jpeg::graphics/jpeg
USE_GMAKE=		Yes
USE_CXX=		Yes

CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--enable-locales-fix \
			--disable-nls \
			--without-fribidi \
			--with-openssl \
			--with-libjpeg
CPPFLAGS+=		-DPORT_VERSION=\"${VSN}-${DASH_VER}\"

.if ${FLAVOUR:L:Mno_msn}
CONFIGURE_ARGS+=	--disable-msn
.endif

CONFIGURE_ARGS+=	--with-gpgme=${LOCALBASE:Q}
LIB_DEPENDS+=		gpgme::security/gpgme

MODGNU_RECURSE_DIRS=	${WRKSRC}/connwrap-0.1 ${WRKSRC}/firetalk-0.1 \
			${WRKSRC}/kkconsui-0.1 ${WRKSRC}/kkstrtext-0.1 \
			${WRKSRC}/kksystr-0.1 ${WRKSRC}/libgadu-0.1 \
			${WRKSRC}/libicq2000-0.1 ${WRKSRC}/libjabber-0.1 \
			${WRKSRC}/libmsn-3.2 ${WRKSRC}/libyahoo2-0.1 ${WRKSRC}

DOCS=			ChangeLog FAQ README

post-extract:
	cp ${FILESDIR}/sautoconv.c ${WRKSRC}/connwrap-0.1/

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
	${INSTALL_SCRIPT} ${FILESDIR}/cicq2log.sh ${PREFIX}/bin/cicq2log

.include <bsd.port.mk>

MODGNU_post-patch+=	( cd ${WRKSRC}; echo Running \
			    "autoheader-${AUTOCONF_VERSION} in ${WRKSRC}"; \
			${_SYSTRACE_CMD} ${SETENV} ${AUTOCONF_ENV} \
			    ${AUTOHEADER} );
