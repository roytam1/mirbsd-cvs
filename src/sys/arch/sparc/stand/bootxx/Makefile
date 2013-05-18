# $MirOS: src/sys/arch/sparc/stand/bootxx/Makefile,v 1.3 2006/06/16 21:52:52 tg Exp $
# $OpenBSD: Makefile,v 1.7 2003/08/11 06:35:45 deraadt Exp $
# $NetBSD: Makefile,v 1.2 1995/09/30 21:43:38 pk Exp $

.PATH:	${.CURDIR}/../common

PROG=	bootxx

NOMAN=	yes
INSTALL_STRIP=

SRCS=	srt0.S bootxx.c closeall.c dvma.c promdev.c

# pre-built bits of libkern
KOBJS=	__main.o bzero.o urem.o udiv.o
_KOBJS=${KOBJS:S,^,${LIBKERNOBJDIR}/,g}
# pre-built bits of libsa
SOBJS=	alloc.o exit.o printf.o memcpy.o memset.o
_SOBJS=${SOBJS:S,^,${LIBSAOBJDIR}/,g}

CPPFLAGS+=	-I${.CURDIR}/../common -I${.CURDIR}/../../../../arch \
		-I${.CURDIR}/../../../.. -I${.CURDIR}/../../../../lib/libsa \
		-DBOOTXX

CLEANFILES+=	${PROG}.elf

${PROG}: ${OBJS}
	${LD} -N -Ttext ${RELOC} -e start ${OBJS} ${_SOBJS} ${_KOBJS} \
	    -o ${PROG}.elf
	@size ${PROG}.elf
	elf2aout ${PROG}.elf ${PROG} -b

srt0.o: srt0.S
	${CC} ${CFLAGS} ${CPPFLAGS} -D_LOCORE -c ${.IMPSRC}

.include <bsd.prog.mk>
