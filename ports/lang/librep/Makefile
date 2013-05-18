# $OpenBSD: Makefile,v 1.14 2004/03/03 08:55:28 pvalchev Exp $

COMMENT=	"Emacs Lisp-like runtime library"

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

VERSION=	0.16.2
DISTNAME=	librep-${VERSION}
CATEGORIES=	lang

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=librep/}

HOMEPAGE=	http://librep.sourceforge.net/

MODULES=	devel/gettext
LIB_DEPENDS=	gdbm.2::databases/gdbm


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

SUBST_VARS=	OPSYS_VER VERSION

.if ${MACHINE_ARCH:Mpowerpc}
PATCH_LIST=	gcc-* patch-*
.endif

USE_GMAKE=	Yes
CONFIGURE_STYLE= gnu
CONFIGURE_ARGS+= ${CONFIGURE_SHARED} --enable-static
CONFIGURE_ARGS+= --without-gmp

NO_REGRESS=	Yes

.include <bsd.port.mk>
