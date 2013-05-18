# $MirOS: src/sys/arch/sparc/stand/bootxx/Makefile,v 1.16 2008/08/01 18:45:40 tg Exp $
# $OpenBSD: Makefile,v 1.7 2003/08/11 06:35:45 deraadt Exp $
# $NetBSD: Makefile,v 1.2 1995/09/30 21:43:38 pk Exp $

.PATH:	${.CURDIR}/../common
S=	${.CURDIR}/../../../..

PROG=		bootxx
NOMAN=		yes
INSTALL_STRIP=	#empty
CLEANFILES+=	${PROG}~ bxinst

SRCS=		srt0.S bootxx.c btable.S closeall.c dvma.c promdev.c

CPPFLAGS+=	-I${.CURDIR}/../common -I${.CURDIR}/../../../../arch \
		-I${.CURDIR}/../../../.. -I${.CURDIR}/../../../../lib/libsa \
		-DBOOTXX

all: ${PROG} bxinst

${PROG}: ${OBJS} ${DLIBSA}
	${LD} -N -Ttext ${RELOC2} --format a.out-sparc-netbsd \
	    -e start ${OBJS} ${LLIBSA} -o $@~
	@size $@~
	strip -x $@~
	elf2aout $@~ $@ -b

bxinst: ${.CURDIR}/mkbxinst.sh ${PROG}
	${MKSH} ${.CURDIR}/mkbxinst.sh ${PROG} >$@

srt0.o: srt0.S
	${CC} ${CFLAGS} ${CPPFLAGS} -D_LOCORE -c ${.IMPSRC}

.include <bsd.prog.mk>
