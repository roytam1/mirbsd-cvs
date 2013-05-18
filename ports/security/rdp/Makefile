# $MirOS: ports/security/rdp/Makefile,v 1.5 2008/10/04 19:03:40 tg Exp $
# $OpenBSD: Makefile,v 1.16 2004/02/01 07:12:39 pvalchev Exp $

COMMENT=	ICMP router discovery protocol spoofer

DISTNAME=	rdp
PKGNAME=	rdp-1.0-0
CATEGORIES=	security
MASTER_SITES=	${MASTER_SITE_OPENBSD}

LIB_DEPENDS=	net::net/libnet

PERMIT_PACKAGE_CDROM=	"no license"
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	"no license"
PERMIT_DISTFILES_FTP=	Yes

WRKDIST=	${WRKDIR}

do-build:
	cd ${WRKSRC} && ${_PASS_CC:Q} ${CFLAGS} -I${PREFIX}/include -o rdp \
		icmp_rdp.c -L${PREFIX}/lib -lnet -lpcap

NO_REGRESS=	Yes

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/rdp ${PREFIX}/sbin
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/rdp
	${INSTALL_DATA} ${WRKSRC}/rdp.advisory ${PREFIX}/share/doc/rdp

.include <bsd.port.mk>
