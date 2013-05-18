# $MirOS: src/usr.bin/less/less/Makefile,v 1.1 2005/03/13 18:56:34 tg Exp $

PROG=		less
SRCS=		brac.c ch.c charset.c cmdbuf.c command.c decode.c edit.c \
		filename.c forwback.c help.c ifile.c input.c jump.c line.c \
		linenum.c lsystem.c main.c mark.c optfunc.c option.c \
		opttbl.c os.c output.c position.c prompt.c screen.c \
		search.c signal.c tags.c ttyin.c version.c
DPADD+=		${LIBCURSES}
LDADD+=		-lcurses
LINKS=		${BINDIR}/${PROG} ${BINDIR}/more \
		${BINDIR}/${PROG} ${BINDIR}/page
MLINKS=		less.1 more.1 \
		less.1 page.1

afterinstall:
	install -c -o ${BINOWN} -g ${BINGRP} -m ${NONBINMODE} \
	    ${TOP}/less.hlp ${DESTDIR}${HELPFILE}

.include <bsd.prog.mk>
