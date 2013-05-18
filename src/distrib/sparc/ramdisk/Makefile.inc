# $MirOS: src/distrib/sparc/ramdisk/Makefile.inc,v 1.5 2006/07/05 22:49:14 tg Exp $
# $OpenBSD: Makefile.inc,v 1.14 2002/05/01 19:21:28 mickey Exp $

IMAGESIZE?=		3584
GZIP?=			gzip
GZIPFLAGS?=		-9vn
GZIPEXT?=		.gz
MAKEFLOPPY=		1
RAWLABEL=
BOOT=			${DESTDIR}/usr/mdec/boot
INSTALLBOOT=		${DESTDIR}/usr/mdec/installboot
AOUT_BSDRD=		Yes

USE_MAKEFS=		#defined
NEWFSOPTS_RD?=		${NEWFSOPTS} -i 8192 -c 64 -s ${IMAGESIZE}
