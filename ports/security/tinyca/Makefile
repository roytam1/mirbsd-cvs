# $MirOS: ports/security/tinyca/Makefile,v 1.1.7.1 2005/03/18 15:51:56 tg Exp $

COMMENT=			gui to manage a certification authority
DISTNAME=	tinyca-0.6.4
CATEGORIES=	security
HOMEPAGE=	http://tinyca.sm-zone.net/index.html

# GNU GPLv2
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=	http://tinyca.sm-zone.net/

RUN_DEPENDS=	::x11/p5-Gtk,gnome \
		::converters/p5-Locale-gettext \
		::archivers/zip

NO_REGRESS=	Yes

do-build:
	@echo 'g#%%LOCALBASE%%#s##${LOCALBASE}#\nwq' | ed -s ${WRKSRC}/tinyca

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/libdata/tinyca
	${INSTALL_DATA_DIR} ${PREFIX}/share/locale/de/LC_MESSAGES/
	${INSTALL_DATA_DIR} ${PREFIX}/share/tinyca/templates
	${INSTALL_SCRIPT} ${WRKSRC}/tinyca ${PREFIX}/bin
	${INSTALL_DATA} ${WRKSRC}/templates/openssl.cnf ${PREFIX}/share/tinyca/templates
	@msgfmt ${WRKSRC}/po/de.po -o ${PREFIX}/share/locale/de/LC_MESSAGES/tinyca.mo
	@cp -R ${WRKSRC}/lib/* ${PREFIX}/libdata/tinyca

.include <bsd.port.mk>
