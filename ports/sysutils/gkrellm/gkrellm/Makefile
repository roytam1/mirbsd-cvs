# $MirOS: ports/sysutils/gkrellm/gkrellm/Makefile,v 1.10 2008/10/16 19:44:13 tg Exp $
# $OpenBSD: Makefile,v 1.10 2004/05/18 14:49:56 naddy Exp $

BROKEN=			unfetchable distfile

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=		single process stack of system monitors for GTK+2 (server)
COMMENT-client=		single process stack of system monitors for GTK+2

VSN=		2.2.0
DISTNAME=	gkrellm-${VSN}
PKGNAME=	gkrellm-server-${VSN}-${DASH_VER}
PKGNAME-client=	gkrellm-${VSN}-${DASH_VER}
CATEGORIES=	sysutils sysutils/gkrellm

HOMEPAGE=	http://www.gkrellm.net/

# GPL
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

MASTER_SITES=	http://web.wt.net/~billw/gkrellm/
EXTRACT_SUFX=	.tar.bz2

PSEUDO_FLAVOURS=	no_client
FLAVOUR?=

MULTI_PACKAGES=
.if !${FLAVOUR:L:Mno_client}
MULTI_PACKAGES+=-client
.endif
SUBPACKAGE?=

MODULES+=	devel/pkgconfig
LIB_DEPENDS=	gthread-2.0.=0::devel/glib

NO_REGRESS=	Yes
USE_GMAKE=	Yes

ALL_TARGET=	openbsd
INSTALL_TARGET=	install_openbsd

.if ${MULTI_PACKAGES:M-client}
USE_X11=	Yes
.  if !defined(PACKAGING) || !empty(SUBPACKAGE)
LIB_DEPENDS+=	gdk-x11-2.0.=0,gdk_pixbuf-2.0.=0,gtk-x11-2.0.=0::x11/gtk+
.  endif
.else
WRKBUILD=	${WRKDIST}/server
.endif

pre-configure:
	@perl -pi -e "s|%%SYSCONFDIR%%|${SYSCONFDIR}|g" \
		${WRKSRC}/server/gkrellmd.h

.include <bsd.port.mk>
