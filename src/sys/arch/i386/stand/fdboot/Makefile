# $MirOS: src/sys/arch/i386/stand/fdboot/Makefile,v 1.12 2009/02/01 16:16:31 tg Exp $

#BOOTSELECT_HOOK=yes
BOOTLDR_PATH=	${.CURDIR}/../boot
NOMAN=		yes
SMALL_BOOT=	Yes

# This gets installed under a different name
realinstall:
	${INSTALL} ${INSTALL_COPY} ${INSTALL_STRIP} -o ${BINOWN} -g ${BINGRP} \
	    -m ${BINMODE} ${PROG} ${DESTDIR}${BINDIR}/boot.fd

.PATH: ${BOOTLDR_PATH}
.include "${BOOTLDR_PATH}/Makefile"

SRCS+=		strerr.c
${PROG}:	strerr.o

.PATH: ${.CURDIR}/../libsa
LIBSA_FLAGS=	-I${.CURDIR}/../libsa -I${S}/stand/boot -I${S}/lib \
		-D__INTERNAL_LIBSA_CREAD \
		-DHEAP_LIMIT=${HEAP_LIMIT}
SRCS+=		biosdev.c cmd_i386.c debug.c dev_i386.c diskprobe.c gidt.S
${PROG}:	biosdev.o cmd_i386.o debug.o dev_i386.o diskprobe.o gidt.o
CFLAGS_biosdev.o+=	${LIBSA_FLAGS}
CFLAGS_cmd_i386.o+=	${LIBSA_FLAGS}
CFLAGS_debug.o+=	${LIBSA_FLAGS}
CFLAGS_debug_i386.o+=	${LIBSA_FLAGS}
CFLAGS_dev_i386.o+=	${LIBSA_FLAGS}
CFLAGS_diskprobe.o+=	${LIBSA_FLAGS}
CFLAGS_gidt.o+=		${LIBSA_FLAGS}
