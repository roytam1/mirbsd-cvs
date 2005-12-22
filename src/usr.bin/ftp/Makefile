# $MirOS: src/usr.bin/ftp/Makefile,v 1.2 2005/03/13 18:32:59 tg Exp $
# $OpenBSD: Makefile,v 1.20 2003/11/20 23:32:26 tedu Exp $

# Define SMALL to disable command line editing
#CPPFLAGS+=	-DSMALL

# Uncomment the following to provide defaults for gate-ftp operation
#CPPFLAGS+=	-DGATE_SERVER=\"ftp-gw.host\" # -DGATE_PORT=21

.if (defined(USE_SOCKS) && ${USE_SOCKS:L} == "yes")
CPPFLAGS+=	-DSOCKS -I/usr/local/include
LDADD+=		-lsocks5
.endif

PROG=	ftp
SRCS=	cmds.c cmdtab.c complete.c domacro.c fetch.c ftp.c main.c ruserpass.c \
	stringlist.c util.c

.ifndef NO_INET6
CPPFLAGS+=	-DINET6
.endif
CFLAGS+=	-Wall

LDADD+=		-ledit -lcurses -lutil
DPADD+=		${LIBEDIT} ${LIBCURSES} ${LIBUTIL}
LDSTATIC=	${STATIC}

.include <bsd.prog.mk>
