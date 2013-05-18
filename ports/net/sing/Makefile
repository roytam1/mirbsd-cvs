# $OpenBSD: Makefile,v 1.9 2003/04/01 16:58:37 danh Exp $

COMMENT=	"send ICMP nasty garbage"

DISTNAME=	SING-1.1
PKGNAME=	${DISTNAME:L}-1
CATEGORIES=	net security
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=sing/}
EXTRACT_SUFX=	.tgz

HOMEPAGE=	http://sourceforge.net/projects/sing/

LIB_DEPENDS=	net::net/libnet


PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE= autoconf

.include <bsd.port.mk>
