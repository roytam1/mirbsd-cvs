# $MirOS: src/usr.bin/awk/Makefile,v 1.2 2005/03/13 18:32:41 tg Exp $
# $OpenBSD: Makefile,v 1.7 2004/12/30 01:52:48 millert Exp $

PROG=		awk
LINKS=		${BINDIR}/awk ${BINDIR}/nawk
SRCS=		awkgram.y b.c lex.c lib.c main.c parse.c proctab.c run.c tran.c
LDADD=		-lm
DPADD=		${LIBM}
CLEANFILES+=	proctab.c maketab
CPPFLAGS+=	-I. -DHAS_ISBLANK -DNDEBUG
HOSTCFLAGS?=	${CFLAGS}
MLINKS=		awk.1 nawk.1

# This just gets installed verbatim
.if make(install)
SUBDIR+=	 USD.doc
.endif

proctab.c: maketab
	./maketab >proctab.c

maketab: awkgram.h maketab.c
	${HOSTCC} ${HOSTCFLAGS} ${CPPFLAGS} ${.CURDIR}/maketab.c -o $@

.include <bsd.prog.mk>
