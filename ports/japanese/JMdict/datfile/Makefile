# $MirOS: ports/japanese/jmdict/datfile/Makefile,v 1.3 2007/04/12 20:20:41 bsiegert Exp $

.include <mirports.sys.mk>

COMMENT=		sqlite2 format JMdict database
CATEGORIES=		japanese
VSN!=			cd ${PORTSDIR}/japanese/JMdict && ${MAKE} show=VSN
PKGNAME=		jmdict-datfile-${VSN}-${DASH_VER}
HOMEPAGE=		http://mandrill.fuxx0r.net/jmdict.php

# Creative Commons by-sa 2.5
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

BUILD_DEPENDS+=		:JMdict-${VSN}:japanese/JMdict
BUILD_DEPENDS+=		::japanese/jmdict/jmdict_import

WRKDIST=		${WRKDIR}
NO_DISTFILES=		Yes
NO_CHECKSUM=		Yes
NO_REGRESS=		Yes
USE_CXX=		Yes # depends on jmdict_import, which uses CXX
PKG_ARCH=		*

do-build:
	@echo WARNING: This is a very time-consuming build
	@echo process, which can take over an hour at 1 GHz!
	cd ${WRKBUILD} && \
	    ln -s ${LOCALBASE}/share/JMdict/JMdict && \
	    ${LOCALBASE}/bin/jmdict_import

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/{,doc/}jmdict-datfile
	${INSTALL_DATA} ${WRKBUILD}/dictionary ${PREFIX}/share/jmdict-datfile/
	${INSTALL_DATA} ${LOCALBASE}/share/doc/JMdict/licence.html \
	    ${PREFIX}/share/doc/jmdict-datfile/

.include <bsd.port.mk>
