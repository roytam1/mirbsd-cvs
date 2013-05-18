# $MirOS$
# $OpenBSD: Makefile,v 1.12 2003/07/17 05:24:04 kevlo Exp $

COMMENT=		module for writing rpc servers and clients

DISTNAME=		PlRPC-0.2020
PKGNAME=		p5-${DISTNAME}-${DASH_VER}
CATEGORIES=		net perl5


PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=RPC/}

B_R_DEPENDS=		:p5-Net-Daemon->=0.13:net/p5-Net-Daemon

CONFIGURE_STYLE=	perl
WRKDIST=		${WRKDIR}/PlRPC

.include <bsd.port.mk>
