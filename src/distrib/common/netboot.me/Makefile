# $MirOS: src/distrib/common/netboot.me/Makefile,v 1.3 2010/01/30 14:31:03 tg Exp $

TOPDIR=		${.CURDIR}/../..

MACHCONF=	netboot.me
INST_FILES=	${CDROM:S/^no$//} bsd4me.rd

.include "../Makefile"

all: bsd4me.rd
bsd4me.rd: bsd.rd
	cp $> $@
