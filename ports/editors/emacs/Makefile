# $MirOS: ports/editors/emacs/Makefile,v 1.9 2008/11/08 23:03:39 tg Exp $
# $OpenBSD: Makefile,v 1.21 2004/02/04 07:39:18 sturm Exp $

COMMENT=		GNU editor: extensible, customizable, self documenting
COMMENT-el=		elisp sources for those who want to read/modify them
COMMENT-leim=		Library of Emacs Input Methods
VERSION=		21.3
DASH_VER=		1
DISTNAME=		emacs-${VERSION}
FULLPKGNAME-el=		emacs-el-${VERSION}-${DASH_VER}
FULLPKGNAME-leim=	emacs-leim-${VERSION}-${DASH_VER}
CATEGORIES=		editors
RESPONSIBLE=		Stephen Paskaluk <sap@mirbsd.org>
HOMEPAGE=		http://www.gnu.org/software/emacs/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

.include <mirports.sys.mk>

#MASTER_SITES=		${MASTER_SITE_GNU:=emacs/}
MASTER_SITES=		ftp://ftp.gnu.org/old-gnu/emacs/
DISTFILES=		emacs-${VERSION}.tar.gz leim-${VERSION}.tar.gz

MULTI_PACKAGES=		-el -leim
SUBPACKAGE?=

FLAVOURS=		no_x11
FLAVOUR?=

.if ${OSname} == "MidnightBSD"
GCCARCH=		${ARCH}-ecce-freebsd6
.elif ${OSname} == "MirBSD"
GCCARCH=		${ARCH}-ecce-openbsd3.5
.else
GCCARCH=		${OStriplet}
.endif

USE_CXX=		Yes
CONFIGURE_STYLE=	gnu dest
CONFIGURE_ARGS=		${GCCARCH} \
			--with-pop
.if ${OBJECT_FMT:U} == "ELF"
LDFLAGS+=		-Z
.endif

SUBST_VARS=		GCCARCH VERSION

.if ${FLAVOUR:L:Mno_x11}
CONFIGURE_ARGS+=	--with-x=no
.else
USE_X11=		Yes
LIB_DEPENDS+=		ungif.5::graphics/libungif \
			jpeg.62::graphics/jpeg \
			tiff.35::graphics/tiff
.endif
MODULES+=		graphics/png

.if defined(PACKAGING)
.  if !empty(SUBPACKAGE)
RUN_DEPENDS=		:emacs-${VERSION}*:editors/emacs
LIB_DEPENDS=
.  endif
.  if ${SUBPACKAGE} == "-el"
PKG_ARCH=		*
.  endif
.endif

.include <bsd.port.mk>
