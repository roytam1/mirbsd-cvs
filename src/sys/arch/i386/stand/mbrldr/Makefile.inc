# $MirOS: src/sbin/bootsys/i386/mbrldr/Makefile.inc,v 1.1.7.1 2005/03/06 16:33:40 tg Exp $

.ifndef MODSRC_SYS_ARCH_I386_STAND_MBRLDR_MAKEFILE_INC
MODSRC_SYS_ARCH_I386_STAND_MBRLDR_MAKEFILE_INC=1

SRCS+=		mbr.S
.PATH:		${.CURDIR}/../mbrldr

NOMAN?=		Yes
INSTALL_STRIP=	# set to empty value
LDFLAGS=	-nostdlib -Ttext 0 -N -x -Bstatic
INSTALL_BIN?=	Yes

CLEANFILES+=	mbrcode.h

all: mbrcode.h

mbrcode.h: ${PROG}
	print '/* $$Mir''BSD$$ */\n/*-\n * Automatically' \
	    'generated, do not edit!\n * mbrldr Version' \
	    '${V} for ${MACHINE}\n */' >$@
	hexdump -ve '8/1 "0x%02X, " "\n"' ${.ALLSRC} >>$@

.if exists(../Makefile.inc)
.  include "../Makefile.inc"
.endif

.endif
