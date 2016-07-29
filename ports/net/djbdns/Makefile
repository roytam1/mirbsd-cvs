# $MirOS: ports/net/djbdns/Makefile,v 1.49 2016/06/12 22:28:38 tg Exp $

COMMENT=		collection of Domain Name System server and tools
VERSION=		1.05
CATEGORIES=		net
DISTNAME=		djbdns-${VERSION}
DASH_VER=		46
MANVER=			20031023
HOMEPAGE=		http://cr.yp.to/djbdns.html
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.org>

# Public Domain: http://cr.yp.to/distributors.html
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

FLAVOURS=		eorsn icann opennic
FLAVOUR?=		icann

DISTFILES=		${DISTNAME}${EXTRACT_SUFX} \
			${DISTNAME}-man-${MANVER}${EXTRACT_SUFX}:0
MASTER_SITES=		http://cr.yp.to/djbdns/ \
			ftp://ftp.id.wustl.edu/pub/qmail/
MASTER_SITES0=		http://smarden.org/pape/djb/manpages/

RUN_DEPENDS=		::sysutils/daemontools
NO_REGRESS=		Yes

.undef DNSROOT

# root hints:		ftp://ftp.internic.net/domain/named.root.sig
# root hints:		ftp://ftp.internic.net/domain/named.root
.if ${FLAVOUR:L:Micann}
.  ifdef DNSROOT
BROKEN=			Multiple DNS Roots chosen; invalid combination
.  else
DNSROOT=		icann
.  endif
.endif

# public resolvers:	2a01:7e0::212:224:71:71 212.224.71.71 79.133.62.62
# root hints:		http://www.orsn.org/roothint/root-hint.txt
.if ${FLAVOUR:L:Meorsn}
.  ifdef DNSROOT
BROKEN=			Multiple DNS Roots chosen; invalid combination
.  else
DNSROOT=		eorsn
.  endif
.endif

# public resolvers:	185.27.253.92 62.141.38.230 78.138.98.82 78.138.97.33
# root hints:		$(dig . NS @75.127.96.89)
.if ${FLAVOUR:L:Mopennic}
.  ifdef DNSROOT
BROKEN=			Multiple DNS Roots chosen; invalid combination
.  else
DNSROOT=		opennic
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

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/djbdns
	${INSTALL_DATA} ${FILESDIR}/data/dnsroots.${DNSROOT} \
	    ${PREFIX}/share/djbdns/dnsroots.global

.include <bsd.port.mk>
