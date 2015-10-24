# $MirOS: src/distrib/common/Makefile,v 1.66 2015/01/02 13:54:17 tg Exp $

.include <bsd.own.mk>

# common variables
REALOBJDIR!=	realpath ${.OBJDIR}
TOPDIR?=	${.CURDIR}/..
SYSDIR=		${TOPDIR}/../sys
MACHCONF?=	${MACHINE}

.if exists(${TOPDIR}/common/Makefile.${MACHCONF})
.  include "${TOPDIR}/common/Makefile.${MACHCONF}"
.endif

# compiler options
.if ${COPTS:M-O*:N-Os}
COPTS+=		-Os
.endif
.if !${COPTS:M-Os}
COPTS+=		-Os
.endif
CFLAGS+=	${CDIAGFLAGS} ${COPTS}
HOSTCFLAGS?=	${CFLAGS}

# temporary mounts
WRKDIR=		${REALOBJDIR}/tmpdata
TMPMOUNT=	${REALOBJDIR}/tmpmnt
VND?=		svnd0
VND_DEV=	/dev/${VND}a
VND_RDEV=	/dev/r${VND}a
VND_CRDEV=	/dev/r${VND}c
RAWLABEL?=	-r

# tools selection
RDSETROOT?=	elfrdsetroot
CRUNCHGENOPTS?=	-E
STRIP?=		strip
STRIP_CBIN?=	--strip-all -R .comment -R .eh_frame
STRIP_KERNEL?=	--strip-all -R .comment -R .eh_frame

# crunched binary and ramdisk (miniroot filesystem)
CBIN?=		instbin
LISTS?=		${TOPDIR}/common/listbeg.${MACHCONF} ${TOPDIR}/common/list \
		${TOPDIR}/common/listend.${MACHCONF}
.for _i in ${LISTADDS}
LISTS+=		${TOPDIR}/common/listadd.${_i}
.endfor
MTREE?=		${TOPDIR}/common/mtree.conf
IMAGE?=		ramdisk${OSrev}.fs
IMAGESIZE?=	3584
IMAGEOPTS?=	minfree=0,optimization=space,bsize=4096,fsize=512,density=3072
IMAGETYPE?=	rdroot
IMAGE_PREP?=	@:

# kernel (build one, create bsd.rd)
RAMDISK?=	RAMDISK
KERNEL_BUILD?=	Yes
KERNEL_BSDRD?=	Yes
BSDRD_COMPR?=	gzip -vn9
AOUT_BSDRD?=	No
RAMDISK_PREP?=	@:

.if ${KERNEL_BUILD:L} != "no"
.  include "${TOPDIR}/common/Makefile.kernel"
.endif

# floppy (set to no to disable)
FLOPPY?=	floppy${OSrev}.fs
FLOPPYSIZE?=	2880
FLOPPYGEOM?=	80:2:18
FLOPPYFILES?=	boot bsd
BOOT?=		${DESTDIR}/usr/mdec/boot
BOOT_TAR?=	${DESTDIR}/usr/mdec/boot.fd
BOOTXX?=	${DESTDIR}/usr/mdec/bootxx
BOOTXX_TAR?=	cat ${DESTDIR}/usr/mdec/bootxx.tar -
BOOTSH?=	${DESTDIR}/usr/mdec/bootxx.sh

# compact disc image (set to no to disable)
CDROM?=		cdrom${OSrev}.iso
CDROM_OPTS+=	applicationid=NetBSD_makefs
CDROM_OPTS+=	label=MirOS~v${OSrev}~BSD/${MACHINE}~boot-only~CD
CDROM_OPTS+=	no-trailing-padding
CDROM_OPTS+=	preparer=MirBSD_and_its_contributors
CDROM_OPTS+=	publisher=Copyright_\<c\>_2002=2015_The_MirOS_Project
CDROM_OPTS+=	rockridge
CDROM_OPTS+=	rr-squash
CDROM_OPTS+=	volumeid=$$(uname -slm | tr -- '- \#' :_):Setup
#CDROM_OPTS+=	v=1

#---

.if ${KERNEL_BSDRD:L} == "yes"
_RD_KERNELS=	bsd.rd
.  if ${AOUT_BSDRD:L} != "no"
_RD_KERNELS+=	bsd.rd.net
.  endif
.endif

ALL_TGTS=	${IMAGE} ${_RD_KERNELS} ${FLOPPY:S/^no$//} ${CDROM:S/^no$//}
INST_FILES?=	${_RD_KERNELS} ${FLOPPY:S/^no$//} ${CDROM:S/^no$//}
_RD_TARGETS?=	${_RD_KERNELS} ${FLOPPY:S/^no$//} ${CDROM:S/^no$//}

all: ${ALL_TGTS}

install:
.for _i in ${INST_FILES}
	${INSTALL} -c -o ${SHAREOWN} -g ${SHAREGRP} -m ${SHAREMODE} \
	    ${_i} ${DESTDIR}/snapshot/
.endfor

unconfig:
	-${SUDO} umount -f ${VND_DEV}
	-${SUDO} vnconfig -u ${VND}
	-${SUDO} rm -rf ${TMPMOUNT} ${WRKDIR} ${IMAGE}

cleannobsd: unconfig
	rm -f *core ${CBIN} ${CBIN}.{cache,conf,mk,unstripped} ${IMAGE} \
	    ${RDSETROOT} *.c *.o *.lo *.loo *~ bsd.uc ${_RD_TARGETS} \
	    ${CLEANFILES}

clean cleandir: cleannobsd
	rm -f bsd
.if ${KERNEL_BUILD:L} != "no"
	rm -rf build
.endif

${RDSETROOT}: ${TOPDIR}/common/${RDSETROOT}.c
	${HOSTCC} ${HOSTCFLAGS} -DDEBUG -o $@ $>

${CBIN}.conf: ${LISTS}
	awk -f ${TOPDIR}/common/makeconf.awk CBIN=${CBIN} ${LISTS} >$@

${CBIN}.mk ${CBIN}.cache ${CBIN}.c: ${CBIN}.conf
	crunchgen ${CRUNCHGENOPTS} -D ${BSDSRCDIR} -L ${DESTDIR}/usr/lib \
	    -c ${CBIN}.c -e ${CBIN} -m ${CBIN}.mk ${CBIN}.conf

${CBIN}: ${CBIN}.mk ${CBIN}.cache ${CBIN}.c
	${MAKE} -f ${CBIN}.mk all
	cp ${CBIN} ${CBIN}.unstripped
	${STRIP} ${STRIP_CBIN} ${CBIN}

${IMAGE}: ${CBIN}
	test ! -e ${TMPMOUNT} || (cd ${.CURDIR}; ${MAKE} unconfig)
	${SUDO} rm -rf ${WRKDIR}
	${SUDO} mkdir -p ${WRKDIR}
	${SUDO} mtree -Udef ${MTREE} -p ${WRKDIR}/
	OBJDIR=${REALOBJDIR:Q} TARGDIR=${WRKDIR:Q} TOPDIR=${TOPDIR:Q} \
	    DESTDIR=${DESTDIR:Q} BSDOBJDIR=${BSDOBJDIR:Q} \
	    ${SUDO} ${SHELL} ${TOPDIR}/common/runlist.sh ${LISTS}
	${SUDO} rm ${WRKDIR}/${CBIN}
	${SUDO} makefs -s ${IMAGESIZE}b -o ${IMAGEOPTS} ${IMAGE} ${WRKDIR}
.ifndef IMAGE_NO_ARND
	${SUDO} dd if=/dev/arandom bs=32 count=1 of=$@ conv=notrunc
.endif
	sync
	${SUDO} mkdir -p ${TMPMOUNT}
	${SUDO} vnconfig -v -c ${VND} ${IMAGE}
	${SUDO} disklabel -w ${RAWLABEL} ${VND} ${IMAGETYPE}
	${SUDO} mount -r ${VND_DEV} ${TMPMOUNT}
	${IMAGE_PREP}
	@echo ""
	@df -i ${TMPMOUNT}
	@echo ""
	${SUDO} umount ${TMPMOUNT}
	${SUDO} fsck -fy ${VND_RDEV}
	${SUDO} vnconfig -v -u ${VND}
	${SUDO} rm -rf ${TMPMOUNT} ${WRKDIR}

bsd.uc: bsd ${IMAGE} ${RDSETROOT}
	-rm -f $@ $@~
	gzip -fd <bsd >$@~
	${RAMDISK_PREP}
	${REALOBJDIR}/${RDSETROOT} $@~ <${IMAGE}
	mv -f $@~ $@

bsd.rd: bsd.uc
	cp -f bsd.uc bsd.uc~
	config -ef bsd.uc~ <<<"quit"
	${BSDRD_COMPR} <bsd.uc~ >$@
	-rm -f bsd.uc~

bsd.rd.net: bsd.uc
	cp -f bsd.uc bsd.uc~
	config -ef bsd.uc~ <<<"quit"
	${STRIP} ${STRIP_KERNEL} bsd.uc~
	elf2aout bsd.uc~ $@ -b
	-rm -f bsd.uc~

FLOPPY_BOOTCFG?=@:
${FLOPPY}: bsd.uc
	test ! -e ${TMPMOUNT} || (cd ${.CURDIR}; ${MAKE} unconfig)
	${SUDO} rm -rf ${WRKDIR} e~
	mkdir -p ${WRKDIR}
	cp -f bsd.uc bsd.uc~
	config -ef bsd.uc~ <<<"quit"
	${STRIP} ${STRIP_KERNEL} bsd.uc~
	gzip -vn9 <bsd.uc~ >${WRKDIR}/bsd
	-rm -f bsd.uc~
	${FLOPPY_BOOTCFG}
	dd if=/dev/zero of=${FLOPPY}~ count=${FLOPPYSIZE}
	(tar -b 1 -M dist -cf - -C ${WRKDIR} ${FLOPPYFILES} || touch e~) | \
	    ${BOOTXX_TAR} | dd of=${FLOPPY}~ conv=notrunc
	@[[ ! -e e~ ]]
	(( $$(stat -f %z ${FLOPPY}~) == 512 * ${FLOPPYSIZE} ))
	mv -f ${FLOPPY}~ ${FLOPPY}
	rm -rf ${WRKDIR} e~

${CDROM}: cdrom-prepare cdrom-mdcopy cdrom-generate cdrom-mdboot

cdrom-prepare: bsd.uc
	${SUDO} rm -rf ${WRKDIR}
	mkdir -p ${WRKDIR}/v${OSrev}/${MACHINE}
	@if [[ -e ${TOPDIR}/contrib ]]; then \
		echo Integrating contrib dir; \
		mkdir ${WRKDIR}/contrib; \
		cd ${TOPDIR}/contrib; \
		pax -v -rw -pe . ${WRKDIR}/contrib/; \
	fi
	cp ${BOOT} ${WRKDIR}/b_${MACHINE}.ldr
.if exists(${TOPDIR}/common/boot.cfg.${MACHINE})
	cp ${TOPDIR}/common/boot.cfg.${MACHINE} ${WRKDIR}/boot.cfg
.endif
.if defined(LGRUBCFG)
	mkdir -p ${WRKDIR}/boot/grub
	cp ${TOPDIR}/common/${LGRUBCFG}/loopback.* ${WRKDIR}/boot/grub/
.endif
	cp ${BOOTSH} ${WRKDIR}/v${OSrev}/${MACHINE}/
	cp -f bsd.uc bsd.uc~
	config -ef bsd.uc~ <<<"quit"
	${BSDRD_COMPR} <bsd.uc~ >${WRKDIR}/v${OSrev}/${MACHINE}/bsd.rd
	-rm -f bsd.uc~
	cp ${TOPDIR}/common/00-README ${WRKDIR}/
	chmod -R u+w ${WRKDIR}

cdrom-generate:
	chmod -R u+w ${WRKDIR}
	makefs -t cd9660 -o "$$(print -r -- ${CDROM_OPTS} | tr ' ~' ', ')" \
	    ${CDROM} ${WRKDIR}
	# pad the ISO with ]0;256K] NUL bytes, ie. for
	# a geometry of 16 heads, 32 sectors per track
	dd if=/dev/zero count=1 bs=$$((# (512 * 32 * 16) - \
	    ($$(stat -f %z ${CDROM}) % (512 * 32 * 16)) )) 2>&- >>${CDROM}

.include <bsd.obj.mk>
.include <bsd.subdir.mk>
