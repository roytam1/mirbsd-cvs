# $MirOS: ports/infrastructure/templates/perlmod.Makefile,v 1.1 2009/01/01 17:11:33 bsiegert Exp $

COMMENT=		dispatches messages to one or more outputs
DISTNAME=		Log-Dispatch-2.22
PKGNAME=		p5-${DISTNAME}-${DASH_VER}
CATEGORIES=		devel perl5
MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=../../authors/id/D/DR/DROLSKY}

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	perl modbuild

B_R_DEPENDS+=		::devel/p5-File-Temp
B_R_DEPENDS+=		:p5-Params-Validate>=0.15:devel/p5-Params-Validate

PKG_ARCH=		*

# @@DECLS@@

.include <bsd.port.mk>
