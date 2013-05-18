# $MirOS: ports/textproc/p5-XML-Simple/Makefile,v 1.4 2007/06/21 17:43:08 bsiegert Exp $
# $OpenBSD: Makefile,v 1.12 2004/04/11 15:16:07 brad Exp $

COMMENT=	trivial perl API for reading/writing XML

DISTNAME=	XML-Simple-2.18
PKGNAME=	p5-${DISTNAME}-${DASH_VER}
CATEGORIES=	textproc perl5
MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=XML/}

HOMEPAGE=	http://www.web.co.nz/~grantm/cpan/

B_R_DEPENDS=  :p5-XML-Parser->=2:textproc/p5-XML-Parser \
		:p5-XML-SAX->=0.12:textproc/p5-XML-SAX

# GPL/Artistic
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE= perl

.include <bsd.port.mk>
