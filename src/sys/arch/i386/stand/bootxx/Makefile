# $MirOS: src/sys/arch/i386/stand/bootxx/Makefile,v 1.3 2007/10/20 21:28:40 tg Exp $

PROG=		bootxx
SRCS+=		bootxx.S
NOMAN=		Yes
INSTALL_STRIP=	# empty
CPPFLAGS+=	${DEBUGFLAGS}
CLEANFILES+=	${PROG}~ ${.CURDIR}/disasm bxinst

all: ${PROG} bxinst

${PROG}: ${OBJS} ${DPADD}
	${LD} -N -Ttext 0 -e _start ${OBJS} ${LDADD} -o $@~
	@size $@~
	objcopy -x $@~ $@

disasm: ${.CURDIR}/disasm

bxinst: ${.CURDIR}/mkbxinst.sh ${PROG}
	${MKSH} ${.CURDIR}/mkbxinst.sh ${PROG} >$@

${.CURDIR}/disasm: ${PROG}
	objdump -dS -Mintel,i8086 ${PROG}~ >$@

.include <bsd.prog.mk>
