# $MirOS: ports/mailnews/courier-imap/Makefile,v 1.5 2008/03/09 17:23:04 tg Exp $
# $OpenBSD: Makefile,v 1.37 2004/02/16 17:14:52 avsm Exp $ 

COMMENT=			imap server for maildir format mailboxes
COMMENT-pop3=			pop3 server for maildir format mailboxes
COMMENT-ldap=			ldap authentication module for courier-imap
COMMENT-mysql=			mysql authentication module for courier-imap
COMMENT-pgsql=			pgsql authentication module for courier-imap

COURIERVER=	1.7.2
DISTNAME=	courier-imap-${COURIERVER}
FULLPKGNAME=	courier-imap-${COURIERVER}p0-0
FULLPKGNAME-pop3= courier-pop3-${COURIERVER}p0-0
FULLPKGNAME-ldap= courier-ldap-${COURIERVER}-0
FULLPKGNAME-mysql= courier-mysql-${COURIERVER}-0
FULLPKGNAME-pgsql= courier-pgsql-${COURIERVER}-0

CATEGORIES=	mail
MASTER_SITES=   ${MASTER_SITE_SOURCEFORGE:=courier/}
EXTRACT_SUFX=	.tar.bz2
HOMEPAGE=	http://www.inter7.com/courierimap/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MULTI_PACKAGES=	-pop3
SUBPACKAGE?=
FLAVOUR?=	no_mysql

COURIERCONF=	${SYSCONFDIR}/courier-imap
COURIERSTATE=	/var/run/courier-imap
SUBST_VARS=	COURIERSTATE COURIERCONF COURIERVER
EXAMPLE_DIR= 	${PREFIX}/share/examples/courier-imap
USE_GMAKE=	Yes

LIB_DEPENDS=	gdbm.2::databases/gdbm

CONFIGURE_STYLE= gnu old
CONFIGURE_ARGS=	--disable-root-check --datadir=${PREFIX}/sbin \
		--with-userdb=${SYSCONFDIR}/userdb --with-authuserdb \
		--sysconfdir=${COURIERCONF} --with-authdaemon \
		--with-authdaemonvar=${COURIERSTATE} \
		--enable-workarounds-for-imap-client-bugs \
		--with-db=gdbm --with-authpwd \
		--localstatedir=${COURIERSTATE} \
		--without-ipv6

# mysql
PSEUDO_FLAVOURS+=	no_mysql
.if ${FLAVOUR:L:Mno_mysql}
CONFIGURE_ARGS+=	--without-authmysql
.else
BROKEN=			depends on mysql, which is broken
MULTI_PACKAGES+=	-mysql
CONFIGURE_ARGS+=	--with-authmysql \
			--with-mysql-libs=${LOCALBASE}/lib/mysql \
			--with-mysql-includes=${LOCALBASE}/include/mysql
USE_CXX=		Yes
MYSQL_DEPENDS+=		lib/mysql/mysqlclient.10::databases/mysql
.endif

# openldap
PSEUDO_FLAVOURS+=	no_ldap
.if ${FLAVOUR:L:Mno_ldap}
CONFIGURE_ARGS+=	--without-authldap
.else
MULTI_PACKAGES+=	-ldap
CONFIGURE_ARGS+=	--with-authldap
LDAP_DEPENDS+=		ldap.2,lber.2:openldap-client-2.*:databases/openldap
.endif

# postgresql
PSEUDO_FLAVOURS+=	no_pgsql
.if !${FLAVOUR:L:Mno_pgsql}
MULTI_PACKAGES+=	-pgsql
CONFIGURE_ARGS+=	--with-pgsql-libs=${LOCALBASE}/lib \
			--with-pgsql-includes=${LOCALBASE}/include/postgresql
PGSQL_DEPENDS+=		pq.2::databases/postgresql
.endif

# pop3 has no dependencies
POP3_DEPENDS=

.if defined(PACKAGING) && !empty(SUBPACKAGE)
LIB_DEPENDS=            ${${SUBPACKAGE:U:S/-//g}_DEPENDS}
RUN_DEPENDS=		:courier-imap-${COURIERVER}:mailnews/courier-imap
.else
.for i in ${MULTI_PACKAGES}
LIB_DEPENDS+=           ${${i:U:S/-//g}_DEPENDS}
.endfor
.endif

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/courier-imap
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/courier-imap
.for i in pop3d-ssl imapd-ssl pop3d imapd
	${INSTALL_DATA} ${WRKINST}${COURIERCONF}/$i.dist ${EXAMPLE_DIR}/$i
.endfor
.for i in imapd.cnf pop3d.cnf quotawarnmsg.example
	${INSTALL_DATA} ${WRKINST}${COURIERCONF}/$i ${EXAMPLE_DIR}
.endfor
.for i in mysql ldap pgsql daemon
	-${INSTALL_DATA} ${WRKINST}${COURIERCONF}/auth${i}rc.dist \
			${EXAMPLE_DIR}/auth${i}rc
.endfor
.for i in authmysql.html authmysql.myownquery authpostgres.html ldap
	-${INSTALL_DATA} ${WRKSRC}/authlib/README.${i} \
			${PREFIX}/share/doc/courier-imap
.endfor
.for i in cram pwd userdb
	${INSTALL_PROGRAM} ${WRKBUILD}/authlib/auth${i} \
			${PREFIX}/libexec/authlib
.endfor

.include <bsd.port.mk>
