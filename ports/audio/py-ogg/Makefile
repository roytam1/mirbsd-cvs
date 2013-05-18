# $OpenBSD: Makefile,v 1.3 2004/01/30 08:39:48 xsa Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}
COMMENT=			Python wrapper for the Ogg libraries
DISTNAME=	pyogg-1.3
PKGNAME=	${DISTNAME:S/py/py-/}-0
CATEGORIES=	audio
HOMEPAGE=	http://www.andrewchatham.com/pyogg/

# LGPL 
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${HOMEPAGE}download/

MODULES=	lang/python

LIB_DEPENDS=	ogg::audio/libogg

do-configure:
	@cd ${WRKSRC} && ${MODPY_BIN} ./config_unix.py --prefix ${PREFIX} 

do-regress: fake
	@cd ${WRKSRC}/test && ${MAKE_ENV} \
		PYTHONPATH=${WRKINST}${MODPY_SITEPKG} ${MODPY_BIN} ./testogg.py

.include <bsd.port.mk>
