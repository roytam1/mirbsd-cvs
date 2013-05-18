# $MirOS$
# $OpenBSD: Makefile,v 1.10 2003/11/12 06:27:05 kevlo Exp $

COMMENT=		extension for portable daemons

DISTNAME=		Net-Daemon-0.43
PKGNAME=		p5-${DISTNAME}-${DASH_VER}
CATEGORIES=		net perl5

# GPL/Artistic
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES= 		  ${MASTER_SITE_PERL_CPAN:=Net/}

CONFIGURE_STYLE=	perl
PKG_ARCH=		*

WRKDIST=		${WRKDIR}/Net-Daemon

.include <bsd.port.mk>
