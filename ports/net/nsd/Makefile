# $OpenBSD: Makefile,v 1.19 2004/05/18 11:33:09 jakob Exp $

BROKEN=			bind9 port doesn't include named-xfer; upgrading
BROKEN+=		nsd will solve this since newer versions include
BROKEN+=		their own zone transfer client

COMMENT=		authoritative-only name server daemon

VERSION=	2.1.0
DISTNAME=	nsd-${VERSION}
PKGNAME=	nsd-${VERSION}-1
CATEGORIES=	net

MASTER_SITES=	http://www.nlnetlabs.nl/downloads/nsd/

HOMEPAGE=	http://www.nlnetlabs.nl/nsd/


PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

#RUN_DEPENDS=	:named-xfer-*:net/named-xfer

CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	--enable-dnssec \
			--enable-bind8-stats \
			--with-namedxfer=${LOCALBASE}/libexec/named-xfer \
			--with-libwrap=/usr/lib \
			--with-user=named \
			--with-pidfile=/var/run/nsd.pid \
			--with-zonesdir=/var/nsd \
			--with-dbfile=/var/nsd/nsd.db

NO_REGRESS=	Yes

DOCDIR=		share/doc/nsd
DOCFILES=	README RELNOTES CREDITS DIFFERENCES REQUIREMENTS

EXAMPLESDIR=	share/examples/nsd

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/nsd ${PREFIX}/sbin
	${INSTALL_PROGRAM} ${WRKSRC}/nsd-notify ${PREFIX}/sbin
	${INSTALL_PROGRAM} ${WRKSRC}/zonec ${PREFIX}/sbin
	${INSTALL_SCRIPT} ${WRKSRC}/nsdc.sh ${PREFIX}/sbin/nsdc
	${INSTALL_MAN} ${WRKSRC}/nsd.8 ${PREFIX}/man/man8
	${INSTALL_MAN} ${WRKSRC}/nsd-notify.8 ${PREFIX}/man/man8
	${INSTALL_MAN} ${WRKSRC}/nsdc.8 ${PREFIX}/man/man8
	${INSTALL_MAN} ${WRKSRC}/zonec.8 ${PREFIX}/man/man8
	${INSTALL_DATA_DIR} ${PREFIX}/${EXAMPLESDIR}
	${INSTALL_DATA} ${WRKSRC}/nsd.zones.sample ${PREFIX}/${EXAMPLESDIR}
	${INSTALL_DATA} ${WRKSRC}/nsdc.conf.sample ${PREFIX}/${EXAMPLESDIR}
	${INSTALL_DATA_DIR} ${PREFIX}/${DOCDIR}
.for f in ${DOCFILES}
	${INSTALL_DATA} ${WRKSRC}/${f} ${PREFIX}/${DOCDIR}
.endfor

.include <bsd.port.mk>
