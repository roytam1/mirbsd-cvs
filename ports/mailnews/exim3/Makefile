# $MirOS: ports/mailnews/exim3/Makefile,v 1.5 2007/04/12 20:22:18 bsiegert Exp $
# $OpenBSD: Makefile,v 1.39 2004/05/10 08:42:42 brad Exp $

COMMENT=	flexible mail transfer agent
VERSION=	3.36
VERSION_DOC=	3.30
DISTNAME=	exim-${VERSION}
DASH_VER=	3
CATEGORIES=	mail
MASTER_SITES=	ftp://ftp.csx.cam.ac.uk/pub/software/email/exim/exim3/ \
		ftp://ftp.exim.org/pub/exim/exim3/ \
		ftp://ftp.fu-berlin.de/unix/mail/exim/exim3/
DISTFILES=	exim-${VERSION}.tar.gz exim-texinfo-${VERSION_DOC}.tar.gz
HOMEPAGE=	http://www.exim.org/

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

# ldap - once openldap is supported by exim
FLAVOURS=	no_x11 no_perl mysql postgresql ldap no_ssl
FLAVOUR?=

MAKE_ENV=	FLAVOUR="${FLAVOUR}"

EXIM_MAKECAT=
EXIM_LOOKUP_INCLUDE=
EXIM_LOOKUP_LIBS=

.if !${FLAVOUR:L:Mno_x11}
USE_X11=	Yes
EXIM_MAKECAT+=	"EXIM_MONITOR=eximon.bin\n"
.endif

.if !${FLAVOUR:L:Mno_perl}
EXIM_MAKECAT+=	"EXIM_PERL=perl.o\n"
.endif

.if ${FLAVOUR:L:Mldap}
LIB_DEPENDS+=	ldap.2,lber:openldap-client-2.*:databases/openldap
EXIM_MAKECAT+=	"LOOKUP_LDAP=yes\nLDAP_LIB_TYPE=OPENLDAP2\n"
EXIM_LOOKUP_INCLUDE+=	-I${LOCALBASE}/include
EXIM_LOOKUP_LIBS+=	-L${LOCALBASE}/lib -lldap -llber
.endif

.if ${FLAVOUR:L:Mmysql}
USE_CXX=	Yes
LIB_DEPENDS+=	lib/mysql/mysqlclient.10::databases/mysql
EXIM_MAKECAT+=	"LOOKUP_MYSQL=yes\n"
EXIM_LOOKUP_INCLUDE+=	-I${LOCALBASE}/include/mysql
EXIM_LOOKUP_LIBS+=	-L${LOCALBASE}/lib/mysql -lmysqlclient
.endif

.if ${FLAVOUR:L:Mpostgresql}
LIB_DEPENDS+=	pq.2::databases/postgresql
EXIM_MAKECAT+=	"LOOKUP_PGSQL=yes\n"
EXIM_LOOKUP_INCLUDE+=	-I${LOCALBASE}/include/postgresql
EXIM_LOOKUP_LIBS+=	-L${LOCALBASE}/lib -lpq
PERMIT_PACKAGE_CDROM=	dependency databases/postgresql is not allowed for CDROM
.endif

.if !${FLAVOUR:L:Mno_ssl}
EXIM_MAKECAT+=	"SUPPORT_TLS=yes\nTLS_LIBS=-lssl -lcrypto\n"
.endif

NO_REGRESS=	Yes

do-configure:
	@mkdir -p ${WRKSRC}/Local
	@cp ${FILESDIR}/Makefile ${WRKSRC}/Local
.if !${FLAVOUR:L:Mno_x11}
	@cp ${FILESDIR}/eximon.conf ${WRKSRC}/Local
.endif
	@echo -n ${EXIM_MAKECAT} >> ${WRKSRC}/Local/Makefile
	@echo "LOOKUP_INCLUDE=${EXIM_LOOKUP_INCLUDE}">>${WRKSRC}/Local/Makefile
	@echo "LOOKUP_LIBS=${EXIM_LOOKUP_LIBS}">>${WRKSRC}/Local/Makefile
	@cd ${WRKSRC}/doc ; \
	for i in ../../exim-texinfo-${VERSION_DOC}/doc/* ; do \
		ln -sf $$i ; \
	done

pre-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/exim

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/exim
	${INSTALL_DATA} ${WRKSRC}/doc/spec.txt ${PREFIX}/share/doc/exim/spec.txt

.include <bsd.port.mk>
