# $MirOS: contrib/gnu/e3/Makefile,v 1.4 2008/12/30 01:20:29 tg Exp $

PROG=		e3
BINDIR?=	${BSD_PREFIX}/bin
LINKS+=		${BINDIR}/${PROG} ${BINDIR}/e3ws \
		${BINDIR}/${PROG} ${BINDIR}/e3em \
		${BINDIR}/${PROG} ${BINDIR}/e3pi \
		${BINDIR}/${PROG} ${BINDIR}/e3vi \
		${BINDIR}/${PROG} ${BINDIR}/e3ne

SRCS=		e3.asm
NASMFLAGS+=	-felf
NASMFLAGS+=	-i${.CURDIR:Q}/
NASMFLAGS+=	-w+orphan-labels
NASMFLAGS+=	-O7
NASMFLAGS+=	-DMIRBSD

# we use Esc+X instead of Alt-X
NASMFLAGS+=	-DALT_IS_META

LDFLAGS+=	-e _start
LDFLAGS+=	-Bstatic

# exactly one of the following:
NASMFLAGS+=	-DSED
#NASMFLAGS+=	-DEX
#NASMFLAGS+=	-DPERLPIPE

.include <bsd.own.mk>

.ifdef DEBUG
NASMFLAGS+=	-g
.endif

.SUFFIXES: .asm
CLEANFILES+=	${PROG}~

.asm.o:
	nasm ${NASMFLAGS} -o $@ $<

${PROG}: ${OBJS}
	ld ${LDFLAGS} -o $@~ ${OBJS}
	${STRIP} -s -R .comment $@~
	mv -f $@~ $@

.include <bsd.prog.mk>
