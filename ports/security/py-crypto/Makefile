# $MirOS: ports/security/py-crypto/Makefile,v 1.5 2008/08/27 09:52:33 tg Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2004/02/03 07:19:06 ish Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=		cryptographic tools for Python
MODPY_EGG_VERSION=	2.0.1
DISTNAME=		pycrypto-${MODPY_EGG_VERSION}
PKGNAME=		py-crypto-${MODPY_EGG_VERSION}-${DASH_VER}
CATEGORIES=    		security devel
HOMEPAGE=		http://www.dlitz.net/software/pycrypto/

# Public domain.
PERMIT_PACKAGE_CDROM=	"patented algorithm"
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	"patented algorithm"
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://www.amk.ca/files/python/crypto/

MODULES+=		lang/python

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/py-crypto
	${INSTALL_DATA} ${WRKSRC}/README ${PREFIX}/share/doc/py-crypto/

do-regress: fake
	cd ${WRKSRC} && ${MAKE_ENV} \
	    PYTHONPATH=${WRKINST:Q}${MODPY_SITEPKG:Q} ${MODPY_BIN} test.py

.include <bsd.port.mk>
