# $MirOS$
# $OpenBSD: Makefile,v 1.14 2002/10/28 01:38:46 naddy Exp $

COMMENT=		transparent IRC proxy
DISTNAME=		tircproxy-0.4.5
DASH_VER=		1
CATEGORIES=     	net
HOMEPAGE=		http://bre.klaki.net/programs/tircproxy/

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${HOMEPAGE}

#XXX this *must* be changed to autoconf some time…
CONFIGURE_STYLE=	gnu
INSTALL_TARGET=		install-strip
WRKDIST=		${WRKDIR}/tircproxy-0.4
NO_REGRESS=		Yes

.include <bsd.port.mk>
