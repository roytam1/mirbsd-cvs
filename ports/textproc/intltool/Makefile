# $MirOS: ports/textproc/intltool/Makefile,v 1.2 2005/12/29 15:42:19 bsiegert Exp $
# $OpenBSD: Makefile,v 1.4 2004/10/26 03:53:41 marcm Exp $

COMMENT=			Internationalization tool

DISTNAME=		intltool-0.34.1
CATEGORIES=		textproc

HOMEPAGE=		http://www.gnome.org

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/intltool/0.34/}
EXTRACT_SUFX=           .tar.bz2

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

BUILD_DEPENDS=		:p5-XML-Parser-*:textproc/p5-XML-Parser
RUN_DEPENDS=		${BUILD_DEPENDS}

USE_GMAKE=		Yes
CONFIGURE_STYLE= 	autogen
AUTOCONF_NEW=		Yes

.include <bsd.port.mk>
