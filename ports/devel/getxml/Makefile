# $MirOS: ports/devel/getxml/Makefile,v 1.2 2005/03/30 16:51:07 bsiegert Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2002/12/04 14:29:58 naddy Exp $

COMMENT=			XML internationalization tool

DISTNAME=	getxml-1.0.4
CATEGORIES=	devel

HOMEPAGE=	http://www.gnu.org/software/toutdoux/en/index.html

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_GNU:=toutdoux/}

LIB_DEPENDS=	xml.9::textproc/libxml1 \
		glib.1::devel/glib1

CONFIGURE_STYLE=	gnu

.include <bsd.port.mk>
