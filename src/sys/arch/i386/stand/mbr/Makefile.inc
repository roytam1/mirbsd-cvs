# $MirOS: src/sys/arch/i386/stand/mbr/Makefile.inc,v 1.1 2007/02/26 00:13:27 tg Exp $

.ifndef MODSRC_SYS_ARCH_I386_STAND_MBR_MAKEFILE_INC
MODSRC_SYS_ARCH_I386_STAND_MBR_MAKEFILE_INC=	# defined

SRCS+=		mbr.S
.PATH:		${.CURDIR}/..

NOMAN=		Yes
INSTALL_STRIP=	# empty
LDFLAGS=	-nostdlib -Ttext 0 -N -Bstatic
CLEANFILES+=	${PROG}.elf ${.CURDIR}/disasm

${PROG}: ${OBJS} ${DPADD}
	${LD} ${LDFLAGS} -o ${PROG} ${OBJS} ${LDADD}
	@size ${PROG}
	mv ${PROG} ${PROG}.elf
	objcopy -O binary ${PROG}.elf ${PROG}
	@ls -l ${.OBJDIR}/${PROG}

disasm: ${.CURDIR}/disasm

${.CURDIR}/disasm: ${PROG}
#	ndisasm -b 16 $> >$@
	objdump -d -Mintel,i8086 ${PROG}.elf >$@

.if exists(../Makefile.inc)
.  include "../Makefile.inc"
.endif

V=		${REAL_V}

.endif
