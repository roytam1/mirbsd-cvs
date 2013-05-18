# $MirOS: src/distrib/sparc/ramdisk/Makefile.inc,v 1.2 2005/03/06 18:58:07 tg Exp $
# $OpenBSD: Makefile.inc,v 1.14 2002/05/01 19:21:28 mickey Exp $

IMAGESIZE?=		3840
GZIP?=			gzip
GZIPFLAGS?=		-9vn
GZIPEXT?=		.gz
MAKEFLOPPY=		1
RAWLABEL=
BOOT=			${DESTDIR}/usr/mdec/boot
INSTALLBOOT=		${DESTDIR}/usr/mdec/installboot
AOUT_BSDRD=		Yes
