# $MirOS$

COMMENT=		Python command line parser
VERSION=		1.1
DISTNAME=		argparse-${VERSION}
EXTRACT_SUFX=		.zip
CATEGORIES=     	devel

# Apache License 2.0
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=	Yes

HOMEPAGE=		http://code.google.com/p/argparse/
MASTER_SITES=		${MASTER_SITE_PYPI:=a/argparse/}

MODULES=		lang/python
MODPY_EGG_VERSION=	1.1

NO_REGRESS=		Yes

post-install:
	${INSTALL_DATA_DIR} ${PREFIX:Q}/share/doc/py-argparse
	rm -rf ${WRKSRC:Q}/doc/source
	cp -r ${WRKSRC:Q}/doc/* ${PREFIX:Q}/share/doc/py-argparse/

.include <bsd.port.mk>
