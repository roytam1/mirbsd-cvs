# $MirOS$

SRC_PATH?=	${.CURDIR}/../compress
NOPROG=		Yes
MAN+=		gzexe.1 zdiff.1 zforce.1 zmore.1 znew.1
LINKS+=		${BINDIR}/zdiff ${BINDIR}/zcmp
MLINKS+=	zdiff.1 zcmp.1
LINKS+=		${BINDIR}/zmore ${BINDIR}/zless
MLINKS+=	zmore.1 zless.1

.PATH: ${SRC_PATH}

afterinstall:
	${INSTALL} -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${SRC_PATH}/gzexe ${SRC_PATH}/zdiff ${SRC_PATH}/zforce \
	    ${SRC_PATH}/zmore ${SRC_PATH}/znew ${DESTDIR}${BINDIR}/

.include <bsd.prog.mk>
