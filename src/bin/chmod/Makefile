# $MirOS: src/bin/chmod/Makefile,v 1.5 2006/06/15 18:25:15 tg Exp $
# $OpenBSD: Makefile,v 1.7 2001/09/06 18:52:55 mickey Exp $

PROG=	chgrp
SRCS=	chmod.c
MAN=	chmod.1 chgrp.1 chown.8 chflags.1
LINKS=	${BINDIR}/${PROG} ${BINDIR}/chmod \
	${BINDIR}/${PROG} /sbin/chown

afterinstall:
	-rm -f ${DESTDIR}/usr/bin/chflags
	cd ${DESTDIR}/usr/bin && ln -s ../..${BINDIR}/chmod chflags

.include <bsd.prog.mk>
