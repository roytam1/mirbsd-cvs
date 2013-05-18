# $MirOS: ports/net/bind/Makefile,v 1.9 2008/05/25 20:56:38 tg Exp $
# $OpenBSD: Makefile,v 1.42 2003/04/10 18:08:56 jsyn Exp $

BROKEN+=		distfile fetch problem
BROKEN+=		netaddr.c:136: error: conflicting types for 'isc_netaddr_format'

COMMENT=		ISC BIND 9 libraries, audited OpenBSD version
COMMENT-server=		ISC BIND 9 server, audited OpenBSD version
COMMENT-client=		ISC BIND 9 client tools, audited OpenBSD version

VERSION=		9.3.4.1
CVS_DISTREPO=		:ext:anoncvs@anoncvs.ca.openbsd.org:/cvs
CVS_DISTDATE=		2007/07/25
CVS_DISTMODS=		src/usr.sbin/bind src/etc/bind
CVS_DISTFILE=		bind

PKGNAME=		bind-${VERSION}-${DASH_VER}
FULLPKGNAME=		bind-lib-${VERSION}-${DASH_VER}
PKGNAME-server=		bind-server-${VERSION}-${DASH_VER}
PKGNAME-client=		bind-client-${VERSION}-${DASH_VER}

CATEGORIES=		net

HOMEPAGE=		http://www.isc.org/products/BIND/
RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

# BSD licence
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

WRKDIST=		${WRKDIR}/src/usr.sbin/bind/
ETCDIR=			${WRKDIR}/src/etc/bind/

DATADIR=		/var/named
SUBST_VARS+=		DATADIR

MULTI_PACKAGES=		-server -client
SUBPACKAGE?=
FLAVOURS=		static threads
FLAVOUR?=

.if defined(PACKAGING) && ${FLAVOUR} != "static"
. if ${SUBPACKAGE} == "-client"
RUN_DEPENDS=		:bind-lib-${VERSION}:net/bind
. elif ${SUBPACKAGE} == "-server"
RUN_DEPENDS=		:bind-lib-${VERSION}:net/bind \
			:bind-client-${VERSION}:net/bind
. endif
.endif

.if ${FLAVOUR:L:Mstatic}
CFLAGS+=		"-static"
NO_SHARED_LIBS=		Yes
.endif

.include <mirports.sys.mk>
.if ${OStype:M*BSD}
RND_DEVICE=		/dev/arandom
.else
RND_DEVICE=		/dev/urandom
.endif

NO_REGRESS=		Yes
CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes

CONFIGURE_ARGS+=	--with-libtool ${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--localstatedir=/var
CONFIGURE_ARGS+=	--disable-libbind
CONFIGURE_ARGS+=	--with-openssl=/usr
CONFIGURE_ARGS+=	--with-randomdev=/dev/arandom

.if ${FLAVOUR:L:Mthreads}
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
.for file in localhost loopback loopback6.arpa
	${INSTALL_DATA} ${ETCDIR}/db.${file} ${PREFIX}/share/examples/bind9/standard/${file}
.endfor
	sed -e s,@LOCALBASE@,${LOCALBASE}, < ${FILESDIR}/rc.local.frag > ${PREFIX}/share/examples/bind9/rc.local.frag

.include <bsd.port.mk>
