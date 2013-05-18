# $MirOS$

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
MTREE?=		${TOPDIR}/miniroot/mtree.conf.small
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
.  include "${TOPDIR}/Makefile.kernel"
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

#---

_RD_KERNELS=	bsd.rd
.if ${AOUT_BSDRD:L} != "no"
_RD_KERNELS+=	bsd.rd.net
.endif

.if ${FLOPPY:L} != "no"
ALL_TGTS=	${_RD_KERNELS}
INST_FILES?=	${_RD_KERNELS}
.else
ALL_TGTS=	${_RD_KERNELS} ${FLOPPY}
INST_FILES?=	${_RD_KERNELS} ${FLOPPY}
.endif

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
	    ${RDSETROOT} *.c *.o *.lo bsd.{uc,st} ${_RD_KERNELS}

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
	OBJDIR=${REALOBJDIR} TARGDIR=${TMPMOUNT} TOPDIR=${TOPDIR} \
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

.include <bsd.obj.mk>
.include <bsd.subdir.mk>
