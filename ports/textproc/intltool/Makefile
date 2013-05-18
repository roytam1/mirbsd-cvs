# $MirOS: ports/textproc/intltool/Makefile,v 1.3 2006/09/14 00:14:05 tg Exp $
# $OpenBSD: Makefile,v 1.4 2004/10/26 03:53:41 marcm Exp $

COMMENT=		internationalization tool
VERSION=		0.35.5
DISTNAME=		intltool-${VERSION}
CATEGORIES=		textproc x11/gnome

HOMEPAGE=		http://www.gnome.org

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/intltool/${VERSION:R}/}
EXTRACT_SUFX=           .tar.bz2

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

B_R_DEPENDS=		:p5-XML-Parser-*:textproc/p5-XML-Parser

USE_GMAKE=		Yes
CONFIGURE_STYLE= 	autoconf no-autoheader
AUTOCONF_NEW=		Yes

.include <bsd.port.mk>
