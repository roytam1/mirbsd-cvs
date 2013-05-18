# $MirOS: ports/mailnews/p5-MIME-tools/Makefile,v 1.3 2006/09/14 00:10:41 tg Exp $
# $OpenBSD: Makefile,v 1.12 2002/11/27 06:49:42 pvalchev Exp $

COMMENT=		modules for parsing (and creating!) MIME entities
DISTNAME=		MIME-tools-5.427
PKGNAME=		p5-${DISTNAME}-${DASH_VER}
CATEGORIES=		mailnews perl5
HOMEPAGE=		http://www.zeegee.com/code/perl/MIME-tools/

# like Perl
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=MIME/}

B_R_DEPENDS+=		::mailnews/p5-Mail-Tools
B_R_DEPENDS+=		:p5-IO-stringy->=1.211:devel/p5-IO-stringy

CONFIGURE_STYLE= 	perl
PKG_ARCH=		*

.include <bsd.port.mk>
