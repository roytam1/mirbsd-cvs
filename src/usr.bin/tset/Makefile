# $MirOS$
# $OpenBSD: Makefile,v 1.7 2000/02/20 21:50:18 millert Exp $

PROG=	tset
SRCS=	tset.c dump_entry.c termcap.c
DPADD=	${LIBCURSES}
LDADD=	-lcurses
CURSES= ${.CURDIR}/../../lib/libcurses
TIC= ${.CURDIR}/../tic
CPPFLAGS+= -I${CURSES} -I${TIC} -I${.CURDIR} -I.
CLEANFILES+= termsort.c
.PATH:  ${TIC}
LINKS=	${BINDIR}/tset ${BINDIR}/reset
MLINKS=	tset.1 reset.1

beforedepend: termsort.c

termsort.c: ${TIC}/MKtermsort.sh
	${SHELL} ${TIC}/MKtermsort.sh awk ${CURSES}/Caps >$@

.include <bsd.prog.mk>
