# $MirOS: ports/net/proftpd/Makefile,v 1.1.7.1 2005/03/18 15:48:55 tg Exp $

COMMENT=        highly configurable ftp daemon
DISTNAME=	proftpd-1.2.9
CATEGORIES=	net
HOMEPAGE=	http://www.proftpd.org/
MASTER_SITES=	ftp://ftp.proftpd.net/distrib/source/ \
		ftp://ftp.stikman.com/pub/proftpd/ \
		ftp://ftp.empora.de/pub/mirrors/ftp.proftpd.org/ \
		ftp://ftp.fastorama.com/ \
		ftp://ftp.middle-earth.it/proftpd/ \
		ftp://ftp.dataguard.no/pub/proftpd/ \
		ftp://spirit.bentel.sk/mirrors/Proftpd/ \
		ftp://ftp.task.gda.pl/pub/proftpd/ \
		ftp://mirror1.dataphone.se/pub/ProFTPD/ \
		ftp://ftp.oss.eznetsols.org/proftpd/ \
		ftp://ftp.ccp14.ac.uk/ccp14/ftp-mirror/programming/proftpd/ \
		ftp://proftpd.networkedsystems.co.uk/ \
		ftp://www.linuxceptional.com/proftpd/ \
		ftp://ftp.ethereal.com/mirrors/ftp.proftpd.org/ \
		ftp://mirror.cybercomm.nl/

# GNU GPL
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

FLAVORS=		ldap mysql pgsql ssl
FLAVOR?=

MOD=			mod_ratio:mod_readme:mod_wrap

.if ${FLAVOR:L:Mldap}
LIB_DEPENDS+=		ldap.2,lber:openldap-client-2.*:databases/openldap
MOD:=			${MOD}:mod_ldap
.endif

.if ${FLAVOR:L:Mmysql}
LIB_DEPENDS+=		lib/mysql/mysqlclient.10:mysql-client-3.23.*:databases/mysql
MOD:=			${MOD}:mod_sql:mod_sql_mysql
.endif

.if ${FLAVOR:L:Mpgsql}
LIB_DEPENDS+=		pq.2::databases/postgresql
MOD:=			${MOD}:mod_sql:mod_sql_postgres
.endif

.if ${FLAVOR:L:Mssl}
CFLAGS+=		-DHAVE_OPENSSL
LDFLAGS+=		-lssl -lcrypto
.endif

CONFIGURE_STYLE=        gnu
CONFIGURE_ARGS+=        --localstatedir=/var/run \
			--disable-sendfile \
			--disable-pam \
			--enable-ipv6 \
			--with-includes=${LOCALBASE}/include \
			--with-libraries=${LOCALBASE}/lib

.if defined(MOD)
CONFIGURE_ARGS+=	--with-modules=${MOD}
.endif

SAMPLE=			anonymous.conf basic.conf \
			complex-virtual.conf mod_sql.conf virtual.conf

DOCS=			README README.IPv6 README.LDAP README.mod_sql

post-configure:
	@mv ${WRKSRC}/Make.rules ${WRKSRC}/Make.rules.pre_sed
	@sed -e 's: -lnsl::' \
		< ${WRKSRC}/Make.rules.pre_sed > ${WRKSRC}/Make.rules

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/proftpd
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/proftpd
	cd ${WRKDIST}/sample-configurations && ${INSTALL_DATA} ${SAMPLE} \
		${PREFIX}/share/examples/proftpd
	cd ${WRKDIST} && ${INSTALL_DATA} ${DOCS} \
		${PREFIX}/share/doc/proftpd

.include <bsd.port.mk>
