# $OpenBSD: Makefile,v 1.2 2002/12/29 19:37:52 fgsch Exp $

COMMENT=			convert Excel and PowerPoint to HTML

VSN=			0.2.9.8
DISTNAME=		xlHtml-${VSN}
PKGNAME=		xlhtml-${VSN}-${DASH_VER}
CATEGORIES=		converters

MASTER_SITES=	http://www.xlhtml.org/
HOMEPAGE=	http://www.xlhtml.org/

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE= gnu
CONFIGURE_ARGS= --enable-static ${CONFIGURE_SHARED}

.include <bsd.port.mk>
