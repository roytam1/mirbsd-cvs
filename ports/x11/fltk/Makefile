# $MirOS: ports/x11/fltk/Makefile,v 1.4 2010/11/19 16:27:13 bsiegert Exp $
# $OpenBSD: Makefile,v 1.28 2004/03/04 17:49:26 espie Exp $

COMMENT=		Fast Light Tool Kit
VSN=			1.1.4
DISTNAME=		fltk-${VSN}
CATEGORIES=		x11
HOMEPAGE=		http://www.fltk.org/

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

DISTFILES=	${DISTNAME}-source${EXTRACT_SUFX}
MASTER_SITES=	ftp://ftp.easysw.com/pub/fltk/${VSN}/ \
		ftp://ftp2.easysw.com/pub/fltk/${VSN}/ \
		ftp://ftp.funet.fi/pub/mirrors/ftp.easysw.com/pub/fltk/${VSN}/ \
		ftp://gd.tuwien.ac.at/hci/fltk/${VSN}/

LIB_DEPENDS+=		jpeg.62::graphics/jpeg
MODULES+=		graphics/png

NO_REGRESS=		Yes
USE_X11=		Yes
USE_CXX=		Yes
CONFIGURE_STYLE=	autoconf dest no-autoheader
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
MAKE_ENV+=		SYSCONFDIR=${SYSCONFDIR:Q}

.include <bsd.port.mk>
