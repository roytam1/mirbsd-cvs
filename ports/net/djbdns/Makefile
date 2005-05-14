# $MirOS: ports/net/djbdns/Makefile,v 1.1.7.1 2005/03/18 15:48:07 tg Exp $

COMMENT=		"collection of Domain Name System server and tools"
VERSION=		1.05
CATEGORIES=		net
DISTNAME=		djbdns-${VERSION}
PKGNAME=		djbdns-${VERSION}p10
HOMEPAGE=		http://cr.yp.to/djbdns.html
RESPONSIBLE=		Thorsten Glaser <tg@${_DOMAIN_DU_JOUR}>

# May distribute unchanged distfiles. May distribute patches.
# Must not distribute binaries (changed or not).
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	"http://cr.yp.to/distributors.html"
PERMIT_PACKAGE_FTP=	"http://cr.yp.to/distributors.html"

FLAVORS=		eorsn icann opennic orsc
FLAVOR?=		eorsn

DISTFILES=		${DISTNAME}${EXTRACT_SUFX} \
			${DISTNAME}-man${EXTRACT_SUFX}:0
MASTER_SITES=		http://cr.yp.to/djbdns/ \
			ftp://ftp.id.wustl.edu/pub/qmail/
MASTER_SITES0=		${_MASTER_SITE_MIRBSD}

RUN_DEPENDS=		::sysutils/daemontools
NO_REGRESS=		Yes

.undef DNSROOT
DNSROOT6=	eorsn6

.if ${FLAVOR:L:Mopennic}
.  ifdef DNSROOT
BROKEN=		Multiple DNS Roots chosen; invalid combination
.  else
DNSROOT=	opennic
.  endif
.endif

.if ${FLAVOR:L:Morsc}
.  ifdef DNSROOT
BROKEN=		Multiple DNS Roots chosen; invalid combination
.  else
DNSROOT=	orsc
.  endif
.endif

.if ${FLAVOR:L:Micann}
.  ifdef DNSROOT
BROKEN=		Multiple DNS Roots chosen; invalid combination
.  else
DNSROOT=	icann
.  endif
.endif

.if ${FLAVOR:L:Meorsn}
.  ifdef DNSROOT
BROKEN=		Multiple DNS Roots chosen; invalid combination
.  else
DNSROOT=	eorsn
.  endif
.endif

.if !defined(DNSROOT) || ${DNSROOT} == ""
BROKEN=		choose a DNS Root flavour (default: eorsn)
.endif

WRKDIST=		${WRKDIR}
WRKSRC=			${WRKDIR}/build
CONFIGURE_STYLE=	simple
CONFIGURE_ENV+=		TOP=${WRKDIR}
MAKE_ENV+=		TOP=${WRKDIR}

post-extract:
	cd ${FILESDIR}; find build -type f \! -path \*CVS\* \
	    | cpio -pdu ${WRKDIR}/
	cd ${WRKDIR}; mv djbdns-${VERSION} src; mv djbdns-man man

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/djbdns
	${INSTALL_DATA} ${FILESDIR}/data/dnsroots.${DNSROOT} \
	    ${PREFIX}/share/djbdns/dnsroots.global
	${INSTALL_DATA} ${FILESDIR}/data/dnsroots.${DNSROOT6} \
	    ${PREFIX}/share/djbdns/dnsroots.global.v6

.include <bsd.port.mk>
