# $MirOS: src/usr.bin/xinstall/Makefile,v 1.2 2005/06/02 22:45:53 tg Exp $

PROG=	xinstall
MAN=	install.1

afterinstall:
	cd ${DESTDIR}${BINDIR} && mv ${PROG} install

.include <bsd.prog.mk>
