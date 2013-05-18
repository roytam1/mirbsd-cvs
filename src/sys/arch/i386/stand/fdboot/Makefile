# $MirOS: src/sys/arch/i386/stand/fdboot/Makefile,v 1.2 2006/05/15 20:47:40 tg Exp $

#BOOTSELECT_HOOK=yes
CPPFLAGS+=	-DFFS_ONLY -DSMALL_BOOT
BOOTLDR_PATH=	${.CURDIR}/../boot
NOMAN=		yes

install:
	# This doesn't get installed

.PATH: ${BOOTLDR_PATH}
.include "${BOOTLDR_PATH}/Makefile"
