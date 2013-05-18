# $MirOS: src/distrib/sparc/ramdisk/Makefile.inc,v 1.3 2006/07/03 23:17:50 tg Exp $
# $OpenBSD: Makefile.inc,v 1.14 2002/05/01 19:21:28 mickey Exp $

IMAGESIZE?=		4096
GZIP?=			gzip
GZIPFLAGS?=		-9vn
GZIPEXT?=		.gz
MAKEFLOPPY=		1
RAWLABEL=
BOOT=			${DESTDIR}/usr/mdec/boot
INSTALLBOOT=		${DESTDIR}/usr/mdec/installboot
AOUT_BSDRD=		Yes
