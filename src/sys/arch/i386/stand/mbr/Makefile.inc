# $MirOS: src/sys/arch/i386/stand/mbr/Makefile.inc,v 1.2 2008/08/01 12:41:42 tg Exp $

.ifndef MODSRC_SYS_ARCH_I386_STAND_MBR_MAKEFILE_INC
MODSRC_SYS_ARCH_I386_STAND_MBR_MAKEFILE_INC=	# defined

SRCS+=		mbr.S
.PATH:		${.CURDIR}/..

NOMAN=		Yes
INSTALL_STRIP=	# empty
LDFLAGS=	-nostdlib -Ttext 0 -N -Bstatic
CLEANFILES+=	${PROG}.elf ${PROG}.tmp ${.CURDIR}/disasm

${PROG}: ${OBJS} ${DPADD}
	${LD} ${LDFLAGS} -o $@.elf ${OBJS} ${LDADD}
	@objcopy -O binary $@.elf $@.tmp
	@dd if=${PROG}.tmp bs=1 skip=0x0600 of=$@ 2>&-
	@size --target=binary $@

disasm: ${.CURDIR}/disasm

${.CURDIR}/disasm: ${PROG}
#	ndisasm -b 16 $> >$@
	objdump -d -Mintel,i8086 ${PROG}.elf >$@

.if exists(../Makefile.inc)
.  include "../Makefile.inc"
.endif

V=		${REAL_V}

.endif
