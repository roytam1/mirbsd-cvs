# $MirOS: ports/net/bind/Makefile,v 1.3 2006/02/09 09:36:07 tg Exp $
# $OpenBSD: Makefile,v 1.42 2003/04/10 18:08:56 jsyn Exp $

COMMENT=			ISC BIND 9 libraries, audited OpenBSD version
COMMENT-server=			ISC BIND 9 server, audited OpenBSD version
COMMENT-client=			ISC BIND 9 client tools, audited OpenBSD version

VERSION=		9.2.3p1
DASHVER=		20031222
DISTNAME=		bind9-${DASHVER}

FULLPKGNAME=		bind-lib-${VERSION}-0
PKGNAME-server=		bind-server-${VERSION}-0
PKGNAME-client=		bind-client-${VERSION}-0

CATEGORIES=		net

MASTER_SITES=		${_MASTER_SITE_MIRBSD}

EXTRACT_SUFX=		.tar.bz2

HOMEPAGE=		http://www.isc.org/products/BIND/
RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

# BSD license
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

WRKDIST=		${WRKDIR}/src/usr.sbin/bind/
ETCDIR=			${WRKDIR}/src/etc/bind/

CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	--with-libtool ${CONFIGURE_SHARED} \
			--localstatedir=/var \
			--disable-libbind \
			--with-openssl=/usr \
			--with-randomdev=/dev/arandom
AUTOCONF_NEW=		Yes
MODGNU_CONFIG_GUESS_DIRS= ${WRKSRC}

REGRESS_TARGET=		test

MULTI_PACKAGES=		-server -client
SUBPACKAGE?=

FLAVORS=		static threads
FLAVOR?=

.if defined(PACKAGING) && ${FLAVOR} != "static"
. if ${SUBPACKAGE} == "-client"
RUN_DEPENDS=		:bind-lib-${VERSION}:net/bind9
. elif ${SUBPACKAGE} == "-server"
RUN_DEPENDS=		:bind-lib-${VERSION}:net/bind9 \
			:bind-client-${VERSION}:net/bind9
. endif
.endif

.if ${FLAVOR:L:Mstatic}
CFLAGS+=		"-static"
NO_SHARED_LIBS=		Yes
.endif

.if ${FLAVOR:L:Mthreads}
CONFIGURE_ARGS+=	--enable-threads
.else
CONFIGURE_ARGS+=	--disable-threads
.endif

MISCDOCFILES=	dnssec ipv6 migration migration-4to9 \
		options rfc-compliance roadmap sdb

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/bind9/arm
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/bind9/misc
	${INSTALL_DATA} ${WRKSRC}/doc/arm/*.html ${PREFIX}/share/doc/bind9/arm
.for file in ${MISCDOCFILES}
	${INSTALL_DATA} ${WRKSRC}/doc/misc/${file} ${PREFIX}/share/doc/bind9/misc
.endfor
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/bind9
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/bind9/etc
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/bind9/standard
	${INSTALL_DATA} ${ETCDIR}/named-*.conf ${PREFIX}/share/examples/bind9/etc
	${INSTALL_DATA} ${ETCDIR}/root.hint ${PREFIX}/share/examples/bind9/standard
.for file in localhost loopback loopback6.arpa loopback6.int
	${INSTALL_DATA} ${ETCDIR}/db.${file} ${PREFIX}/share/examples/bind9/standard/${file}
.endfor
	sed -e s,@LOCALBASE@,${LOCALBASE}, < ${FILESDIR}/rc.local.frag > ${PREFIX}/share/examples/bind9/rc.local.frag

.include <bsd.port.mk>
