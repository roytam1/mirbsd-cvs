# $MirOS: src/sys/arch/i386/stand/bootxx/Makefile,v 1.12 2009/06/29 20:32:38 tg Exp $

PROG=		bootxx
SRCS+=		bootxx.S
NOMAN=		Yes
INSTALL_STRIP=	# empty
LDFLAGS=	-nostdlib -Ttext 0xFE00 -N -Bstatic -e _start
CPPFLAGS+=	${DEBUGFLAGS}
CLEANFILES+=	${PROG}~ ${.CURDIR}/disasm bxinst bootgrub.mksh

all: ${PROG} bxinst

${PROG}: ${OBJS} ${DPADD}
	${LD} ${LDFLAGS} -o $@~ ${OBJS} ${LDADD}
	@size $@~
	objcopy -x -R .comment $@~ $@

disasm: ${.CURDIR}/disasm

bxinst: ${.CURDIR}/mkbxinst.sh ${PROG}
	${MKSH} ${.CURDIR}/mkbxinst.sh ${PROG}~ >$@

${.CURDIR}/disasm: ${PROG}
	objdump -dS -Mintel,i8086 ${PROG}~ >$@

.include <bsd.prog.mk>

BOOT_TYPE?=	bsd
.if (${BOOT_TYPE:L} == "grub") || (${BOOT_TYPE:L} == "grubfat")
CPPFLAGS+=	-USA_LINKSEG -DSA_LINKSEG=0x0800 -DBOOT_GRUB
.  if ${BOOT_TYPE:L} == "grubfat"
CPPFLAGS+=	BPB_SPACE
.  endif

all: boot${BOOT_TYPE:L}.mksh

boot${BOOT_TYPE:L}.mksh: bxinst
	sed \
	    -e 's/\$$Mir''OS.*\$$/$$I''d$$/' \
	    -e '/^. Self-inst/s!MirOS BSD/i386!GNU GRUB2 on i386-pc!' \
	    $> >$@
.endif
