# $MirOS: ports/textproc/p5-XML-Parser/Makefile,v 1.5 2008/04/07 18:17:06 tg Exp $
# $OpenBSD: Makefile,v 1.9 2004/01/17 15:58:10 naddy Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=		perl module for parsing XML documents
DISTNAME=		XML-Parser-2.31
PKGNAME=		p5-${DISTNAME}-${DASH_VER}
CATEGORIES=		textproc perl5
HOMEPAGE=		http://wwwx.netheaven.com/~coopercc/xmlparser/
MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=XML/} \
			${HOMEPAGE}

# GPL/Artistic
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES+=		textproc/expat

CONFIGURE_STYLE=	perl
CONFIGURE_ARGS+=	EXPATLIBPATH=${EXPAT_PREFIX}/lib \
			EXPATINCPATH=${EXPAT_PREFIX}/include

.include <bsd.port.mk>
