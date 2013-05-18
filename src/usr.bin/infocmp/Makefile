# $MirOS$

PROG=		infocmp
DPADD+=		${LIBCURSES}
LDADD+=		-lcurses

NCMANSRCS+=	infocmp.1m

.include <bsd.own.mk>

LIBNCDIR?=	${BSDSRCDIR}/lib/libncurses
.include "${LIBNCDIR}/Makefile.inc"

CPPFLAGS+=	-I${NCSRCDIR}/progs

.PATH: ${NCSRCDIR}/progs

SRCS+=		dump_entry.c
SRCS+=		infocmp.c

GENERATED=	ncurses_def.h parametrized.h termsort.c
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

.include <bsd.prog.mk>

dump_entry.o: termsort.c
${OBJS}: ${GENERATED:Ntermsort.c}
