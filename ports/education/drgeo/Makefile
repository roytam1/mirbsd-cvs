# $MirOS: ports/education/drgeo/Makefile,v 1.4 2006/06/03 16:02:39 bsiegert Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2004/02/21 12:31:02 espie Exp $

COMMENT=			interactive geometry program

DISTNAME=	drgeo-0.9.12
PKGNAME=	${DISTNAME}-1
CATEGORIES=	education math

HOMEPAGE=	http://www.ofset.org/drgeo/	


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=ofset/}
DISTFILES=	${DISTNAME}.tar.gz

MODULES=	devel/gettext devel/pkgconfig

LIB_DEPENDS=	xml2.2.6::textproc/libxml \
		glade-2.0.0.0::devel/libglade \
		guile::lang/guile


CONFIGURE_STYLE=	gnu
USE_GMAKE=		Yes

.include <bsd.port.mk>
