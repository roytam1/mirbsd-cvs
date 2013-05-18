# $MirOS: ports/converters/p5-Locale-gettext/Makefile,v 1.3 2005/07/07 21:18:14 bsiegert Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=			interface to gettext() internationalization function
DISTNAME=	gettext-1.02
PKGNAME=	p5-Locale-${DISTNAME}-0
CATEGORIES=	converters perl5

# GNU GPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=   ${MASTER_SITE_PERL_CPAN:=Locale/}

MODULES=	devel/gettext

DIST_SUBDIR=	${PKGNAME}
CONFIGURE_STYLE=perl

.include <bsd.port.mk>
