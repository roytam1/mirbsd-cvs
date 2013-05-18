# $MirOS: src/sys/arch/sparc/stand/bootxx/Makefile,v 1.7 2007/10/16 20:45:28 tg Exp $
# $OpenBSD: Makefile,v 1.7 2003/08/11 06:35:45 deraadt Exp $
# $NetBSD: Makefile,v 1.2 1995/09/30 21:43:38 pk Exp $

.PATH:	${.CURDIR}/../common
S=	${.CURDIR}/../../../..

PROG=	bootxx

NOMAN=	yes
INSTALL_STRIP=

SRCS=	srt0.S bootxx.c btable.S closeall.c dvma.c promdev.c

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

CLEANFILES+=	${PROG}.bin ${PROG}.ofs
mkbin: .PHONY ${PROG}
	strip -F a.out-sunos-big -s -o ${PROG}.bin ${PROG}
	print -n '\01\03\01\07\060\0200\0\07' | \
	    dd of=${PROG}.bin conv=notrunc 2>/dev/null
	eval $$(nm --target=a.out-sunos-big ${PROG} | \
	    sed -n '/_start$$/s/^\([0-9a-fA-F]*\) . \(_.*\)$$/\2=0x\1/p'); \
	typeset -Uui16 ofs; ((ofs = _block_start - _start + 32)); \
	print $$((ofs)) 0x$${ofs#16#} >${PROG}.ofs

srt0.o: srt0.S
	${CC} ${CFLAGS} ${CPPFLAGS} -D_LOCORE -c ${.IMPSRC}

.include <bsd.prog.mk>
