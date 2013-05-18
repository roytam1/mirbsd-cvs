# $MirOS: ports/textproc/p5-XML-Sablotron/Makefile,v 1.3 2005/07/07 21:27:17 bsiegert Exp $
# $OpenBSD: Makefile,v 1.13 2004/02/29 01:03:32 avsm Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=			perl interface to the Sablotron XSLT engine
DISTNAME=	XML-Sablotron-1.0
PKGNAME=	p5-${DISTNAME}-0
CATEGORIES=	textproc perl5
MASTER_SITES=	http://download-1.gingerall.cz/download/sablot/
HOMEPAGE=	http://www.gingerall.cz/

LIB_DEPENDS=	sablot.100::textproc/sablotron

# GPL/Mozilla
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE= perl
CONFIGURE_ARGS=  EXPATLIBPATH="${LOCALBASE}/lib" EXPATINCPATH="${LOCALBASE}/include" SABLOTLIBPATH="${LOCALBASE}/lib" SABLOTINCPATH="${LOCALBASE}/include"

.include <bsd.port.mk>
