# $MirOS: ports/sysutils/dvd+rw-tools/Makefile,v 1.2 2005/10/18 14:15:38 bsiegert Exp $
# $OpenBSD: Makefile,v 1.2 2005/01/27 10:57:20 espie Exp $

NOT_FOR_PLATFORM=	Darwin:*:*

COMMENT=			mastering tools for DVD+RW/+R/-R/-RW

DISTNAME=		dvd+rw-tools-5.21.4.10.8
PKGNAME=		${DISTNAME}-1
CATEGORIES=		sysutils
HOMEPAGE=		http://fy.chalmers.se/~appro/linux/DVD+RW/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${HOMEPAGE}tools/

RUN_DEPENDS=		:cdrtools->=1.10:sysutils/cdrtools

USE_CXX=		Yes
NO_REGRESS=		Yes

PROGS=			growisofs dvd+rw-format dvd+rw-booktype dvd+rw-mediainfo

post-patch:
	cp ${FILESDIR}/Makefile ${WRKSRC}
.for dir in ${PROGS}
	mkdir ${WRKSRC}/${dir}
	cp ${FILESDIR}/Makefile.${dir} ${WRKSRC}/${dir}/Makefile
.endfor


post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/dvd+rw-tools
	${INSTALL_DATA} ${WRKSRC}/index.html ${PREFIX}/share/doc/dvd+rw-tools

.include <bsd.port.mk>
