# $OpenBSD: Makefile,v 1.3 2003/10/18 19:44:44 sturm Exp $

COMMENT=			convert man pages to HTML

DISTNAME=	man2web-0.88
CATEGORIES=	www
HOMEPAGE=	http://man2web.sourceforge.net/


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=man2web/}

CONFIGURE_STYLE= gnu
CONFIGURE_ARGS=	--with-distro=openbsd-3
CONFIGURE_ARGS+= --disable-lynx		# requires lynxcgi support

FAKE_FLAGS=	${DESTDIRNAME}=${WRKINST} \
		sysconfdir=${PREFIX}/share/examples/man2web

.include <bsd.port.mk>
