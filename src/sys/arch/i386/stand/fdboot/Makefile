# $MirOS: src/sys/arch/i386/stand/fdboot/Makefile,v 1.6 2007/05/24 21:38:05 tg Exp $

#BOOTSELECT_HOOK=yes
CPPFLAGS+=	-DSMALL_BOOT
BOOTLDR_PATH=	${.CURDIR}/../boot
NOMAN=		yes

# This doesn't get installed
install:

.PATH: ${BOOTLDR_PATH}
.include "${BOOTLDR_PATH}/Makefile"

SRCS+=		strerr.c
${PROG}:	strerr.o

.PATH: ${.CURDIR}/../libsa
LIBSA_FLAGS=	-I${.CURDIR}/../libsa -I${S}/stand/boot -I${S}/lib \
		-D__INTERNAL_LIBSA_CREAD \
		-DLINKADDR=0x40120 -DHEAP_LIMIT=0x90000
#SRCS+=		biosdev.c cmd_i386.c dev_i386.c diskprobe.c
#${PROG}:	biosdev.o cmd_i386.o dev_i386.o diskprobe.o
SRCS+=		biosdev.c cmd_i386.c debug.c dev_i386.c diskprobe.c
${PROG}:	biosdev.o cmd_i386.o debug.o dev_i386.o diskprobe.o
CFLAGS_biosdev.o+=	${LIBSA_FLAGS}
CFLAGS_cmd_i386.o+=	${LIBSA_FLAGS}
CFLAGS_debug.o+=	${LIBSA_FLAGS}
CFLAGS_debug_i386.o+=	${LIBSA_FLAGS}
CFLAGS_dev_i386.o+=	${LIBSA_FLAGS}
CFLAGS_diskprobe.o+=	${LIBSA_FLAGS}
