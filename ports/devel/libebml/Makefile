# $MirOS: ports/devel/libebml/Makefile,v 1.2 2005/08/21 11:48:33 tg Exp $

COMMENT=			access library for the EBML format
CATEGORIES=		devel graphics
DISTNAME=		libebml-0.7.0
RESPONSIBLE=		Thorsten Glaser <tg@66h.42h.de>
HOMEPAGE=		http://matroska.org/
MASTER_SITES=		http://dl.matroska.org/downloads/libebml/
EXTRACT_SUFX=		.tar.bz2

# GNU LGPLv2.1
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_CXX=		Yes

post-extract:
	cp ${FILESDIR}/Makefile ${WRKSRC}/

.include <bsd.port.mk>
