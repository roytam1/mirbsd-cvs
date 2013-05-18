# $MirOS: ports/net/djbdns/Makefile,v 1.29 2006/11/16 21:27:41 tg Exp $

COMMENT=		collection of Domain Name System server and tools
VERSION=		1.05
CATEGORIES=		net
DISTNAME=		djbdns-${VERSION}
MANVER=			20031023
PKGNAME=		djbdns-${VERSION}-31
HOMEPAGE=		http://cr.yp.to/djbdns.html
RESPONSIBLE=		Thorsten Glaser <tg@66h.42h.de>

# May distribute unchanged distfiles. May distribute patches.
# Must not distribute binaries (changed or not).
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	"http://cr.yp.to/distributors.html"
PERMIT_PACKAGE_FTP=	"http://cr.yp.to/distributors.html"

FLAVORS=		eorsn icann opennic
FLAVOR?=		eorsn

DISTFILES=		${DISTNAME}${EXTRACT_SUFX} \
			${DISTNAME}-man-${MANVER}${EXTRACT_SUFX}:0
MASTER_SITES=		http://cr.yp.to/djbdns/ \
			ftp://ftp.id.wustl.edu/pub/qmail/
MASTER_SITES0=		http://smarden.org/pape/djb/manpages/

RUN_DEPENDS=		::sysutils/daemontools
NO_REGRESS=		Yes

.undef DNSROOT
DNSROOT6=		eorsn6

.if ${FLAVOR:L:Mopennic}
.  ifdef DNSROOT
BROKEN=			Multiple DNS Roots chosen; invalid combination
.  else
DNSROOT=		opennic
.  endif
.endif

.if ${FLAVOR:L:Micann}
.  ifdef DNSROOT
BROKEN=			Multiple DNS Roots chosen; invalid combination
.  else
DNSROOT=		icann
.  endif
.endif

.if ${FLAVOR:L:Meorsn}
.  ifdef DNSROOT
BROKEN=			Multiple DNS Roots chosen; invalid combination
.  else
DNSROOT=		eorsn
.  endif
.endif

.if !defined(DNSROOT) || ${DNSROOT} == ""
BROKEN=			choose a DNS Root flavour (default: eorsn)
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

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/djbdns
	${INSTALL_DATA} ${FILESDIR}/data/dnsroots.${DNSROOT} \
	    ${PREFIX}/share/djbdns/dnsroots.global
	${INSTALL_DATA} ${FILESDIR}/data/dnsroots.${DNSROOT6} \
	    ${PREFIX}/share/djbdns/dnsroots.global.v6

.include <bsd.port.mk>
