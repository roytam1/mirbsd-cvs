# $MirOS: ports/books/mirex/Makefile,v 1.31 2014/07/21 20:42:01 tg Exp $

COMMENT=		MirOS sample files, keys and information
CATEGORIES=		books
MCZ_FETCH=		Yes
CVS_DISTREPO=		${_MIROS_ANONCVS}
CVS_DISTDATE=		2014/10/03
PKGNAME=		${CVS_DISTFILE}-${CVS_DISTDATE:M*/*:S!/!!g}-${DASH_VER}
CVS_DISTMODS=		contrib/samples \
			contrib/hosted/tg/uhr \
			src/share/doc/README \
			src/share/misc \
			www/files/MirOS-Licence \
			www/files/MirOS-Licence.htm
CVS_DISTFILE=		mirex
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>
HOMEPAGE=		http://MirBSD.de/

# MirOS licence
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

WRKDIST=		${WRKDIR}/contrib/samples
DATA_DIR=		${PREFIX}/share/examples/mirex
KEYS=			1 2

# sync with src/distrib/common/listend.i386-big
post-build:
	saveIFS=$$IFS; \
	    tail -3 <${WRKDIR}/src/share/doc/README | grep '^key ' | \
	    while IFS="	" read keynr keyfile; do \
		IFS=" :"; set -A keyno -- $$keynr; IFS=$$saveIFS; \
		print -r -- $$keyfile >${WRKBUILD}/gzsigkey.$${keyno[1]}; \
	done

pre-install:
	${INSTALL_DATA_DIR} ${DATA_DIR}
.for _k in ${KEYS}
	${INSTALL_DATA} ${WRKBUILD}/gzsigkey.${_k} ${DATA_DIR}/
.endfor
	${INSTALL_DATA} ${WRKDIR}/contrib/hosted/tg/uhr ${DATA_DIR}/
	cd ${WRKDIR}/src/share/misc && ${INSTALL_DATA} \
	    acronyms getopt *.template utf-8-demo ${DATA_DIR}/
	cd ${WRKDIR}/www/files && ${INSTALL_DATA} MirOS-Licence* ${DATA_DIR}/

.include <bsd.port.mk>
