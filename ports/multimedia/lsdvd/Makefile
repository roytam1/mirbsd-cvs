# $MirOS: ports/multimedia/lsdvd/Makefile,v 1.2 2006/02/09 11:12:11 tg Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2004/06/21 21:26:24 xsa Exp $

COMMENT=			print information about the content and structure of a DVD

DISTNAME=	lsdvd-0.10
CATEGORIES=	multimedia

HOMEPAGE=	http://acidrip.thirtythreeandathird.net/lsdvd.html

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=acidrip/}

LIB_DEPENDS=	dvdread.3.0::devel/libdvdread

CONFIGURE_STYLE=gnu

.include <bsd.port.mk>
