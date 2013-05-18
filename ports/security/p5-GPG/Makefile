# $MirOS: ports/security/p5-GPG/Makefile,v 1.4 2008/03/23 13:10:09 bsiegert Exp $
# $OpenBSD: Makefile,v 1.8 2002/12/29 20:31:40 fgsch Exp $

COMMENT=	perl5 interface to GnuPG using scalars

VERSION=	0.06
DASH_VER=	1
DISTNAME=	GPG-${VERSION}
PKGNAME=	p5-${DISTNAME}-${DASH_VER}
CATEGORIES=	security perl5
MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=../../authors/id/M/MI/MILES/}

BUILD_DEPENDS=	:gnupg-*:security/gnupg
RUN_DEPENDS=	${BUILD_DEPENDS}


PERMIT_PACKAGE_CDROM=	"no license"
PERMIT_PACKAGE_FTP=	"no license"
PERMIT_DISTFILES_CDROM=	"no license"
PERMIT_DISTFILES_FTP=	"no license"

CONFIGURE_STYLE= perl

.include <bsd.port.mk>	
