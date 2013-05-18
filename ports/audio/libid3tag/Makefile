# $MirOS: ports/audio/libid3tag/Makefile,v 1.2 2006/06/23 22:08:07 bsiegert Exp $
# $OpenBSD: Makefile,v 1.3 2004/02/21 02:32:20 naddy Exp $

COMMENT=			library for reading ID3 tags

DISTNAME=	libid3tag-0.15.1b
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

CONFIGURE_STYLE=autoconf
AUTOCONF_NEW=	yes
CONFIGURE_ARGS=	${CONFIGURE_SHARED}

.include <bsd.port.mk>
