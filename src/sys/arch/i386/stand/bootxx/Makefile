# $MirOS: src/sys/arch/i386/stand/bootxx/Makefile,v 1.1 2007/02/26 02:11:32 tg Exp $

PROG=		bootxx
SRCS+=		bootxx.S
NOMAN=		Yes
INSTALL_STRIP=	# empty
LDFLAGS=	-nostdlib -Ttext 0 -N -Bstatic
CPPFLAGS+=	${DEBUGFLAGS}
CLEANFILES+=	${PROG}.elf ${.CURDIR}/disasm

all: ${PROG}

${PROG}: ${PROG}.elf
	objcopy -x $@.elf $@

.include <bsd.prog.mk>

LINK.prog=	:

${PROG}.elf: ${OBJS} ${DPADD}
	${LD} ${LDFLAGS} -o ${PROG}.elf ${OBJS} ${LDADD}

disasm: ${.CURDIR}/disasm

${.CURDIR}/disasm: ${PROG}
	objdump -d -Mintel,i8086 ${PROG}.elf >$@

.include <bsd.prog.mk>
