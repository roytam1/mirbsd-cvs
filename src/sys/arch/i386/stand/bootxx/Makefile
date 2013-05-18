# $MirOS$

PROG=		bootxx
SRCS+=		bootxx.S
NOMAN=		Yes
INSTALL_STRIP=	# empty
LDFLAGS=	-nostdlib -Ttext 0 -N -Bstatic
CPPFLAGS+=	${DEBUGFLAGS}
CLEANFILES+=	${PROG}.elf ${.CURDIR}/disasm

${PROG}: ${OBJS} ${DPADD}
	${LD} ${LDFLAGS} -o ${PROG}.elf ${OBJS} ${LDADD}
	objcopy -x ${PROG}.elf ${PROG}
	@size ${PROG}
	@ls -l ${.OBJDIR}/${PROG}

disasm: ${.CURDIR}/disasm

${.CURDIR}/disasm: ${PROG}
	objdump -d -Mintel,i8086 ${PROG}.elf >$@

.include <bsd.prog.mk>
