# $MirOS$

COMMENT=		"extensible open standard Audio/Video container format"
CATEGORIES=		graphics multimedia
DISTNAME=		libmatroska-0.7.0
RESPONSIBLE=		Thorsten Glaser <tg@${_DOMAIN_DU_JOUR}>
HOMEPAGE=		http://matroska.org/
MASTER_SITES=		http://dl.matroska.org/downloads/libmatroska/
EXTRACT_SUFX=		.tar.bz2

# GNU LGPLv2.1
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_CXX=		Yes

LIB_DEPENDS+=		ebml::devel/libebml

post-extract:
	cp ${FILESDIR}/Makefile ${WRKSRC}/

NO_REGRESS=		Yes

.include <bsd.port.mk>
