# $MirOS: src/gnu/usr.bin/anoncvs/Makefile,v 1.11 2010/12/12 23:42:24 tg Exp $

CBIN=		anoncvsbin
BINDIR=		/var/anoncvs
BINOWN=		root
BINGRP=		_anoncvs
BINMODE=	110

CLEANFILES+=	${CBIN}.conf ${CBIN}.c ${CBIN}.cache ${CBIN}.mk \
		${CBIN}.o ${CBIN} cvs.lo* cvs_stub.c cvs_stub.o

all:	${CBIN}

${CBIN}.mk ${CBIN}.cache ${CBIN}.c: ${CBIN}.conf
	crunchgen -E -D ${BSDSRCDIR} -L ${DESTDIR}/usr/lib \
	    -c ${CBIN}.c -e ${CBIN} -m ${CBIN}.mk ${CBIN}.conf

${CBIN}.conf: crunch.conf
	sed 's%OBJPATH%${BSDOBJDIR}%g' <${.CURDIR}/crunch.conf >${CBIN}.conf

${CBIN}: ${CBIN}.mk ${CBIN}.cache ${CBIN}.c
	${MAKE} -f ${CBIN}.mk

realinstall:
	${INSTALL} ${INSTALL_COPY} ${INSTALL_STRIP} -o ${BINOWN} -g ${BINGRP} \
	    -m ${BINMODE} ${CBIN} ${DESTDIR}${BINDIR}
	cd ${DESTDIR}${BINDIR}; ln -f ${CBIN} bin/cvs; rm ${CBIN}

.if defined(DESTDIR) && ${DESTDIR} != "" && ${DESTDIR} != "/"
distribution:
	install -c -o ${BINOWN} -g ${CONFGRP} -m ${NONBINMODE} \
	    /dev/null ${DESTDIR}${BINDIR}/.hushlogin
	install -c -o ${BINOWN} -g ${CONFGRP} -m ${NONBINMODE} \
	    ${.CURDIR}/dot.plan ${DESTDIR}${BINDIR}/.plan
	install -c -o ${BINOWN} -g ${CONFGRP} -m ${NONBINMODE} \
	    ${.CURDIR}/resolv.conf ${DESTDIR}${BINDIR}/etc/
	install -c -o ${BINOWN} -g ${CONFGRP} -m ${NONBINMODE} \
	    ${DESTDIR}/etc/group ${DESTDIR}${BINDIR}/etc/
	install -c -o ${BINOWN} -g ${CONFGRP} -m ${NONBINMODE} \
	    ${DESTDIR}/etc/hosts ${DESTDIR}${BINDIR}/etc/
	install -c -o ${BINOWN} -g ${CONFGRP} -m ${NONBINMODE} \
	    ${DESTDIR}/etc/passwd ${DESTDIR}${BINDIR}/etc/
	install -c -o ${BINOWN} -g ${CONFGRP} -m ${NONBINMODE} \
	    ${DESTDIR}/etc/protocols ${DESTDIR}${BINDIR}/etc/
	install -c -o ${BINOWN} -g ${CONFGRP} -m ${NONBINMODE} \
	    ${DESTDIR}/etc/pwd.db ${DESTDIR}${BINDIR}/etc/
	install -c -o ${BINOWN} -g ${CONFGRP} -m ${NONBINMODE} \
	    ${DESTDIR}/etc/services ${DESTDIR}${BINDIR}/etc/
	install -c -o ${BINOWN} -g ${CONFGRP} -m ${NONBINMODE} \
	    ${DESTDIR}/etc/ttys.dist ${DESTDIR}${BINDIR}/etc/ttys
	ln -sf ../usr/share/zoneinfo/UTC ${DESTDIR}${BINDIR}/etc/localtime
.else
distribution:
	@echo "Error: doing make distribution here is a great cause"
	@echo "	of potential security problems. Please do not do this."
	@exit 1
.endif

depend:

lint:

tags:

.include <bsd.prog.mk>
