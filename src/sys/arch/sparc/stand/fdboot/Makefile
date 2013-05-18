# $MirOS: src/sys/arch/sparc/stand/fdboot/Makefile,v 1.4 2010/01/10 12:55:22 tg Exp $

SMALL_BOOT=	Yes
BOOTLDR_PATH?=	${.CURDIR}/../boot
CPPFLAGS+=	-DUSE_USTARFS

.PATH: ${BOOTLDR_PATH}

# This gets installed under a different name
realinstall:
	${INSTALL} ${INSTALL_COPY} ${INSTALL_STRIP} -o ${BINOWN} -g ${BINGRP} \
	    -m ${BINMODE} ${PROG} ${DESTDIR}${BINDIR}/boot.fd

.include "${BOOTLDR_PATH}/Makefile"

SRCS+=		strerr.c
${PROG}.elf:	strerr.o
