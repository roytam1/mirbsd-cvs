# $MirOS: ports/www/php/Makefile.inc,v 1.20 2010/01/28 15:59:40 tg Exp $
# $OpenBSD: Makefile.inc,v 1.1.1.1 2004/10/02 11:32:35 robert Exp $

.include <mirports.sys.mk>

# This port currently only works with archs supporting dynamic loading
# and has a httpd that supports DSOs.
NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

VSN=			5.0.5
HV=			0.4.8
DASH_VER=		6
DISTNAME=		php-${VSN}
CATEGORIES=		www lang
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>
HOMEPAGE=		http://www.php.net/ \
			http://www.hardened-php.net/
MASTER_SITES=		http://museum.php.net/php5/
MASTER_SITES0=		http://www.hardened-php.net/
PATCHFILES=		hardening-patch-${VSN}-${HV}.patch.gz:0
PATCH_DIST_STRIP=	-p1

# UPGRADERS: please read BOTH the PHP and Zend licenses
# and make sure they are safe before an upgrade
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	"modified versions must not be called PHP"
PERMIT_PACKAGE_FTP=	"modified versions must not be called PHP"

PHP_CONFIG_PATH=	${WWW_PREFIX}/conf
PHP_CONFIG_FILE=	${PHP_CONFIG_PATH}/php.ini

# where the main php module is stored (outside the chroot)
HTTPD_MODULE_SUBDIR=	lib/php
HTTPD_MODULE_DIR=	${LOCALBASE}/${HTTPD_MODULE_SUBDIR}

# where the PEAR and extension modules are (inside the chroot)
CHROOT_DIR?=		${WWW_PREFIX}
PEAR_DIR?=		${CHROOT_DIR}/pear
MODULES_SUBDIR=		lib/php/modules
MODULES_DIR=		${CHROOT_DIR}/${MODULES_SUBDIR}

CONFIGURE_STYLE=	autogen
AUTOGEN=		${MKSH} ${PORTSDIR}/www/php/files/autogen.sh
CONFIGURE_ENV+=		EXTENSION_DIR=${MODULES_DIR}
EXTRA_MAKE_ENV+=	${CONFIGURE_ENV}

CONFIGURE_ARGS+=	--enable-shared \
			--disable-static \
			--disable-short-tags \
			--with-config-file-path=${PHP_CONFIG_PATH:Q} \
			--with-config-file-scan-dir=${PHP_CONFIG_PATH:Q}/php \
			--enable-inline-optimization \
			--with-libxml-dir=${LOCALBASE:Q} \
			--with-iconv=${ICONV_PREFIX:Q} \
			--with-sqlite=${LOCALBASE:Q} \
			--with-libedit \
			--without-gettext \
			--disable-sqlite-utf8 \
			--with-apxs=/usr/sbin/apxs \
			--without-mysql \
			--enable-xml \
			--enable-wddx \
			--enable-cli \
			--enable-dio \
			--with-pear=${PEAR_DIR:Q} \
			--enable-bcmath \
			--enable-session \
			--enable-trans-sid \
			--enable-calendar \
			--enable-ctype \
			--enable-ftp \
			--enable-mbstring \
			--with-pcre-regex \
			--with-posix \
		 	--with-openssl \
			--with-zlib \
			--enable-sockets \
			--enable-sysvsem \
			--enable-sysvshm \
			--enable-exif \
			--with-pic

.if ${OStype} == "MirBSD"
CONFIGURE_ARGS+=	--disable-yp
.else
CONFIGURE_ARGS+=	--enable-yp
.endif

MODULES+=		converters/libiconv
CORE_DEPENDENCY=	:php-core-${VSN}-${DASH_VER}:www/php/core
CORE_LIB_DEPENDS+=	xml2::textproc/libxml \
			sqlite::databases/sqlite2

CONFIGURE_ENV+=		TERM=vt100

REGRESS_TARGET=		test
REGRESS_FLAGS=		NO_INTERACTION=1

CHECKSUM_FILE?=		${PORTSDIR}/www/php/distinfo
PATCH_LIST=		${PORTSDIR}/www/php/patches/patch-* \
			patch-*

post-extract:
	@rm -f ${WRKSRC}/ext/standard/*.orig
