# $MirOS$

COMMENT=	"collection of Domain Name System tools"
NO_REGRESS=	Yes
VERSION=	1.05
CATEGORIES=	net
DISTNAME=	djbdns-${VERSION}
PKGNAME=	${PKGBASE}-${VERSION}p9
HOMEPAGE=	http://cr.yp.to/djbdns.html
RESPONSIBLE=	Thorsten Glaser <tg@${_DOMAIN_DU_JOUR}>

# May distribute unchanged distfiles.
# May distribute patches.
# Must not distribute binaries.
PERMIT_PACKAGE_CDROM=	"http://cr.yp.to/distributors.html"
PERMIT_PACKAGE_FTP=	"http://cr.yp.to/distributors.html"
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

FLAVORS=	opennic orsc icann eorsn no_ipv4 no_ipv6 original
FLAVOR?=	eorsn

DISTFILES=	${DISTNAME}${EXTRACT_SUFX} ${DISTNAME}-man${EXTRACT_SUFX}:0
MASTER_SITES=	http://cr.yp.to/djbdns/ \
		ftp://ftp.id.wustl.edu/pub/qmail/
MASTER_SITES0=	${_MASTER_SITE_MIRBSD}

RUN_DEPENDS=	::sysutils/daemontools

.if ${FLAVOR:L:Moriginal}
FLAVOR=		original no_ipv6 icann
.endif

.if ${FLAVOR:L:Mno_ipv6}
.  if ${FLAVOR:L:Mno_ipv4}
BROKEN=		Choose either one: no_ipv4, no_ipv6 or none of those
.  else
# no_ipv6: the "original" djbdns
PKGTYPE=	djbdns
PKGBASE=	djbdns
.  endif
.elif ${FLAVOR:L:Mno_ipv4}
# no_ipv4: the AF_INET6 listening flavour
PKGTYPE=	fefedns
PKGBASE=	djbdns6
FLAVOR=		no_ipv4
PLIST=		${PKGDIR}/PLIST6
FULLPKGNAME=	${PKGNAME}
DNSROOT=	eorsn6
.else
# neither: the AF_INET listening flavour
PKGTYPE=	tinydns
PKGBASE=	djbdns
.endif

.if ${FLAVOR:L:Mopennic}
.  ifdef DNSROOT
BROKEN=		Multiple DNS Roots chosen; invalid combination
.  else
DNSROOT=opennic
.  endif
.endif

.if ${FLAVOR:L:Morsc}
.  ifdef DNSROOT
BROKEN=		Multiple DNS Roots chosen; invalid combination
.  else
DNSROOT=orsc
.  endif
.endif

.if ${FLAVOR:L:Micann}
.  ifdef DNSROOT
BROKEN=		Multiple DNS Roots chosen; invalid combination
.  else
DNSROOT=icann
.  endif
.endif

.if ${FLAVOR:L:Meorsn}
.  ifdef DNSROOT
BROKEN=		Multiple DNS Roots chosen; invalid combination
.  else
DNSROOT=eorsn
.  endif
.endif

.if !defined(DNSROOT) || ${DNSROOT} == ""
BROKEN=		"choose a DNS Root flavour (default: eorsn)"
.endif

# datasize limit in 'run' files is too low for ld.so
# to be able to pull in libc
LDFLAGS+=	-static

ALL_TARGET=	default
INSTALL_TARGET=	setup check

MAN5LIST=	qualification
MAN1LIST=	dnsfilter dnsipq dnsname dnsqr dnstxt dnsip \
		dnsmx dnsq dnstrace dnstracesort
MAN8LIST=	axfr-get dnscache pickdns rbldns tinydns axfrdns \
		pickdns-conf rbldns-conf tinydns-conf walldns-conf \
		dnscache-conf pickdns-data rbldns-data tinydns-data \
		tinydns-edit walldns

BINLIST=	axfr-get axfrdns axfrdns-conf dnscache dnscache-conf \
		dnsfilter dnsip dnsipq dnsmx dnsname dnsq dnsqr dnstrace \
		dnstxt pickdns pickdns-conf pickdns-data random-ip rbldns \
		rbldns-conf rbldns-data tinydns tinydns-conf tinydns-data \
		tinydns-edit tinydns-get walldns walldns-conf
.if ${PKGTYPE} != "djbdns"
BINLIST+=	dnsip6 dnsip6q
.endif

SCRIPTLIST=	dnstracesort

.if ${PKGTYPE} == "djbdns"
PATCH_LIST=	0patch-Makefile 0patch-hier_c 0patch-dns_h
.  if ${FLAVOR:L:Moriginal}
FILES_LIST=	../pkg/SECURITY
.  else
PATCH_LIST+=	0patch-dnscache_c 0patch-query_c
FILES_LIST=	ignoreip-update
.  endif
.elif ${PKGTYPE} == "fefedns"
PATCH_LIST=	0patch-Makefile 0patch-hier_c 0patch-dnscache_c \
		0patch-query_c 4patch-Makefile 6patch-Makefile \
		patch-FILES patch-TARGETS patch-axfr-get_c 0patch-dns_h \
		46patch-dns_h patch-dns_name_c patch-dns_rcip_c \
		patch-dns_resolve_c patch-dns_transmit_c \
		patch-dnscache-conf_c 6patch-dnscache_c patch-dnsfilter_c \
		patch-dnsname_c patch-dnsq_c patch-dnstrace_c \
		patch-dnstracesort_sh 46patch-hier_c patch-log_c \
		patch-okclient_c patch-pickdns-conf_c patch-printrecord_c \
		patch-qlog_c 6patch-query_c patch-query_h patch-rbldns-conf_c \
		patch-roots_c patch-server_c patch-socket_bind_c \
		patch-socket_h patch-tinydns-conf_c patch-tinydns-data_c \
		patch-tinydns-edit_c patch-walldns-conf_c 6_patch-tdlookup_c
FILES_LIST=	dns_ip6.c dns_ipq6.c dns_nd6.c dns_sortip6.c \
		dnsip6.c dnsip6q.c fmt_xlong.c \
		haveip6.h1 haveip6.h2 haven2i.h1 haven2i.h2 \
		ip6.h ip6_fmt.c ip6_scan.c scan_xlong.c \
		sockaddr_in6.h1 sockaddr_in6.h2 \
		socket_accept6.c socket_bind6.c socket_connect6.c \
		socket_getifidx.c socket_noipv6.c \
		socket_recv6.c socket_send6.c socket_tcp6.c socket_udp6.c \
		tryip6.c tryn2i.c trysa6.c
.else
PATCH_LIST=	0patch-Makefile 0patch-hier_c 0patch-dnscache_c \
		0patch-query_c 4patch-Makefile patch-FILES \
		patch-TARGETS patch-axfr-get_c 46patch-dns_h \
		patch-dnstrace_c patch-dnstracesort_sh \
		46patch-hier_c patch-printrecord_c 4_patch-tdlookup_c \
		patch-tinydns-data_c patch-tinydns-data_8
FILES_LIST=	dns_ip6.c dns_ipq6.c dns_nd6.c dns_sortip6.c \
		dnsip6.c dnsip6q.c fmt_xlong.c \
		ip6.h ip6_fmt.c ip6_scan.c scan_xlong.c ignoreip-update
.endif

.if ${OSname} == "mirbsd" && ${OSrev} >= 8
PATCH_LIST+=	patch-tai_now_c patch-taia_now_c
.endif

pre-patch:
	@cp ${FILESDIR}/dnsroots.${DNSROOT} \
	  ${WRKSRC}/dnsroots.global || { \
		echo "invalid combination of flavors!"; \
		exit 1; \
	  }

pre-build:
.for file in ${FILES_LIST}
	cp ${FILESDIR}/${file} ${WRKSRC}
.endfor
	echo ${CC} ${CFLAGS} > ${WRKSRC}/conf-cc
	echo ${CC} -s ${LDFLAGS} > ${WRKSRC}/conf-ld
	echo ${PREFIX} > ${WRKSRC}/conf-home

pre-install:
	@echo ${PREFIX} > ${WRKSRC}/conf-home
	${INSTALL_DATA_DIR} ${PREFIX}/share/djbdns

post-install:
.for file in ${BINLIST}
	@strip ${PREFIX}/bin/${file}
.endfor
.for file in ${BINLIST} ${SCRIPTLIST}
	@chmod 0555 ${PREFIX}/bin/${file}
.  if ${PKGTYPE} == "fefedns"
	@mv ${PREFIX}/bin/${file} ${PREFIX}/bin/6${file}
.  endif
.endfor
.if ${PKGTYPE} != "fefedns"
.  for mtype in 1 5 8
.    for file in ${MAN${mtype}LIST}
	${INSTALL_MAN} ${WRKDIR}/djbdns-man/${file}.${mtype} \
		${PREFIX}/man/man${mtype}
.    endfor
.  endfor
.endif
.if ${FLAVOR:L:Mno_ipv4}
	cd ${PREFIX}/share/djbdns && mv dnsroots.global dnsroots.global.v6
.endif
	if [ -e ${WRKSRC}/SECURITY ]; then ${INSTALL_DATA} \
	    ${WRKSRC}/SECURITY ${PREFIX}/share/djbdns; fi
	if [ -e ${WRKSRC}/ignoreip-update ]; then ${INSTALL_SCRIPT} \
	    ${WRKSRC}/ignoreip-update ${PREFIX}/bin; fi

.include <bsd.port.mk>
