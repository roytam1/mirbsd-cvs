# $MirOS: src/usr.bin/ftp/Makefile,v 1.6 2007/07/15 20:01:07 tg Exp $
# $OpenBSD: Makefile,v 1.22 2007/06/13 13:52:26 pyr Exp $

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
	cookie.c stringlist.c util.c

.ifndef NO_INET6
CPPFLAGS+=	-DINET6
.endif
.ifdef SMALL
CPPFLAGS+=	-DSMALL
.else
LDADD+=		-ledit -lssl -lcrypto
DPADD+=		${LIBEDIT} ${LIBSSL} ${LIBCRYPTO}
.endif

LDADD+=		-lcurses -lutil
DPADD+=		${LIBCURSES} ${LIBUTIL}

CFLAGS+=	-Wall

.include <bsd.prog.mk>
