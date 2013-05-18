# $MirOS: ports/databases/mysql/Makefile,v 1.5 2007/03/31 22:01:55 tg Exp $
# $OpenBSD: Makefile,v 1.99 2004/05/21 12:16:21 brad Exp $
# Uses pthreads

BROKEN=		needs fixing/updating, any volunteers?

# test that!
#.if ${MACHINE_ARCH} == "hppa" || ${MACHINE_ARCH} == "m88k"
#BROKEN=		gen_lex_hash hangs
#.endif

COMMENT=			multithreaded SQL database (client)
COMMENT-server=			multithreaded SQL database (server)
COMMENT-tests=			multithreaded SQL database (regression test suite)
VERSION=	4.0.20
DISTNAME=	mysql-${VERSION}
FULLPKGNAME=	mysql-client-${VERSION}-0
PKGNAME-server=	mysql-server-${VERSION}-0
FULLPKGNAME-tests= mysql-tests-${VERSION}-0
CATEGORIES=	databases
VSN=		MySQL-4.0
MASTER_SITES=	http://mysql.mirrors.pair.com/Downloads/${VSN}/
HOMEPAGE=	http://www.mysql.com/

# GNU GPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

DB_DIR?=	/var/mysql
SOCKET_DIR=	/var/run/mysql
SUBST_VARS=	DB_DIR SOCKET_DIR VERSION

VMEM_WARNING=	Yes
USE_GMAKE=	Yes
USE_CXX=	Yes
CONFIGURE_STYLE=autoconf
AUTOCONF_NEW=	Yes
CONFIGURE_ARGS+= ${CONFIGURE_SHARED}
CONFIGURE_ARGS+= --enable-thread-safe-client \
		 --localstatedir="${DB_DIR}" \
		 --with-comment='MirPorts: ${FULLPKGNAME-server}' \
		 --with-libwrap \
		 --with-mysqld-user="_mysql" \
		 --with-openssl \
		 --with-unix-socket-path="${SOCKET_DIR}/mysql.sock" \
		 --with-vio \
		 --without-bench \
		 --without-debug \
		 --without-docs \
		 --without-extra-tools \
		 --without-readline

.include <mirports.sys.mk>

.if defined(USE_GCC3) && (${USE_GCC3:L} == "yes")
CONFIGURE_ARGS+=--with-client-ldflags=-lsupc++ \
		--with-mysqld-ldflags=-lsupc++
.endif


.if ${MACHINE} == "i386"
CONFIGURE_ARGS+= --enable-assembler
.endif

MULTI_PACKAGES=	-server -tests
SUBPACKAGE?=

.if ${SUBPACKAGE} == "-server"
RUN_DEPENDS=	:mysql-client-4.0.*:databases/mysql \
		:p5-DBD-mysql-*:databases/p5-DBD-mysql
.endif

DOCS=		manual.html manual.ps manual_toc.html manual.txt

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/mysql/Flags
	cd ${WRKSRC}/Docs; ${INSTALL_DATA} ${DOCS} ${PREFIX}/share/doc/mysql
	${INSTALL_DATA} ${WRKSRC}/Docs/Flags/*.gif \
		${PREFIX}/share/doc/mysql/Flags
	cd ${PREFIX}/lib && ln -sf mysql/libmysqlclient.so.12.0 . && \
		ln -sf mysql/libmysqlclient_r.so.12.0 .

do-regress:
	@cd ${WRKSRC}/mysql-test && ./mysql-test-run --force

.include <bsd.port.mk>
