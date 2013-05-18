# $OpenBSD: Makefile,v 1.2 2004/01/17 15:58:08 naddy Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=			perl interface to the sync() system functions

VSN=		0.09
DISTNAME=	File-Sync-${VSN}
PKGNAME=	p5-${DISTNAME}-${DASH_VER}
CATEGORIES=	devel perl5

MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=File/}


# same as perl
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE= perl

.include <bsd.port.mk>
