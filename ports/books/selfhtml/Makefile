# $MirOS: ports/books/selfhtml/Makefile,v 1.5 2008/11/08 23:03:35 tg Exp $

COMMENT=		German HTML compendium
CATEGORIES=		books www
VSN=			8.1.2
DISTNAME=		selfhtml${VSN:S/.//g}
PKGNAME=		selfhtml-${VSN}-${DASH_VER}
HOMEPAGE=		http://aktuell.de.selfhtml.org/
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.org>

# http://de.selfhtml.org/editorial/copyright.htm
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	"may not modify"
PERMIT_PACKAGE_FTP=	"may not modify"

EXTRACT_SUFX=		.zip
_USE_ZIP_SUBDIR=	Yes
MASTER_SITES=		\
			http://d-graff.de/selfhtml/ \
			http://decaf.de/selfhtml/ \
			http://download.mediatory.net/selfhtml/ \
			http://ftp.tu-clausthal.de/pub/selfhtml/ \
			http://ftp.uni-ulm.de/mirrors/selfhtml/ \
			http://hell.meiert.org/core/zip/ \
			http://mirrors.riehle-web.com/selfhtml/ \
			http://ng76.de/selfhtml/download/ \
			http://selfhtml.hegglin.net/ \
			http://selfhtml.meta-text.net/ \
			http://skop.net/selfhtml/ \
			http://wilfing.eu/selfhtml/ \
			http://www.mcwiwa.de/selfhtml/ \
			http://www.scytheman.ch/ \
			http://www.to-kl.de/self/ \
			http://www.unet.univie.ac.at/~a9105535/ \
			ftp://ftp.rub.de/pub/selfhtml/ \
			ftp://ftp.uni-ulm.de/mirrors/selfhtml/ \

NO_BUILD=		Yes
NO_REGRESS=		Yes

DATA_DIR=		${PREFIX}/share/doc/selfhtml

do-install:
	${INSTALL_DATA_DIR} ${DATA_DIR:Q}
	cd ${WRKSRC:Q} && pax -rw -pe * ${DATA_DIR:Q}/
	cd ${DATA_DIR:Q}/src && \
	    rm -f selfnosize.css.orig && \
	    mv selfhtml.css selfnormal.css && \
	    mv selfnosize.css selfhtml.css
	rm -f ${DATA_DIR:Q}/editorial/selfhtmlfaq.htm.orig
	chown -R ${DOCOWN}:${DOCGRP} ${DATA_DIR:Q}
	chmod -R a=rX ${DATA_DIR:Q}

.include <bsd.port.mk>
