# $MirOS: src/distrib/ramdisk/Makefile,v 1.15 2006/08/17 13:49:42 tg Exp $

.include <bsd.own.mk>

# common variables
REALOBJDIR!=	readlink -nf ${.OBJDIR}
TOPDIR?=	${.CURDIR}/..
SYSDIR=		${TOPDIR}/../sys
MACHCONF?=	${MACHINE}

.if ${.CURDIR}/Makefile.${MACHCONF} != "no"
.  include "${.CURDIR}/Makefile.${MACHCONF}"
.endif

# compiler options
.if !${COPTS:M-Os}
COPTS+=		-Os
.endif
CFLAGS+=	${CDIAGFLAGS} ${COPTS}
HOSTCFLAGS?=	${CFLAGS}

# temporary mounts
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

# crunched binary and ramdisk
CBIN?=		instbin
LISTS?=		${.CURDIR}/listhdr.${MACHCONF} ${.CURDIR}/list \
		${.CURDIR}/listend.${MACHCONF}
MTREE?=		${TOPDIR}/miniroot/mtree.conf
IMAGE?=		ramdisk${OSrev}.fs
IMAGESIZE?=	8192
IMAGEOPTS?=	minfree=0,optimization=space,bsize=4096,fsize=512,density=3072
IMAGETYPE?=	rdroot

# kernel
RAMDISK?=	RAMDISK
KERNEL_BUILD?=	Yes
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

_RD_KERNELS=	bsd.rd
.if ${AOUT_BSDRD:L} != "no"
_RD_KERNELS+=	bsd.rd.net
.endif

ALL_TGTS=	${_RD_KERNELS} ${FLOPPY:S/^no$//} ${CDROM:S/^no$//}
INST_FILES?=	${_RD_KERNELS} ${FLOPPY:S/^no$//} ${CDROM:S/^no$//}

all: ${ALL_TGTS}

install:
.for _i in ${INST_FILES}
	${INSTALL} -c -o ${SHAREOWN} -g ${SHAREGRP} -m ${SHAREMODE} \
	    ${_i} ${DESTDIR}/snapshot/
.endfor

unconfig:
	-${SUDO} umount -f ${VND_DEV}
	-${SUDO} vnconfig -u ${VND}
	-${SUDO} rm -rf ${TMPMOUNT} ${IMAGE} ${FLOPPY}

cleannobsd: unconfig
	rm -f *core ${CBIN} ${CBIN}.mk ${CBIN}.cache ${CBIN}.conf \
	    ${RDSETROOT} *.c *.o *.lo bsd.{uc,st} ${_RD_KERNELS} mkisofs.log
	rm -rf workdir

clean cleandir: cleannobsd
	rm -f bsd
.if ${KERNEL_BUILD:L} != "no"
	rm -rf build
.endif

${RDSETROOT}: ${TOPDIR}/common/${RDSETROOT}.c
	${HOSTCC} ${HOSTCFLAGS} -DDEBUG -o $@ $>

${CBIN}.conf: ${LISTS}
	awk -f ${TOPDIR}/miniroot/makeconf.awk CBIN=${CBIN} ${LISTS} >$@

${CBIN}.mk ${CBIN}.cache ${CBIN}.c: ${CBIN}.conf
	crunchgen ${CRUNCHGENOPTS} -D ${TOPDIR}/.. -L ${DESTDIR}/usr/lib \
	    -c ${CBIN}.c -e ${CBIN} -m ${CBIN}.mk ${CBIN}.conf

${CBIN}: ${CBIN}.mk ${CBIN}.cache ${CBIN}.c
	${MAKE} -f ${CBIN}.mk all
	${STRIP} ${STRIP_CBIN} ${CBIN}

${IMAGE}: ${CBIN}
	test ! -e ${TMPMOUNT} || (cd ${.CURDIR}; ${MAKE} unconfig)
	${SUDO} mkdir -p ${TMPMOUNT}
	${SUDO} mtree -def ${MTREE} -p ${TMPMOUNT}/ -u
	OBJDIR=${REALOBJDIR:Q} TARGDIR=${TMPMOUNT:Q} TOPDIR=${TOPDIR:Q} \
	    DESTDIR=${DESTDIR:Q} BSDOBJDIR=${BSDOBJDIR:Q} \
	    ${SUDO} ${SHELL} ${TOPDIR}/miniroot/runlist.sh ${LISTS}
	${SUDO} rm ${TMPMOUNT}/${CBIN}
	${SUDO} makefs -s ${IMAGESIZE}b -o ${IMAGEOPTS} ${IMAGE} ${TMPMOUNT}
	${SUDO} vnconfig -v -c ${VND} ${IMAGE}
	${SUDO} disklabel -w ${RAWLABEL} ${VND} ${IMAGETYPE}
	${SUDO} mount -r ${VND_DEV} ${TMPMOUNT}
	@echo ""
	@df -i ${TMPMOUNT}
	@echo ""
	${SUDO} umount ${TMPMOUNT}
	${SUDO} fsck -fy ${VND_RDEV}
	${SUDO} vnconfig -v -u ${VND}
	${SUDO} rm -rf ${TMPMOUNT}

bsd.uc: bsd ${IMAGE} ${RDSETROOT}
	-rm -f $@
	gzip -d <$> >$@
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
	test ! -e ${TMPMOUNT} || (cd ${.CURDIR}; ${MAKE} unconfig)
	mkdir -p ${TMPMOUNT}
	cp ${BOOT} ${TMPMOUNT}/boot
	gzip -vn9 <bsd.st >${TMPMOUNT}/bsd
	${SUDO} chown -R 0:0 ${TMPMOUNT}
	${SUDO} chmod -R u=rwX,go=rX ${TMPMOUNT}
	${SUDO} makefs -s ${FLOPPYSIZE}b -o ${FLOPPYOPTS} ${FLOPPY} ${TMPMOUNT}
	${SUDO} vnconfig -v -c ${VND} ${FLOPPY}
	${SUDO} disklabel -w ${RAWLABEL} ${VND} ${FLOPPYTYPE}
	${SUDO} mount -r ${VND_DEV} ${TMPMOUNT}
	@echo ""
	@df -i ${TMPMOUNT}
	@echo ""
	${SUDO} ${INSTALLBOOT} -v ${TMPMOUNT}/boot ${BOOTXX} ${VND_CRDEV}
	${SUDO} umount ${TMPMOUNT}
	${SUDO} fsck -fy ${VND_RDEV}
	${SUDO} vnconfig -v -u ${VND}
	${SUDO} rm -rf ${TMPMOUNT}

${CDROM}: cdrom-prepare cdrom-mdcopy cdrom-generate cdrom-mdboot

cdrom-prepare: bsd.rd
	-rm -rf workdir
	mkdir -p workdir/{etc,v${OSrev}/${MACHINE}}
	@if [[ -e ${.CURDIR}/contrib ]]; then \
		echo Integrating contrib dir; \
		mkdir workdir/contrib; \
		cd workdir/contrib; \
		lndir ${.CURDIR}/contrib; \
	fi
	cp ${BOOT} workdir/etc/boot.ldr
	cp ${.CURDIR}/boot.cfg.${MACHINE} workdir/etc/boot.cfg
	cp bsd.rd workdir/v${OSrev}/${MACHINE}/
	cp ${.CURDIR}/00-README workdir/

cdrom-generate:
	mkisofs -r -f -L -d -D -N -v -v \
	    -P 'The http://mirbsd.de/ team and its contributors' \
	    -p 'Copyright © 2002-2006 by The MirOS Project' \
	    -V 'MirOS #${OSrev} BSD/${MACHINE} boot-only CD' \
	    -volset "$$(uname -slm) Setup" -sysid "MirOSBSD" \
	    -pad -o ${CDROM} workdir 2>&1 | tee mkisofs.log

.include <bsd.obj.mk>
.include <bsd.subdir.mk>
