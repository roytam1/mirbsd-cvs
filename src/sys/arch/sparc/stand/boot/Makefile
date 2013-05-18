# $MirOS: src/sys/arch/sparc/stand/boot/Makefile,v 1.11 2009/02/01 16:12:30 tg Exp $
# $OpenBSD: Makefile,v 1.12 2003/08/11 06:35:45 deraadt Exp $
# $NetBSD: Makefile,v 1.2 1995/09/30 21:43:38 pk Exp $

.PATH:	${.CURDIR}/../common
S=	${.CURDIR}/../../../..

PROG=		boot
NOMAN=		yes
INSTALL_STRIP=	#empty
SMALL_BOOT?=	No
CLEANFILES+=	${PROG}~

SRCS=		srt0.S boot.c conf.c dvma.c promdev.c
.if ${SMALL_BOOT:L} == "no"
SRCS+=		net.c netif_sun.c
.endif
SRCS+=		loadfile.c

CPPFLAGS+=	-I${.CURDIR}/../common -I${.CURDIR}/../../../../arch \
		-I${.CURDIR}/../../../.. -I${.CURDIR}/../../../../lib/libsa \
		-DSPARC_BOOT_AOUT -DSPARC_BOOT_ELF
.if ${SMALL_BOOT:L} != "no"
CPPFLAGS+=	-DSMALL_BOOT
V=		${REAL_V}-small
.endif

${PROG}: ${OBJS} ${DLIBSA}
	${LD} -N -Ttext ${RELOC2} --format a.out-sparc-netbsd \
	    -e start ${OBJS} ${LLIBSA} -o $@~
	@size $@~
	strip -x $@~
	elf2aout $@~ $@ -b

srt0.o: srt0.S
	${CC} ${CFLAGS} ${CPPFLAGS} -D_LOCORE -c ${.IMPSRC}

.include <bsd.prog.mk>
