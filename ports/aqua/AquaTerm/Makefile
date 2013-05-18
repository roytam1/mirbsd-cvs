# $MirOS: ports/aqua/AquaTerm/Makefile,v 1.3 2006/12/20 15:30:33 tg Exp $

ONLY_FOR_PLATFORM=	Darwin:*:*
COMMENT=		Mac OS X graphics terminal

VERSION=		1.0.1
DISTNAME=		aquaterm_src.${VERSION}
PKGNAME=		AquaTerm-${VERSION}-${DASH_VER}
CATEGORIES=		aqua

HOMEPAGE=		http://aquaterm.sourceforge.net/
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=aquaterm/}

RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

# BSD-like
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

XCODEBUILD=		xcodebuild -target AquaTerm -buildstyle Deployment \
			USER_APPS_DIR=${LOCALBASE:Q}/Applications \
			LOCAL_LIBRARY_DIR=${LOCALBASE:Q}
FRAMEWORK=		Frameworks/AquaTerm.Framework/Versions/A

post-extract:
	mkdir ${WRKSRC:Q}
.for dir in aquaterm adapters
	mv ${WRKSRC:Q}/../${dir} ${WRKSRC:Q}
.endfor
	cd ${WRKSRC:Q}/aquaterm && cp AquaTerm.framework-Info.plist AquaTermFwk-Info.plist

do-build:
	cd ${WRKSRC:Q}/aquaterm && ${XCODEBUILD}

do-install:
	cd ${WRKSRC:Q}/aquaterm && ${XCODEBUILD} install DSTROOT=${DESTDIR:Q}
	${INSTALL_DATA_DIR} ${PREFIX}/include/aquaterm
.for h in AQTAdapter.h aquaterm.h
	cd ${PREFIX}/include/aquaterm && ln -s ../../${FRAMEWORK}/Headers/$h .
.endfor
	cd ${PREFIX}/lib && ln -s ../${FRAMEWORK}/AquaTerm libaquaterm.A.dylib \
		&& ln -s libaquaterm.A.dylib libaquaterm.dylib


.include <bsd.port.mk>
