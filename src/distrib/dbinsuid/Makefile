# $MirOS$

CBIN=		dbinsuid
BINDIR=		/sbin
BINOWN=		root
BINGRP=		bin
BINMODE=	4555
NOMAN=		Yes

LINKS+=		${BINDIR}/${CBIN} /sbin/ping \
		${BINDIR}/${CBIN} /sbin/ping6 \
		${BINDIR}/${CBIN} /usr/sbin/traceroute \
		${BINDIR}/${CBIN} /usr/sbin/traceroute6

CLEANFILES+=	${CBIN}.conf ${CBIN}.c ${CBIN}.cache ${CBIN}.mk

all: ${CBIN}

${CBIN}.mk ${CBIN}.cache ${CBIN}.c: ${CBIN}.conf
	crunchgen -E -D ${BSDSRCDIR} -L ${DESTDIR}/usr/lib \
	    -c ${CBIN}.c -e ${CBIN} -m ${CBIN}.mk ${.ALLSRC}

${CBIN}.conf: crunch.conf
	cp $> $@

${CBIN}: ${CBIN}.mk ${CBIN}.cache ${CBIN}.c
	${MAKE} -f ${CBIN}.mk $@

clean: ${CBIN}.mk
	${MAKE} -f ${CBIN}.mk $@
	-rm -f ${CLEANFILES}

cleandir: clean
	-rm -f .depend

depend lint tags: ${CBIN}.mk
	${MAKE} -f ${CBIN}.mk $@

install:
	${INSTALL} ${INSTALL_COPY} ${INSTALL_STRIP} -o ${BINOWN} -g ${BINGRP} \
	    -m ${BINMODE} ${CBIN} ${DESTDIR}${BINDIR}/
.  if defined(LINKS) && !empty(LINKS)
.    for lnk file in ${LINKS}
	@l=${DESTDIR}${lnk}; \
	 t=${DESTDIR}${file}; \
	 echo $$t -\> $$l; \
	 rm -f $$t; ln $$l $$t || cp $$l $$t
.    endfor
.  endif
	-rm ${DESTDIR}${BINDIR}/${CBIN}

.include <bsd.prog.mk>
