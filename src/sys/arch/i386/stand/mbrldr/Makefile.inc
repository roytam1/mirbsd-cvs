# $MirOS: src/sys/arch/i386/stand/mbrldr/Makefile.inc,v 1.3 2005/03/15 17:25:54 tg Exp $

.ifndef MODSRC_SYS_ARCH_I386_STAND_MBRLDR_MAKEFILE_INC
MODSRC_SYS_ARCH_I386_STAND_MBRLDR_MAKEFILE_INC=1

SRCS+=		mbr.S
.PATH:		${.CURDIR}/../mbrldr

NOMAN?=		Yes
INSTALL_STRIP=	# set to empty value
LDFLAGS=	-nostdlib -Ttext 0 -N -x -Bstatic
INSTALL_BIN?=	Yes
DEBUGPROGS=	No

CLEANFILES+=	mbrcode.h

all: mbrcode.h

mbrcode.h: ${PROG}
	print '/* $$Mir''OS$$ */\n/*-\n * Automatically' \
	    'generated, do not edit!\n * ${PROG} Version' \
	    '${V} for ${MACHINE}\n */' >$@
	hexdump -ve '8/1 "0x%02X, " "\n"' ${.ALLSRC} >>$@

.if defined(INSTALL_BIN)
${PROG}: ${OBJS} ${DPADD}
	${LD} ${LDFLAGS} -o ${PROG} ${OBJS} ${LDADD}
	@size ${PROG}
	@cp ${PROG} ${PROG}.elf
	objcopy -O binary ${PROG} ${PROG}.bin
.  if ${INSTALL_BIN:L} == "yes"
	@cp ${PROG}.bin ${PROG}
	@ls -l ${.OBJDIR}/${PROG}
.  endif

disasm: ${PROG}
	ndisasm -b 16 ${PROG}.bin >${.CURDIR}/disasm

CLEANFILES+=	${.CURDIR}/disasm ${PROG}.elf ${PROG}.bin
.endif

.if exists(../Makefile.inc)
.  include "../Makefile.inc"
.endif

.endif
