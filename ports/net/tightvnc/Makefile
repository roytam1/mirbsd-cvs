# $MirOS$
# $OpenBSD: Makefile,v 1.12 2004/04/21 12:56:30 wilfried Exp $

# Xvnc is broken
VIEWER_ONLY=		#defined

COMMENT=		cross-platform remote desktop access
COMMENT-viewer=		client for cross-platform remote desktop access

VERSION=		tightvnc-1.2.7
PKGNAME=        	${VERSION}-${DASH_VER}
DISTNAME=       	${VERSION}_unixsrc
CATEGORIES=		net
MASTER_SITES=   	${MASTER_SITE_SOURCEFORGE:=vnc-tight/}
HOMEPAGE=		http://www.tightvnc.org/
LIB_DEPENDS=		jpeg.62.::graphics/jpeg

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

WRKDIST=		${WRKDIR}/vnc_unixsrc
MULTI_PACKAGES=		-viewer
SUBPACKAGE?=
CONFIGURE_STYLE=	imake
USE_X11=		Yes
ALL_TARGET=    		World
NO_REGRESS=		Yes

.ifdef VIEWER_ONLY
COMMENT=		${COMMENT-viewer}
DESCR=			${PKGDIR}/DESCR-viewer
PLIST=			${PKGDIR}/PLIST-viewer
FULLPKGNAME=		${PKGNAME}-viewer
MULTI_PACKAGES:=
ALL_TARGET=		all
.else
DOCUMENTATION=		vncserver.man vncpasswd/vncpasswd.man \
			vncconnect/vncconnect.man \
			Xvnc/programs/Xserver/Xvnc.man
.endif
DOCUMENTATION+=		vncviewer/vncviewer.man

.if ${MACHINE_ARCH} == "sparc64"
PATCH_LIST=		patch-* gcc-*
.endif

# We have to frob a few things, and we want our own permissions, so it's easier
# to do the install ourselves.
post-install:
	${INSTALL_PROGRAM} ${WRKSRC}/vncviewer/vncviewer ${PREFIX}/bin/vncviewer
.ifndef VIEWER_ONLY
	${INSTALL_PROGRAM} ${WRKSRC}/Xvnc/programs/Xserver/Xvnc ${PREFIX}/bin/Xvnc
	${INSTALL_PROGRAM} ${WRKSRC}/vncpasswd/vncpasswd ${PREFIX}/bin/vncpasswd
	${INSTALL_PROGRAM} ${WRKSRC}/vncconnect/vncconnect ${PREFIX}/bin/vncconnect
	sed  -e s%/usr/local/vnc/classes%${TRUEPREFIX}/share/vnc/classes% \
		< ${WRKSRC}/vncserver \
		> ${WRKSRC}/vncserver.local
	${INSTALL_SCRIPT} ${WRKSRC}/vncserver.local ${PREFIX}/bin/vncserver
# Go install Java classes
	${INSTALL_DATA_DIR} ${PREFIX}/share/vnc
	cp -R ${WRKSRC}/classes ${PREFIX}/share/vnc/
.endif
.for i in ${DOCUMENTATION}
	${INSTALL_MAN} ${WRKSRC}/$i ${PREFIX}/man/man1/${i:T:R}.1
.endfor

.include <bsd.port.mk>
