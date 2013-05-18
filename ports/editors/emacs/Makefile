# $MirOS: ports/editors/emacs/Makefile,v 1.3 2006/02/09 11:11:30 tg Exp $
# $OpenBSD: Makefile,v 1.21 2004/02/04 07:39:18 sturm Exp $

COMMENT=			GNU editor: extensible, customizable, self documenting
COMMENT-el=			elisp sources for those who want to read/modify them
COMMENT-leim=			Library of Emacs Input Methods
VERSION=		21.3
DISTNAME=		emacs-${VERSION}
FULLPKGNAME-el=		emacs-el-${VERSION}-0
FULLPKGNAME-leim=	emacs-leim-${VERSION}-0
CATEGORIES=		editors
RESPONSIBLE=		Stephen Paskaluk <sap@66h.42h.de>
HOMEPAGE=		http://www.gnu.org/software/emacs/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNU:=emacs/}
DISTFILES=		emacs-${VERSION}.tar.gz leim-${VERSION}.tar.gz

MULTI_PACKAGES=		-el -leim
SUBPACKAGE?=

FLAVORS=		no_x11
FLAVOR?=

GCCARCH=		${AUTOCONF_FAKEOS}

USE_CXX=		Yes
CONFIGURE_STYLE=	gnu dest
CONFIGURE_ARGS=		${GCCARCH} --with-pop
.include <bsd.own.mk>
.if ${OBJECT_FMT:U} == "ELF"
LDFLAGS+=		-Z
.endif

SUBST_VARS=		GCCARCH VERSION

.if ${FLAVOR:L:Mno_x11}
CONFIGURE_ARGS+=	--with-x=no
.else
USE_X11=Yes
LIB_DEPENDS=		ungif.5::graphics/libungif \
			jpeg.62::graphics/jpeg \
			tiff.35::graphics/tiff
.endif
MODULES+=		graphics/png

.if defined(PACKAGING)
.  if !empty(SUBPACKAGE)
RUN_DEPENDS=		:emacs-${VERSION}*:editors/emacs21
LIB_DEPENDS=
.  endif
.  if ${SUBPACKAGE} == "-el"
PKG_ARCH=		*
.  endif
.endif

.include <bsd.port.mk>
