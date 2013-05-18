# $MirOS: src/distrib/i386/ramdisk/Makefile,v 1.2 2006/05/15 19:20:15 tg Exp $
# $OpenBSD: Makefile,v 1.2 2002/04/30 03:23:57 deraadt Exp $

RAMDISK=	RAMDISK
KERNEL_LOCAL_BUILD=defined
FLOPPYSIZE=	5760
FLOPPYTYPE=	floppy288
XNAME=		ramdisk
FLOPPYSECS=	36
DO_FLOPPY=	no

IS_SMALL_DISC=	no

.include "${.CURDIR}/../common/Makefile.inc"

bsd: ${REALOBJDIR}/../generic/bsd
	-rm -f $@
	cp $> $@
