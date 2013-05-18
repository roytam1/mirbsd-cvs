# $MirOS: src/sys/arch/sparc/stand/bootxx/Makefile,v 1.11 2007/10/16 21:40:58 tg Exp $
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

CLEANFILES+=	${PROG}.{bin,elf} bxinst

all: ${PROG} bxinst

${PROG}: ${PROG}.elf
	elf2aout $@.elf $@ -b

.include <bsd.prog.mk>

${PROG}.bin: ${PROG}
	strip -F a.out-sunos-big -s -o $@ $>

${PROG}.elf: ${OBJS}
	${LD} -N -Ttext ${RELOC} -e start ${OBJS} ${_SOBJS} ${_KOBJS} -o $@
	@size $@

bxinst: ${PROG}.bin bxinst.sh
	eval $$(nm --target=a.out-sunos-big ${PROG} | \
	    sed -n '/_start$$/s/^\([0-9a-fA-F]*\) . \(_.*\)$$/\2=0x\1/p'); \
	typeset -Uui10 ofs tblsz; ((ofs = _block_start - _start + 32)); \
	tblsz=$$(dd if=${PROG}.bin bs=1 skip=$$ofs count=4 2>/dev/null | \
	    hexdump -ve '"0x" 4/1 "%02X"'); \
	sed -e "s@@TBLSZ@@$$tblsz" \
	    -e "s@@PARTONE@@$$(dd bs=1 skip=8 count=$$((ofs - 8)) \
		if=${PROG}.bin 2>/dev/null | hexdump -ve '1/1 "\\\\0%o"')" \
	    -e "s@@PARTTWO@@$$(dd bs=1 skip=$$((ofs + tblsz * 4 + 8)) \
		if=${PROG}.bin 2>/dev/null | hexdump -ve '1/1 "\\\\0%o"')" \
	    <${.CURDIR}/bxinst.sh >$@

srt0.o: srt0.S
	${CC} ${CFLAGS} ${CPPFLAGS} -D_LOCORE -c ${.IMPSRC}

afterinstall:
	${INSTALL} ${INSTALL_COPY} ${INSTALL_STRIP} -o ${BINOWN} -g ${BINGRP} \
	    -m ${BINMODE} bxinst ${DESTDIR}${BINDIR}/bxinst.sparc
