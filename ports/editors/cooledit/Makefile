# $OpenBSD: Makefile,v 1.14 2003/08/01 19:13:25 espie Exp $

COMMENT=			easy to use, graphical editor

CATEGORIES=	editors
MASTER_SITES=	${HOMEPAGE}
HOMEPAGE= 	http://cooledit.sourceforge.net/ 
DISTNAME=	cooledit-3.17.7


FLAVOURS=	python
FLAVOUR?=

PYTHON_VER=	2.3

.if ${FLAVOUR:L:Mpython}
LIB_DEPENDS+=	python${PYTHON_VER}.0.0:python-${PYTHON_VER}*:lang/python/${PYTHON_VER}
CFLAGS+=	-pthread
CONFIGURE_ENV+=	PYTHON_VER=${PYTHON_VER}
.else
CONFIGURE_ENV+=	NOPYTHON=Yes
.endif

USE_X11=		Yes

CONFIGURE_STYLE=	gnu
CONFIGURE_ENV+=		XTERM_CMD=xterm
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--enable-static --disable-mail-author

PERMIT_PACKAGE_FTP=Yes
PERMIT_DISTFILES_FTP=Yes
PERMIT_PACKAGE_CDROM=Yes
PERMIT_DISTFILES_CDROM=Yes

.include <bsd.port.mk>
