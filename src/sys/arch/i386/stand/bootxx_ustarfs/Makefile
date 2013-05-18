# $MirOS: src/sys/arch/i386/stand/bootxx/Makefile,v 1.16 2009/06/29 20:50:59 tg Exp $

PROG=		bootxx_ustarfs
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
	printf '%s\0' "$$(${MKSH} ${.CURDIR}/tarcksum $@.tmp)" | \
	    dd of=$@.tmp bs=1 seek=148 conv=notrunc
	mv -f $@.tmp $@

disasm: ${.CURDIR}/disasm

${.CURDIR}/disasm: ${PROG}
	(cat ${PROG}; dd if=/dev/zero count=2 2>&-) | tar -tvvf -
	objdump -dS -Mintel,i8086 ${PROG}.elf >$@

.include <bsd.prog.mk>
