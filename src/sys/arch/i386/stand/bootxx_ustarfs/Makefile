# $MirOS: src/sys/arch/i386/stand/bootxx_ustarfs/Makefile,v 1.4 2010/01/16 22:34:25 tg Exp $

PROG=		bootxx.tar
SRCS+=		bootxx.S
NOMAN=		Yes
INSTALL_STRIP=	# empty
LDFLAGS=	-nostdlib -Ttext 0xFE00 -N -Bstatic -e _start
CPPFLAGS+=	${DEBUGFLAGS}
CLEANFILES+=	${PROG}.elf ${PROG}.tmp ${.CURDIR}/disasm

all: ${PROG}

${PROG}: ${OBJS} ${DPADD}
	${LD} ${LDFLAGS} -o $@.elf ${OBJS} ${LDADD}
	@size $@.elf
	objcopy -O binary $@.elf $@.tmp
	print -n "$$(${MKSH} ${.CURDIR}/tarcksum $@.tmp)\\0" | \
	    dd of=$@.tmp bs=1 seek=148 conv=notrunc
	mv -f $@.tmp $@

disasm: ${.CURDIR}/disasm

${.CURDIR}/disasm: ${PROG}
	(cat ${PROG}; dd if=/dev/zero count=2 2>&-) | tar -tvvf -
	objdump -dS -Mintel,i8086 ${PROG}.elf >$@

.include <bsd.prog.mk>
BINMODE=	${SHAREMODE}
