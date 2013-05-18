# $MirOS: src/gnu/usr.bin/anoncvs/Makefile,v 1.3 2005/12/04 20:29:50 tg Exp $

CBIN=		anoncvsbin
BINDIR=		/var/anoncvs/anoncvs
BINOWN=		root
BINGRP=		wheel
BINMODE=	111

CLEANFILES+=	${CBIN}.conf ${CBIN}.c ${CBIN}.cache ${CBIN}.mk \
		${CBIN}.o ${CBIN} cat.lo cat_stub.c cat_stub.o mksh.lo \
		mksh_stub.c mksh_stub.o pwd.lo pwd_stub.c pwd_stub.o rm.lo \
		rm_stub.c rm_stub.o cvs.lo cvs_stub.c cvs_stub.o

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
	cd ${DESTDIR}${BINDIR}; ln -f ${CBIN} bin/cat; ln -f ${CBIN} bin/pwd; \
	    ln -f ${CBIN} bin/rm; ln -f ${CBIN} bin/sh; \
	    ln -f ${CBIN} bin/cvs; rm ${CBIN}

.if defined(DESTDIR) && ${DESTDIR} != "" && ${DESTDIR} != "/"
distribution:
	install -c -o ${BINOWN} -g ${BINGRP} -m ${NONBINMODE} \
	    /dev/null ${DESTDIR}${BINDIR}/.hushlogin
	install -c -o ${BINOWN} -g ${BINGRP} -m ${NONBINMODE} \
	    ${.CURDIR}/dot.plan ${DESTDIR}${BINDIR}/.plan
	install -c -o ${BINOWN} -g ${BINGRP} -m ${NONBINMODE} \
	    ${.CURDIR}/dot.profile ${DESTDIR}${BINDIR}/.profile
	install -c -o ${BINOWN} -g ${BINGRP} -m ${NONBINMODE} \
	    ${.CURDIR}/resolv.conf ${DESTDIR}${BINDIR}/etc
	install -c -o ${BINOWN} -g ${BINGRP} -m ${NONBINMODE} \
	    ${DESTDIR}/etc/group ${DESTDIR}${BINDIR}/etc
	install -c -o ${BINOWN} -g ${BINGRP} -m ${NONBINMODE} \
	    ${DESTDIR}/etc/hosts ${DESTDIR}${BINDIR}/etc
	install -c -o ${BINOWN} -g ${BINGRP} -m ${NONBINMODE} \
	    ${DESTDIR}/etc/passwd ${DESTDIR}${BINDIR}/etc
	install -c -o ${BINOWN} -g ${BINGRP} -m ${NONBINMODE} \
	    ${DESTDIR}/etc/protocols ${DESTDIR}${BINDIR}/etc
	install -c -o ${BINOWN} -g ${BINGRP} -m ${NONBINMODE} \
	    ${DESTDIR}/etc/pwd.db ${DESTDIR}${BINDIR}/etc
	install -c -o ${BINOWN} -g ${BINGRP} -m ${NONBINMODE} \
	    ${DESTDIR}/etc/services ${DESTDIR}${BINDIR}/etc
	install -c -o ${BINOWN} -g ${BINGRP} -m ${NONBINMODE} \
	    ${DESTDIR}/etc/ttys ${DESTDIR}${BINDIR}/etc
.else
distribution:
	@echo "Error: doing make distribution here is a great cause"
	@echo "	of potential security problems. Please do not do this."
	@exit 1
.endif

depend:
	# Nothing here so far...

lint:
	# Nothing here so far...

tags:
	# Nothing here so far...

.include <bsd.prog.mk>
