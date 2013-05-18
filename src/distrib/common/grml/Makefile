# $MirOS: src/distrib/common/grml/Makefile,v 1.2 2009/01/24 19:15:46 tg Exp $

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
CDROM_OPTS+=	bootimage=i386\;eltorito.loo
CDROM_OPTS+=	no-emul-boot

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

# for testing this in stand-alone mode

cdrom-mdcopy:
	dd if=/dev/arandom bs=2048 count=1 of=eltorito.loo

cdrom-mdboot:
	getextent_cd9660 -f ${CDROM} b_${MACHINE}.ldr | \
	    ${MKSH} ${BOOTSH} -A -S 2 | \
	    dd of=${CDROM} conv=notrunc 2>/dev/null
	getextent_cd9660 -f ${CDROM} b_${MACHINE}.ldr | \
	    ${MKSH} ${BOOTSH} -B 11 | \
	    dd of=${CDROM} conv=notrunc bs=2048 seek=$$(getextent_cd9660 \
	    -f ${CDROM} -b '$$BootImage$$') 2>/dev/null

cdrom-test: .PHONY
	cd ${.CURDIR} && exec ${MAKE} CDROM=cdrom${OSrev}.iso
