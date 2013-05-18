# $MirOS: src/distrib/baselive/Makefile,v 1.29 2008/07/12 21:39:52 tg Exp $

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

BATCH?=		No

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
	test ! -e ${TMPMOUNT} || (cd ${.CURDIR}; ${MAKE} unconfig)
	${SUDO} rm -rf ${WRKDIR}
	mkdir -p ${WRKDIR}/v${OSrev}/${MACHINE}
.for _i in base dev etc gnu xbase xetc xsrv
	cd ${WRKDIR} && ${SUDO} tar xzphf ${BSDRELDIR}/rel/${_i}${OSrev}.ngz
.endfor
	cd ${WRKDIR}/v${OSrev}/${MACHINE} && lndir ${BSDRELDIR}/rel
	${SUDO} chown -R 0:0 ${WRKDIR}/v${OSrev}
	cp ${TOPDIR}/common/{00-README,01-3RDPTY} ${WRKDIR}/
	cat ${TOPDIR}/common/boot.cfg.${MACHINE} ${.CURDIR}/boot.cfg.tail | \
	    sudo dd of=${WRKDIR}/boot.cfg

unpack-md:

${IMAGE}:
	test ! -e ${TMPMOUNT} || (cd ${.CURDIR}; ${MAKE} unconfig)
	${SUDO} mkdir -p ${TMPMOUNT}
	${SUDO} chown 0:0 ${TMPMOUNT}
	${SUDO} cp ${WRKDIR}/dev/MAKEDEV ${TMPMOUNT}/
	cd ${TMPMOUNT} && ${SUDO} ${MKSH} MAKEDEV all
	-${SUDO} dd if=/dev/arandom bs=512 count=4 of=${TMPMOUNT}/.rs
	${SUDO} makefs -s ${IMAGESIZE}b -o ${IMAGEOPTS} ${IMAGE} ${TMPMOUNT}
	${SUDO} dd if=/dev/arandom bs=512 count=1 of=$@ conv=notrunc
	sync
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
		print -u2 Aborted: your checkout is not complete; \
		exit 1; \
	fi
	@if [[ ! -s ${BSDSRCDIR}/contrib/code/Snippets/tinyirc.c ]]; then \
		print -u2 Aborted: your checkout is not complete; \
		exit 1; \
	fi
	mkdir -p tempdir
	cd tempdir; CC=${CC:Q} CFLAGS=${CFLAGS:Q}\ ${COPTS:Q}\ -Ddefutf8 \
	    ${MKSH} ${BSDSRCDIR}/contrib/code/jupp/configure \
	    --prefix=/usr --sysconfdir=/etc --disable-dependency-tracking && \
	    make && ${SUDO} make install DESTDIR=${WRKDIR:Q}
	cd tempdir; cp ${BSDSRCDIR}/contrib/code/Snippets/tinyirc.c . && \
	    print 'PROG=tinyirc\nLDADD=-ltermcap\nNOMAN=yes\n.include' \
	    '<bsd.prog.mk>' >mkirc && make -f mkirc && \
	    ${SUDO} make -f mkirc install BINDIR=${WRKDIR}/usr/bin
	${SUDO} install -o 0 -g 0 -m 644 \
	    ${BSDSRCDIR}/contrib/samples/dot.Xmodmap \
	    ${WRKDIR}/etc/skel/.Xmodmap

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
.if ${DEBUGLIBS:L} == "yes"
	-for name in ${WRKDIR}/usr/{,X11R6/}lib/*@(.so.*|.a); do \
		print -n stripping $${name##*/} ...; \
		if [[ $$name = *.a ]]; then \
			${SUDO} strip -g $$name && print; \
		else \
			${SUDO} strip -s $$name && print; \
		fi; \
	done
.endif

makeimg: cdrom-prepare cdrom-mdcopy cdrom-generate cdrom-mdboot cdrom-finish

cdrom-prepare: bsd.gz
	${SUDO} dd if=bsd.gz obs=2048 conv=osync of=${WRKDIR}/bsd
	cd ${WRKDIR}; \
	    ${SUDO} cp ${BOOT} boot.ldr; \
	    ${SUDO} rm -f CKSUM*; \
	    while IFS= read -r line; do \
		if [[ $$line = *" = "+([0-9a-fA-F]) ]]; then \
			two=$${line#+([A-Z0-9]) \(}; \
		else \
			two=$${line#+([0-9]) +([0-9]) }; \
		fi; \
		one=$${line%%$$two}; \
		print -r "$${one}v${OSrev}/${MACHINE}/$$two"; \
	    done <v${OSrev}/${MACHINE}/CKSUM >CKSUM; \
	    ${SUDO} touch boot.cat; \
	    cksum -a cksum -a rmd160 -a tiger 0* bsd boot.* stand/* >>CKSUM
	-${SUDO} rm -f ${WRKDIR}/boot.cat ${CDROM}

cdrom-generate:
.if ${BATCH:L} != "yes"
	@print WRKDIR is \"${WRKDIR:Q}\"
	@print Build coordination: press RETURN to continue...; read dummy
.endif
	[[ ! -s ${WRKDIR}/loot ]] || \
	    perl -pi -e 's/bsd/lsd/g; s/B(SD|(?i)oot)/L$1/g' ${WRKDIR}/loot
	cd ${WRKDIR}; \
	    sort -k3 |& exec 3>&p; exec 4<&p; \
	    sort |& exec 5>&p; exec 6<&p; \
	    while IFS= read -r line; do \
		if [[ $$line = *" = "+([0-9a-fA-F]) ]]; then \
			print -ru5 "$$line"; \
		else \
			print -ru3 "$$line"; \
		fi; \
	    done <CKSUM; rm -f CKSUM; \
	    exec 3>&-; exec 5>&-; \
	    (cat <&4; cat <&6) | gzip -n9 >CKSUM.gz; \
	    dd if=/dev/zero bs=256 count=5 >>CKSUM.gz; \
	    ${SUDO} chown 0:0 00-README CKSUM.gz boot* bsd*; \
	    ${SUDO} chmod 444 00-README CKSUM.gz boot* bsd*; \
	    ${SUDO} chown 0:0 .; ${SUDO} chmod 555 .; \
	    ${SUDO} ${MKSH} ${.CURDIR}/mklocatedb.sh ${REALOBJDIR}/${IMAGE}
	${SUDO} mkisofs -R -f -L -d -D -N -v -v ${CDROM_MDOPTS} \
	    -P 'The MirOS Project and its contributors' \
	    -p 'Copyright © 2007-2008 Thorsten Glaser' \
	    -V 'MirOS #${OSrev} BSD/${MACHINE} Live CD' \
	    -volset "$$(uname -slm) Live" -sysid "MirOSBSD" \
	    -pad -o ${CDROM} ${WRKDIR} 2>&1 | tee mkisofs.log
	${SUDO} chown $$(id -u) ${CDROM} ${WRKDIR}
	${SUDO} chmod 755 ${WRKDIR}

cdrom-finish:

clean cleandir cleannobsd: cleanworkdir unconfig
	-rm -f ${CDROM} bsd{,.gz,.tmp} mkisofs.log ${IMAGE}
	-rm -rf tempdir

cleanworkdir:
	-test ! -e ${WRKDIR} || ${SUDO} rm -rf ${WRKDIR}

tstmnt:
	${SUDO} mkdir -p ${TMPMOUNT}
	${SUDO} vnconfig svnd0 ${CDROM}
	${SUDO} mount_cd9660 /dev/svnd0a ${TMPMOUNT}

tstumnt: unconfig

unconfig:
	-${SUDO} umount -f ${VND_DEV}
	-${SUDO} vnconfig -u ${VND}
	-${SUDO} rm -rf ${TMPMOUNT}

.include <bsd.obj.mk>
.include <bsd.subdir.mk>
