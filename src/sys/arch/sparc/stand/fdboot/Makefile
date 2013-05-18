# $MirOS: src/sys/arch/sparc/stand/fdboot/Makefile,v 1.2 2008/10/21 18:51:00 tg Exp $

SMALL_BOOT=	Yes
BOOTLDR_PATH?=	${.CURDIR}/../boot

.PATH: ${BOOTLDR_PATH}

# This doesn't get installed
install:

.include "${BOOTLDR_PATH}/Makefile"

SRCS+=		strerr.c
${PROG}.elf:	strerr.o
