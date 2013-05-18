# $MirOS: ports/net/roxirc/Makefile,v 1.3 2007/04/13 19:27:52 bsiegert Exp $
# $OpenBSD: Makefile,v 1.8 2004/02/02 17:35:01 sturm Exp $

BROKEN=			unfetchable distfile

COMMENT=	Tcl/Tk irc client

DISTNAME=	roxirc-2.0
CATEGORIES=	net

HOMEPAGE=	http://roxirc.lighter.net/


PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

MASTER_SITES=	${HOMEPAGE}/download/betas/

RUN_DEPENDS=	:tk-8.4.*:x11/tk/8.4

USE_X11=	Yes # depends on tk, which needs X11
NO_BUILD=	Yes
NO_REGRESS=	Yes
PKG_ARCH=	*

DOCS=	bindings config extras help hilight lagmeter menus mirccolors \
	oper prefs single startup

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/roxirc
	${INSTALL_SCRIPT} ${WRKSRC}/roxirc ${PREFIX}/bin
	cd ${WRKSRC}; ${INSTALL_DATA} ${DOCS} ${PREFIX}/share/doc/roxirc

.include <bsd.port.mk> 
