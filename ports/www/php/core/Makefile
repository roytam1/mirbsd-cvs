# $MirOS: ports/www/php/core/Makefile,v 1.13 2006/02/21 17:40:12 tg Exp $
# $OpenBSD: Makefile,v 1.12 2005/12/29 23:03:29 sturm Exp $

MULTI_PACKAGES=		-pear
SUBPACKAGE?=

COMMENT=			server-side HTML-embedded scripting language
COMMENT-pear=			base classes for common PHP tasks
PKGNAME=		php-core-${V}-${PV}
FULLPKGNAME-pear=	php-pear-${V}-${PV}

CONFIGURE_ARGS+=	--with-apxs=/usr/sbin/apxs \
			--without-mysql \
			--enable-xml \
			--with-libxml-dir=${LOCALBASE:Q} \
			--enable-wddx \
			--enable-cli \
			--with-iconv=${ICONV_PREFIX:Q} \
			--without-gettext \
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
			--enable-sockets \
			--enable-sysvsem \
			--enable-sysvshm \
			--enable-exif \
			--with-libedit \
			--with-sqlite=${LOCALBASE:Q} \
			--disable-sqlite-utf8

.include <mirports.sys.mk>

.if ${OStype} == "MirBSD"
CONFIGURE_ARGS+=	--disable-yp
.else
CONFIGURE_ARGS+=	--enable-yp
.endif

MODULES+=		converters/libiconv

# some variables to substitute
SUBST_VARS+=		PHP_CONFIG_FILE PHP_CONFIG_PATH WWW_PREFIX
PHP_VERSION=		${V}

.for i in TRUEPREFIX PHP_CONFIG_FILE MODULES_DIR PHP_VERSION HTTPD_MODULE_DIR
PHPXS_SUBST+=		-e 's,${i},${${i}},'
.endfor

.if defined(PACKAGING) && !empty(SUBPACKAGE)
PREFIX=			${CHROOT_DIR}
RUN_DEPENDS=		:php-core-${V}-${PV}:www/php/core
MODULES=
.else
LIB_DEPENDS+=		xml2::textproc/libxml \
			sqlite::databases/sqlite2
.endif

pre-fake:
	${INSTALL_DATA_DIR} ${PREFIX}/${HTTPD_MODULE_SUBDIR}

INSTALL_TARGET= 	install-pear install-headers install-build \
			install-programs
FAKE_FLAGS= 		INSTALL_ROOT=${DESTDIR}

pre-configure:
	perl -p -i.orig -e "s,MIRPORTS_PEAR_ROOT,'${CHROOT_DIR}/pear',g" \
	    ${WRKSRC}/pear/PEAR/Config.php \
	    ${WRKSRC}/scripts/phpize.in \
	    ${WRKSRC}/scripts/php-config.in
	-rm -f ${WRKSRC}/build/libtool.m4
	cp ${WRKSRC}/libtool.m4 ${WRKSRC}/build/

post-install:
	${INSTALL_DATA} ${WRKBUILD}/.libs/libphp5.so \
	    ${PREFIX}/${HTTPD_MODULE_SUBDIR}
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/php
	${INSTALL_PROGRAM} ${WRKBUILD}/sapi/cli/php ${PREFIX}/bin
.for i in dist recommended
	sed -e 's,MODULES_DIR,${MODULES_DIR},' \
	     -e 's,MIRPORTS_INCLUDE_PATH,/pear/lib:${CHROOT_DIR}/pear/lib,' \
		<${WRKSRC}/php.ini-${i} \
		>${PREFIX}/share/doc/php/php.ini-${i}
.endfor
	${INSTALL_DATA} ${WRKSRC}/LICENSE ${PREFIX}/share/doc/php/LICENSE.php
	${INSTALL_DATA} ${WRKSRC}/Zend/LICENSE \
	    ${PREFIX}/share/doc/php/LICENSE.zend
	${INSTALL_DATA} ${WRKSRC}/NEWS ${PREFIX}/share/doc/php/
	sed ${PHPXS_SUBST} <${FILESDIR}/phpxs >${PREFIX}/sbin/phpxs
	chown ${BINOWN}:${BINGRP} ${PREFIX}/sbin/phpxs
	chmod ${BINMODE} ${PREFIX}/sbin/phpxs
	${INSTALL_MAN} ${WRKSRC}/sapi/cli/php.1 ${PREFIX}/man/man1/
	mv ${WRKINST}${SYSCONFDIR}/pear.conf ${WRKINST}${PEAR_DIR}/data/

.include <bsd.port.mk>
