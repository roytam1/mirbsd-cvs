# $MirOS: ports/sysutils/gkrellm/gkrellm/Makefile,v 1.6 2006/02/09 11:15:26 tg Exp $
# $OpenBSD: Makefile,v 1.10 2004/05/18 14:49:56 naddy Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=			single process stack of system monitors for GTK+2 (server)
COMMENT-client=			single process stack of system monitors for GTK+2

V=		2.2.0
DISTNAME=	gkrellm-${V}
PKGNAME=	gkrellm-server-${V}-0
PKGNAME-client=	gkrellm-${V}-0
CATEGORIES=	sysutils sysutils/gkrellm

HOMEPAGE=	http://www.gkrellm.net/

# GPL
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

MASTER_SITES=	http://web.wt.net/~billw/gkrellm/
EXTRACT_SUFX=	.tar.bz2

PSEUDO_FLAVORS=	no_client
FLAVOR?=

MULTI_PACKAGES=
.if !${FLAVOR:L:Mno_client}
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
