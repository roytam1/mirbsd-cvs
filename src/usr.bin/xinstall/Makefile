# $MirOS: src/usr.bin/xinstall/Makefile,v 1.4 2008/03/14 14:26:55 tg Exp $

PROG=	xinstall
MAN=	install.1

.include <bsd.own.mk>

realinstall:
.if (${OBJECT_FMT} == "Mach-O") && (${LINK.prog} != "NO")
	@echo Relinking ${PROG}
	${LINK.prog} -o ${PROG}
.endif
	${INSTALL} ${INSTALL_COPY} ${INSTALL_STRIP} -o ${BINOWN} -g ${BINGRP} \
	    -m ${BINMODE} ${PROG} ${DESTDIR}${BINDIR}/install

.include <bsd.prog.mk>
