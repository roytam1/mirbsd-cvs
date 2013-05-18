# $MirOS: ports/security/cyrus-sasl/Makefile,v 1.1.7.1 2005/03/18 15:51:21 tg Exp $
# $OpenBSD: Makefile,v 1.12 2004/02/17 03:26:02 kevlo Exp $

COMMENT=	"RFC 2222 SASL (Simple Authentication and Security Layer)"
DISTNAME=	cyrus-sasl-2.1.17
CATEGORIES=     security
MASTER_SITES=	ftp://ftp.andrew.cmu.edu/pub/cyrus-mail/ \
		ftp://ftp.andrew.cmu.edu/pub/cyrus-mail/OLD-VERSIONS/sasl/
HOMEPAGE=	http://asg.web.cmu.edu/sasl/

PERMIT_PACKAGE_CDROM=	yes
PERMIT_PACKAGE_FTP=	yes
PERMIT_DISTFILES_CDROM=	yes
PERMIT_DISTFILES_FTP=	yes


MODGNU_CONFIG_GUESS_DIRS= ${WRKSRC}/config ${WRKSRC}/saslauthd/config

CONFIGURE_ENV+=		CFLAGS="-O2" LDFLAGS='${LDFLAGS}' \
			CPPFLAGS="-I/usr/local/include/db4"
CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--with-saslauthd="/var/sasl2" \
			--with-staticsasl \
			--with-openssl \
			--enable-login \
			--disable-gssapi \
			--disable-krb4 \
			--disable-otp \
			--disable-java \
			--enable-cram \
			--disable-srp \
			--enable-anon \
			--enable-digest \
			--enable-checkapop \
			--disable-alwaystrue \
			--disable-ntlm \
			--disable-sample

FLAVORS=	db4
FLAVOR?=

.if ${FLAVOR:L} == "db4"
CONFIGURE_ARGS+=	--with-dblib=berkeley \
			--with-bdb-libdir="${LOCALBASE}/lib/db4" \
			--with-bdb-incdir="${LOCALBASE}/include/db4"
LIB_DEPENDS=		db.4.2::databases/db
.else
CONFIGURE_ARGS+=	--with-dblib=ndbm \
			--without-bdb-libdir \
			--without-bdb-incdir
.endif

post-build:
	(cd ${WRKBUILD}/saslauthd; \
	${SETENV} ${MAKE_ENV} ${MAKE_PROGRAM} ${MAKE_FLAGS} testsaslauthd)

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/sasl2
	${INSTALL_DATA} ${WRKSRC}/doc/*.html ${PREFIX}/share/doc/sasl2
	${INSTALL_DATA} ${WRKSRC}/doc/*.txt ${PREFIX}/share/doc/sasl2
	${INSTALL_PROGRAM} ${WRKBUILD}/saslauthd/testsaslauthd ${PREFIX}/sbin

.include <bsd.port.mk>
