# $OpenBSD: Makefile,v 1.1.1.1 2004/05/19 09:21:59 sturm Exp $

COMMENT=			add / call inheritable triggers

DISTNAME=	Class-Trigger-0.08
PKGNAME=	p5-${DISTNAME}-0
CATEGORIES=	devel perl5


# Same as Perl
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=Class/}

CONFIGURE_STYLE=perl

BUILD_DEPENDS=	${RUN_DEPENDS}
RUN_DEPENDS=	::devel/p5-Class-Data-Inheritable \
		::devel/p5-IO-stringy

PKG_ARCH=	*

.include <bsd.port.mk>
