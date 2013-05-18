# $OpenBSD: Makefile,v 1.12 2002/09/17 15:17:41 wilfried Exp $

BROKEN=			depends on fltk, which is broken

COMMENT=			Text Editor for FLTK

VSN=			0.4.5
DISTNAME=		fl_editor-${VSN}
PKGNAME=		fleditor-${VSN}-${DASH_VER}
CATEGORIES=		x11

HOMEPAGE=		http://www.robertk.com/source/


# LPGL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://www.robertk.com/source/fl_editor/
EXTRACT_SUFX=		.tgz

LIB_DEPENDS=		fltk.1::x11/fltk

USE_X11=		Yes
REGRESS_TARGET=		test
CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--with-fltk=${LOCALBASE}

WRKDIST=		${WRKDIR}/fl_editor

# This regression test wants an X11 display
REGRESS_FLAGS+=         DISPLAY=${DISPLAY} XAUTHORITY=${XAUTHORITY}
REGRESS_IS_INTERACTIVE= Yes

post-patch:
	@rmdir ${WRKSRC}/obj

pre-regress:
.for t in DISPLAY XAUTHORITY
.if !defined($t)
	@echo "$t needs to be set to run regress"; exit 1
.endif
.endfor

do-install:
	@${install_shared_frag}
	${INSTALL_DATA} ${WRKBUILD}/libfleditor.a ${PREFIX}/lib
	${INSTALL_DATA_DIR} ${PREFIX}/include/FL
	${INSTALL_DATA} ${WRKSRC}/FL/*.[Hh] ${PREFIX}/include/FL

.include <bsd.port.mk>

.if defined(NO_SHARED_LIBS) && ${NO_SHARED_LIBS:L} == "yes"
install_shared_frag= :
.else
install_shared_frag=\
	${INSTALL_DATA} ${WRKBUILD}/libfleditor.so* ${PREFIX}/lib
.endif
