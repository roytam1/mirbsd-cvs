# $MirOS: src/sys/arch/i386/stand/liveboot/Makefile,v 1.2 2006/04/06 10:58:15 tg Exp $

#BOOTSELECT_HOOK=yes
CPPFLAGS+=	-DFFS_ONLY
BOOTLDR_PATH=	${.CURDIR}/../boot

install:
	# This doesn't get installed

.PATH: ${BOOTLDR_PATH}
.include "${BOOTLDR_PATH}/Makefile"
