# $MirOS: src/sys/arch/i386/stand/mbr/Makefile.inc,v 1.4 2009/01/31 23:39:55 tg Exp $

.ifndef MODSRC_SYS_ARCH_I386_STAND_MBR_MAKEFILE_INC
MODSRC_SYS_ARCH_I386_STAND_MBR_MAKEFILE_INC=	# defined

SRCS+=		mbr.S
.PATH:		${.CURDIR}/..

NOMAN=		Yes
INSTALL_STRIP=	# empty
LDFLAGS=	-nostdlib -Ttext 0x0600 -N -Bstatic -e _start
CLEANFILES+=	${PROG}.elf ${PROG}.tmp ${.CURDIR}/disasm

${PROG}: ${OBJS} ${DPADD}
	${LD} ${LDFLAGS} -o $@.elf ${OBJS} ${LDADD}
	@size $@.elf
	@objcopy -O binary $@.elf $@

disasm: ${.CURDIR}/disasm

${.CURDIR}/disasm: ${PROG}
#	ndisasm -b 16 $> >$@
	objdump -d -Mintel,i8086 ${PROG}.elf >$@

.if exists(../Makefile.inc)
.  include "../Makefile.inc"
.endif

V=		${REAL_V}
BINMODE=	${SHAREMODE}

.endif
