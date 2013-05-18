# $MirOS: ports/mailnews/exim/Makefile,v 1.11 2008/10/04 19:03:16 tg Exp $

COMMENT=		flexible mail transfer agent
VERSION=		4.69
DISTNAME=		exim-${VERSION}
DASH_VER=		0
CATEGORIES=		mail
MASTER_SITES=		ftp://ftp.csx.cam.ac.uk/pub/software/email/exim/exim4/ \
			http://ftp.planetmirror.com/pub/exim/exim4/ \
			ftp://ftp.planetmirror.com/pub/exim/exim4/
				
EXTRACT_SUFX=		.tar.bz2
SUBST_VARS+=		VERSION
HOMEPAGE=		http://www.exim.org/
RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

NO_REGRESS=		Yes

FLAVOURS=		no_x11 no_perl mysql pgsql ldap iconv
FLAVOUR?=

EXIM_ROUTERS=		ACCEPT DNSLOOKUP IPLITERAL MANUALROUTE QUERYPROGRAM REDIRECT # IPLOOKUP
EXIM_TRANSPORTS=	APPENDFILE AUTOREPLY PIPE SMTP # LMTP
EXIM_MAILBOX_FORMATS=	MAILDIR # MAILSTORE MBX
EXIM_LOOKUP_METHODS=	DBM LSEARCH CDB DNSDB DSEARCH PASSWD
EXIM_AUTH_MECHANISMS=	CRAM_MD5 PLAINTEXT SPA

.if !${FLAVOUR:L:Mno_x11}
USE_X11=		Yes
.endif

.if ${FLAVOUR:L:Mmysql}
LIB_DEPENDS+=		lib/mysql/mysqlclient.10:mysql-client-*:databases/mysql
EXIM_LOOKUP_METHODS+=	MYSQL
EXIM_LOOKUP_INCLUDE+=	-I${LOCALBASE}/include/mysql
EXIM_LOOKUP_LIBS+=	-L${LOCALBASE}/lib/mysql -lmysqlclient
.endif

.if ${FLAVOUR:L:Mpgsql}
LIB_DEPENDS+=		pq.2::databases/postgresql
EXIM_LOOKUP_METHODS+=	PGSQL
EXIM_LOOKUP_INCLUDE+=	-I${LOCALBASE}/include/postgresql
EXIM_LOOKUP_LIBS+=	-L${LOCALBASE}/lib/ -lpq
PERMIT_PACKAGE_CDROM=	dependency databases/postgresql is not allowed for CDROM
.endif

.if ${FLAVOUR:L:Mldap}
LIB_DEPENDS+=		ldap.2,lber:openldap-client-2.*:databases/openldap
EXIM_LOOKUP_METHODS+=	LDAP
EXIM_LOOKUP_INCLUDE+=	-I${LOCALBASE}/include
EXIM_LOOKUP_LIBS+=	-L${LOCALBASE}/lib -lldap -llber
.endif

.if ${FLAVOUR:L:Miconv}
MODULES+=		converters/libiconv
EXIM_EXTRA_LIBS+=	-L${ICONV_PREFIX}/lib -liconv
EXIM_CFLAGS+=		-I${ICONV_PREFIX}/include
.endif

post-patch:
	cp ${WRKSRC}/OS/Makefile-OpenBSD ${WRKSRC}/OS/Makefile-MirBSD
	cp ${WRKSRC}/OS/Makefile-OpenBSD ${WRKSRC}/OS/Makefile-ekkoBSD
	cp ${WRKSRC}/OS/os.h-OpenBSD ${WRKSRC}/OS/os.h-MirBSD
	cp ${WRKSRC}/OS/os.h-OpenBSD ${WRKSRC}/OS/os.h-ekkoBSD

do-configure:
	@echo "BIN_DIRECTORY=${PREFIX}/sbin" >> ${WRKSRC}/Local/Makefile
	@echo "CONFIGURE_FILE=${SYSCONFDIR}/exim/exim.conf" >> ${WRKSRC}/Local/Makefile
	@echo "SPOOL_DIRECTORY=/var/spool/exim" >> ${WRKSRC}/Local/Makefile
	@echo "LOG_FILE_PATH=syslog" >> ${WRKSRC}/Local/Makefile
	@echo "SYSTEM_ALIASES_FILE=/etc/mail/aliases" >> ${WRKSRC}/Local/Makefile
	@echo "PID_FILE_PATH=/var/run/exim.pid" >> ${WRKSRC}/Local/Makefile
	@echo "EXIM_USER=root" >> ${WRKSRC}/Local/Makefile
	@echo "ALT_CONFIG_ROOT_ONLY=yes" >> ${WRKSRC}/Local/Makefile
	@echo "HEADERS_CHARSET=\"ISO-8859-1\"" >> ${WRKSRC}/Local/Makefile
	@echo "SYSLOG_LOG_PID=yes" >> ${WRKSRC}/Local/Makefile
	@echo "EXICYCLOG_MAX=7" >> ${WRKSRC}/Local/Makefile
	@echo "COMPRESS_COMMAND=/usr/bin/gzip" >> ${WRKSRC}/Local/Makefile
	@echo "COMPRESS_SUFFIX=gz" >> ${WRKSRC}/Local/Makefile
	@echo "ZCAT_COMMAND=/usr/bin/zcat" >> ${WRKSRC}/Local/Makefile
	@echo "CYRUS_PWCHECK_SOCKET=/var/pwcheck/pwcheck" >> ${WRKSRC}/Local/Makefile
	@echo "CYRUS_SASLAUTHD_SOCKET=/var/sasl2/mux" >> ${WRKSRC}/Local/Makefile
	@echo "WITH_CONTENT_SCAN=yes" >> ${WRKSRC}/Local/Makefile
	@echo "HAVE_IPV6=yes" >> ${WRKSRC}/Local/Makefile
.for ROUTER in ${EXIM_ROUTERS}
	@echo "ROUTER_${ROUTER}=yes" >> ${WRKSRC}/Local/Makefile
.endfor
.for TRANSPORT in ${EXIM_TRANSPORTS}
	@echo "TRANSPORT_${TRANSPORT}=yes" >> ${WRKSRC}/Local/Makefile
.endfor
.for FORMAT in ${EXIM_MAILBOX_FORMATS}
	@echo "SUPPORT_${FORMAT}=yes" >> ${WRKSRC}/Local/Makefile
.endfor
.for METHOD in ${EXIM_LOOKUP_METHODS}
	@echo "LOOKUP_${METHOD}=yes" >> ${WRKSRC}/Local/Makefile
.endfor
.for MECHANISM in ${EXIM_AUTH_MECHANISMS}
	@echo "AUTH_${MECHANISM}=yes" >> ${WRKSRC}/Local/Makefile
.endfor
	@echo "LOOKUP_INCLUDE=${EXIM_LOOKUP_INCLUDE}" >> ${WRKSRC}/Local/Makefile
	@echo "LOOKUP_LIBS=${EXIM_LOOKUP_LIBS}" >> ${WRKSRC}/Local/Makefile
	@echo "EXTRALIBS_EXIM=${EXIM_EXTRA_LIBS}" >> ${WRKSRC}/Local/Makefile
	@echo "CFLAGS=${EXIM_CFLAGS}" >> ${WRKSRC}/Local/Makefile
.if !${FLAVOUR:L:Mno_x11}
	@echo "EXIM_MONITOR=eximon.bin" >> ${WRKSRC}/Local/Makefile
	@cp ${WRKSRC}/exim_monitor/EDITME ${WRKSRC}/Local/eximon.conf
.endif
	@echo "SUPPORT_TLS=yes" >> ${WRKSRC}/Local/Makefile
	@echo "TLS_LIBS=-lssl -lcrypto" >> ${WRKSRC}/Local/Makefile
.if !${FLAVOUR:L:Mno_perl}
	@echo "EXIM_PERL=perl.o" >> ${WRKSRC}/Local/Makefile
.endif
.if ${FLAVOUR:L:Mldap}
	@echo "LDAP_LIB_TYPE=OPENLDAP2" >> ${WRKSRC}/Local/Makefile
.endif
.if ${FLAVOUR:L:Miconv}
	@echo "HAVE_ICONV=yes" >> ${WRKSRC}/Local/Makefile
.endif
	@echo CC=${_PASS_CC:T:Q} >> ${WRKSRC}/Local/Makefile
	@echo CFLAGS=${CFLAGS:Q} >> ${WRKSRC}/Local/Makefile

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/exim
	${INSTALL_DATA} ${WRKINST}/etc/exim/exim.conf ${PREFIX}/share/examples/exim
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/exim
	${INSTALL_DATA} ${WRKSRC}/doc/spec.txt ${PREFIX}/share/doc/exim
	${INSTALL_DATA} ${WRKSRC}/doc/README.SIEVE ${PREFIX}/share/doc/exim
	${INSTALL_DATA} ${WRKSRC}/doc/filter.txt ${PREFIX}/share/doc/exim
	${INSTALL_MAN} ${WRKSRC}/doc/exim.8 ${PREFIX}/man/man8

.include <bsd.port.mk>
