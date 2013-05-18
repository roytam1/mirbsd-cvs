# $MirOS: ports/korean/hanterm-xf/Makefile,v 1.5 2006/02/09 11:11:54 tg Exp $
# $OpenBSD: Makefile,v 1.6 2004/01/25 21:10:50 pvalchev Exp $

COMMENT=			XFree86-based xterm with Korean language support
DISTNAME=	hanterm-xf-p19
PKGNAME=	hanterm-xf-19-0
CATEGORIES=	korean x11
MASTER_SITES=	http://www.hanterm.org/download/hanterm-xf/
HOMEPAGE=	http://www.hanterm.org/

PERMIT_PACKAGE_CDROM=	yes
PERMIT_PACKAGE_FTP=	yes
PERMIT_DISTFILES_CDROM=	yes
PERMIT_DISTFILES_FTP=	yes

MODULES=	converters/libiconv
USE_X11=	Yes

CONFIGURE_STYLE=gnu
CONFIGURE_ENV+=	X_EXTRA_LIBS="-L${ICONV_PREFIX}/lib -liconv"

NO_REGRESS=	Yes

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/hanterm ${PREFIX}/bin
	${INSTALL_DATA} ${WRKSRC}/Hanterm.ad \
		${PREFIX}/lib/X11/app-defaults/Hanterm

.include <bsd.port.mk>
