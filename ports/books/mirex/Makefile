# $MirOS: ports/books/mirex/Makefile,v 1.5 2006/01/27 01:03:33 tg Exp $

COMMENT=		"MirOS sample files, keys and information"
CATEGORIES=		books
CVS_DISTREPO=		_anoncvs@anoncvs.66h.42h.de:/cvs
CVS_DISTDATE=		2006/02/21 03:00
CVS_DISTMODS=		contrib/samples src/share/doc/README
CVS_DISTFILE=		mirex
PKGNAME=		${_CVS_DISTF:R}-0
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>
HOMEPAGE=		http://MirBSD.org/

# MirOS licence
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

WRKDIST=		${WRKDIR}/contrib/samples
DATA_DIR=		${PREFIX}/share/examples/mirex
KEYS=			1 2

post-build:
	tail -3 <${WRKDIR}/src/share/doc/README | grep '^key ' \
	    | while IFS="	" read keynr keyfile; do \
		IFS=" :"; set -A keyno $$keynr; IFS=; \
		print $$keyfile >${WRKBUILD}/gzsigkey.$${keyno[1]}; \
	done

pre-install:
	${INSTALL_DATA_DIR} ${DATA_DIR}
.for _k in ${KEYS}
	${INSTALL_DATA} ${WRKBUILD}/gzsigkey.${_k} ${DATA_DIR}/
.endfor

.include <bsd.port.mk>
