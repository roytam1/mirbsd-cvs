# $OpenBSD: Makefile,v 1.3 2004/02/21 02:32:20 naddy Exp $

COMMENT=	"command-line MPEG audio decoder and player"

DISTNAME=	madplay-0.15.1b
PKGNAME=	${DISTNAME}-1
CATEGORIES=	audio
HOMEPAGE=	http://mad.sourceforge.net/


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	ftp://ftp.mars.org/pub/mpeg/ \
		${MASTER_SITE_SOURCEFORGE:=mad/}

MODULES=	devel/gettext
LIB_DEPENDS=	id3tag::audio/libid3tag mad::audio/libmad

FLAVORS=	esd
FLAVOR?=

.if ${FLAVOR:L:Mesd}
CONFIGURE_ARGS+= --with-esd
LIB_DEPENDS+=   esd.2::audio/esound
.else
CONFIGURE_ARGS+= --without-esd
.endif

CONFIGURE_STYLE=gnu

.include <bsd.port.mk>
