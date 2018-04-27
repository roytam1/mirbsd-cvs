# $MirOS: src/sys/arch/sparc/stand/bootxx/Makefile,v 1.21 2010/01/16 23:25:53 tg Exp $
# $OpenBSD: Makefile,v 1.7 2003/08/11 06:35:45 deraadt Exp $
# $NetBSD: Makefile,v 1.2 1995/09/30 21:43:38 pk Exp $

.PATH:	${.CURDIR}/../common
S=	${.CURDIR}/../../../..

PROG=		bootxx
NOMAN=		yes
INSTALL_STRIP=	#empty
CLEANFILES+=	${PROG}.elf bxinst

SRCS=		srt0.S bootxx.c btable.S closeall.c dvma.c promdev.c

CPPFLAGS+=	-I${.CURDIR}/../common -I${.CURDIR}/../../../../arch \
		-I${.CURDIR}/../../../.. -I${.CURDIR}/../../../../lib/libsa \
		-DBOOTXX

# bootxx has a maximum size of 7680 bytes, which is exactly
# 15 512-byte sectors and checked by our mkbxinst.sh

all: ${PROG} bxinst

${PROG}: ${PROG}.elf
	elf2aout ${PROG}.elf ${PROG} -b

bxinst: ${.CURDIR}/mkbxinst.sh ${PROG}
	BSDSRCDIR=${BSDSRCDIR:Q} ${MKSH} ${.CURDIR}/mkbxinst.sh ${PROG} >$@

srt0.o: srt0.S
	${CC} ${CFLAGS} ${CPPFLAGS} -D_LOCORE -c ${.IMPSRC}

.include <bsd.prog.mk>
BINMODE=	${SHAREMODE}

${PROG}.elf: ${OBJS} ${DLIBSA}
	${LD} -N -Ttext ${RELOC} -e start ${OBJS} ${LLIBSA} -o $@
	@size $@
