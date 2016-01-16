# $MirOS: src/share/tmac/tab/Makefile,v 1.2 2006/06/16 22:55:11 tg Exp $
# @(#)Makefile	4.14 (Berkeley) 4/30/91

.include <bsd.own.mk>

PROGS=	tab300 tab300-12 tab302 tab302-12 tab37 tab382 tab382-12 tab450 \
	tab450-12 tab833 tab833-12 tabepson tabitoh tabitoh12 tablpr \
	tabnec tabnec-t tabnec12 tabnec25-t tabqume tabqume12 tabx-ecs \
	tabx-ecs12 tabxerox tabxerox12 tabcol tabcolhl
OBJS=	${PROGS:=.o} mktab.o
SRCS=	${PROGS:=.c} mktab.c
CLEANFILES+=${PROGS} xtab*
LINKS=	${BINDIR}/tmac/tablpr ${BINDIR}/tmac/tabtn300 \
	${BINDIR}/tmac/tablpr ${BINDIR}/tmac/tabcrt \
	${BINDIR}/tmac/tabcol ${BINDIR}/tmac/tabascii \
	${BINDIR}/tmac/tabcol ${BINDIR}/tmac/tablatin1 \
	${BINDIR}/tmac/tablpr ${BINDIR}/tmac/tab \
	${BINDIR}/tmac/tab302 ${BINDIR}/tmac/tab300s \
	${BINDIR}/tmac/tab302-12 ${BINDIR}/tmac/tab300s-12 \
	${BINDIR}/tmac/tab302 ${BINDIR}/tmac/tabdtc \
	${BINDIR}/tmac/tab302-12 ${BINDIR}/tmac/tabdtc12 \
	${BINDIR}/tmac/tab450 ${BINDIR}/tmac/tabipsi \
	${BINDIR}/tmac/tab450-12 ${BINDIR}/tmac/tabipsi12

all: ${PROGS}

mktab.o: mktab.c
	${HOSTCC} ${HOSTCFLAGS} ${CPPFLAGS} -c ${CFLAGS_${.TARGET}} ${.IMPSRC}

.for file in ${PROGS}
${file}: x${file}
	./x${file} >${file}

${file}.o: ${file}.c
	${HOSTCC} ${HOSTCFLAGS} ${CPPFLAGS} -c ${CFLAGS_${.TARGET}} ${.IMPSRC}

x${file}: mktab.o ${file}.o
	${HOSTCC} ${LDFLAGS} ${LDSTATIC} -o $@ ${.ALLSRC}
.endfor

beforeinstall:
	install -c -o ${BINOWN} -g ${BINGRP} -m ${NONBINMODE} \
	    ${PROGS} ${DESTDIR}${BINDIR}/tmac/
	install -c -o ${BINOWN} -g ${BINGRP} -m ${DOCMODE} \
	    ${.CURDIR}/README ${DESTDIR}${BINDIR}/tmac/README.tab

.if exists(../../Makefile.inc)
.  include "../../Makefile.inc"
.endif
.include <bsd.prog.mk>
