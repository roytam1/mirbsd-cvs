# $MirOS: src/sys/arch/i386/stand/fdboot/Makefile,v 1.3 2006/08/19 12:45:47 tg Exp $

#BOOTSELECT_HOOK=yes
CPPFLAGS+=	-DSMALL_BOOT
BOOTLDR_PATH=	${.CURDIR}/../boot
NOMAN=		yes

install:
	# This doesn't get installed

.PATH: ${BOOTLDR_PATH}
.include "${BOOTLDR_PATH}/Makefile"

SRCS+=		strerr.c
${PROG}:	strerr.o

.PATH: ${.CURDIR}/../libsa
LIBSA_FLAGS=	-I${.CURDIR}/../libsa -I${S}/stand/boot -I${S}/lib \
		-I${BSDSRCDIR}/lib/libz -D__INTERNAL_LIBSA_CREAD \
		-DLINKADDR=0x40120 -DHEAP_LIMIT=0x90000
SRCS+=		biosdev.c cmd_i386.c dev_i386.c diskprobe.c
${PROG}:	biosdev.o cmd_i386.o dev_i386.o diskprobe.o
CFLAGS_biosdev.o+=	${LIBSA_FLAGS}
CFLAGS_cmd_i386.o+=	${LIBSA_FLAGS}
CFLAGS_dev_i386.o+=	${LIBSA_FLAGS}
CFLAGS_diskprobe.o+=	${LIBSA_FLAGS}
