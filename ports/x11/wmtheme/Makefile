# $MirOS: ports/x11/wmtheme/Makefile,v 1.3 2006/09/14 00:15:44 tg Exp $
# $OpenBSD: Makefile,v 1.12 2003/10/08 17:13:18 sturm Exp $

COMMENT=		window manager theme utility

DISTNAME=		wmtheme-1.3.2
CATEGORIES=		x11 

HOMEPAGE=		http://wmtheme.sourceforge.net/


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=wmtheme/}

NO_REGRESS=		Yes

USE_X11=		Yes
LIB_DEPENDS=		gtk.1.2,gdk.1.2::x11/gtk+1
USE_GMAKE=		Yes
EXTRA_THEMES=		gotheme ortheme

FAKE_FLAGS+=		prefix=${PREFIX} DESTDIR=${WRKINST}

post-install:
.for i in ${EXTRA_THEMES}
	cd ${PREFIX}/bin; ln -sf wmtheme $i;
	cd ${PREFIX}/man/man1; ln -sf wmtheme.1.gz $i.1.gz
.endfor

.include <bsd.port.mk>
