# $MirOS: src/sys/arch/i386/stand/liveboot/Makefile,v 1.2 2006/04/06 10:58:15 tg Exp $

BOOTSELECT_HOOK=yes
BOOTLDR_PATH=	${.CURDIR}/../boot
NOMAN=		yes

install:
	# This doesn't get installed

.PATH: ${BOOTLDR_PATH}
.include "${BOOTLDR_PATH}/Makefile"
