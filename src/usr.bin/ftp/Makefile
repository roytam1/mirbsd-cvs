# $MirOS: src/usr.bin/ftp/Makefile,v 1.3 2005/04/13 16:10:27 tg Exp $
# $OpenBSD: Makefile,v 1.20 2003/11/20 23:32:26 tedu Exp $

.include <bsd.own.mk>

# Uncomment the following to provide defaults for gate-ftp operation
#CPPFLAGS+=	-DGATE_SERVER=\"ftp-gw.host\" # -DGATE_PORT=21

.if (defined(USE_SOCKS) && ${USE_SOCKS:L} == "yes")
LOCALBASE?=	/usr/mpkg
CPPFLAGS+=	-DSOCKS -I${LOCALBASE}/include
LDADD+=		-lsocks5
.endif

PROG=	ftp
SRCS=	cmds.c cmdtab.c complete.c domacro.c fetch.c ftp.c main.c ruserpass.c \
	stringlist.c util.c

.ifndef NO_INET6
CPPFLAGS+=	-DINET6
.endif
.ifdef SMALL
CPPFLAGS+=	-DSMALL
.else
LDADD+=		-ledit
DPADD+=		${LIBEDIT}
.endif

LDADD+=		-lcurses -lutil
DPADD+=		${LIBCURSES} ${LIBUTIL}

CFLAGS+=	-Wall
LDSTATIC=	${STATIC}

.include <bsd.prog.mk>
