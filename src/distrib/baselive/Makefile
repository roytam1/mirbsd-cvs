# $MirOS: src/distrib/baselive/Makefile,v 1.7 2006/10/02 07:08:10 tg Exp $

.include <bsd.own.mk>

# common variables
REALOBJDIR!=	readlink -nf ${.OBJDIR}
TOPDIR?=	${.CURDIR}/..

.MAIN: all

.if exists(${.CURDIR}/Makefile.${MACHINE})
.  include "${.CURDIR}/Makefile.${MACHINE}"
.endif

# temporary mounts
WRKDIR=		${REALOBJDIR}/tmpdata
TMPMOUNT=	${REALOBJDIR}/tmpmnt
VND?=		svnd0
VND_DEV=	/dev/${VND}a
VND_RDEV=	/dev/r${VND}a
VND_CRDEV=	/dev/r${VND}c
RAWLABEL?=	-r

RDSETROOT?=	${REALOBJDIR}/../common/elfrdsetroot

IMAGE?=		mrdev${OSrev}.fs
IMAGESIZE?=	8192
IMAGEOPTS?=	minfree=0,optimization=space,bsize=4096,fsize=512,density=2048
IMAGETYPE?=	ipldisc
IMAGE_PREP?=	@:
KERNEL_PREP?=	@:

INSTALLBOOT?=	${DESTDIR}/usr/mdec/installboot
BOOT?=		${DESTDIR}/usr/mdec/boot
BOOTXX?=	${DESTDIR}/usr/mdec/bootxx

CDROM?=		livecd${OSrev}.iso
CDROM_MDOPTS?=

all install:

do-cdrom: unpack addcontrib prepimg nukefiles makeimg

.if !target(it)
it:
	@print -u2 The baselive cd infrastructure is not ready yet.
	@print -u2 Please try again later.
	@touch ${CDROM}
.endif

unpack: unpack-mi unpack-md

unpack-mi:
	test ! -e ${TMPMOUNT} || (cd ${TOPDIR}/common; ${MAKE} unconfig)
	${SUDO} rm -rf ${WRKDIR}
	mkdir -p ${WRKDIR}/v${OSrev}
.for _i in base dev etc gnu xbase xetc
	cd ${WRKDIR} && ${SUDO} tar xzphf ${BSDRELDIR}/rel/${_i}${OSrev}.ngz
.endfor
	cd ${WRKDIR}/v${OSrev} && ln -s ${BSDRELDIR}/rel ${MACHINE}
	cp ${TOPDIR}/common/00-README ${WRKDIR}/
	cat ${TOPDIR}/common/boot.cfg.${MACHINE} ${.CURDIR}/boot.cfg.tail | \
	    sudo dd of=${WRKDIR}/etc/boot.cfg

unpack-md:

${IMAGE}:
	test ! -e ${TMPMOUNT} || (cd ${TOPDIR}/common; ${MAKE} unconfig)
	${SUDO} rm -rf ${TMPMOUNT}
	${SUDO} mkdir -p ${TMPMOUNT}
	${SUDO} cp ${WRKDIR}/dev/MAKEDEV ${TMPMOUNT}/
	cd ${TMPMOUNT} && ${SUDO} ${MKSH} MAKEDEV all
	-${SUDO} dd if=/dev/arandom bs=512 count=4 of=${TMPMOUNT}/.rs
	${SUDO} makefs -s ${IMAGESIZE}b -o ${IMAGEOPTS} ${IMAGE} ${TMPMOUNT}
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
	${SUDO} rm -rf ${TMPMOUNT}

addcontrib:
	@if [[ ! -s ${BSDSRCDIR}/contrib/code/jupp/jupprc ]]; then \
		print -u2 Aborted: your checkout not complete; \
		exit 1; \
	fi
	@if [[ ! -s ${BSDSRCDIR}/contrib/code/Snippets/tinyirc.c ]]; then \
		print -u2 Aborted: your checkout not complete; \
		exit 1; \
	fi
	mkdir -p tempdir
	cd tempdir; CC=${CC:Q} CFLAGS=${CFLAGS:Q}\ ${COPTS:Q} \
	    ${MKSH} ${BSDSRCDIR}/contrib/code/jupp/configure \
	    --prefix=/usr --sysconfdir=/etc && \
	    make && ${SUDO} make install DESTDIR=${WRKDIR:Q}
	cd tempdir; cp ${BSDSRCDIR}/contrib/code/Snippets/tinyirc.c . && \
	    print 'PROG=tinyirc\nLDADD=-ltermcap\nNOMAN=yes\n.include' \
	    '<bsd.prog.mk>' >mkirc && make -f mkirc && \
	    ${SUDO} make -f mkirc install BINDIR=${WRKDIR}/usr/bin

prepimg:
	cd ${WRKDIR} && MACHINE=${MACHINE} \
	    ${SUDO} ${MKSH} ${.CURDIR}/munge_it.sh

bsd.gz: bsd ${IMAGE}
	-rm -f bsd.tmp
	gzip -d <bsd >bsd.tmp
	${KERNEL_PREP}
	${RDSETROOT} bsd.tmp <${IMAGE}
	gzip -n9 <bsd.tmp >$@

nukefiles:
	cd ${WRKDIR} && ${SUDO} rm -rf etc/X11 usr/{local/lib/X11,releng} \
	    usr/{,X11R6/}{doc,info,man} usr/X11R6/lib/X11/doc
	-for name in ${WRKDIR}/usr/{,X11R6/}lib/*@(.so.*|.a); do \
		print -n stripping $${name##*/} ...; \
		if [[ $$name = *.a ]]; then \
			${SUDO} strip -g $$name && print; \
		else \
			${SUDO} strip -s $$name && print; \
		fi; \
	done

makeimg: cdrom-prepare cdrom-mdcopy cdrom-generate cdrom-mdboot cdrom-finish

cdrom-prepare: bsd.gz
	${SUDO} dd if=bsd.gz obs=2048 conv=osync of=${WRKDIR}/bsd
	${SUDO} cp ${BOOT} ${WRKDIR}/etc/boot.ldr
	cd ${WRKDIR}; sed 's!RMD160 (!&v${OSrev}/${MACHINE}/!' \
	    <v${OSrev}/${MACHINE}/RMD160 >RMD160; ${SUDO} touch etc/boot.cat
	cd ${WRKDIR}; rmd160 00-README bsd etc/boot.* stand/* >>RMD160
	-${SUDO} rm -f ${WRKDIR}/etc/boot.cat ${CDROM} ${WRKDIR}/RMD160.gz

cdrom-generate:
	cd ${WRKDIR}; sort -uo RMD160 RMD160; gzip -n9 RMD160
	# pad for gzsig(1) application later on
	dd if=/dev/zero count=2 >>${WRKDIR}/RMD160.gz
	cd ${WRKDIR} && ${SUDO} ${MKSH} ${.CURDIR}/mklocatedb.sh \
	    ${REALOBJDIR}/${IMAGE}
	${SUDO} mkisofs -R -f -L -d -D -N -v -v ${CDROM_MDOPTS} \
	    -P 'The MirOS Project and its contributors' \
	    -p 'Copyright © 2006 Thorsten Glaser' \
	    -V 'MirOS #${OSrev} BSD/${MACHINE} Live CD' \
	    -volset "$$(uname -slm) Live" -sysid "MirOSBSD" \
	    -pad -o ${CDROM} ${WRKDIR} 2>&1 | tee mkisofs.log
	${SUDO} chown $$(id -u) ${CDROM}

cdrom-finish:

clean cleandir cleannobsd: cleanworkdir tstumnt
	-rm -f ${CDROM} bsd{,.gz,.tmp} mkisofs.log ${IMAGE}
	-rm -rf tempdir

cleanworkdir:
	-test ! -e ${WRKDIR} || ${SUDO} rm -rf ${WRKDIR}

tstmnt:
	${SUDO} mkdir -p ${TMPMOUNT}
	${SUDO} vnconfig svnd0 ${CDROM}
	${SUDO} mount_cd9660 /dev/svnd0a ${TMPMOUNT}

tstumnt:
	test ! -e ${TMPMOUNT} || (cd ${TOPDIR}/common; ${MAKE} unconfig)

.include <bsd.obj.mk>
.include <bsd.subdir.mk>
