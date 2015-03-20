# $MirOS: ports/x11/envypn-font/Makefile,v 1.4 2015/03/03 22:58:16 tg Exp $

COMMENT=		Readable terminal font inspired by Envy Code R
VSN=			1.6.2
DISTNAME=		envypn-font-${VSN}
CATEGORIES=		x11
HOMEPAGE=		http://ywstd.fr/me/#envypn

# MirOS
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://files.ywstd.fr/p/envypn-font/MirBSD/
DISTFILES=		envypn-font-MirBSD-${VSN}${EXTRACT_SUFX}

NO_REGRESS=		Yes
USE_X11=		Yes

FONTDIR=		${PREFIX}/lib/X11/fonts/envypn

do-build:
	# this could look nicer with set -o pipefail (mksh R46+)
.for _f in envypn7x13 envypn7x13e envypn7x15 envypn7x15e
	cd ${WRKBUILD:Q} && \
	    ${MKSH} ${PORTSDIR}/infrastructure/scripts/bdfctool -d \
	    <${WRKSRC:Q}/${_f}.bdfc >${_f}.bdf
	cd ${WRKBUILD:Q} && bdftopcf -t ${_f}.bdf >${_f}.pcf
	cd ${WRKBUILD:Q} && ${GZIP_CMD} ${_f}.pcf
.endfor
	cd ${WRKSRC:Q} && sed s,@PREFIX@,${PREFIX:Q},g <README >README.i

do-install:
	${INSTALL_DATA_DIR} ${PREFIX:Q}/share/doc/envypn-font ${FONTDIR:Q}
	${INSTALL_DATA} ${WRKSRC:Q}/README.i \
	    ${PREFIX:Q}/share/doc/envypn-font/README
	cd ${WRKSRC:Q} && ${INSTALL_DATA} fonts.alias *.pcf.gz ${FONTDIR:Q}/
	cd ${FONTDIR:Q} && ${X11BASE:Q}/bin/mkfontdir

.include <bsd.port.mk>
