# $MirOS: ports/editors/scintilla/Makefile,v 1.4 2006/02/09 11:11:31 tg Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2003/08/14 18:24:30 sturm Exp $

COMMENT=			source code editing component for GTK+

VERSION=	1.54
DISTNAME=	scintilla${VERSION:S/.//}
PKGNAME=	scintilla-${VERSION}-0
CATEGORIES=	editors x11

HOMEPAGE=	http://www.scintilla.org/


# old Python license
PERMIT_PACKAGE_CDROM=	"may not sell"
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	"may not sell"
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=scintilla/}
EXTRACT_SUFX=	.tgz

USE_X11=	Yes
USE_GMAKE=	Yes
USE_CXX=	Yes
NO_REGRESS=	Yes

MAKE_FILE=	makefile
MAKE_ENV=		NO_SHARED_LIBS='${NO_SHARED_LIBS}'

WRKDIST=	${WRKDIR}/scintilla
WRKSRC=		${WRKDIST}/gtk

LIB_DEPENDS=	gtk.1.2,gdk.1.2::x11/gtk+1

post-extract:
	perl -pi -e 's|\x0d||' ${WRKDIST}/include/*.h ${WRKDIST}/gtk/*.cxx \
	    ${WRKDIST}/src/*.cxx

.include <bsd.port.mk>
