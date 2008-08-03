# $MirOS$

COMMENT=		net neutrality testing tool
DISTNAME=		switzerland-0.0.5
CATEGORIES=		security sysutils
HOMEPAGE=		http://sourceforge.net/projects/switzerland/
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=switzerland/}
EXTRACT_SUFX=		.tgz

# GNU GPLv3
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MODULES+=		lang/python
MODPY_VERSION=		2.5
MODPY_MINPKG=		2.4
NO_REGRESS=		Yes

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/switzerland
	cd ${WRKSRC} && ${INSTALL_DATA} doc/design.pdf BUGS.txt CREDITS \
	    README.txt ${PREFIX}/share/doc/switzerland/

.include <bsd.port.mk>
