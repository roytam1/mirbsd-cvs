# $MirOS$
# $OpenBSD: Makefile,v 1.2 2004/05/17 11:34:06 grange Exp $

COMMENT=		IPv4/IPv6 traffic collector

DISTNAME=		cnupm-3.12
CATEGORIES=		net

HOMEPAGE=		http://pdp-11.org.ru/~form/cnupm

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${HOMEPAGE}/files/

MAKE_ENV=		BINDIR=${TRUEPREFIX}/sbin MANDIR=${TRUEPREFIX}/man/cat
CFLAGS+=		-DCNUPM_USER=\"_cnupm\"

FLAVOURS=		static
FLAVOUR?=

.if ${FLAVOUR:Mstatic}
LDSTATIC=		-static
MAKE_ENV+=		LDSTATIC=${LDSTATIC}
.endif

post-extract:
	@rm ${WRKSRC}/include/sys/tree.h

.include <bsd.port.mk>
