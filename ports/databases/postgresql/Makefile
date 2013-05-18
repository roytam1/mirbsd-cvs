# $MirOS: ports/databases/postgresql/Makefile,v 1.5 2006/09/14 00:07:57 tg Exp $
# $OpenBSD: Makefile,v 1.68 2004/02/04 07:39:18 sturm Exp $

COMMENT=		PostgreSQL RDBMS clients and utilities
COMMENT-tcl=		PostgreSQL RDBMS tcl libraries and utilities
COMMENT-server=		PostgreSQL RDBMS server software
COMMENT-docs=		PostgreSQL RDBMS documentation

VERSION=		8.0.1
DASH_VER=		1
DISTNAME=		postgresql-${VERSION}
PKGNAME-server=		postgresql-server-${VERSION}-${DASH_VER}
PKGNAME-docs=		postgresql-docs-${VERSION}-${DASH_VER}
PKGNAME-tcl=		postgresql-tcl-${VERSION}-${DASH_VER}
CATEGORIES=		databases
HOMEPAGE=		http://www.postgresql.org/

# BSD
PERMIT_DISTFILES_CDROM=	"without fee clause"
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	"without fee clause"
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=	\
	ftp://ftp.de.postgresql.org/mirror/postgresql/source/v${VERSION}/ \
	ftp://ftp2.de.postgresql.org/pub/comp/os/unix/database/postgresql/source/v${VERSION}/ \
	ftp://ftp3.de.postgresql.org/pub/Mirrors/ftp.postgresql.org/source/v${VERSION}/ \
	ftp://ftp4.de.postgresql.org/pub/mirrors/postgresql/source/v${VERSION}/ \
	ftp://ftp7.de.postgresql.org/pub/ftp.postgresql.org/source/v${VERSION}/ \
	ftp://ftp8.de.postgresql.org/pub/misc/pgsql/source/v${VERSION}/ \
	ftp://ftp4.ar.postgresql.org/pub/mirrors/postgresql/source/v${VERSION}/ \
	ftp://ftp.au.postgresql.org/pub/postgresql/source/v${VERSION}/ \
	ftp://ftp2.au.postgresql.org/pub/postgresql/source/v${VERSION}/ \
	ftp://ftp3.au.postgresql.org/postgresql/source/v${VERSION}/ \
	ftp://ftp.at.postgresql.org/db/www.postgresql.org/pub/source/v${VERSION}/ \
	ftp://ftp.be.postgresql.org/postgresql/source/v${VERSION}/ \
	ftp://ftp.ba.postgresql.org/pub/postgresql/source/v${VERSION}/ \
	ftp://ftp.br.postgresql.org/pub/PostgreSQL/source/v${VERSION}/ \
	ftp://ftp2.br.postgresql.org/postgresql/source/v${VERSION}/ \
	ftp://ftp.bg.postgresql.org/pub/postgresql/source/v${VERSION}/ \
	ftp://ftp3.bg.postgresql.org/postgresql/source/v${VERSION}/ \
	ftp://ftp3.ca.postgresql.org/pub/source/v${VERSION}/ \
	ftp://ftp4.ca.postgresql.org/pub/postgresql/source/v${VERSION}/ \
	ftp://ftp.cl.postgresql.org/ftp/pub/postgresql/source/v${VERSION}/ \
	ftp://ftp.cn.postgresql.org/ftp.postgresql.org/source/v${VERSION}/ \
	ftp://ftp.co.postgresql.org/pub/mirrors/postgresql/source/v${VERSION}/ \
	ftp://ftp2.cr.postgresql.org/pub/Unix/postgres/source/v${VERSION}/ \
	ftp://ftp.hr.postgresql.org/postgresql/source/v${VERSION}/ \
	ftp://ftp.cz.postgresql.org/pub/ftp.postgresql.org/source/v${VERSION}/ \
	ftp://ftp2.cz.postgresql.org/pub/postgresql/source/v${VERSION}/ \
	ftp://ftp.ee.postgresql.org/mirrors/postgresql/source/v${VERSION}/ \
	ftp://ftp.fr.postgresql.org/source/v${VERSION}/ \
	ftp://ftp2.fr.postgresql.org/postgresql/source/v${VERSION}/ \
	ftp://ftp3.fr.postgresql.org/pub/postgresql/source/v${VERSION}/ \
	ftp://ftp.gr.postgresql.org/pub/databases/postgresql/source/v${VERSION}/ \
	ftp://ftp2.gr.postgresql.org/pub/databases/postgresql/source/v${VERSION}/ \
	ftp://ftp.hk.postgresql.org/postgresql/source/v${VERSION}/ \
	ftp://ftp.hu.postgresql.org/pub/postgresql/source/v${VERSION}/ \
	ftp://ftp3.hu.postgresql.org/pub/postgresql/source/v${VERSION}/ \
	ftp://ftp5.id.postgresql.org/postgresql/source/v${VERSION}/ \
	ftp://ftp7.id.postgresql.org/pub/postgresql/source/v${VERSION}/ \
	ftp://ftp.ie.postgresql.org/mirrors/ftp.postgresql.org/pub/source/v${VERSION}/ \
	ftp://ftp2.ie.postgresql.org/mirrors/ftp.postgresql.org/source/v${VERSION}/ \
	ftp://ftp.il.postgresql.org/ftp.postgresql.org/source/v${VERSION}/ \
	ftp://ftp2.it.postgresql.org/mirrors/postgres/source/v${VERSION}/ \
	ftp://ftp5.it.postgresql.org/postgresql/source/v${VERSION}/ \
	ftp://ftp6.it.postgresql.org/pub/PostgreSQL/source/v${VERSION}/ \
	ftp://ftp.jp.postgresql.org/source/v${VERSION}/ \
	ftp://ftp3.kr.postgresql.org:80/pub/mirrors/pgsql/source/v${VERSION}/ \
	ftp://ftp.lv.postgresql.org/pub/software/postgresql/source/v${VERSION}/ \
	ftp://ftp.nl.postgresql.org:21/pub/mirror/postgresql/source/v${VERSION}/ \
	ftp://ftp.eu.postgresql.org/pub/unix/db/postgresql/source/v${VERSION}/ \
	ftp://ftp2.nl.postgresql.org/mirror/postgresql/source/v${VERSION}/ \
	ftp://ftp4.nl.postgresql.org/postgresql.zeelandnet.nl/source/v${VERSION}/ \
	ftp://ftp.nz.postgresql.org/postgresql/source/v${VERSION}/ \
	ftp://ftp.no.postgresql.org/pub/databases/postgresql/source/v${VERSION}/ \
	ftp://ftp6.pl.postgresql.org/pub/postgresql/source/v${VERSION}/ \
	ftp://ftp7.pl.postgresql.org/pub/mirror/ftp.postgresql.org/source/v${VERSION}/ \
	ftp://ftp8.pl.postgresql.org/pub/postgresql/source/v${VERSION}/ \
	ftp://ftp.pt.postgresql.org/postgresql/source/v${VERSION}/ \
	ftp://ftp.pr.postgresql.org/pub/Mirrors/postgresql/source/v${VERSION}/ \
	ftp://ftp6.ro.postgresql.org/pub/mirrors/ftp.postgresql.org/source/v${VERSION}/ \
	ftp://ftp2.ru.postgresql.org/pub/databases/postgresql/source/v${VERSION}/ \
	ftp://ftp3.ru.postgresql.org/pub/mirror/postgresql/pub/source/v${VERSION}/ \
	ftp://ftp6.ru.postgresql.org/pub/pgsql/source/v${VERSION}/ \
	ftp://ftp2.sk.postgresql.org/pub/postgresql/source/v${VERSION}/ \
	ftp://ftp5.es.postgresql.org/mirror/postgresql/source/v${VERSION}/ \
	ftp://ftp.se.postgresql.org/pub/databases/relational/postgresql/source/v${VERSION}/ \
	ftp://ftp2.ch.postgresql.org/pub/postgresql/source/v${VERSION}/ \
	ftp://ftp.tw.postgresql.org/pub/postgresql/source/v${VERSION}/ \
	ftp://ftp3.tw.postgresql.org/pub/Unix/Database/postgresql/source/v${VERSION}/ \
	ftp://ftp5.tw.postgresql.org/pub/Unix/Database/PostgreSQL/source/v${VERSION}/ \
	ftp://ftp6.tr.postgresql.org/postgresql/source/v${VERSION}/ \
	ftp://ftp2.uk.postgresql.org/sites/ftp.postgresql.org/source/v${VERSION}/ \
	ftp://ftp4.uk.postgresql.org/sites/ftp.postgresql.org/source/v${VERSION}/ \
	ftp://ftp8.uk.postgresql.org/sites/ftp.postgresql.org/source/v${VERSION}/ \
	ftp://ftp3.us.postgresql.org/pub/postgresql/source/v${VERSION}/ \
	ftp://ftp5.us.postgresql.org/pub/PostgreSQL/source/v${VERSION}/ \
	ftp://ftp8.us.postgresql.org/postgresql/source/v${VERSION}/ \
	ftp://ftp9.us.postgresql.org/pub/mirrors/postgresql/source/v${VERSION}/ \
	ftp://ftp10.us.postgresql.org/pub/postgresql/source/v${VERSION}/ \
	ftp://ftp13.us.postgresql.org/mirror/postgresql/source/v${VERSION}/ \
	ftp://ftp22.us.postgresql.org/mirrors/ftp.postgresql.org/source/v${VERSION}/ \
	ftp://ftp24.us.postgresql.org/postgresql/source/v${VERSION}/

PSEUDO_FLAVORS=	tcl
.if ${OStype} == "OpenBSD"
FLAVORS=	kerberos
FLAVOR?=	kerberos
.else
FLAVOR?=
.endif

.if ${OStype} != "MirBSD"
LIB_DEPENDS+=	readline::devel/libreadline
.endif

MULTI_PACKAGES=	-server -docs
SUBPACKAGE?=

SUBST_VARS=	VERSION

MAKE_FILE=	GNUmakefile
USE_GMAKE=	Yes
CONFIGURE_STYLE=autoconf no-autoheader
AUTOCONF_NEW=	yes
CONFIGURE_ENV=	LIBS=-lcurses
CONFIGURE_ARGS=	--disable-rpath \
		--enable-integer-datetimes \
		--includedir="${PREFIX}/include/postgresql" \
		--datadir="${PREFIX}/share/postgresql" \
		--with-docdir="${PREFIX}/share/doc/postgresql" \
		--with-perl \
		--without-python \
		--with-openssl \
		${CONFIGURE_SHARED}

# Regression tests must be done manually and not as root. Successful
# runs have been achieved on the i386 using the following:
#
#	$ ulimit -p 128
#	$ ulimit -n 1024
#	$ make regress NO_REGRESS=No
#
# Note, you may also need to change a variety of SYSV IPC parameters.
# See files/README.MirPorts for more details
NO_REGRESS=	Yes

DOCS=	${WRKSRC}/COPYRIGHT ${WRKSRC}/HISTORY \
	${WRKSRC}/INSTALL ${WRKSRC}/README \
	${WRKSRC}/doc/README.mb.big5 ${WRKSRC}/doc/README.mb.jp \
	${WRKSRC}/doc/FAQ{,_DEV,_[a-z]*} ${WRKSRC}/doc/TODO

.if defined(PACKAGING)
. if ${SUBPACKAGE} == "-server"
RUN_DEPENDS=	::databases/postgresql
. endif
.endif

# For tcl
.if ${FLAVOR:L:Mtcl}
MULTI_PACKAGES+= -tcl

TCL_INCDIR=     ${LOCALBASE}/include/tcl8.3
TK_INCDIR=      ${LOCALBASE}/include/tk8.3
CONFIGURE_ENV+= WISH="${LOCALBASE}/bin/wish8.3"
CONFIGURE_ARGS+= --with-tcl \
        --with-tclconfig="${LOCALBASE}/lib/tcl8.3 ${LOCALBASE}/lib/tk8.3" \
        --with-includes="${TCL_INCDIR} ${TK_INCDIR} ${LOCALBASE}/include"
BUILD_DEPENDS+=   tk83::x11/tk/8.3

.  if defined(PACKAGING)
.    if ${SUBPACKAGE} == "-tcl"
RUN_DEPENDS=	::databases/postgresql
LIB_DEPENDS+=   tk83::x11/tk/8.3
.    endif
.  endif
.else
CONFIGURE_ARGS+= --without-tcl
.endif
.if defined(PACKAGING) && ${SUBPACKAGE} == "-docs"
PKG_ARCH=	*
.endif

.if ${FLAVOR:L:Mkerberos}
CONFIGURE_ARGS+=	--with-includes=/usr/include/kerberosV
CONFIGURE_ARGS+=	--with-krb5=/usr/lib
.endif

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/postgresql
	${INSTALL_DATA} ${DOCS} ${PREFIX}/share/doc/postgresql
	@sed -e s#!!PREFIX!!#${TRUEPREFIX}#g ${FILESDIR}/README.MirPorts \
	    >${WRKBUILD}/README.MirPorts
	${INSTALL_DATA} ${WRKBUILD}/README.MirPorts \
	    ${PREFIX}/share/doc/postgresql/

.include <bsd.port.mk>
