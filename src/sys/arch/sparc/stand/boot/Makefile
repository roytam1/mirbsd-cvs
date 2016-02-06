# $MirOS: src/sys/arch/sparc/stand/boot/Makefile,v 1.16 2009/04/17 18:57:07 tg Exp $
# $OpenBSD: Makefile,v 1.12 2003/08/11 06:35:45 deraadt Exp $
# $NetBSD: Makefile,v 1.2 1995/09/30 21:43:38 pk Exp $

.PATH:	${.CURDIR}/../common
S=	${.CURDIR}/../../../..

PROG=		boot
NOMAN=		yes
INSTALL_STRIP=	#empty
SMALL_BOOT?=	No
CLEANFILES+=	${PROG}~ ${PROG}.aout ${PROG}.elf
SRCS=		srt0.S boot.c conf.c dvma.c promdev.c
.if ${SMALL_BOOT:L} == "no"
SRCS+=		net.c netif_sun.c
.endif
SRCS+=		loadfile.c

CPPFLAGS+=	-I${.CURDIR}/../common -I${.CURDIR}/../../../../arch \
		-I${.CURDIR}/../../../.. -I${.CURDIR}/../../../../lib/libsa
.if ${SMALL_BOOT:L} != "no"
CPPFLAGS+=	-DSMALL_BOOT
CPPFLAGS+=	-DSPARC_BOOT_ELF
V=		${REAL_V}-small
.else
CPPFLAGS+=	-DSPARC_BOOT_AOUT -DSPARC_BOOT_ELF
.endif

${PROG}: ${PROG}.elf
	rm -f ${PROG} ${PROG}~ ${PROG}.aout
	# create stripped version of loader, for later patching
	objcopy -S ${PROG}.elf ${PROG}~
	elf2aout ${PROG}~ ${PROG}.aout -b
.if ${SMALL_BOOT:L} == "no"
	# create unstripped version of loader, for symbol retrieval
	rm -f ${PROG}~
	elf2aout ${PROG}.elf ${PROG}~ -b
	# write offset to path to default kernel file into loader
	set -A sect_text -- $$(objdump -wh --target=a.out-sunos-big \
	    ${PROG}~ | fgrep .text); (( fofs_text = 0x$${sect_text[5]} )); \
	nm --target=a.out-sunos-big ${PROG}~ |& \
	while read -p adr typ sym; do \
		[[ $$sym = _@(__defkernel|_aout_advecs_start|start) ]] || continue; \
		eval typeset -i10 sym$$sym=0x\$$adr; \
	done; \
	typeset -Z11 -Uui16 ofs nofs advecs; \
	(( nofs = -(ofs = sym___defkernel - sym_start + fofs_text) )); \
	(( advecs = sym__aout_advecs_start - sym_start + fofs_text )); \
	: check if advecs are still at the correct place in ${PROG}.aout; \
	tstval=$$(dd if=${PROG}.aout bs=1 count=4 skip=$$((advecs)) | \
	    hexdump -ve '1/1 "%02X"'); [[ $$tstval = 20355601 ]] || exit 1; \
	print -n "$$(sed 's/\(..\)/\\x\1/g' <<<"$${nofs#16#}$${ofs#16#}")" | \
	    dd conv=notrunc bs=1 seek=$$((advecs + 4)) of=${PROG}.aout
.endif
	# sort-of install the patched a.out file
	mv -f ${PROG}.aout ${PROG}

srt0.o: srt0.S
	${CC} ${CFLAGS} ${CPPFLAGS} -D_LOCORE -c ${.IMPSRC}

.include <bsd.prog.mk>
BINMODE=	${SHAREMODE}

${PROG}.elf: ${OBJS} ${DLIBSA}
	${LD} -N -Ttext ${RELOC2} -e start ${OBJS} ${LLIBSA} -o $@
	@size $@
