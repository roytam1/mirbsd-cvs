# $OpenBSD: Makefile,v 1.12 2003/06/22 10:11:29 sturm Exp $

DISTNAME=	scanlogd-2.2
PKGNAME=	${DISTNAME}-1
CATEGORIES=	security
COMMENT=			TCP port scan detection tool
HOMEPAGE=	http://www.openwall.com/scanlogd/


MASTER_SITES=	ftp://ftp.openwall.com/pub/projects/scanlogd/ \
		ftp://rt.fm/pub/scanlogd/

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

BUILD_DEPENDS=	::net/libnids
LIB_DEPENDS=	net::net/libnet

ALL_TARGET=	libnids
NO_REGRESS=	Yes

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/scanlogd ${PREFIX}/sbin/scanlogd
	${INSTALL_MAN} ${WRKSRC}/scanlogd.8 ${PREFIX}/man/man8/scanlogd.8

.include <bsd.port.mk>
