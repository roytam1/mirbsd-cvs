# $MirOS: ports/www/p5-libwww/Makefile,v 1.4 2006/09/14 00:14:57 tg Exp $
# $OpenBSD: Makefile,v 1.20 2003/10/18 19:44:57 sturm Exp $

COMMENT=	library for WWW access in Perl (LWP)

DISTNAME=	libwww-perl-5.834
PKGNAME=	p5-${DISTNAME:S/-perl-/-/}-${DASH_VER}
CATEGORIES=	www perl5
MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=LWP/}

B_R_DEPENDS+=	:p5-URI->1.10:www/p5-URI \
		:p5-HTML-Parser->=2.20:www/p5-HTML-Parser \
		:p5-Crypt-SSLeay-*:security/p5-Crypt-SSLeay \
		:p5-HTTP-GHTTP-*:www/p5-HTTP-GHTTP \
		:p5-Compress-Zlib-*:archivers/p5-Compress-Zlib \
		::converters/p5-Encode

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE= perl

.include <bsd.port.mk>
