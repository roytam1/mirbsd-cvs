# $OpenBSD: Makefile,v 1.2 2003/08/17 14:25:28 sturm Exp $

COMMENT=			flexible and small GTK+ editor

VERSION=		1.54
DISTNAME=		scite${VERSION:S/.//}
PKGNAME=		scite-${VERSION}-0
CATEGORIES=		editors x11

HOMEPAGE=		http://www.scintilla.org/SciTE.html


# old Python license
PERMIT_PACKAGE_CDROM=	"may not sell"
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	"may not sell"
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=scintilla/}
EXTRACT_SUFX=		.tgz

LIB_DEPENDS=		gthread.1.2::devel/glib1\
			scintilla.1,scintilla_lexers.1::editors/scintilla

USE_GMAKE=		Yes
USE_X11=		Yes
USE_CXX=		Yes
NO_REGRESS=		Yes
WRKDIST=		${WRKDIR}/scite
WRKSRC=			${WRKDIST}/gtk
MAKE_FILE=		makefile

post-extract:
	perl -pi -e 's|\x0d||' ${WRKDIST}/gtk/*.cxx ${WRKDIST}/src/*.cxx

.include <bsd.port.mk>
