# $MirOS$

INSTDIR=papers
FILES=	Makefile
SUBDIR!=echo */Makefile | sed 's,/Makefile[[:>:]],,g'

beforeinstall:
	install -c -o ${DOCOWN} -g ${DOCGRP} -m ${DOCMODE} ${FILES} \
	    ${DESTDIR}${DOCDIR}/${INSTDIR}/

.include <bsd.subdir.mk>
