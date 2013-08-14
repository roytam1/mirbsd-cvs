# $MirOS: ports/net/djbdns/Makefile,v 1.44 2013/01/05 01:50:13 tg Exp $

COMMENT=		collection of Domain Name System server and tools
VERSION=		1.05
CATEGORIES=		net
DISTNAME=		djbdns-${VERSION}
DASH_VER=		42
MANVER=			20031023
HOMEPAGE=		http://cr.yp.to/djbdns.html
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.org>

# Public Domain: http://cr.yp.to/distributors.html
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

FLAVOURS=		eorsn icann
FLAVOUR?=		icann

DISTFILES=		${DISTNAME}${EXTRACT_SUFX} \
			${DISTNAME}-man-${MANVER}${EXTRACT_SUFX}:0
MASTER_SITES=		http://cr.yp.to/djbdns/ \
			ftp://ftp.id.wustl.edu/pub/qmail/
MASTER_SITES0=		http://smarden.org/pape/djb/manpages/

RUN_DEPENDS=		::sysutils/daemontools
NO_REGRESS=		Yes

.undef DNSROOT

.if ${FLAVOUR:L:Micann}
.  ifdef DNSROOT
BROKEN=			Multiple DNS Roots chosen; invalid combination
.  else
DNSROOT=		icann
DNSROOT6=		icann
.  endif
.endif

# public resolvers:	2a01:7e0::212:224:71:71 212.224.71.71 79.133.62.62
.if ${FLAVOUR:L:Meorsn}
.  ifdef DNSROOT
BROKEN=			Multiple DNS Roots chosen; invalid combination
.  else
DNSROOT=		eorsn
DNSROOT6=		eorsn6
.  endif
.endif

.if !defined(DNSROOT) || ${DNSROOT} == ""
BROKEN=			choose a DNS Root flavour (suggest: eorsn)
.endif

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
	cat ${FILESDIR}/data/dnsroots.${DNSROOT6} \
	    ${FILESDIR}/data/dnsroots.${DNSROOT} \
	    >${WRKBUILD}/dnsroots.6+4

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/djbdns
	${INSTALL_DATA} ${FILESDIR}/data/dnsroots.${DNSROOT} \
	    ${PREFIX}/share/djbdns/dnsroots.global
	${INSTALL_DATA} ${WRKBUILD}/dnsroots.6+4 \
	    ${PREFIX}/share/djbdns/dnsroots.global.v6

.include <bsd.port.mk>
