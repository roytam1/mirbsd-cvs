# $MirOS: ports/devel/glib1/Makefile,v 1.8 2006/09/14 00:08:12 tg Exp $
# $OpenBSD: Makefile,v 1.52 2003/05/27 23:00:50 miod Exp $

COMMENT=		useful routines for C programming
DISTNAME=		glib-1.2.10
PKGNAME=		${DISTNAME}-3
CATEGORIES=		devel
MASTER_SITES=		${MASTER_SITE_GNOME:=sources/glib/1.2/}
HOMEPAGE=		http://www.gtk.org/

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	autoconf
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--enable-static \
			--disable-libtool-lock

NO_REGRESS=		Yes

post-extract:
	@rm -f ${WRKSRC}/docs/glib.info*

.include <bsd.port.mk>
