# $MirOS: src/sys/arch/i386/stand/bootxx/Makefile,v 1.4 2008/10/21 18:50:59 tg Exp $

PROG=		bootxx
SRCS+=		bootxx.S
NOMAN=		Yes
INSTALL_STRIP=	# empty
LDFLAGS=	-nostdlib -Ttext 0xFE00 -N -Bstatic -e _start
CPPFLAGS+=	${DEBUGFLAGS}
CLEANFILES+=	${PROG}~ ${.CURDIR}/disasm bxinst

all: ${PROG} bxinst

${PROG}: ${OBJS} ${DPADD}
	${LD} ${LDFLAGS} -o $@~ ${OBJS} ${LDADD}
	@size $@~
	objcopy -x $@~ $@

disasm: ${.CURDIR}/disasm

bxinst: ${.CURDIR}/mkbxinst.sh ${PROG}
	${MKSH} ${.CURDIR}/mkbxinst.sh ${PROG} >$@

${.CURDIR}/disasm: ${PROG}
	objdump -dS -Mintel,i8086 ${PROG}~ >$@

.include <bsd.prog.mk>
