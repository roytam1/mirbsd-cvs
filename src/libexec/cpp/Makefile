# $MirOS$
# @(#)Makefile	5.2 (Berkeley) 5/12/90

PROG=		cpp
SRCS=		cpp.c cpy.c rodata.o
NOMAN=		yes
CPPFLAGS+=	-Dunix=1 -DFLEXNAMES
CLEANFILES+=	cpy.c rodata.c

beforedepend: cpy.c

rodata.c: cpy.c

cpy.c: cpy.y
	${YACC} -r ${.ALLSRC}
	mv y.tab.c rodata.c
	mv y.code.c cpy.c

afterinstall:
	${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${.CURDIR}/xcpp.sh ${DESTDIR}/usr/bin/cpp

.include <bsd.prog.mk>
