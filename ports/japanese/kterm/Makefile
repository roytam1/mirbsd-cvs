# $MirOS: ports/japanese/kterm/Makefile,v 1.4 2007/02/11 00:33:02 tg Exp $
# $OpenBSD: Makefile,v 1.19 2002/11/21 05:48:41 pvalchev Exp $

COMMENT=		Japanese-capable xterm
VERSION=		6.2.0
DASH_VER=		1
DISTNAME=		kterm-${VERSION}
PKGNAME=		ja-${DISTNAME}-${DASH_VER}
CATEGORIES=		japanese x11

# X11
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_XCONTRIB:=applications/}
MASTER_SITES0=		ftp://ftp.kame.net/pub/kame/misc/
PATCHFILES=		kterm-620-0213-20010706.diff.gz:0
PATCH_DIST_STRIP=	-p1

USE_X11=		Yes
CONFIGURE_STYLE=	imake
NO_REGRESS=		Yes

FLAVOURS=		xaw3d tek nextaw
FLAVOUR?=

.if ${FLAVOUR:L:Mxaw3d}
LIB_DEPENDS=		Xaw3d.6.1::x11/Xaw3d
MAKE_ENV=		EXTRA_DEFINES=-DKTERM_XAW3D
MAKE_FLAGS+=		XAWLIB=-lXaw3d
.endif

.if ${FLAVOUR:L:Mnextaw}
.  if ${FLAVOUR:L:Mxaw3d}
ERRORS+=		"cannot specify both neXtaw and Xaw3d"
.  else
LIB_DEPENDS=		neXtaw.15.1::x11/neXtaw
MAKE_ENV=		EXTRA_DEFINES=-DKTERM_XAW3D
.  endif
MAKE_FLAGS+=		XAWLIB=-lneXtaw
.endif

.if ${FLAVOUR:L:Mtek}
pre-configure:
	print '%g/define KTERM_NOTEK/s//undef KTERM_NOTEK/g\nwq' | \
	    ed -s ${WRKSRC}/kterm.h
.endif

.include <bsd.port.mk>
