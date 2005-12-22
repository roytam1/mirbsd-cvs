# $MirOS$
# $OpenBSD: Makefile,v 1.2 2002/04/30 03:23:57 deraadt Exp $

RAMDISK=	RAMDISK
KERNEL_LOCAL_BUILD=defined
FLOPPYSIZE=	288
FLOPPYTYPE=	floppy288
XNAME=		ramdisk
FLOPPYSECS=	36
DO_FLOPPY=	no

.include "${.CURDIR}/../common/Makefile.inc"

bsd: ${REALOBJDIR}/../generic/bsd
	-rm -f $@
	cp $> $@
