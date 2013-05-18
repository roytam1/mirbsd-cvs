# $MirOS: ports/books/selfhtml/Makefile,v 1.3 2005/08/21 11:48:22 tg Exp $

COMMENT=			German HTML compendium
CATEGORIES=		books www
DISTNAME=		selfhtml81
EXTRACT_SUFX=		.zip
PKGNAME=		selfhtml-8.1-0
HOMEPAGE=		http://aktuell.de.selfhtml.org/
RESPONSIBLE=		Thorsten Glaser <tg@66h.42h.de>

# http://de.selfhtml.org/editorial/copyright.htm
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	"may not modify"
PERMIT_PACKAGE_FTP=	"may not modify"

MASTER_SITES=		\
			ftp://ftp.join.uni-muenster.de/pub/documents/selfhtml/ \
			http://gd.tuwien.ac.at/languages/html/selfhtml/ \
			http://ftp-stud.fht-esslingen.de/pub/Mirrors/selfhtml/ \
			ftp://ftp.uni-ulm.de/mirrors/selfhtml/ \
			http://www.stud.uni-goettingen.de/software/ \
			ftp://ftp.hu-berlin.de/pub/www/selfhtml/ \
			ftp://ftp.tu-clausthal.de/pub/selfhtml/

NO_BUILD=		Yes
NO_REGRESS=		Yes

DATA_DIR=		${PREFIX}/share/doc/selfhtml

do-install:
	${INSTALL_DATA_DIR} ${DATA_DIR}
	cd ${WRKSRC} && find . -type f | cpio -pdlu ${DATA_DIR}/
	cd ${DATA_DIR}/src && rm selfhtml.css && mv selfnosize.css selfhtml.css
	chown -R ${DOCOWN}:${DOCGRP} ${DATA_DIR}
	chmod -R a=rX ${DATA_DIR}

.include <bsd.port.mk>
