# $MirOS: src/usr.bin/awk/Makefile,v 1.3 2007/04/28 00:12:46 tg Exp $
# $OpenBSD: Makefile,v 1.14 2013/08/18 22:06:44 miod Exp $

PROG=		awk
SRCS=		awkgram.y b.c lex.c lib.c main.c parse.c proctab.c run.c tran.c
LDADD=		-lm
DPADD=		${LIBM}
CLEANFILES+=	proctab.c maketab
CPPFLAGS+=	-I. -DHAS_ISBLANK -DNDEBUG
HOSTCFLAGS?=	${CFLAGS}

CFLAGS_b.o+=	-Wno-cast-qual
CFLAGS_run.o+=	-Wno-bad-function-cast
CFLAGS_run.o+=	-Wno-unused-parameter

# This just gets installed verbatim
.if make(install)
SUBDIR+=	 USD.doc
.endif

proctab.c: maketab
	./maketab >proctab.c

maketab: awkgram.h maketab.c
	${HOSTCC} ${HOSTCFLAGS} ${CPPFLAGS} ${.CURDIR}/maketab.c -o $@

.include <bsd.prog.mk>
