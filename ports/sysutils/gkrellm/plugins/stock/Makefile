# $OpenBSD: Makefile,v 1.1.1.1 2003/11/03 20:34:18 sturm Exp $

COMMENT=			Stock Ticker for GkrellM2

VERSION=	0.5.1
DISTNAME=	gkrellstock-${VERSION}
CATEGORIES=	misc sysutils/gkrellm

HOMEPAGE=	http://gkrellstock.sourceforge.net/
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=gkrellstock/}

RUN_DEPENDS+=	:p5-Finance-Quote-*:misc/p5-Finance-Quote

WRKDIST=       	${WRKDIR}/gkrellStock-${VERSION}
ALL_TARGET=	gkrellstock.so
PLUGIN=		${WRKSRC}/gkrellstock.so
PERLDIR=	${PREFIX}/libdata/perl5/site_perl/Finance/Quote/

post-install:
	${INSTALL_DATA_DIR} ${PERLDIR}
	${INSTALL_DATA} ${WRKSRC}/Asia.pm ${PERLDIR}
	${INSTALL_SCRIPT} ${WRKSRC}/GetQuote2 ${PREFIX}/bin

.include <bsd.port.mk>
