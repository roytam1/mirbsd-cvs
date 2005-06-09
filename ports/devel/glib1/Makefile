# $MirOS: ports/devel/glib1/Makefile,v 1.2 2005/06/09 19:56:31 tg Exp $
# $OpenBSD: Makefile,v 1.52 2003/05/27 23:00:50 miod Exp $

COMMENT=	"useful routines for C programming"
DISTNAME=	glib-1.2.10
CATEGORIES=	devel
MASTER_SITES=	${MASTER_SITE_GNOME:=sources/glib/1.2/}
HOMEPAGE=	http://www.gtk.org/

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

SEPARATE_BUILD=		concurrent
CONFIGURE_STYLE=	autoconf
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} --enable-static

NO_REGRESS=	Yes

post-extract:
	@rm -f ${WRKSRC}/docs/glib.info*

.include <bsd.port.mk>
