# $MirOS$

CPPFLAGS+=	-DSMALL_BOOT
SMALL_BOOT=	Yes
BOOTLDR_PATH=	${.CURDIR}/../boot

.PATH: ${BOOTLDR_PATH}

# This doesn't get installed
install:

.include "${BOOTLDR_PATH}/Makefile"
