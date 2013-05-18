# $MirOS: src/sys/arch/i386/stand/bootxx/Makefile,v 1.2 2007/10/20 18:22:40 tg Exp $

PROG=		bootxx
SRCS+=		bootxx.S
NOMAN=		Yes
INSTALL_STRIP=	# empty
LDFLAGS=	-nostdlib -Ttext 0 -N -Bstatic
CPPFLAGS+=	${DEBUGFLAGS}
CLEANFILES+=	${PROG}.elf ${.CURDIR}/disasm bxinst

all: ${PROG} bxinst

${PROG}: ${PROG}.elf
	objcopy -x $@.elf $@

.include <bsd.prog.mk>

LINK.prog=	:

${PROG}.elf: ${OBJS} ${DPADD}
	${LD} ${LDFLAGS} -o ${PROG}.elf ${OBJS} ${LDADD}

disasm: ${.CURDIR}/disasm

bxinst: ${.CURDIR}/mkbxinst.sh ${PROG}.elf
	${MKSH} ${.CURDIR}/mkbxinst.sh ${PROG}.elf >$@

${.CURDIR}/disasm: ${PROG}
	objdump -d -Mintel,i8086 ${PROG}.elf >$@

.include <bsd.prog.mk>
