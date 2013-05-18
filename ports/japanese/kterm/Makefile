# $MirOS: ports/japanese/kterm/Makefile,v 1.2 2005/07/07 21:22:14 bsiegert Exp $
# $OpenBSD: Makefile,v 1.19 2002/11/21 05:48:41 pvalchev Exp $

COMMENT=			Japanese-capable xterm
VERSION=	6.2.0
DISTNAME=	kterm-${VERSION}
PKGNAME=	ja-kterm-${VERSION}-1
CATEGORIES=	japanese x11
MASTER_SITES=	${MASTER_SITE_XCONTRIB:=applications/}

# License: X
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES0=	ftp://ftp.kame.net/pub/kame/misc/
PATCHFILES=	kterm-620-0213-20010706.diff.gz:0
PATCH_DIST_STRIP=	-p1

CONFIGURE_STYLE=imake

FLAVORS=	xaw3d tek nextaw
FLAVOR?=

.if ${FLAVOR:L:Mxaw3d}
LIB_DEPENDS=	Xaw3d.6.1::x11/Xaw3d
MAKE_ENV=	EXTRA_DEFINES=-DKTERM_XAW3D
MAKE_FLAGS+=	XAWLIB=-lXaw3d
.endif

.if ${FLAVOR:L:Mnextaw}
.  if ${FLAVOR:L:Mxaw3d}
ERRORS+=	"cannot specify both neXtaw and Xaw3d"
.  else
LIB_DEPENDS=	neXtaw.15.1::x11/neXtaw
MAKE_ENV=	EXTRA_DEFINES=-DKTERM_XAW3D
.  endif
MAKE_FLAGS+=	XAWLIB=-lneXtaw
.endif

.if ${FLAVOR:L:Mtek}
pre-configure:
	perl -pi.bak -e 's/define KTERM_NOTEK/undef KTERM_NOTEK/;' \
	  ${WRKSRC}/kterm.h
.endif

NO_REGRESS=	Yes

.include <bsd.port.mk>
