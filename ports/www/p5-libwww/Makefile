# $MirOS: ports/www/p5-libwww/Makefile,v 1.3 2006/03/25 13:30:06 bsiegert Exp $
# $OpenBSD: Makefile,v 1.20 2003/10/18 19:44:57 sturm Exp $

COMMENT=			library for WWW access in Perl

DISTNAME=	libwww-perl-5.805
PKGNAME=	p5-${DISTNAME:S/-perl-/-/}-0
CATEGORIES=	www perl5
MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=LWP/}

BUILD_DEPENDS=  :p5-URI->1.10:www/p5-URI \
		:p5-HTML-Parser->=2.20:www/p5-HTML-Parser \
		:p5-Crypt-SSLeay-*:security/p5-Crypt-SSLeay \
		:p5-HTTP-GHTTP-*:www/p5-HTTP-GHTTP \
		:p5-Compress-Zlib-*:archivers/p5-Compress-Zlib
RUN_DEPENDS=    ${BUILD_DEPENDS}

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE= perl

.include <bsd.port.mk>
