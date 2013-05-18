# $MirOS$

PROG=		unzip
SRCS=		crypt.c envargs.c explode.c extract.c fileio.c \
		globals.c inflate.c list.c match.c process.c \
		ttyio.c unix.c unreduce.c unshrink.c unzip.c zipinfo.c
MAN=		unzip.1 zipgrep.1 zipinfo.1
LINKS=		${BINDIR}/unzip ${BINDIR}/zipinfo

afterinstall:
	${INSTALL} -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${WRKSRC}/unix/zipgrep ${DESTDIR}${BINDIR}/

.include <bsd.prog.mk>
