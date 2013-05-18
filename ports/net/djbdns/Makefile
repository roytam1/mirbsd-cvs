# $MirOS: ports/net/djbdns/Makefile,v 1.38 2009/05/30 21:52:28 tg Exp $

COMMENT=		collection of Domain Name System server and tools
VERSION=		1.05
CATEGORIES=		net
DISTNAME=		djbdns-${VERSION}
DASH_VER=		37
MANVER=			20031023
HOMEPAGE=		http://cr.yp.to/djbdns.html
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.org>

# Public Domain: http://cr.yp.to/distributors.html
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

DISTFILES=		${DISTNAME}${EXTRACT_SUFX} \
			${DISTNAME}-man-${MANVER}${EXTRACT_SUFX}:0
MASTER_SITES=		http://cr.yp.to/djbdns/ \
			ftp://ftp.id.wustl.edu/pub/qmail/
MASTER_SITES0=		http://smarden.org/pape/djb/manpages/

RUN_DEPENDS=		::sysutils/daemontools
NO_REGRESS=		Yes

WRKDIST=		${WRKDIR}
WRKSRC=			${WRKDIR}/build
CONFIGURE_STYLE=	simple
CONFIGURE_ENV+=		TOP=${WRKDIR} SYSCONFDIR=${SYSCONFDIR:Q}
MAKE_ENV+=		TOP=${WRKDIR}
CPPFLAGS+=		-D_SYSCONFDIR=\"${SYSCONFDIR:Q}\"
CPPFLAGS+=		-D_DJBDNS_PORT_V=\"${PKGNAME:Q}\"
CPPFLAGS+=		-D_PATH_MKSH=\"${MKSH:Q}\"

post-extract:
	cd ${FILESDIR}; pax -rw build ${WRKDIR}
	cd ${WRKDIR}; mv djbdns-${VERSION} src; mv djbdns-man man

post-build:
	cat ${FILESDIR}/data/dnsroots.icann6 ${FILESDIR}/data/dnsroots.icann \
	    >${WRKBUILD}/dnsroots.icann6+4

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/djbdns
	${INSTALL_DATA} ${FILESDIR}/data/dnsroots.icann \
	    ${PREFIX}/share/djbdns/dnsroots.global
	${INSTALL_DATA} ${WRKBUILD}/dnsroots.icann6+4 \
	    ${PREFIX}/share/djbdns/dnsroots.global.v6

.include <bsd.port.mk>
