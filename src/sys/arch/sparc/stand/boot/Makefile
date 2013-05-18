# $MirOS: src/sys/arch/sparc/stand/boot/Makefile,v 1.4 2007/06/11 21:12:58 tg Exp $
# $OpenBSD: Makefile,v 1.12 2003/08/11 06:35:45 deraadt Exp $
# $NetBSD: Makefile,v 1.2 1995/09/30 21:43:38 pk Exp $

.PATH:	${.CURDIR}/../common
S=	${.CURDIR}/../../../..

PROG=	boot

NOMAN=	yes
INSTALL_STRIP=

SRCS=	srt0.S boot.c conf.c dvma.c net.c netif_sun.c promdev.c version.c
SRCS+=	loadfile.c

CPPFLAGS+=	-I${.CURDIR}/../common -I${.CURDIR}/../../../../arch \
		-I${.CURDIR}/../../../.. -I${.CURDIR}/../../../../lib/libsa \
		-DSPARC_BOOT_AOUT -DSPARC_BOOT_ELF

CLEANFILES+=	${PROG}.elf
LIBS=		${LIBSA} ${LIBKERN} ${LIBZ}

${PROG}: ${OBJS} ${LIBS}
	${LD} -N -Ttext ${RELOC2} --format a.out-sparc-netbsd \
	    -e start ${OBJS} --start-group ${LIBSA} ${LIBKERN} ${LIBZ} \
	    $$(${CC} -print-libgcc-file-name) --end-group -o ${PROG}.elf
	@size ${PROG}.elf
	strip -s ${PROG}.elf
	elf2aout ${PROG}.elf ${PROG} -b

srt0.o: srt0.S
	${CC} ${CFLAGS} ${CPPFLAGS} -D_LOCORE -c ${.IMPSRC}

.include <bsd.prog.mk>
