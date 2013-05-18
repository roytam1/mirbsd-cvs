# $OpenBSD: Makefile,v 1.1.1.1 2004/05/20 11:14:50 sturm Exp $

COMMENT=			lightweight, universal exporting/require of variables

VSN=		0.03
DISTNAME=	UNIVERSAL-exports-${VSN}
PKGNAME=	p5-Universal-exports-${VSN}-${DASH_VER}
CATEGORIES=	devel perl5


# Same as Perl
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=UNIVERSAL/}

CONFIGURE_STYLE=perl

RUN_DEPENDS=	::devel/p5-Exporter-Lite
REGRESS_DEPENDS=${RUN_DEPENDS}

PKG_ARCH=	*

.include <bsd.port.mk>
