# $OpenBSD: Makefile,v 1.5 2004/05/18 23:26:33 dons Exp $

BROKEN=			unfetchable distfile

COMMENT=		advanced revision control system written in Haskell

VSN=		0.9.20
DISTNAME=	darcs-${VSN}
CATEGORIES=	devel

HOMEPAGE=	http://www.abridgegame.org/darcs/
MASTER_SITES=	${HOMEPAGE}

MODULES=	lang/ghc
LIB_DEPENDS=	curl.2::net/curl

CONFIGURE_STYLE= gnu
CONFIGURE_ARGS=	--datadir=${PREFIX}/share --libexecdir=${PREFIX}/libexec

USE_GMAKE=	Yes
USE_CXX=	Yes
MAKE_FILE=	GNUmakefile
INSTALL_TARGET= install installserver

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

.include <bsd.port.mk>
