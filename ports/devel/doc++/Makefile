# $OpenBSD: Makefile,v 1.12 2003/07/14 07:16:32 kevlo Exp $

COMMENT=	"documentation system for C, C++, IDL and Java"

DISTNAME=	doc++-3.4.10
CATEGORIES=	devel

HOMEPAGE=	http://docpp.sourceforge.net/


PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=docpp/}

RUN_DEPENDS=	:ghostscript-*:print/ghostscript/gnu \
		:teTeX_base-*:print/teTeX/base

USE_GMAKE=	Yes
USE_CXX=	Yes
CONFIGURE_STYLE= gnu

MODULES=	devel/gettext

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/doc++
	${INSTALL_DATA} ${WRKSRC}/doc/manual/html/* ${PREFIX}/share/doc/doc++

.include <bsd.port.mk>
