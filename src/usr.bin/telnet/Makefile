# $MirOS: src/usr.bin/telnet/Makefile,v 1.3 2005/03/15 19:23:57 tg Exp $
# $OpenBSD: Makefile,v 1.20 2003/06/03 02:56:17 millert Exp $

PROG=		telnet
SRCS=		auth.c authenc.c commands.c encrypt.c genget.c \
		getent.c main.c misc.c network.c ring.c sys_bsd.c \
		telnet.c terminal.c tn3270.c utilities.c

CPPFLAGS+=	-DKLUDGELINEMODE -DUSE_TERMIO -DENV_HACK -DHAS_CGETENT -Dunix
CFLAGS+=	-Wall -Wno-unused
LDADD+=		-lcurses
DPADD+=		${LIBCURSES}

.include <bsd.prog.mk>
