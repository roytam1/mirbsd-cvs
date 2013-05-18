# $MirOS$
# $OpenBSD: Makefile,v 1.1.1.1 2004/05/02 23:09:37 naddy Exp $

COMMENT=		persistence framework for Apache session data

DISTNAME=		Apache-Session-1.88
PKGNAME=		p5-${DISTNAME}-${DASH_VER}
CATEGORIES=		www databases perl5
MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=../../authors/id/C/CH/CHORNY/}

EXTRACT_SUFX=		.zip

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	perl

B_R_DEPENDS+=		:p5-Test-Deep>=0.082:devel/p5-Test-Deep
B_R_DEPENDS+=		:p5-Test-Exception>=0.15:devel/p5-Test-Exception
B_R_DEPENDS+=		::devel/p5-File-Temp

PKG_ARCH=		*

.include <bsd.port.mk>
