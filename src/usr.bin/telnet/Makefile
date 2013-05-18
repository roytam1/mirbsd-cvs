# $MirOS: src/usr.bin/telnet/Makefile,v 1.4 2005/06/26 17:34:46 tg Exp $
# $OpenBSD: Makefile,v 1.23 2005/05/24 03:41:58 deraadt Exp $

PROG=		telnet
SRCS=		auth.c authenc.c commands.c encrypt.c genget.c \
		getent.c main.c misc.c network.c ring.c sys_bsd.c \
		telnet.c terminal.c utilities.c

CPPFLAGS+=	-DKLUDGELINEMODE -DUSE_TERMIO -DENV_HACK -DSKEY -Dunix
CPPFLAGS+=	-DHAS_CGETENT
CFLAGS+=	-Wall -Wno-unused
LDADD+=		-lcurses
DPADD+=		${LIBCURSES}

.include <bsd.prog.mk>
