# $OpenBSD: Makefile,v 1.6 2002/10/27 17:21:39 naddy Exp $

BROKEN=			unfetchable distfile

COMMENT=		simple interactive POP3 client

DISTNAME=	prepop-0.1b7
CATEGORIES=	mail

HOMEPAGE=	http://www.rundegren.com/software/prepop/


# GPL
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

MASTER_SITES=	${HOMEPAGE}

MAKE_FLAGS= \
	CC=${_PASS_CXX:T:Q} \
	CFLAGS='${CFLAGS} -c -DVERSION="$${VERSION}" -DDATE="$${DATE}"' \
	LDFLAGS='-lreadline -ltermcap'

USE_CXX=	Yes
ALL_TARGET=	compile link

NO_REGRESS=	Yes

do-install:
	${INSTALL_PROGRAM} ${WRKBUILD}/prepop ${PREFIX}/bin
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/prepop
	${INSTALL_DATA} ${WRKSRC}/MANUAL ${PREFIX}/share/doc/prepop

.include <bsd.port.mk>
