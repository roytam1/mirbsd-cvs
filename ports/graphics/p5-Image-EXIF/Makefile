# $OpenBSD: Makefile,v 1.2 2004/05/18 20:52:48 naddy Exp $

COMMENT=			interface to read EXIF tags in JPEG images

DISTNAME=	Image-EXIF-0.98.6
PKGNAME=	p5-${DISTNAME}-0
CATEGORIES=	graphics perl5 

HOMEPAGE=       http://search.cpan.org/dist/Image-EXIF/


# BSD
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=Image/}

EXTRACT_SUFX=	.tgz

LIB_DEPENDS=	exif.8::graphics/libexif

CONFIGURE_STYLE=perl

post-patch:
	@perl -i -p -e 's#/usr/local#${LOCALBASE}#' ${WRKDIST}/Makefile.PL

.include <bsd.port.mk>
