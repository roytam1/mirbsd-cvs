# $MirOS: src/sys/arch/sparc/stand/bootxx/Makefile,v 1.15 2007/10/20 20:24:41 tg Exp $
# $OpenBSD: Makefile,v 1.7 2003/08/11 06:35:45 deraadt Exp $
# $NetBSD: Makefile,v 1.2 1995/09/30 21:43:38 pk Exp $

.PATH:	${.CURDIR}/../common
S=	${.CURDIR}/../../../..

PROG=		bootxx
NOMAN=		yes
INSTALL_STRIP=	#empty
SRCS=		srt0.S bootxx.c btable.S closeall.c dvma.c promdev.c

CPPFLAGS+=	-I${.CURDIR}/../common -I${.CURDIR}/../../../../arch \
		-I${.CURDIR}/../../../.. -I${.CURDIR}/../../../../lib/libsa \
		-DBOOTXX

CLEANFILES+=	${PROG}.{bin,elf} bxinst

all: ${PROG} bxinst

${PROG}: ${PROG}.elf
	elf2aout $@.elf $@ -b

.include <bsd.prog.mk>

LINK.prog=	:

${PROG}.elf: ${OBJS}
	${LD} -N -Ttext ${RELOC} -e start ${OBJS} ${LLIBSA} -o $@

bxinst: ${.CURDIR}/mkbxinst.sh ${PROG}
	${MKSH} ${.CURDIR}/mkbxinst.sh ${PROG} >$@

srt0.o: srt0.S
	${CC} ${CFLAGS} ${CPPFLAGS} -D_LOCORE -c ${.IMPSRC}
