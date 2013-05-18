# $MirOS: ports/net/pure-ftpd/Makefile,v 1.6 2008/03/09 17:23:22 tg Exp $
# $OpenBSD: Makefile,v 1.31 2004/03/08 03:57:16 brad Exp $

COMMENT=	small, easy to set up, fast and very secure FTP server
DISTNAME=	pure-ftpd-1.0.18
DASH_VER=	1
CATEGORIES=	net
MASTER_SITES=	ftp://ftp.pureftpd.org/pub/pure-ftpd/releases/ \
		ftp://ftp2.fr.pureftpd.org/pub/mirrors/ftp.fr.pureftpd.org/pub/pure-ftpd/releases/ \
		ftp://ftp3.fr.pureftpd.org/pure-ftpd/releases/ \
		ftp://ftp.dk.pureftpd.org/mirrors/pure-ftpd/releases/ \
		ftp://ftp.es.pureftpd.org/mirror/pureftpd/latest/releases/ \
		ftp://ftp.nl.pureftpd.org/pub/pure-ftpd/releases/ \
		ftp://ftp.fr.pureftpd.org/pub/pure-ftpd/releases/ \
		ftp://ftp.cn.pureftpd.org/pub/pureftpd/pure-ftpd/releases/ \
		${MASTER_SITE_SOURCEFORGE:=pureftpd/}
HOMEPAGE=	http://www.pureftpd.org/

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE= gnu
CONFIGURE_ARGS+= --with-everything \
		 --with-paranoidmsg \
		 --with-privsep \
		 --with-tls \
		 --with-largefile

FLAVOURS=	ldap mysql postgresql no_banner virtual_chroot
FLAVOUR?=

.if ${FLAVOUR:L:Mldap}
LIB_DEPENDS+=	ldap.2,lber:openldap-client-2.*:databases/openldap
CONFIGURE_ARGS+=--with-ldap="${LOCALBASE}"
DOCS+=		README.LDAP pureftpd.schema
CONF_FILE+= 	pureftpd-ldap.conf
.endif

.if ${FLAVOUR:L:Mmysql}
BROKEN=			depends on mysql, which is broken
USE_CXX=	Yes
LIB_DEPENDS+= lib/mysql/mysqlclient.10::databases/mysql
CONFIGURE_ARGS+= --with-mysql="${LOCALBASE}"
DOCS+=	README.MySQL
CONF_FILE+= pureftpd-mysql.conf
.endif

.if ${FLAVOUR:L:Mpostgresql}
PERMIT_PACKAGE_CDROM=	dependency databases/postgresql is not allowed for CDROM
LIB_DEPENDS+=	pq.2::databases/postgresql
CONFIGURE_ARGS+=--with-pgsql="${LOCALBASE}"
DOCS+=		README.PGSQL
CONF_FILE+= 	pureftpd-pgsql.conf
.endif

.if ${FLAVOUR:L:Mno_banner}
CONFIGURE_ARGS+=--without-banner
.endif

.if ${FLAVOUR:L:Mvirtual_chroot}
CONFIGURE_ARGS+=--with-virtualchroot
.endif

DOCS+=	README README.Configuration-File README.Contrib README.TLS \
	README.Virtual-Users README.Authentication-Modules pure-ftpd.png

CONTRIB= xml_python_processors.txt pure-vpopauth.pl

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/pure-ftpd
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/pure-ftpd
	${INSTALL_PROGRAM} ${WRKBUILD}/configuration-file/pure-config.pl \
		${PREFIX}/sbin
	${INSTALL_DATA} ${WRKBUILD}/configuration-file/pure-ftpd.conf \
		${PREFIX}/share/examples/pure-ftpd/pure-ftpd.conf.sample
	cd ${WRKSRC}; ${INSTALL_DATA} ${DOCS} ${PREFIX}/share/doc/pure-ftpd
.if defined(CONF_FILE) && !empty(CONF_FILE)
	cd ${WRKSRC}; ${INSTALL_DATA} ${CONF_FILE} \
		${PREFIX}/share/examples/pure-ftpd
.endif
	cd ${WRKSRC}/contrib; ${INSTALL_DATA} ${CONTRIB} \
		${PREFIX}/share/examples/pure-ftpd

.include <bsd.port.mk>
