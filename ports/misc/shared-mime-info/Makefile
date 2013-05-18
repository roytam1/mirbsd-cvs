# $OpenBSD: Makefile,v 1.10 2004/12/22 11:50:29 alek Exp $

COMMENT=		"Shared mime database for desktops"

VERSION=		0.15
DISTNAME=		shared-mime-info-${VERSION}
CATEGORIES=		misc

HOMEPAGE=		http://www.freedesktop.org/software/shared-mime-info/
MASTER_SITES=		${HOMEPAGE}

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

BUILD_DEPENDS=		:p5-XML-Parser-*:textproc/p5-XML-Parser
LIB_DEPENDS=		glib-2.0.0.0,gmodule-2.0.0.0,gobject-2.0.0.0::devel/glib \
			xml2::textproc/libxml
MODULES+=		devel/pkgconfig

USE_CXX=		Yes
CONFIGURE_STYLE=	gnu

.include <bsd.port.mk>
