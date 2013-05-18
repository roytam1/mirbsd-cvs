# $OpenBSD: Makefile,v 1.3 2004/04/08 06:22:34 marcm Exp $

COMMENT=		"PDF viewer for GNOME"

DISTNAME=		gpdf-0.112
CATEGORIES=		textproc x11/gnome

HOMEPAGE=		http://www.inf.tu-dresden.de/~mk793652/gpdf/


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/gpdf/0.112/}
EXTRACT_SUFX=		.tar.bz2

MODULES=		devel/gettext devel/pkgconfig

BUILD_DEPENDS=		:p5-XML-Parser-*:textproc/p5-XML-Parser
LIB_DEPENDS=		gnomeui-2::x11/gnome/libgnomeui \
			gnomeprintui-2-2::x11/gnome/libgnomeprintui

USE_GMAKE=		Yes
CONFIGURE_STYLE=	gnu

.include <bsd.port.mk>
