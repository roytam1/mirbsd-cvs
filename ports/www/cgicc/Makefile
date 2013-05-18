# $MirOS$
# $OpenBSD: Makefile,v 1.8 2004/02/25 02:35:17 naddy Exp $

COMMENT=	C++ compliant CGI applications libraries

DISTNAME=	cgicc-3.2.1
DASH_VER=	1
CATEGORIES=     www devel

MASTER_SITES=	${MASTER_SITE_GNU:=cgicc/}
HOMEPAGE=	http://www.gnu.org/software/cgicc/cgicc.html


# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_CXX=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS=		${CONFIGURE_SHARED} --enable-static

FAKE_FLAGS=	${DESTDIRNAME}=${WRKINST} \
		docdir=${DESTDIR}${PREFIX}/share/doc/cgicc

.include <bsd.port.mk>
