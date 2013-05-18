# $MirOS: ports/www/php/extensions/Makefile,v 1.28 2009/08/16 17:25:53 tg Exp $
# $OpenBSD: Makefile,v 1.17 2005/12/29 23:06:28 sturm Exp $

FULLPKGNAME=		php-extensions-${VSN}-${DASH_VER}
COMMENT=		informational package about PHP5 extensions

MULTI_PACKAGES=
SUBPACKAGE?=

# extensions get installed under the httpd chroot
PREFIX?=		${CHROOT_DIR}

FLAVOURS=
FLAVOUR?=

BUILD_DEPENDS+=		${CORE_LIB_DEPENDS}
RUN_DEPENDS+=		${CORE_DEPENDENCY}

GRAPHIC_DEPENDS=	jpeg.62::graphics/jpeg
MODPNG_AUTODEPS=	No
MODULES+=		graphics/png
GRAPHIC_DEPENDS+=	${MODPNG_DEPENDS}

GRAPHIC_CONFIG=		--with-jpeg-dir=${LOCALBASE:Q} \
			--with-png-dir=${PNG_BASE:Q} \
			--with-zlib-dir=/usr

.include <mirports.sys.mk>

# bz2
PSEUDO_FLAVOURS+=	no_bz2
.if ${FLAVOUR:L:Mno_bz2}
CONFIGURE_ARGS+=	--without-bz2
.else
MULTI_PACKAGES+=	-bz2
COMMENT-bz2=		bzip2 compression extensions for php
CONFIGURE_ARGS+=	--with-bz2=shared,${LOCALBASE:Q}
BZ2_DEPENDS=		bz2::archivers/bzip2
.endif

# curl
PSEUDO_FLAVOURS+=	no_curl
.if ${FLAVOUR:L:Mno_curl}
CONFIGURE_ARGS+=	--without-curl
.else
MULTI_PACKAGES+=	-curl
COMMENT-curl=		curl URL library extensions for php
CONFIGURE_ARGS+=	--with-curl=shared,${LOCALBASE:Q}
CURL_DEPENDS=		curl::net/curl
.endif

# dba
PSEUDO_FLAVOURS+=	no_dba
.if ${FLAVOUR:L:Mno_dba}
CONFIGURE_ARGS+=	--disable-dba
.else
MULTI_PACKAGES+=	-dba
COMMENT-dba=		dba GDBM access extensions for php
CONFIGURE_ARGS+=	--enable-dba=shared --with-gdbm=${LOCALBASE:Q}
DBA_DEPENDS=		gdbm::databases/gdbm
.endif

# dbase
PSEUDO_FLAVOURS+=	no_dbase
.if ${FLAVOUR:L:Mno_dbase}
CONFIGURE_ARGS+=	--disable-dbase
.else
MULTI_PACKAGES+=	-dbase
COMMENT-dbase=		dBase database access extensions for php
CONFIGURE_ARGS+=	--enable-dbase=shared
.endif

# dbx
PSEUDO_FLAVOURS+=	no_dbx
.if ${FLAVOUR:L:Mno_dbx}
CONFIGURE_ARGS+=	--disable-dbx
.else
MULTI_PACKAGES+=	-dbx
COMMENT-dbx=		dbx database abstraction interface for php
CONFIGURE_ARGS+=	--enable-dbx=shared
.endif

# fam
PSEUDO_FLAVOURS+=	no_fam
.if ${FLAVOUR:L:Mno_fam}
CONFIGURE_ARGS+=	--disable-fam
.else
MULTI_PACKAGES+=	-fam
COMMENT-fam=		filesystem alteration monitor extensions for php
CONFIGURE_ARGS+=	--with-fam=shared,${LOCALBASE:Q}
FAM_DEPENDS=		fam::sysutils/fam
.endif

# filepro
PSEUDO_FLAVOURS+=	no_filepro
.if ${FLAVOUR:L:Mno_filepro}
CONFIGURE_ARGS+=	--disable-filepro
.else
MULTI_PACKAGES+=	-filepro
COMMENT-filepro=	filepro database access extensions for php
CONFIGURE_ARGS+=	--enable-filepro=shared
.endif

# gd
PSEUDO_FLAVOURS+=	no_gd
.if ${FLAVOUR:L:Mno_gd}
CONFIGURE_ARGS+=	--without-gd --without-xpm-dir --without-ttf \
			--without-freetype-dir
.else
MULTI_PACKAGES+=	-gd
COMMENT-gd=		image manipulation extensions for php
GD_DEPENDS=		${GRAPHIC_DEPENDS} \
			t1:t1lib->=5.1.2:devel/t1lib
USE_X11=		yes
# uses the bundled libgd2, we only have libgd1 in ports
CONFIGURE_ARGS+=	--with-gd=shared \
			${GRAPHIC_CONFIG} \
			--with-freetype-dir=${X11BASE:Q} \
			--enable-gd-native-ttf \
			--with-xpm-dir=${X11BASE:Q} \
			--with-t1lib=${LOCALBASE:Q}
.endif

# gmp
PSEUDO_FLAVOURS+=	no_gmp
.if ${FLAVOUR:L:Mno_gmp}
CONFIGURE_ARGS+=	--without-gmp
.else
MULTI_PACKAGES+=	-gmp
COMMENT-gmp=		gmp math library support for php
CONFIGURE_ARGS+=	--with-gmp=shared,${LOCALBASE:Q}
GMP_DEPENDS=		gmp::devel/gmp
.endif

# imap
PSEUDO_FLAVOURS+=	no_imap
.if ${FLAVOUR:L:Mno_imap}
CONFIGURE_ARGS+=	--without-imap --without-kerberos
.else
MULTI_PACKAGES+=	-imap
COMMENT-imap=		imap, pop3 and nntp extensions for php
CONFIGURE_ARGS+=	--with-imap=shared,${LOCALBASE:Q} --with-imap-ssl
.  if ${OStype} == "OpenBSD"
CONFIGURE_ARGS+=	--with-kerberos=/usr
.  endif
BUILD_DEPENDS+=		:c-client->=4.64-7:mailnews/pine,-cclient
.endif

# ldap
PSEUDO_FLAVOURS+=	no_ldap
.if ${FLAVOUR:L:Mno_ldap}
CONFIGURE_ARGS+=	--without-ldap
.else
MULTI_PACKAGES+=	-ldap
COMMENT-ldap=		ldap protocol extensions for php
CONFIGURE_ARGS+=	--with-ldap=shared,${LOCALBASE:Q}
LDAP_DEPENDS=		ldap,lber::databases/openldap
.endif

# mcrypt
PSEUDO_FLAVOURS+=	no_mcrypt
.if ${FLAVOUR:L:Mno_mcrypt}
CONFIGURE_ARGS+=	--without-mcrypt
.else
MULTI_PACKAGES+=	-mcrypt
COMMENT-mcrypt=		mcrypt encryption/decryption extensions for php
CONFIGURE_ARGS+=	--with-mcrypt=shared,${LOCALBASE:Q}
MCRYPT_DEPENDS=		mcrypt::security/libmcrypt ltdl::devel/libtool
.endif

# mhash
PSEUDO_FLAVOURS+=	no_mhash
.if ${FLAVOUR:L:Mno_mhash}
CONFIGURE_ARGS+=	--without-mhash
.else
MULTI_PACKAGES+=	-mhash
COMMENT-mhash=		mhash extensions for php
CONFIGURE_ARGS+=	--with-mhash=shared,${LOCALBASE:Q}
MHASH_DEPENDS=		mhash::security/mhash
.endif

# mysql
PSEUDO_FLAVOURS+=	no_mysql
FLAVOUR+=		no_mysql	# since it's broken
.if ${FLAVOUR:L:Mno_mysql}
CONFIGURE_ARGS+=	--without-mysql
.else
MULTI_PACKAGES+=	-mysql
COMMENT-mysql=		mysql database access extensions for php
CONFIGURE_ARGS+=	--with-mysql=shared,${LOCALBASE:Q}
MYSQL_DEPENDS=		lib/mysql/mysqlclient::databases/mysql
USE_CXX=		Yes
.endif

# ncurses
PSEUDO_FLAVOURS+=	no_ncurses
.if ${FLAVOUR:L:Mno_ncurses}
CONFIGURE_ARGS+=	--without-ncurses
.else
MULTI_PACKAGES+=	-ncurses
COMMENT-ncurses=	ncurses extensions for php
CONFIGURE_ARGS+=	--with-ncurses=shared,${LOCALBASE:Q}
.endif

# odbc
PSEUDO_FLAVOURS+=	no_odbc
.if ${FLAVOUR:L:Mno_odbc}
CONFIGURE_ARGS+=	--without-odbc
.else
MULTI_PACKAGES+=	-odbc
COMMENT-odbc=		odbc database access extensions for php
CONFIGURE_ARGS+=	--with-iodbc=shared
ODBC_DEPENDS=		iodbc::databases/iodbc
.endif

# pgsql
PSEUDO_FLAVOURS+=	no_pgsql
.if ${FLAVOUR:L:Mno_pgsql}
CONFIGURE_ARGS+=	--without-pgsql
.else
MULTI_PACKAGES+=	-pgsql
COMMENT-pgsql=		pgsql database access extensions for php
CONFIGURE_ARGS+=	--with-pgsql=shared,${LOCALBASE:Q}
PGSQL_DEPENDS=		pq::databases/postgresql
.endif

# shmop
PSEUDO_FLAVOURS+=	no_shmop
.if ${FLAVOUR:L:Mno_shmop}
CONFIGURE_ARGS+=	--disable-shmop
.else
MULTI_PACKAGES+=	-shmop
COMMENT-shmop=		shared memory extensions for php
CONFIGURE_ARGS+=	--enable-shmop=shared
.endif

# soap
PSEUDO_FLAVOURS+=	no_soap
.if ${FLAVOUR:L:Mno_soap}
CONFIGURE_ARGS+=	--without-soap
.else
MULTI_PACKAGES+=	-soap
COMMENT-soap=		SOAP functions for php
CONFIGURE_ARGS+=	--enable-soap=shared
.endif

# snmp
PSEUDO_FLAVOURS+=	no_snmp
.if ${FLAVOUR:L:Mno_snmp}
CONFIGURE_ARGS+=	--without-snmp
.else
MULTI_PACKAGES+=	-snmp
COMMENT-snmp=		snmp protocol extensions for php
CONFIGURE_ARGS+=	--with-snmp=shared,${LOCALBASE:Q} --enable-ucd-snmp-hack
SNMP_DEPENDS=		snmp::net/ucd-snmp
.endif

# sybase-ct
PSEUDO_FLAVOURS+=	no_sybase_ct
.if ${FLAVOUR:L:Mno_sybase_ct}
CONFIGURE_ARGS+=	--without-sybase-ct
.else
MULTI_PACKAGES+=	-sybase_ct
COMMENT-sybase_ct=	sybase database access extensions for php
CONFIGURE_ARGS+=	--with-sybase-ct=shared,${LOCALBASE:Q}
SYBASE_CT_DEPENDS=	ct::databases/freetds
.endif

# xml-rpc
PSEUDO_FLAVOURS+=	no_xmlrpc
.if ${FLAVOUR:L:Mno_xmlrpc}
CONFIGURE_ARGS+=	--without-xmlrpc
.else
MULTI_PACKAGES+=	-xmlrpc
COMMENT-xmlrpc=		XML RPC functions for php
CONFIGURE_ARGS+=	--with-xmlrpc=shared
.  if ${OStype} != "MirBSD"
XMLRPC_DEPENDS=		expat::textproc/expat
.  endif
.endif

# xsl
PSEUDO_FLAVOURS+=	no_xsl
.if ${FLAVOUR:L:Mno_xsl}
CONFIGURE_ARGS+=	--without-xsl
.else
MULTI_PACKAGES+=	-xsl
COMMENT-xsl=		XSL functions for php
CONFIGURE_ARGS+=	--with-xsl=shared,${LOCALBASE:Q} --enable-dom
XSL_DEPENDS=		xslt,exslt::textproc/libxslt
.endif

.for i in ${MULTI_PACKAGES}
.  if !defined(FULLPKGNAME${i})
DASH_VER${i}?=		${DASH_VER}
FULLPKGNAME${i}=	php${i}-${VSN}-${DASH_VER${i}}
.  endif
.endfor

.if defined(PACKAGING) && !empty(SUBPACKAGE)
MODULE_NAME=		${SUBPACKAGE:S/-//g}
LIB_DEPENDS+=		${${MODULE_NAME:U}_DEPENDS}
MESSAGE=		${PKGDIR}/MESSAGE
SUBST_VARS=		MODULE_NAME PHP_CONFIG_FILE LOCALBASE
.elif defined(PACKAGING) && empty(SUBPACKAGE)
LIB_DEPENDS=
MESSAGE=		${PKGDIR}/DESCR
.else
.  for i in ${MULTI_PACKAGES}
LIB_DEPENDS+=		${${i:U:S/-//g}_DEPENDS}
.  endfor
.endif

ALL_TARGET=		build-modules

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/${MODULES_SUBDIR}
.for m in ${MULTI_PACKAGES:S/-//g}
	${INSTALL_DATA} ${WRKBUILD}/modules/${m}.so \
		${PREFIX}/${MODULES_SUBDIR}/${m}.so
.endfor

.include <bsd.port.mk>
