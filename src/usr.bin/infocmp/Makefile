# $MirOS$
# $OpenBSD: Makefile,v 1.2 2000/02/20 21:50:18 millert Exp $

PROG=	infocmp
SRCS=	infocmp.c dump_entry.c
MAN=	infocmp.1tbl
DPADD=	${LIBCURSES}
LDADD=	-lcurses
CURSES= ${.CURDIR}/../../lib/libcurses
TIC=	${.CURDIR}/../tic
CPPFLAGS+=	-I${CURSES} -I${TIC} -I.
CLEANFILES+=	termsort.c
.PATH:  ${TIC}

beforedepend: termsort.c

termsort.c: ${TIC}/MKtermsort.sh
	${SHELL} ${TIC}/MKtermsort.sh awk ${CURSES}/Caps >${.TARGET}

.include <bsd.prog.mk>
