# $MirOS: src/share/dict/papers/Makefile,v 1.1.7.1 2005/03/06 16:33:40 tg Exp $

BINDIR=	/usr/share/dict/papers
NOMAN=	yes
NOPROG=	yes
FILES=	INDEX Rbstjissue Rv7man
GENF=	Ind.ia Ind.ib Ind.ic

.if ${.OBJDIR} != ${.CURDIR}
CLEANFILES+=	${FILES} ${GENF}
.endif

depend:
.for _i in ${FILES}
	ln -sf ${.CURDIR}/${_i} .
.endfor

all:
	mkey Rbstjissue Rv7man | inv -v -h997 -n Ind

install:
.for _i in ${FILES}
	install -c -o ${DOCOWN} -g ${DOCGRP} -m ${DOCMODE} \
	    ${.CURDIR}/${_i} ${DESTDIR}${BINDIR}/
.endfor
.for _i in ${GENF}
	install -c -o ${DOCOWN} -g ${DOCGRP} -m ${DOCMODE} \
	    ${_i} ${DESTDIR}${BINDIR}/
.endfor

.include <bsd.prog.mk>
