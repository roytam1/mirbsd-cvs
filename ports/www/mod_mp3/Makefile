# $OpenBSD: Makefile,v 1.3 2004/01/30 08:39:49 xsa Exp $

COMMENT=			turns Apache into an MP3 or Ogg streaming server

# This port currently only works with archs supporting dynamic loading
# and has Apache that supports DSOs.
NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

DISTNAME=	mod_mp3-0.39
CATEGORIES=	www audio
MASTER_SITES=	http://software.tangent.org/download/ \
		ftp://ftp.tangent.org/pub/apache/

HOMEPAGE=	http://media.tangent.org/

# Apache
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

FLAVOURS=	mysql postgresql
FLAVOUR?=

CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	--with-apxs=/usr/sbin/apxs \
			--with-perl=/usr/bin/perl

NO_REGRESS=	Yes

EXAMPLESRC=	${WRKSRC}/support
CONF=		${EXAMPLESRC}/mp3.conf

.if ${FLAVOUR:L:Mmysql} && ${FLAVOUR:L:Mpostgresql}
ERRORS+= "Fatal: mutually exclusive flavours: ${FLAVOURS}"
.endif

.if ${FLAVOUR:L:Mmysql}
BROKEN=			depends on mysql, which is broken
LIB_DEPENDS+=	lib/mysql/mysqlclient.10::databases/mysql
CONFIGURE_ARGS+=	--with-mysql="${LOCALBASE}"
CONF=	${EXAMPLESRC}/mp3_with_mysql.conf
EXAMPLES+=	${EXAMPLESRC}/mysql_schema
.endif

.if ${FLAVOUR:L:Mpostgresql}
LIB_DEPENDS+=	pq.2::databases/postgresql
CONFIGURE_ARGS+=	--with-postgres="${LOCALBASE}"
CONF=	${FILESDIR}/mp3_with_postgresql.conf
EXAMPLES+=	${EXAMPLESRC}/pgsql_schema
.endif

post-build:
	@sed 's,!!PREFIX!!,${PREFIX},' \
		< ${FILESDIR}/mod_mp3-enable \
		> ${WRKBUILD}/mod_mp3-enable

do-install:
	${INSTALL_DATA} ${WRKBUILD}/src/mod_mp3.so ${PREFIX}/lib
	${INSTALL_SCRIPT} ${WRKBUILD}/mod_mp3-enable ${PREFIX}/sbin
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/mod_mp3
	${INSTALL_DATA} ${WRKSRC}/faq.html ${PREFIX}/share/doc/mod_mp3
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/mod_mp3
	${INSTALL_DATA} ${CONF} ${PREFIX}/share/examples/mod_mp3/mp3.conf
.if defined(EXAMPLES)
	${INSTALL_DATA} ${EXAMPLES} ${PREFIX}/share/examples/mod_mp3
.endif

.include <bsd.port.mk>
