# $MirOS: src/sys/arch/i386/stand/liveboot/Makefile,v 1.1 2006/04/05 22:12:17 tg Exp $

BOOTSELECT_HOOK=yes
BOOTLDR_PATH=	${.CURDIR}/../boot

install:
	# This doesn't get installed

.PATH: ${BOOTLDR_PATH}
.include "${BOOTLDR_PATH}/Makefile"
