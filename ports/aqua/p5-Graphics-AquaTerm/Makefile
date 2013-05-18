# $MirOS: ports/aqua/p5-Graphics-AquaTerm/Makefile,v 1.1 2006/07/16 12:01:06 bsiegert Exp $

ONLY_FOR_PLATFORM=	Darwin:*:*
COMMENT=			AquaTerm perl adapter module

VERSION=		1.0.0
DASH_VER=		0
DISTNAME=		aquaterm_src.${VERSION}
PKGNAME=		p5-Graphics-AquaTerm-${VERSION}-${DASH_VER}
CATEGORIES=		aqua perl5

HOMEPAGE=		http://aquaterm.sourceforge.net/
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=aquaterm/}

RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

# BSD-like
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

post-extract:
	mkdir ${WRKSRC:Q}
	mv ${WRKSRC:Q}/../adapters/perl/* ${WRKSRC:Q}

pre-configure:
	perl -pi -e 's|%%PREFIX%%|${PREFIX}|g' ${WRKSRC}/Makefile.PL

CONFIGURE_STYLE=	perl

.include <bsd.port.mk>
