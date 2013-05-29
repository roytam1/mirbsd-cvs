# $MirOS: ports/x11/terminus-font/Makefile,v 1.5 2009/06/22 12:07:34 tg Exp $

COMMENT=		Readable terminal font inspired by Envy Code R
DISTNAME=		envypn-font-1.5.1
CATEGORIES=		x11
HOMEPAGE=		http://tetedulinuxien.fr/qui-suis-je/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://linuxien.legtux.org/projects/envypn-font/

NO_REGRESS=		Yes
USE_X11=		Yes

FONTDIR=		${PREFIX}/lib/X11/fonts/envypn

do-build:
.for _f in envypn7x13.pcf envypn7x13e.pcf envypn7x15.pcf envypn7x15e.pcf
	cd ${WRKSRC:Q} && ${GZIP_CMD} <${_f} >${_f}.gz
.endfor
	cd ${WRKSRC:Q} && sed s,@PREFIX@,${PREFIX:Q},g <README >README.i

do-install:
	${INSTALL_DATA_DIR} ${PREFIX:Q}/share/doc/envypn-font ${FONTDIR:Q}
	${INSTALL_DATA} ${WRKSRC:Q}/README.i \
	    ${PREFIX:Q}/share/doc/envypn-font/README
	cd ${WRKSRC:Q} && ${INSTALL_DATA} fonts.alias *.pcf.gz ${FONTDIR:Q}/
	cd ${FONTDIR:Q} && ${X11BASE:Q}/bin/mkfontdir

.include <bsd.port.mk>
