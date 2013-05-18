# $MirOS: src/share/mk/Makefile,v 1.3 2005/11/17 12:05:08 tg Exp $
# $OpenBSD: Makefile,v 1.8 2002/01/01 23:40:28 provos Exp $
# $NetBSD: Makefile,v 1.12 1995/10/22 00:45:53 christos Exp $

FILES=		bsd.cfwrap.mk bsd.dep.mk bsd.doc.mk bsd.lib.mk bsd.lkm.mk \
		bsd.lt.mk bsd.man.mk bsd.obj.mk bsd.own.mk bsd.prog.mk \
		bsd.subdir.mk bsd.sys.mk sys.mk
NOOBJ=		Yes

install:
	${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} -m ${NONBINMODE} \
	    ${FILES} ${DESTDIR}${BINDIR}/mk/

.include <bsd.prog.mk>
