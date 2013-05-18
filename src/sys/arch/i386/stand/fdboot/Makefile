# $MirOS: src/sys/arch/i386/stand/fdboot/Makefile,v 1.1 2006/05/15 20:47:06 tg Exp $

#BOOTSELECT_HOOK=yes
CPPFLAGS+=	-DFFS_ONLY
BOOTLDR_PATH=	${.CURDIR}/../boot
NOMAN=		yes

install:
	# This doesn't get installed

.PATH: ${BOOTLDR_PATH}
.include "${BOOTLDR_PATH}/Makefile"
