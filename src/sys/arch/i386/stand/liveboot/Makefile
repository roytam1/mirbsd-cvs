# $MirOS: src/sys/arch/i386/stand/liveboot/Makefile,v 1.3 2006/05/15 20:47:42 tg Exp $

BOOTSELECT_HOOK=yes
BOOTLDR_PATH=	${.CURDIR}/../boot
NOMAN=		yes

# This doesn't get installed
install:

.PATH: ${BOOTLDR_PATH}
.include "${BOOTLDR_PATH}/Makefile"
