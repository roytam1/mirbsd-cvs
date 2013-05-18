# $MirOS: ports/devel/p5-Module-Build/Makefile,v 1.5 2009/05/07 04:58:41 bsiegert Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2004/05/26 11:16:49 msf Exp $

COMMENT=		build and install Perl modules

VSN=			0.31
DASH_VER=		1
DISTNAME=		Module-Build-${VSN}
PKGNAME=		p5-${DISTNAME}-${DASH_VER}
CATEGORIES=		devel perl5


# Artistic
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=Module/}

CONFIGURE_STYLE= perl modbuild

B_R_DEPENDS=	::archivers/p5-Archive-Tar \
		::devel/p5-ExtUtils-ParseXS \
		:p5-YAML->=0.35:devel/p5-YAML

PKG_ARCH=	*

.include <bsd.port.mk>
