# $MirOS: ports/www/php/Makefile.inc,v 1.3 2005/04/10 21:51:47 tg Exp $
# $OpenBSD: Makefile.inc,v 1.1.1.1 2004/10/02 11:32:35 robert Exp $

# This port currently only works with archs supporting dynamic loading
# and has a httpd that supports DSOs.
NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

V=			5.0.4
HV=			0.2.7
#PV=			p0
DISTNAME=		php-${V}
CATEGORIES=		www lang
RESPONSIBLE=		Thorsten Glaser <tg@${_DOMAIN_DU_JOUR}>
HOMEPAGE=		http://www.php.net/ \
			http://www.hardened-php.net/
MASTER_SITES=		\
			http://no.php.net/distributions/ \
			http://uk.php.net/distributions/ \
			http://se.php.net/distributions/ \
			http://us2.php.net/distributions/
MASTER_SITES0=		\
			http://www.hardened-php.net/
PATCHFILES=		\
			hardened-php-${V}-${HV}.patch.gz:0
PATCH_DIST_STRIP=	-p1

# UPGRADERS: please read BOTH the PHP and Zend licenses
# and make sure they are safe before an upgrade
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	"modified versions must not be called PHP"
PERMIT_PACKAGE_FTP=	"modified versions must not be called PHP"

PHP_CONFIG_PATH=	/var/www/conf
PHP_CONFIG_FILE=	${PHP_CONFIG_PATH}/php.ini

# where the main php module is stored (outside the chroot)
HTTPD_MODULE_SUBDIR=	lib/php
HTTPD_MODULE_DIR=	${LOCALBASE}/${HTTPD_MODULE_SUBDIR}

# where the PEAR and extension modules are (inside the chroot)
CHROOT_DIR?=		/var/www
PEAR_DIR?=		${CHROOT_DIR}/pear
MODULES_SUBDIR=		lib/php/modules
MODULES_DIR=		${CHROOT_DIR}/${MODULES_SUBDIR}

CONFIGURE_STYLE=	autogen
AUTOGEN=		${SHELL} ${PORTSDIR}/www/php/files/autogen.sh
CONFIGURE_ENV+=		EXTENSION_DIR=${MODULES_DIR}
MAKE_ENV+=		${CONFIGURE_ENV}

CONFIGURE_ARGS+=	--enable-shared \
			--disable-static \
			--disable-rpath \
			--with-config-file-path=${PHP_CONFIG_PATH} \
			--with-config-file-scan-dir=${PHP_CONFIG_PATH}/php \
			--enable-inline-optimization \
			--with-pic

# default included extensions
CONFIGURE_ARGS+= 	--with-openssl \
			--with-zlib

REGRESS_TARGET=		test
REGRESS_FLAGS=		NO_INTERACTION=1

CHECKSUM_FILE?=		${PORTSDIR}/www/php/distinfo
PATCH_LIST=		${PORTSDIR}/www/php/patches/patch-* \
			patch-*

post-extract:
	@rm -f ${WRKSRC}/ext/standard/*.orig
