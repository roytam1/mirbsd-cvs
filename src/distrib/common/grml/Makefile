# $MirOS$

.include <bsd.own.mk>

TOPDIR=		${.CURDIR}/../..
CBIN=		instbin

IMAGESIZE=	8192
IMAGETYPE=	ipldisc

KERNEL_BUILD=	no
#		(17,0) = rd0a
RAMDISK_PREP=	print 'rootdev 17 0\nquit' | config -ef $@

FLOPPY=		no
CDROM=		no

bsd: ${BSDOBJDIR}/distrib/generic/bsd
	cp -f $> $@

MACHCONF=	nonexistant
LISTS=		${TOPDIR}/common/listbeg.i386-big ${TOPDIR}/common/list \
		${TOPDIR}/common/listend.i386-big ${TOPDIR}/common/grml/listadd

${CBIN}.conf: gnustuff

gnustuff: .PHONY
	for dir in ${.CURDIR}/tinyirc ${TOPDIR}/../contrib/gnu/e3; do \
		(cd $$dir && ${MAKE} obj && ${MAKE} depend && ${MAKE}); \
	done

.include "../Makefile"
