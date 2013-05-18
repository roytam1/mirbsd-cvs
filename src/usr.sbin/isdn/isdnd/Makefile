# $MirOS: src/usr.sbin/isdn/isdnd/Makefile,v 1.2 2005/03/13 19:17:03 tg Exp $
# $NetBSD: Makefile,v 1.5 2001/12/31 19:41:37 thorpej Exp $

PROG=		isdnd
SRCS=		rc_parse.y rc_scan.l main.c rc_config.c log.c curses.c	\
		process.c rates.c msghdl.c fsm.c support.c timer.c	\
		exec.c dial.c monitor.c pcause.c controller.c alias.c	\
		holiday.c
MAN=		isdnd.8 isdnd.rc.5 isdnd.rates.5 isdnd.acct.5
CLEANFILES+=	rc_parse.c rc_parse.h

CPPFLAGS+=	-I${.CURDIR}/../isdnmonitor -I${.CURDIR}/../isdntel -I.

LDADD+=		-ly -ll
DPADD+=		${LIBY} ${LIBL}

beforedepend: rc_parse.h

rc_parse.c rc_parse.h: rc_parse.y
	${YACC} -d ${.ALLSRC}
	mv y.tab.c rc_parse.c
	mv y.tab.h rc_parse.h

.include <bsd.prog.mk>

.if defined(_SMALL) && ${_SMALL:L} == "yes"
I4B_WITHOUT_CURSES=1
.  undef I4B_EXTERNAL_MONITOR
.else
# compile debug support
CPPFLAGS+=	-DDEBUG
.endif

.if !defined(I4B_WITHOUT_CURSES)
CPPFLAGS+=	-DUSE_CURSES
LDADD+=		-lcurses
LDADD+=		-ltermlib
DPADD+=		${LIBCURSES} ${LIBTERMLIB}
.endif

.if defined(I4B_EXTERNAL_MONITOR)
CPPFLAGS+=	-DI4B_EXTERNAL_MONITOR
.  if defined(I4B_NOTCPIP_MONITOR)
CPPFLAGS+=	-DI4B_NOTCPIP_MONITOR
.  endif
.endif
