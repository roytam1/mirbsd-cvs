# $MirOS: ports/textproc/clo++/Makefile,v 1.1.7.1 2005/03/18 15:52:40 tg Exp $
# $OpenBSD: Makefile,v 1.6 2003/11/15 15:12:53 sturm Exp $

COMMENT=	"command line parser generator"

DISTNAME=	clo++-0.3.0
PKGNAME=	${DISTNAME}-1
CATEGORIES=	textproc
HOMEPAGE=	http://pmade.org/~pjones/software/clo++/

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${HOMEPAGE}/download/

LIB_DEPENDS=	xml2.2.6::textproc/libxml

USE_CXX=	Yes
CONFIGURE_STYLE=gnu

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/clo++
	${INSTALL_DATA} ${WRKSRC}/doc/handbook.html ${PREFIX}/share/doc/clo++

.include <bsd.port.mk>
