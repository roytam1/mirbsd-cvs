# $MirOS$

COMMENT=		"Standard Fonts for Ghostscript"
VERSION=		6.0
DISTNAME=		gnu-gs-fonts-std-${VERSION}
PKGNAME=		gs-fonts-std-${VERSION}
CATEGORIES=		print
HOMEPAGE=		http://www.cs.wisc.edu/~ghost/
RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

# GNU GPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNU:=ghostscript/}

NO_REGRESS=		Yes
NO_BUILD=		Yes

do-install:
	mkdir -p ${PREFIX}/share/ghostscript
	mv ${WRKDIR}/fonts ${PREFIX}/share/ghostscript

.include <bsd.port.mk>
