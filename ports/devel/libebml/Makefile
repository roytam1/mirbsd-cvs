# $MirOS: ports/devel/libebml/Makefile,v 1.3 2006/09/14 00:08:20 tg Exp $

COMMENT=			access library for the EBML format
CATEGORIES=		devel graphics
DISTNAME=		libebml-0.7.0
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.org>
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
