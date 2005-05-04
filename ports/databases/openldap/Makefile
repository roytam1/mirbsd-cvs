# $MirOS: ports/databases/openldap/Makefile,v 1.1.7.1 2005/03/18 15:44:10 tg Exp $
# $OpenBSD: Makefile,v 1.40 2004/04/04 21:53:37 jakob Exp $

COMMENT=	"Open source LDAP software (client)"
COMMENT-server=	"Open source LDAP software (server)"
VERSION=	2.2.26

DISTNAME=	openldap-${VERSION}
FULLPKGNAME=	openldap-client-${VERSION}
PKGNAME-server=	openldap-server-${VERSION}
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

SEPARATE_BUILD=		concurrent
CONFIGURE_STYLE=	autoconf

CONFIGURE_ARGS+=	\
			--localstatedir=/var/ldap \
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
			--enable-perl \
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
	@cd ${WRKBUILD}; ${MAKE_PROGRAM} depend

post-install:
	mv ${DESTDIR}${SYSCONFDIR}/openldap ${PREFIX}/share/examples/
	chown -R ${SHAREOWN}:${SHAREGRP} ${PREFIX}/share/examples/openldap
	${INSTALL_DATA} ${WRKSRC}/LICENSE ${PREFIX}/share/openldap/
	@rm -rf ${DESTDIR}/var/ldap

.include <bsd.port.mk>
