# $OpenBSD: Makefile.inc,v 1.37 2004/04/25 10:36:39 jakob Exp $

COMMENT=		fast, secure sendmail replacement
DISTNAME=		postfix-${VERSION}

CATEGORIES=	mail

MASTER_SITE_POSTFIX=\
		ftp://ftp.porcupine.org/mirrors/postfix-release/ \
		ftp://ftp.merit.edu/postfix/ \
		ftp://ftp.sunet.se/pub/unix/mail/postfix/ \
		ftp://ftp.tau.ac.il/pub/unix/mail/postfix/ \
		ftp://ftp.cs.uu.nl/mirror/postfix/postfix-release/

DIST_SUBDIR=	postfix
DISTFILES=	${DISTNAME}${EXTRACT_SUFX}

HOMEPAGE=	http://www.postfix.org/

PERMIT_PACKAGE_CDROM=	"cannot be sold, see section 4 of license"
PERMIT_PACKAGE_FTP=	yes
PERMIT_DISTFILES_CDROM=	"cannot be sold, see section 4 of license"
PERMIT_DISTFILES_FTP=	yes

MAKE_DEBUG?=
MAKE_CCARGS?=	-DFD_SETSIZE=2048
MAKE_CCARGS+=	-DDEF_CONFIG_DIR=\"${SYSCONFDIR}/postfix\"
MAKE_AUXLIBS?=

ALL_TARGET=	default

NO_REGRESS=	Yes

# always include pcre
LIB_DEPENDS+=	pcre::devel/pcre
MAKE_CCARGS+=	-DHAS_PCRE -I${LOCALBASE}/include
MAKE_AUXLIBS+=	-L${LOCALBASE}/lib -lpcre

FLAVOURS+=	sasl2 ldap mysql pgsql
FLAVOUR?=

.if ${FLAVOUR:L:Msasl2}
LIB_DEPENDS+=	sasl2::security/cyrus-sasl
MAKE_CCARGS+=	-I${LOCALBASE}/include -I${LOCALBASE}/include/sasl -DUSE_SASL_AUTH 
MAKE_AUXLIBS+=	-L${LOCALBASE}/lib -lsasl2
.endif

.if ${FLAVOUR:L:Mldap}
LIB_DEPENDS+=	ldap.2,lber:openldap-client-2.*:databases/openldap
MAKE_CCARGS+=	-I${LOCALBASE}/include -DHAS_LDAP
MAKE_AUXLIBS+=	-L${LOCALBASE}/lib -lldap -llber
.endif

.if ${FLAVOUR:L:Mmysql}
USE_CXX=	Yes
LIB_DEPENDS+=	lib/mysql/mysqlclient.10::databases/mysql
MAKE_CCARGS+=	-I${LOCALBASE}/include/mysql -DHAS_MYSQL
MAKE_AUXLIBS+=	-L${LOCALBASE}/lib/mysql -lmysqlclient
.endif

.if ${FLAVOUR:L:Mpgsql}
LIB_DEPENDS+=	pq.3:postgresql-clients-7.*:databases/postgresql
MAKE_CCARGS+=	-I${LOCALBASE}/include/postgresql -DHAS_PGSQL
MAKE_AUXLIBS+=	-L${LOCALBASE}/lib -lpq
.endif


do-configure:
	@cd ${WRKSRC}; ${MAKE_PROGRAM} makefiles \
		CC=${_PASS_CC:T:Q} OPT="${CFLAGS}" DEBUG="${MAKE_DEBUG}" \
		CCARGS='${MAKE_CCARGS}' AUXLIBS="${MAKE_AUXLIBS}"

do-install:
	@(cd ${WRKSRC}; sh postfix-install \
		-non-interactive \
		mail_owner=_postfix \
		setgid_group=_postdrop \
		install_root=${WRKINST} \
		daemon_directory=${TRUEPREFIX}/libexec/postfix \
		command_directory=${TRUEPREFIX}/sbin \
		sendmail_path=${TRUEPREFIX}/sbin/sendmail \
		newalises_path=${TRUEPREFIX}/sbin/newaliases \
		mailq_path=${TRUEPREFIX}/sbin/mailq \
		manpage_directory=${TRUEPREFIX}/man \
		readme_directory=${TRUEPREFIX}/share/doc/postfix/readme \
		html_directory=${TRUEPREFIX}/share/doc/postfix/html \
		)
	@${INSTALL_SCRIPT} ${FILESDIR}/postfix-enable ${PREFIX}/sbin
	@${INSTALL_SCRIPT} ${FILESDIR}/postfix-disable ${PREFIX}/sbin
	@${INSTALL_DATA_DIR} ${PREFIX}/share/examples/postfix
	@mv ${WRKINST}${SYSCONFDIR}/postfix/* ${PREFIX}/share/examples/postfix
	@rm -fr ${WRKINST}/var/spool/postfix
