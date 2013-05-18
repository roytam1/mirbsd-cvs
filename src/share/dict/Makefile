# $MirOS$

SUBDIR=	papers

BINDIR=	/usr/share/dict
NOMAN=	yes
NOPROG=	yes
FILES=	README connectives eign propernames web2 web2a
GENF=	words

CLEANFILES+=	${GENF}

all: _SUBDIRUSE words

words: ${.CURDIR}/eign ${.CURDIR}/web2 ${.CURDIR}/words
	sort -df ${.ALLSRC} | uniq >$@

afterinstall:
.for _i in ${FILES}
	install -c -o ${DOCOWN} -g ${DOCGRP} -m ${DOCMODE} \
	    ${.CURDIR}/${_i} ${DESTDIR}${BINDIR}/
.endfor
.for _i in ${GENF}
	install -c -o ${DOCOWN} -g ${DOCGRP} -m ${DOCMODE} \
	    ${_i} ${DESTDIR}${BINDIR}/
.endfor

.include <bsd.prog.mk>
