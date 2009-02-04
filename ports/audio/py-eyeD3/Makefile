# $MirOS$

COMMENT=		module and program for processing ID3 tags
MODPY_EGG_VERSION=	0.6.17
DISTNAME=		eyeD3-${MODPY_EGG_VERSION}
CATEGORIES=		audio
HOMEPAGE=		http://eyed3.nicfit.net/

# GNU GPLv2+
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		${HOMEPAGE}releases/
MODULES+=		lang/python
MODPY_VERSION=		2.5
MODPY_USE_DISTUTILS=	No
USE_GMAKE=		Yes
CONFIGURE_STYLE=	gnu
CONFIGURE_ENV+= 	PYTHON=${MODPY_BIN:Q}
NO_REGRESS=		Yes

pre-configure:
	print '1c\n#!'${MODPY_BIN:Q}'\n.\nwq' | ed -s ${WRKSRC}/bin/eyeD3

post-install:
	gzip -d ${PREFIX}/man/*/*.gz
	cd ${WRKSRC} && ${INSTALL_DATA} NEWS README.html TODO \
	    ${PREFIX}/share/doc/eyeD3-${MODPY_EGG_VERSION}/
	rm -f ${PREFIX}/share/doc/eyeD3-${MODPY_EGG_VERSION}/COPYING.gz

.include <bsd.port.mk>
