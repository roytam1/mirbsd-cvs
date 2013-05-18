# $MirOS$
# $OpenBSD: Makefile,v 1.1.1.1 2004/05/21 22:11:47 msf Exp $

COMMENT=		convert Perl XS code into C code

DISTNAME=		ExtUtils-ParseXS-2.19
PKGNAME=		p5-${DISTNAME}-${DASH_VER}
CATEGORIES=		devel perl5

# Artistic
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=ExtUtils/}

B_R_DEPENDS=		::devel/p5-ExtUtils-CBuilder

CONFIGURE_STYLE=	perl
CONFIGURE_ARGS+=	INSTALLDIRS= perl

PKG_ARCH=		*

.include <bsd.port.mk>
