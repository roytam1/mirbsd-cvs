# $MirOS: src/usr.bin/top/Makefile,v 1.2 2005/03/15 19:23:58 tg Exp $
# $OpenBSD: Makefile,v 1.10 2003/06/13 21:52:24 deraadt Exp $

PROG=		top
SRCS=		commands.c display.c machine.c screen.c top.c username.c \
		utils.c version.c
CPPFLAGS+=	-I.
DPADD=		${LIBCURSES}
LDADD=		-lcurses
CLEANFILES+=	sigdesc.h

beforedepend: sigdesc.h

sigdesc.h:	sigconv.awk
	awk -f ${.CURDIR}/sigconv.awk /usr/include/sys/signal.h >$@

.include <bsd.prog.mk>
