# $MirOS$

COMMENT=		convert TrueType to EOT (Web Embedded) fonts
DISTNAME=		ttf2eot-0.0.2-2
CATEGORIES=		print www
HOMEPAGE=		http://code.google.com/p/ttf2eot/

# GNU GPLv2
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		http://ttf2eot.googlecode.com/files/
USE_CXX=		Yes

MAKE_FILE=		${.SYSMK}/bsd.prog.mk
EXTRA_XAKE_FLAGS+=	PROG=ttf2eot \
			NOMAN=Yes \
			SRCS=OpenTypeUtilities.cpp\ ttf2eot.cpp

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/ttf2eot
	${INSTALL_DATA} ${WRKSRC}/README ${PREFIX}/share/doc/ttf2eot/

.include <bsd.port.mk>
