# $MirOS: src/distrib/common/Makefile,v 1.14 2006/09/29 22:25:35 tg Exp $

.include <bsd.own.mk>

# common variables
REALOBJDIR!=	readlink -nf ${.OBJDIR}
TOPDIR?=	${.CURDIR}/..
SYSDIR=		${TOPDIR}/../sys
MACHCONF?=	${MACHINE}

.if exists(${TOPDIR}/common/Makefile.${MACHCONF})
.  include "${TOPDIR}/common/Makefile.${MACHCONF}"
.endif

# compiler options
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
AOUT_BSDRD?=	No
RAMDISK_PREP?=	@:

.if ${KERNEL_BUILD:L} != "no"
.  include "${TOPDIR}/common/Makefile.kernel"
.endif

# floppy (set to no to disable)
FLOPPY?=	floppy${OSrev}.fs
FLOPPYSIZE?=	2880
FLOPPYSECS?=	18
FLOPPYOPTS?=	minfree=0,optimization=space,bsize=4096,fsize=512
FLOPPYTYPE?=	floppy3
INSTALLBOOT?=	${DESTDIR}/usr/mdec/installboot -h 2 -s ${FLOPPYSECS}
BOOT?=		${DESTDIR}/usr/mdec/boot
BOOTXX?=	${DESTDIR}/usr/mdec/bootxx

# compact disc image (set to no to disable)
CDROM?=		cdrom${OSrev}.iso
CDROM_MDOPTS?=

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
	rm -f *core ${CBIN} ${CBIN}.mk ${CBIN}.cache ${CBIN}.conf ${IMAGE} \
	    ${RDSETROOT} *.c *.o *.lo bsd.{uc,st} ${_RD_TARGETS} mkisofs.log

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
	crunchgen ${CRUNCHGENOPTS} -D ${TOPDIR}/.. -L ${DESTDIR}/usr/lib \
	    -c ${CBIN}.c -e ${CBIN} -m ${CBIN}.mk ${CBIN}.conf

${CBIN}: ${CBIN}.mk ${CBIN}.cache ${CBIN}.c
	${MAKE} -f ${CBIN}.mk all
	${STRIP} ${STRIP_CBIN} ${CBIN}

${IMAGE}: ${CBIN}
	test ! -e ${TMPMOUNT} || (cd ${TOPDIR}/common; ${MAKE} unconfig)
	${SUDO} rm -rf ${WRKDIR}
	${SUDO} mkdir -p ${WRKDIR}
	${SUDO} mtree -Udef ${MTREE} -p ${WRKDIR}/
	OBJDIR=${REALOBJDIR:Q} TARGDIR=${WRKDIR:Q} TOPDIR=${TOPDIR:Q} \
	    DESTDIR=${DESTDIR:Q} BSDOBJDIR=${BSDOBJDIR:Q} \
	    ${SUDO} ${SHELL} ${TOPDIR}/common/runlist.sh ${LISTS}
	${SUDO} rm ${WRKDIR}/${CBIN}
	${SUDO} makefs -s ${IMAGESIZE}b -o ${IMAGEOPTS} ${IMAGE} ${WRKDIR}
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
	-rm -f $@
	gzip -d <bsd >$@
	${RAMDISK_PREP}
	${REALOBJDIR}/${RDSETROOT} $@ <${IMAGE}

bsd.rd: bsd.uc
	-rm -f $@
	gzip -vn9 <$> >$@

bsd.st: bsd.uc
	cp -f $> $@
	${STRIP} ${STRIP_KERNEL} $@

bsd.rd.net: bsd.st
	-rm -f $@
	elf2aout $> $@ -b

${FLOPPY}: bsd.st
	test ! -e ${TMPMOUNT} || (cd ${TOPDIR}/common; ${MAKE} unconfig)
	${SUDO} rm -rf ${WRKDIR}
	mkdir -p ${WRKDIR}
	cp ${BOOT} ${WRKDIR}/boot
	gzip -vn9 <bsd.st >${WRKDIR}/bsd
	${SUDO} chown -R 0:0 ${WRKDIR}
	${SUDO} chmod -R u=rwX,go=rX ${WRKDIR}
	${SUDO} makefs -s ${FLOPPYSIZE}b -o ${FLOPPYOPTS} ${FLOPPY} ${WRKDIR}
	mkdir -p ${TMPMOUNT}
	${SUDO} vnconfig -v -c ${VND} ${FLOPPY}
	${SUDO} disklabel -w ${RAWLABEL} ${VND} ${FLOPPYTYPE}
	${SUDO} mount -r ${VND_DEV} ${TMPMOUNT}
	${SUDO} ${INSTALLBOOT} -v ${TMPMOUNT}/boot ${BOOTXX} ${VND_CRDEV}
	@echo ""
	@df -i ${TMPMOUNT}
	@echo ""
	${SUDO} umount ${TMPMOUNT}
	${SUDO} fsck -fy ${VND_RDEV}
	${SUDO} vnconfig -v -u ${VND}
	${SUDO} rm -rf ${TMPMOUNT} ${WRKDIR}

${CDROM}: cdrom-prepare cdrom-mdcopy cdrom-generate cdrom-mdboot cdrom-finish

cdrom-prepare: bsd.rd
	${SUDO} rm -rf ${WRKDIR}
	mkdir -p ${WRKDIR}/{etc,v${OSrev}/${MACHINE}}
	@if [[ -e ${TOPDIR}/contrib ]]; then \
		echo Integrating contrib dir; \
		mkdir ${WRKDIR}/contrib; \
		cd ${WRKDIR}/contrib; \
		lndir ${TOPDIR}/contrib; \
	fi
	cp ${BOOT} ${WRKDIR}/boot.ldr
	cp ${TOPDIR}/common/boot.cfg.${MACHINE} ${WRKDIR}/boot.cfg
	cp bsd.rd ${WRKDIR}/v${OSrev}/${MACHINE}/
	cp ${TOPDIR}/common/00-README ${WRKDIR}/
	chmod -R u+w ${WRKDIR}

cdrom-generate:
	chmod -R u+w ${WRKDIR}
	mkisofs -r -f -L -d -D -N -v -v ${CDROM_MDOPTS} \
	    -P 'The http://mirbsd.de/ team and its contributors' \
	    -p 'Copyright © 2002-2006 by The MirOS Project' \
	    -V 'MirOS #${OSrev} BSD/${MACHINE} boot-only CD' \
	    -volset "$$(uname -slm) Setup" -sysid "MirOSBSD" \
	    -pad -o ${CDROM} ${WRKDIR} 2>&1 | tee mkisofs.log

cdrom-finish:
	-rm -rf ${WRKDIR}

.include <bsd.obj.mk>
.include <bsd.subdir.mk>
