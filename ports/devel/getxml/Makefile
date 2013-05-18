# $MirOS: ports/devel/getxml/Makefile,v 1.3 2006/09/14 00:08:12 tg Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2002/12/04 14:29:58 naddy Exp $

COMMENT=		XML internationalization tool

DISTNAME=		getxml-1.0.4
CATEGORIES=		devel

HOMEPAGE=		http://www.gnu.org/software/toutdoux/en/index.html

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNU:=toutdoux/}

LIB_DEPENDS=		xml::textproc/libxml1 \
			glib::devel/glib1

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		no

.include <bsd.port.mk>
