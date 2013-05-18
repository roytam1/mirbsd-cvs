# $MirOS$

PROG=		tic
LINKS=		${BINDIR}/tic ${BINDIR}/captoinfo \
		${BINDIR}/tic ${BINDIR}/infotocap
DPADD+=		${LIBCURSES}
LDADD+=		-lcurses

NCMANSRCS+=	captoinfo.1m
NCMANSRCS+=	infotocap.1m
NCMANSRCS+=	tic.1m

.include <bsd.own.mk>

LIBNCDIR?=	${BSDSRCDIR}/lib/libncurses
.include "${LIBNCDIR}/Makefile.inc"

CPPFLAGS+=	-I${NCSRCDIR}/progs
CPPFLAGS+=	-D'PROG_CAPTOINFO="captoinfo"' \
		-D'PROG_INFOTOCAP="infotocap"' \
		-D'PROG_RESET="reset"' -D'PROG_INIT="init"'

.PATH: ${NCSRCDIR}/progs

SRCS+=		dump_entry.c
SRCS+=		tic.c

GENERATED=	ncurses_def.h parametrized.h termsort.c transform.h
CLEANFILES+=	${GENERATED}

beforedepend: ${GENERATED}

ncurses_def.h: ${NCSRCDIR}/include/MKncurses_def.sh \
    ${NCSRCDIR}/include/ncurses_defs
	AWK=${AWK:Q} ${MKSH} ${NCSRCDIR}/include/MKncurses_def.sh \
	    ${NCSRCDIR}/include/ncurses_defs >$@

parametrized.h: ${NCSRCDIR}/include/MKparametrized.sh ${NCSRCDIR}/include/Caps
	AWK=${AWK:Q} ${MKSH} ${NCSRCDIR}/include/MKparametrized.sh \
	    ${NCSRCDIR}/include/Caps >$@

termsort.c: ${NCSRCDIR}/progs/MKtermsort.sh ${NCSRCDIR}/include/Caps
	${MKSH} ${NCSRCDIR}/progs/MKtermsort.sh ${AWK:Q} \
	    ${NCSRCDIR}/include/Caps >$@

transform.h:
	print -n >$@

.include <bsd.prog.mk>

dump_entry.o: termsort.c
${OBJS}: ${GENERATED:Ntermsort.c}
