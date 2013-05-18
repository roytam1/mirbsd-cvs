# $MirOS: ports/converters/p5-Text-Iconv/Makefile,v 1.4 2006/02/02 21:09:39 tg Exp $
# $OpenBSD: Makefile,v 1.6 2004/01/17 15:58:07 naddy Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=			interface to iconv() codeset conversion function
DISTNAME=	Text-Iconv-1.4
PKGNAME=	p5-${DISTNAME}-0
CATEGORIES=	converters perl5

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=   ${MASTER_SITE_PERL_CPAN:=Text/}

MODULES=	converters/libiconv

CONFIGURE_STYLE= perl
CONFIGURE_ARGS+=LIBS='-L${ICONV_PREFIX}/lib' INC='-I${ICONV_PREFIX}/include'

.include <bsd.port.mk>
