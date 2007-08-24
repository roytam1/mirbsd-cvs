# $MirOS$
# $OpenBSD: Makefile,v 1.2 2006/06/03 09:45:27 alek Exp $

COMMENT=	"application for managing passwords"
DISTNAME=	kedpm-0.4.0
DASH_VER=	1
CATEGORIES=	security
HOMEPAGE=	http://kedpm.sourceforge.net/ 

# GPL 
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=kedpm/}

RUN_DEPENDS=	${MODPY_EXPAT_DEPENDS} \
		:py-crypto-*:security/py-crypto
#		:py-gtk2-*:x11/py-gtk2 \
REGRESS_DEPENDS=${RUN_DEPENDS}

MODULES=	lang/python

do-regress:
	cd ${WRKSRC} && ${MODPY_BIN} ./run_tests

.include <bsd.port.mk>
