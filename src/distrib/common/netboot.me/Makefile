# $MirOS: src/distrib/common/netboot.me/Makefile,v 1.4 2010/03/14 19:36:40 tg Exp $

TOPDIR=		${.CURDIR}/../..

MACHCONF=	netboot.me
INST_FILES=	${CDROM:S/^no$//} bsd4me.rd

.include "../Makefile"

CLEANFILES+=	bsd4me.rd
all: bsd4me.rd
bsd4me.rd: bsd.rd
	cp $> $@
