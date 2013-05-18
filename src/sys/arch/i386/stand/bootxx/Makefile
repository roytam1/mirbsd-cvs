# $MirOS: src/sys/arch/i386/stand/bootxx/Makefile,v 1.5 2009/01/31 18:51:19 tg Exp $

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

BOOT_TYPE?=	bsd
.if ${BOOT_TYPE:L} == "grub"
CPPFLAGS+=	-USA_LINKSEG -DSA_LINKSEG=0x0800 -DBOOT_GRUB
.endif
