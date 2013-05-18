# $MirOS: src/sys/arch/sparc/stand/bootxx/Makefile,v 1.17 2008/10/21 18:51:00 tg Exp $
# $OpenBSD: Makefile,v 1.7 2003/08/11 06:35:45 deraadt Exp $
# $NetBSD: Makefile,v 1.2 1995/09/30 21:43:38 pk Exp $

.PATH:	${.CURDIR}/../common
S=	${.CURDIR}/../../../..

PROG=		bootxx
NOMAN=		yes
INSTALL_STRIP=	#empty
CLEANFILES+=	${PROG}~ ${PROG}.elf ${PROG}.unstripped bxinst

SRCS=		srt0.S bootxx.c btable.S closeall.c dvma.c promdev.c

CPPFLAGS+=	-I${.CURDIR}/../common -I${.CURDIR}/../../../../arch \
		-I${.CURDIR}/../../../.. -I${.CURDIR}/../../../../lib/libsa \
		-DBOOTXX

all: ${PROG} bxinst

${PROG}: ${PROG}.elf
	objcopy -S ${PROG}.elf ${PROG}~
	elf2aout ${PROG}~ ${PROG} -b

${PROG}.unstripped: ${PROG}.elf
	elf2aout ${PROG}.elf ${PROG}.unstripped -b

bxinst: ${.CURDIR}/mkbxinst.sh ${PROG}.unstripped
	${MKSH} ${.CURDIR}/mkbxinst.sh ${PROG}.unstripped >$@

srt0.o: srt0.S
	${CC} ${CFLAGS} ${CPPFLAGS} -D_LOCORE -c ${.IMPSRC}

.include <bsd.prog.mk>

${PROG}.elf: ${OBJS} ${DLIBSA}
	${LD} -N -Ttext ${RELOC2} -e start ${OBJS} ${LLIBSA} -o $@
	@size $@
