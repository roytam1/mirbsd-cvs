# $MirOS: ports/databases/openldap/Makefile,v 1.5 2005/10/13 23:25:33 tg Exp $
# $OpenBSD: Makefile,v 1.40 2004/04/04 21:53:37 jakob Exp $

COMMENT=	"Open source LDAP software (client)"
COMMENT-server=	"Open source LDAP software (server)"
VERSION=	2.2.26
PL=		1

DISTNAME=	openldap-${VERSION}
PKGNAME=	openldap-client-${VERSION}-${PL}
FULLPKGNAME=	${PKGNAME}
PKGNAME-server=	openldap-server-${VERSION}-${PL}
CATEGORIES=	databases net
HOMEPAGE=	http://www.openldap.org/

# OpenLDAP Public License (BSD-style, must contain copy of LICENSE)
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	ftp://ftp.OpenLDAP.org/pub/OpenLDAP/openldap-release/ \
		ftp://ftp.net.lut.ac.uk/openldap/openldap-release/ \
		ftp://sunsite.cnlab-switch.ch/mirror/OpenLDAP/openldap-release/ \
		ftp://mirror.aarnet.edu.au/pub/OpenLDAP/openldap-release/ \
		ftp://gd.tuwien.ac.at/infosys/network/OpenLDAP/openldap-release/ \
		http://www.unibase.cz/ldapcz/Programy/Free/OpenLDAP/openldap-release/ \
		ftp://ftp.ntua.gr/mirror/OpenLDAP/openldap-release/ \
		ftp://ftp.shellhung.org/pub/OpenLDAP/openldap-release/

EXTRACT_SUFX=		.tgz

CONFIGURE_STYLE=	autoconf

.include <mirports.sys.mk>
.if ${__SYSTEM_PORTS:L} == "yes"
LOCALSTATEDIR=		/var/ldap
.else
LOCALSTATEDIR=		${LOCALBASE}/db/ldap
.endif
SUBST_VARS+=		LOCALSTATEDIR

CONFIGURE_ARGS+=	\
			--localstatedir=${LOCALSTATEDIR} \
			--sysconfdir=${SYSCONFDIR} \
			--enable-proctitle \
			--with-threads \
			--enable-debug \
			--enable-ipv6 \
			--enable-syslog \
			--with-tls \
			--enable-slapd \
			--enable-cleartext \
			--enable-crypt \
			--enable-phonetic \
			--enable-rewrite \
			--disable-wrappers \
			--disable-sql \
			--enable-dnssrv \
			--enable-ldap \
			--enable-ldbm \
			--enable-meta \
			--enable-monitor \
			--enable-null \
			--enable-passwd \
			--disable-perl \
			--enable-shell \
			--enable-slurpd \
			${CONFIGURE_SHARED}

FLAVORS=		sasl
FLAVOR?=

REGRESS_TARGET=		test

MULTI_PACKAGES=		-server
SUBPACKAGE?=

.if ${FLAVOR:L:Msasl}
CONFIGURE_ARGS+=	--with-cyrus-sasl \
			--enable-spasswd
LIB_DEPENDS+=		sasl2::security/cyrus-sasl2
CPPFLAGS+=		-I${LOCALBASE}/include/sasl
.else
CONFIGURE_ARGS+=	--without-cyrus-sasl \
			--disable-spasswd
.endif

.if ${FLAVOR:L:Mbdb}
CONFIGURE_ARGS+=	--enable-bdb
BUILD_DEPENDS+=   	:db-4.*:databases/db
CPPFLAGS+=		-I${LOCALBASE}/include/db4
LDFLAGS+=		-L${LOCALBASE}/lib/db4
LIBS+=			-ldb
.else
CONFIGURE_ARGS+=	--disable-bdb
.endif

CONFIGURE_ENV+=		LIBS="${LIBS}"

.if ${SUBPACKAGE} == "-server"
RUN_DEPENDS=		openldap:openldap-client-${VERSION}:databases/openldap
.endif

post-configure:
	@cd ${WRKBUILD} && ${MAKE_PROGRAM} depend

post-install:
	mv ${DESTDIR}${SYSCONFDIR}/openldap ${PREFIX}/share/examples/
	chown -R ${SHAREOWN}:${SHAREGRP} ${PREFIX}/share/examples/openldap
	${INSTALL_DATA} ${WRKSRC}/LICENSE ${PREFIX}/share/openldap/
	@rm -rf ${DESTDIR}${LOCALSTATEDIR}

.include <bsd.port.mk>
