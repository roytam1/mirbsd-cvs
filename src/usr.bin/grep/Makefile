# $MirOS: src/usr.bin/grep/Makefile,v 1.3 2005/03/15 19:23:50 tg Exp $
# $OpenBSD: Makefile,v 1.6 2003/06/25 15:00:04 millert Exp $

PROG=	grep
SRCS=	binary.c file.c grep.c mmfile.c queue.c util.c
LINKS=	${BINDIR}/grep ${BINDIR}/egrep \
	${BINDIR}/grep ${BINDIR}/fgrep \
	${BINDIR}/grep ${BINDIR}/zgrep \
	${BINDIR}/grep ${BINDIR}/zegrep \
	${BINDIR}/grep ${BINDIR}/zfgrep \

MLINKS= grep.1 egrep.1 \
	grep.1 fgrep.1 \
	grep.1 zgrep.1 \
	grep.1 zegrep.1 \
	grep.1 zfgrep.1

CFLAGS+= -Wall
CPPFLAGS+= -DZCONST=const

LDADD=	-lz
DPADD=	${LIBZ}

.include <bsd.prog.mk>
