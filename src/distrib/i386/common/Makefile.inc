# $MirOS: src/distrib/i386/common/Makefile.inc,v 1.6 2006/01/15 23:46:37 tg Exp $
# $OpenBSD: Makefile.inc,v 1.15 2004/11/25 22:02:08 deraadt Exp $

.ifndef _MODSRC_DISTRIB_I386_COMMON_MAKEFILE_INC
_MODSRC_DISTRIB_I386_COMMON_MAKEFILE_INC=1

.include <bsd.own.mk>

TOP=		${.CURDIR}/..
REALOBJDIR!=	readlink ${.OBJDIR} || ( cd ${.OBJDIR} && pwd )
IMAGE=		mr.fs
CBIN?=		instbin
CRUNCHCONF?=	${CBIN}.conf
LISTS?=		${.CURDIR}/../common/list
.if exists(${.CURDIR}/list.local)
LISTS+=		${.CURDIR}/list.local
.endif
UTILS?=		${.CURDIR}/../../miniroot
STRIP?=		strip
STRIP_ADDS?=	-K cngetc

MOUNT_POINT=	${REALOBJDIR}/tmpmnt
MTREE?=		${UTILS}/mtree.conf

XNAME?=		floppy
FS?=		${XNAME}${OSrev}.fs
VND?=		svnd0
VND_DEV=	/dev/${VND}a
VND_RDEV=	/dev/r${VND}a
VND_CRDEV=	/dev/r${VND}c
REALIMAGE=	${REALOBJDIR}/tmp.ima
BOOT=		${DESTDIR}/usr/mdec/boot
FLOPPYSIZE?=	144
FLOPPYSECS?=	18
FLOPPYTYPE?=	floppy3
HOSTCFLAGS?=	${CFLAGS} ${COPTS}
.if !${COPTS:M-Os}
COPTS+=		-Os
.endif
CFLAGS+=	${CDIAGFLAGS} ${COPTS}

SYSDIR=		${.CURDIR}/../../../sys
SYSSUBDIR=	${SYSDIR}/arch/i386
KERNDIR=	${SYSSUBDIR}/compile/${RAMDISK}
MAKE_CLEAN?=	${MAKE} clean

DO_FLOPPY?=	Yes
DO_BSDRD_NAME?=	bsd.rd

.if ${DO_FLOPPY:L} == "yes"
all:	${FS}
.else
all:	${DO_BSDRD_NAME}
.endif

${FS}:	bsd.gz
	dd if=/dev/zero of=${REALIMAGE} bs=10k count=${FLOPPYSIZE}
	${SUDO} vnconfig -v -c ${VND} ${REALIMAGE}
	${SUDO} disklabel -w -r ${VND} ${FLOPPYTYPE}
	${SUDO} newfs -m 0 -o space -i 1048576 -c 80 -b 4096 ${VND_RDEV}
	mkdir -p ${MOUNT_POINT}
	${SUDO} mount ${VND_DEV} ${MOUNT_POINT}
	${SUDO} cp ${BOOT} ${.OBJDIR}/boot
	${SUDO} dd if=${.OBJDIR}/boot of=${MOUNT_POINT}/boot obs=512 conv=osync
	${SUDO} dd if=bsd.gz of=${MOUNT_POINT}/bsd obs=512 conv=osync
	${SUDO} /usr/mdec/installboot -v -s ${FLOPPYSECS} -h 2 \
	    ${MOUNT_POINT}/boot ${DESTDIR}/usr/mdec/ffspbr ${VND_CRDEV}
	@echo ""
	@df -i ${MOUNT_POINT}
	@echo ""
	${SUDO} umount ${MOUNT_POINT}
	${SUDO} vnconfig -u ${VND}
	cp ${REALIMAGE} ${FS}
	rm ${REALIMAGE}

DISKTYPE?=       ipldisc
NBLKS?=          8192
# minfree, opt, b/i  trks, sects, cpg
NEWFSARGS=	-m 0 -o space -c 16 -i 3072

bsd.gz: ${DO_BSDRD_NAME}
	cp ${DO_BSDRD_NAME} bsd.strip
	${STRIP} --strip-all -R .comment -R .eh_frame ${STRIP_ADDS} bsd.strip
	gzip -nc9 bsd.strip >bsd.gz

${DO_BSDRD_NAME}:	${IMAGE} bsd rdsetroot
	gzip -d <bsd >${DO_BSDRD_NAME}
	${.OBJDIR}/rdsetroot ${DO_BSDRD_NAME} <${IMAGE}

.ifndef KERNEL_LOCAL_BUILD
bsd:
	mkdir -p build/${RAMDISK}
	[[ -f build/${RAMDISK}/version || ! -f ${KERNDIR}/version ]] \
	    || cat ${KERNDIR}/version >build/${RAMDISK}/version
	( cd build/${RAMDISK}; config -s ${SYSDIR} -b . \
	    ${SYSSUBDIR}/conf/${RAMDISK} \
	    && ${MAKE_CLEAN} && ${MAKE} depend && exec ${MAKE} bsd )
	mv build/${RAMDISK}/bsd .
	-[[ ! -e ${KERNDIR} ]] \
	    || if ! cat build/${RAMDISK}/version >${KERNDIR}/version; then \
		( print "# warning: kernel version changed"; \
		  print "print $$(<build/${RAMDISK}/version)" \
		     ">${KERNDIR}/version" ) \
		  | tee -a /var/tmp/.buildnotice >&2; \
	    fi
.endif

${IMAGE}: ${CBIN} rd_setup do_files rd_teardown

rd_setup: ${CBIN}
	dd if=/dev/zero of=${REALIMAGE} bs=512 count=${NBLKS}
	${SUDO} vnconfig -v -c ${VND} ${REALIMAGE}
	${SUDO} disklabel -w -r ${VND} ${DISKTYPE}
	${SUDO} newfs ${NEWFSARGS} ${VND_RDEV}
	${SUDO} fsck ${VND_RDEV}
	mkdir -p ${MOUNT_POINT}
	${SUDO} mount ${VND_DEV} ${MOUNT_POINT}

rd_teardown:
	@df -i ${MOUNT_POINT}
	-${SUDO} umount ${MOUNT_POINT}
	-${SUDO} vnconfig -u ${VND}
	cp ${REALIMAGE} ${IMAGE}
	rm ${REALIMAGE}

rdsetroot:	${TOP}/../common/elfrdsetroot.c
	${HOSTCC} ${HOSTCFLAGS} -DDEBUG -o $@ ${TOP}/../common/elfrdsetroot.c

unconfig:
	-${SUDO} umount -f ${MOUNT_POINT}
	-${SUDO} vnconfig -u ${VND}

.PRECIOUS:	${IMAGE}

install:
.ifndef NOBSDRD
	cp ${DO_BSDRD_NAME} ${DESTDIR}/snapshot/
.endif
.if ${DO_FLOPPY:L} == "yes"
	cp ${FS} ${DESTDIR}/snapshot/${FS}
.endif

${CBIN}.mk ${CBIN}.cache ${CBIN}.c: ${CRUNCHCONF}
	crunchgen -E -D ${BSDSRCDIR} -L ${DESTDIR}/usr/lib \
	    -c ${CBIN}.c -e ${CBIN} -m ${CBIN}.mk ${CRUNCHCONF}

${CBIN}: ${CBIN}.mk ${CBIN}.cache ${CBIN}.c
	make -f ${CBIN}.mk CFLAGS="${CFLAGS}" all
	${STRIP} --strip-all -R .comment -R .eh_frame ${CBIN}

${CRUNCHCONF}: ${LISTS}
	awk -f ${UTILS}/makeconf.awk CBIN=${CBIN} ${LISTS} >${CRUNCHCONF}

do_files:
	${SUDO} mtree -def ${MTREE} -p ${MOUNT_POINT}/ -u
	TOPDIR=${TOP} CURDIR=${.CURDIR} OBJDIR=${.OBJDIR} \
	    REV=${OSrev} TARGDIR=${MOUNT_POINT} UTILS=${UTILS} \
	    ${SUDO} ${SHELL} ${UTILS}/runlist.sh ${LISTS}
	${SUDO} rm ${MOUNT_POINT}/${CBIN}

clean cleandir:
.ifndef KERNEL_LOCAL_BUILD
	-rm -rf build
.endif
	/bin/rm -f core ${IMAGE} ${CBIN} ${CBIN}.mk ${CBIN}*.cache boot \
	    *.o *.lo *.c bsd bsd.rd bsd.gz bsd.strip floppy*.fs rdsetroot \
	    cdrom*.fs ${CRUNCHCONF} ${DO_BSDRD_NAME} ${FS} ${REALIMAGE}
	/bin/rm -rf ${MOUNT_POINT}

cleannobsd:
	/bin/rm -f core ${IMAGE} ${CBIN} ${CBIN}.mk ${CBIN}*.cache boot \
	    *.o *.lo *.c bsd.rd bsd.gz bsd.strip floppy*.fs rdsetroot \
	    cdrom*.fs ${CRUNCHCONF} ${DO_BSDRD_NAME} ${FS} ${REALIMAGE}
	/bin/rm -rf ${MOUNT_POINT}

.include <bsd.obj.mk>
.include <bsd.subdir.mk>

.endif
