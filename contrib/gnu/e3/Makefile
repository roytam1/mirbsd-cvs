# $MirOS$

PROG=		e3
BINDIR?=	${BSD_PREFIX}/bin
SRCS=		e3.asm
NASMFLAGS+=	-felf
NASMFLAGS+=	-i${.CURDIR:Q}/
NASMFLAGS+=	-w+orphan-labels
NASMFLAGS+=	-O7
NASMFLAGS+=	-DMIRBSD

LDFLAGS+=	-s
LDFLAGS+=	-e _start
LDFLAGS+=	-Bstatic

# exactly one of the following:
NASMFLAGS+=	-DSED
#NASMFLAGS+=	-DEX
#NASMFLAGS+=	-DPERLPIPE

.SUFFIXES: .asm
CLEANFILES+=	${PROG}~

.asm.o:
	nasm ${NASMFLAGS} -o $@ $<

${PROG}: ${OBJS}
	ld ${LDFLAGS} -o $@~ ${OBJS}
	strip -s -R .comment $@~
	mv -f $@~ $@

.include <bsd.prog.mk>
