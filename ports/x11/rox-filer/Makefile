# $MirOS: ports/x11/rox-filer/Makefile,v 1.10 2010/08/14 20:19:44 tg Exp $
# $OpenBSD: Makefile,v 1.20 2004/04/02 19:07:05 sturm Exp $

COMMENT=		gtk file manager with desktop features
VERSION=		2.1.1
DASH_VER=		2
DISTNAME=		rox-${VERSION}
PKGNAME=		rox-filer-${VERSION}-${DASH_VER}
CATEGORIES=		x11
HOMEPAGE=		http://rox.sourceforge.net/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=rox/}
DISTFILES=		${DISTNAME}.tgz

USE_CXX=		Yes # depends on shared-mime-info, which uses CXX
USE_X11=		Yes
MODULES+=		devel/pkgconfig
LIB_DEPENDS+=		gtk-x11-2.0.0.9,gdk_pixbuf-2.0.0.9,gdk-x11-2.0.0.9::x11/gtk+ \
			xml2::textproc/libxml
RUN_DEPENDS+=		::misc/shared-mime-info
BUILD_DEPENDS+=		::devel/autoconf/2.13

FILE_TO_PATCH=  ${WRKSRC}/ROX-Filer/src/choices.c

SUBST_VARS+=		OSNAME
NO_REGRESS=		Yes

post-patch:
	printf ',g!%s!s!!%s!g\nwq\n' /usr/local/share/Choices \
	    ${PREFIX:Q}/share/rox/Choices | \
	    ed -s ${WRKSRC:Q}/ROX-Filer/src/choices.c
	cd ${WRKSRC:Q}/ROX-Filer/src && autoconf-2.13

do-build:
	@cd ${WRKSRC} && ${SETENV} CC=${_PASS_CC:T:Q} CFLAGS=${CFLAGS:Q} \
	    ${CONFIGURE_ENV} ROX-Filer/AppRun --compile

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/rox
	${INSTALL_MAN} ${WRKSRC}/rox.1 ${PREFIX}/man/man1/
	${INSTALL_MAN} ${WRKSRC}/rox.1 ${PREFIX}/man/man1/ROX-Filer.1
	${INSTALL_DATA_DIR} ${PREFIX}/share/rox/Choices/MIME-types
	${INSTALL_SCRIPT} ${WRKSRC}/Choices/MIME-types/* ${PREFIX}/share/rox/Choices/MIME-types
	@(cd ${WRKSRC}/ROX-Filer/src && make clean)
	@cp -R ${WRKSRC}/ROX-Filer ${PREFIX}/rox
	@rm -f ${PREFIX:Q}/rox/src/*.orig
	printf '#!/bin/sh\nexport XDG_DATA_DIRS=%s/share:/usr/share\nexec %s/rox/ROX-Filer/AppRun "$$@"\n' \
	    ${TRUEPREFIX:Q} ${TRUEPREFIX:Q} >${PREFIX:Q}/bin/rox
	chmod ${BINMODE} ${PREFIX:Q}/bin/rox

.include <bsd.port.mk>
