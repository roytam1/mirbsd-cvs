# $MirOS: src/distrib/ramdisk/Makefile,v 1.7 2006/07/05 21:39:50 tg Exp $
# $OpenBSD: Makefile,v 1.26 2004/02/28 04:53:30 jolan Exp $

CBIN=		instbin
ARCHDIR=	${.CURDIR}/../${MACHINE}/ramdisk
REALOBJDIR!=	readlink -nf ${.OBJDIR} || ( cd ${.OBJDIR} && pwd )

.include <bsd.own.mk>
CFLAGS+=	${CDIAGFLAGS} ${COPTS}
HOSTCFLAGS?=	${CFLAGS}

.if exists(${ARCHDIR}/Makefile.inc)
.  include "${ARCHDIR}/Makefile.inc"
.endif

MOUNT_POINT=	${REALOBJDIR}/tmpmnt
VND?=		svnd0
VND_DEV=	/dev/${VND}a
VND_RDEV=	/dev/r${VND}a
DISKTYPE=	rdroot
REALIMAGE=	${REALOBJDIR}/tmp.ima
IMAGE?=		ramdisk${OSrev}.fs
IMAGESIZE?=	8192			# 4 MiB in 512 byte blocks
NEWFS_WILL_FAIL?=false
.if ${OBJECT_FMT:U} == "ELF"
RDSETROOT?=	elfrdsetroot
CRUNCHGENOPTS?=-E
AOUT_BSDRD?=	No
.else
RDSETROOT?=	rdsetroot
CRUNCHGENOPTS?=
AOUT_BSDRD=	No
.endif
DO_BSDRD_NAME?=	bsd.rd
DO_BSDRD_UC=	uncompressed.${DO_BSDRD_NAME}
KERNEL?=	RAMDISK
UTILS?=		${.CURDIR}/../miniroot
STRIP?=		strip

LISTS=		${.CURDIR}/list ${ARCHDIR}/list
MTREE=		${UTILS}/mtree.conf.small

XNAME?=		floppy
FS?=		${XNAME}${OSrev}.fs
FLOPPYSIZE?=	2880
FLOPPYTYPE?=	floppy
INSTALLBOOT?=	installboot
BOOT?=		${DESTDIR}/usr/mdec/boot
BOOTIN?=	${MOUNT_POINT}/boot
BOOTXX?=	${DESTDIR}/usr/mdec/bootxx
RAWLABEL?=	-r

# old format, minfree, opt, b/i  trks, sects, cpg
NEWFSOPTS=	-t ffs -m 0 -o space -f 1024 -b 8192
NEWFSOPTS_RD?=	${NEWFSOPTS} -i 16384 -c 64 -s ${IMAGESIZE}
#NEWFSOPTS_FD=	${NEWFSOPTS} -i 524288 -c 80 -s ${FLOPPYSIZE}
NEWFSOPTS_FD=	${NEWFSOPTS} -i 1048575 -c 256 -s ${FLOPPYSIZE}

# build kernel
RAMDISK=	${KERNEL}
SYSDIR=		${.CURDIR}/../../sys
.ifndef KERNEL_LOCAL_BUILD
.  include "${.CURDIR}/../Makefile.kernel"
.endif

.if ${AOUT_BSDRD:L} != "yes"
.  ifdef MAKEFLOPPY
all:	bsd.rd ${FS}
.  else
all:	bsd.rd
.  endif
.else
.  ifdef MAKEFLOPPY
all:	bsd.rd bsd.rd.net ${FS}
.  else
all:	bsd.rd bsd.rd.net
.  endif
.endif

${FS}:	bsd.gz ${BOOT} ${BOOTXX}
	dd if=/dev/zero of=${REALIMAGE} count=${FLOPPYSIZE}
	${SUDO} vnconfig -v -c ${VND} ${REALIMAGE}
	${SUDO} disklabel -w ${RAWLABEL} ${VND} ${FLOPPYTYPE}
	${SUDO} newfs ${NEWFSOPTS_FD} ${VND_RDEV}
	mkdir -p ${MOUNT_POINT}
	${SUDO} mount ${VND_DEV} ${MOUNT_POINT}
	${SUDO} cp ${BOOT} ${MOUNT_POINT}/
	${SUDO} dd if=bsd.gz of=${MOUNT_POINT}/bsd obs=512 conv=osync
	${SUDO} ${INSTALLBOOT} -v ${BOOTIN} ${BOOTXX} \
	    $$(echo ${VND_RDEV} | sed -e 's/a$$/c/')
.if (${MACHINE_ARCH} == "vax")
	${SUDO} disklabel -B -b ${BOOTXX} ${VND}
.endif
	@echo ""
	@df -i ${MOUNT_POINT}
	@echo ""
	${SUDO} umount ${MOUNT_POINT}
	${SUDO} vnconfig -u ${VND}
	dd if=${REALIMAGE} of=${FS} count=${FLOPPYSIZE}
	rm -f ${REALIMAGE}

bsd.strip: ${DO_BSDRD_UC}
	cp ${DO_BSDRD_UC} bsd.strip
	${STRIP} --strip-all -R .comment -R .eh_frame bsd.strip

bsd.gz: bsd.strip
	${GZIP} ${GZIPFLAGS} <$> >$@

${DO_BSDRD_UC}: ${IMAGE} bsd ${RDSETROOT}
	gzip -d <bsd >${DO_BSDRD_UC}
	${REALOBJDIR}/${RDSETROOT} ${DO_BSDRD_UC} <${IMAGE}

bsd.rd.net: bsd.strip
	elf2aout $> $@ -b

${DO_BSDRD_NAME}: ${DO_BSDRD_UC}
	gzip -n9 <${DO_BSDRD_UC} >${DO_BSDRD_NAME}

${RDSETROOT}: ${.CURDIR}/../common/${RDSETROOT}.c
	${HOSTCC} ${HOSTCFLAGS} -DDEBUG -o $@ $>

${IMAGE}: ${CBIN}
	dd if=/dev/zero of=${REALIMAGE} count=${IMAGESIZE}
	${SUDO} vnconfig -v -c ${VND} ${REALIMAGE}
	${SUDO} disklabel -w ${RAWLABEL} ${VND} ${DISKTYPE}
	${SUDO} newfs ${NEWFSOPTS_RD} ${VND_RDEV} || ${NEWFS_WILL_FAIL}
	mkdir -p ${MOUNT_POINT}
	${SUDO} mount ${VND_DEV} ${MOUNT_POINT}
	${SUDO} mtree -def ${MTREE} -p ${MOUNT_POINT}/ -u
	REV=${OSrev} CURDIR=${.CURDIR} OBJDIR=${.OBJDIR} ARCHDIR=${ARCHDIR} \
	    TARGDIR=${MOUNT_POINT} UTILS=${UTILS} \
	    ${SUDO} ${SHELL} ${UTILS}/runlist.sh ${LISTS}
	${SUDO} rm ${MOUNT_POINT}/${CBIN}
	@echo ""
	@df -i ${MOUNT_POINT}
	@echo ""
	-${SUDO} umount ${MOUNT_POINT}
	${SUDO} fsck -f ${VND_RDEV}
	-${SUDO} vnconfig -u ${VND}
	cp ${REALIMAGE} ${IMAGE}
	rm ${REALIMAGE}

${CBIN}.conf: ${LISTS}
	awk -f ${UTILS}/makeconf.awk CBIN=${CBIN} ${LISTS} > ${CBIN}.conf

${CBIN}.mk ${CBIN}.cache ${CBIN}.c: ${CBIN}.conf
	crunchgen ${CRUNCHGENOPTS} -D ${.CURDIR}/../.. -L ${DESTDIR}/usr/lib \
	    -c ${CBIN}.c -e ${CBIN} -m ${CBIN}.mk ${CBIN}.conf

${CBIN}: ${CBIN}.mk ${CBIN}.cache ${CBIN}.c
	make -f ${CBIN}.mk all
	${STRIP} --strip-all -R .comment -R .eh_frame ${CBIN}

clean cleandir:
.ifndef KERNEL_LOCAL_BUILD
	-rm -rf build
.endif
	/bin/rm -f *.core ${IMAGE} ${CBIN} ${CBIN}.mk ${CBIN}.cache \
	${CBIN}.conf *.o *.lo *.c bsd bsd.* ${DO_BSDRD_NAME} ${DO_BSDRD_UC} \
	    ${FS} ${REALIMAGE} ${RDSETROOT}
	/bin/rm -rf ${MOUNT_POINT}

cleannobsd:
	/bin/rm -f *.core ${IMAGE} ${CBIN} ${CBIN}.mk ${CBIN}.cache \
	${CBIN}.conf *.o *.lo *.c bsd.* ${DO_BSDRD_NAME} ${DO_BSDRD_UC} \
	    ${FS} ${REALIMAGE} ${RDSETROOT}
	/bin/rm -rf ${MOUNT_POINT}

beforeinstall:
	cp bsd.rd* ${DESTDIR}/snapshot/
.ifdef MAKEFLOPPY
	cp ${FS} ${DESTDIR}/snapshot/
.endif

unconfig:
	-${SUDO} umount -f ${MOUNT_POINT}
	-${SUDO} vnconfig -u ${VND}
	-${SUDO} /bin/rm -f ${REALIMAGE}

.include <bsd.obj.mk>
.include <bsd.subdir.mk>
