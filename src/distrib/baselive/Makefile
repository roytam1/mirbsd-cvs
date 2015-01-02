# $MirOS: src/distrib/baselive/Makefile,v 1.66 2014/01/04 20:24:56 tg Exp $

.include <bsd.own.mk>

# common variables
REALOBJDIR!=	realpath ${.OBJDIR}
TOPDIR?=	${.CURDIR}/..

DUALIVE?=	No
BATCH?=		No
GRML?=		No

.if ${GRML:L} != "no"
BATCH=		No
.endif

.if ${DUALIVE:L} == "no"
STUFFDIR=	${BSDRELDIR}/rel
.else
STUFFDIR=	${DUALIVE}/i386
.endif

.MAIN: all

KERNEL_PREP=	print 'rootdev 6 0\nquit' | config -ef bsd.tmp
.if exists(${REALOBJDIR}/../../sys/arch/i386/stand/liveboot/.)
BOOT=		${REALOBJDIR}/../../sys/arch/i386/stand/liveboot/boot
DO_LIVEBOOT=	#defined
.endif
CDROM_OPTS+=	bootimage=i386\;b_torito.ldr
CDROM_OPTS+=	no-emul-boot

CHAINSECTOR?=	24

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

BOOT?=		${WRKDIR}/v${OSrev}/i386/boot

CDROM?=		livecd${OSrev}.iso
CDROM_OPTS+=	applicationid=NetBSD_makefs
CDROM_OPTS+=	hide-rr-moved
.if ${DUALIVE:L} != "no"
CDROM_OPTS+=	label=MirOS~v${OSrev}~BSD~DuaLive~CD
.else
CDROM_OPTS+=	label=MirOS~v${OSrev}~BSD/i386~Live~CD
.endif
CDROM_OPTS+=	no-trailing-padding
CDROM_OPTS+=	preparer=MirBSD_and_its_contributors
CDROM_OPTS+=	publisher=Copyright_\<c\>_2002=2015_The_MirOS_Project
CDROM_OPTS+=	rockridge
.if ${DUALIVE:L} != "no"
.  if ${GRML:L} != "no"
CDROM_OPTS+=	volumeid=$$(uname -sl | tr -- '- \#' :_):Triforce
.  else
CDROM_OPTS+=	volumeid=$$(uname -sl | tr -- '- \#' :_):DuaLive
.  endif
.else
CDROM_OPTS+=	volumeid=$$(uname -slm | tr -- '- \#' :_):BaseLive
.endif
#CDROM_OPTS+=	v=1

.if ${DUALIVE:L} != "no"
LIVEBOOT_ARGS+=	DUALIVE=Yes
.endif
.if ${GRML:L} != "no"
LIVEBOOT_ARGS+=	GRML=Yes
.endif

BOOTCFG_SRCS=	${TOPDIR}/common/boot.cfg.i386
.if ${GRML:L} != "no"
BOOTCFG_SRCS+=	${.CURDIR}/boot.cfg.grml
.endif
.if ${DUALIVE:L} != "no"
BOOTCFG_SRCS+=	${.CURDIR}/boot.cfg.dual
.endif
BOOTCFG_SRCS+=	${.CURDIR}/boot.cfg.tail

all install:

do-cdrom: unpack addcontrib prepimg nukefiles makeimg

it: do-cdrom

unpack:
	test ! -e ${TMPMOUNT} || (cd ${.CURDIR}; ${MAKE} unconfig)
	${SUDO} rm -rf ${WRKDIR}
	mkdir -p ${WRKDIR}/v${OSrev}/i386
	# ensure they are releatively upfront on the CD
.if ${DUALIVE:L} != "no"
	touch ${WRKDIR}/{b_i386,b_sparc}.ldr
.else
	touch ${WRKDIR}/b_i386.ldr
.endif
.if ${GRML:L} != "no"
	mkdir -p ${WRKDIR}/boot/grml
.endif
	# needed for the installer of MirOS-current snapshots
	ln -s v${OSrev} ${WRKDIR}/current
	# unpack the dist sets
.for _i in base dev etc gnu xbase xetc xfont xserv
	cd ${WRKDIR} && ${SUDO} tar xzphf ${STUFFDIR}/${_i}${OSrev}.ngz
.endfor
	cd ${STUFFDIR} && pax -rw . ${WRKDIR}/v${OSrev}/i386/
.if ${DUALIVE:L} != "no"
	cd ${DUALIVE} && pax -rw sparc ${WRKDIR}/v${OSrev}/
.endif
	${SUDO} chown -R 0:0 ${WRKDIR}/v${OSrev}
	cp ${TOPDIR}/common/{00-README,01-3RDPTY} ${WRKDIR}/
	cat ${BOOTCFG_SRCS} | sudo dd of=${WRKDIR}/boot.cfg
	${SUDO} cp ${.CURDIR}/i386/boot.* ${WRKDIR}/
.if ${GRML:L} == "no"
	${SUDO} rm -f ${WRKDIR}/boot.9
.endif
	${SUDO} mkdir -p ${WRKDIR}/boot/grub
	${SUDO} cp ${.CURDIR}/i386/loopback.* ${WRKDIR}/boot/grub/

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
	    ${MKSH} ${BSDSRCDIR}/contrib/code/jupp/configure --disable-termidx \
	    --sysconfdir=/etc --disable-dependency-tracking --prefix=/usr && \
	    make && ${SUDO} make install DESTDIR=${WRKDIR:Q}
	cd tempdir; cp ${BSDSRCDIR}/contrib/code/Snippets/tinyirc.c . && \
	    make -f tinyirc.c && ${SUDO} make -f tinyirc.c install \
	    DESTDIR=${WRKDIR:Q} BINDIR=/usr/bin
	${SUDO} install -o 0 -g 0 -m 644 \
	    ${BSDSRCDIR}/contrib/samples/dot.Xmodmap \
	    ${WRKDIR}/etc/skel/.Xmodmap

prepimg:
	cd ${WRKDIR} && MACHINE=i386 \
	    ${SUDO} ${MKSH} ${.CURDIR}/munge_it.sh

bsd.gz: bsd ${IMAGE}
	-rm -f bsd.tmp
	gzip -d <bsd >bsd.tmp
	${KERNEL_PREP}
	${RDSETROOT} bsd.tmp <${IMAGE}
	gzip -n9 <bsd.tmp >$@

.if ${DUALIVE:L} != "no"
bsd: ${DUALIVE}/i386/bsd
.else
bsd: ${BSDOBJDIR}/distrib/generic/bsd
.endif
	cp -f $> $@

nukefiles:
	cd ${WRKDIR} && ${SUDO} rm -rf etc/X11 usr/{local/lib/X11,releng} \
	    usr/{,X11R6/}{doc,info,man} usr/X11R6/lib/X11/doc
.if ${DEBUGLIBS:L} == "yes"
	-for name in ${WRKDIR}/usr/{,X11R6/}lib/*@(.so.*|.a); do \
		print -n stripping $${name##*/} ...; \
		if [[ $$name = *.a ]]; then \
			for i in $${name%a}so*; do \
				if [[ -e $$i ]]; then \
					print deleted for $${i##*/}; \
					${SUDO} rm -f $$name; \
				else \
					${SUDO} strip --strip-unneeded \
					    $$name && print; \
				fi; \
				break; \
			done; \
		else \
			${SUDO} strip --strip-unneeded $$name && print; \
		fi; \
	done
.endif

makeimg: cdrom-prepare cdrom-generate

cdrom-prepare: bsd.gz
	${SUDO} chown $$(id -u) ${WRKDIR}
	chmod 755 ${WRKDIR}
	${SUDO} dd if=bsd.gz obs=2048 conv=osync of=${WRKDIR}/bsd
.if ${DUALIVE:L} != "no"
	${SUDO} cp ${DUALIVE}/sparc/boot ${WRKDIR}/b_sparc.ldr
	# fix path to default kernel file in second-stage boot loader
	set -A dump -- $$(dd if=${WRKDIR}/b_sparc.ldr bs=4 count=64 | \
	    hexdump -ve '1/1 "%02X"' | sed 's/\(........\)/ \1/g'); i=0; \
	while (( i < 64 )); do [[ $${dump[i++]} = 2035560? ]] && break; done; \
	if [[ $$i = 64 || $${dump[i-1]} != 20355601 ]]; then \
		print -u2 found invalid or no patch field version; exit 1; \
	fi; ofs=$$((#0x$${dump[i+1]})); \
	print -n v${OSrev}/sparc/bsd.rd\\0 | \
	    ${SUDO} dd of=${WRKDIR}/b_sparc.ldr bs=1 seek=$$ofs conv=notrunc
.endif
.ifdef DO_LIVEBOOT
	cd ${.CURDIR}/../../sys/arch/i386/stand/liveboot; \
	    ${MAKE} ${LIVEBOOT_ARGS} cleandir && \
	    ${MAKE} ${LIVEBOOT_ARGS} depend && \
	    exec ${MAKE} ${LIVEBOOT_ARGS}
.endif
	cd ${WRKDIR}; \
	    ${SUDO} cp ${BOOT} b_i386.ldr; \
	    ${SUDO} rm -f CKSUM*; \
	    if [[ -e v${OSrev}/i386/CKSUM ]]; then \
		cat v${OSrev}/i386/CKSUM >CKSUM~; \
	    else \
		gzip -dc v${OSrev}/i386/CKSUM.gz >CKSUM~; \
	    fi; \
	    while IFS= read -r line; do \
		if [[ $$line = *" = "+([0-9a-fA-F]) ]]; then \
			two=$${line#+([A-Z0-9]) \(}; \
		else \
			two=$${line#+([0-9]) +([0-9]) }; \
		fi; \
		one=$${line%%$$two}; \
		print -r "$${one}v${OSrev}/i386/$$two"; \
	    done <CKSUM~ >>CKSUM
.if ${DUALIVE:L} != "no"
	cd ${WRKDIR}; \
	    if [[ -e v${OSrev}/sparc/CKSUM ]]; then \
		cat v${OSrev}/sparc/CKSUM >CKSUM~; \
	    else \
		gzip -dc v${OSrev}/sparc/CKSUM.gz >CKSUM~; \
	    fi; \
	    while IFS= read -r line; do \
		if [[ $$line = *" = "+([0-9a-fA-F]) ]]; then \
			two=$${line#+([A-Z0-9]) \(}; \
		else \
			two=$${line#+([0-9]) +([0-9]) }; \
		fi; \
		one=$${line%%$$two}; \
		print -r "$${one}v${OSrev}/sparc/$$two"; \
	    done <CKSUM~ >>CKSUM
.endif
	cd ${WRKDIR}; \
	    cksum -a cksum -a rmd160 -a tiger 0* bsd b_* gzs* stand/* >>CKSUM
	-${SUDO} rm -f ${CDROM}* ${WRKDIR}/CKSUM~

cdrom-generate:
.if ${BATCH:L} != "yes"
	@print WRKDIR is \"${WRKDIR:Q}\"
	@print Build coordination: press RETURN to continue...; read dummy
.endif
	${SUDO} chown $$(id -u) ${WRKDIR}
	chmod 755 ${WRKDIR}
	cd ${WRKDIR}; \
	    [[ -e CKSUM && ! -e CKSUM.gz ]] || ${SUDO} gzip -d CKSUM; \
	    sort -k3 |& exec 3>&p; exec 4<&p; \
	    sort |& exec 5>&p; exec 6<&p; \
	    while IFS= read -r line; do \
		if [[ $$line = *" = "+([0-9a-fA-F]) ]]; then \
			print -ru5 "$$line"; \
		else \
			print -ru3 "$$line"; \
		fi; \
	    done <CKSUM; ${SUDO} rm -f CKSUM*; \
	    exec 3>&-; exec 5>&-; \
	    (cat <&4; cat <&6) | gzip -n9 >CKSUM.gz; \
	    dd if=/dev/zero bs=256 count=5 >>CKSUM.gz; \
	    flst=; for f in 0?-* NONFREE.TXT CKSUM.gz b_* gzsig* ?oot* ?sd* \
	    boot/grub/*; do [[ -e $$f ]] && flst="$$flst $$f"; done; \
	    ${SUDO} chown 0:0 . $$flst; \
	    for f in $$flst .; do if [[ -d $$f ]]; then \
		${SUDO} chmod 555 $$f; else ${SUDO} chmod 444 $$f; fi; \
	    done; \
	    ${SUDO} ${MKSH} ${.CURDIR}/mklocatedb.sh ${REALOBJDIR}/${IMAGE}
	(gzip -d <${WRKDIR}/CKSUM.gz | fgrep -v stand/locate.database; \
	    cd ${WRKDIR}; cksum -a cksum -a rmd160 -a tiger \
	    stand/locate.database) >tempdir/CKSUM
	cd ${WRKDIR}; \
	    sort -k3 |& exec 3>&p; exec 4<&p; \
	    sort |& exec 5>&p; exec 6<&p; \
	    while IFS= read -r line; do \
		if [[ $$line = *" = "+([0-9a-fA-F]) ]]; then \
			print -ru5 "$$line"; \
		else \
			print -ru3 "$$line"; \
		fi; \
	    done <${REALOBJDIR}/tempdir/CKSUM; \
	    exec 3>&-; exec 5>&-; \
	    ( (cat <&4; cat <&6) | gzip -n9; \
	      dd if=/dev/zero bs=256 count=5 2>&- ) | \
	    ${SUDO} dd of=CKSUM.gz
	dd if=/dev/arandom bs=2048 count=1 of=b_torito.ldr
	${SUDO} makefs -t cd9660 -o "$$(print -r -- ${CDROM_OPTS} | \
	    tr ' ~' ', ')" ${CDROM} ${WRKDIR}
	${SUDO} chown $$(id -u) ${CDROM} ${WRKDIR}
	chmod 755 ${WRKDIR}
	# pad the ISO with ]0;256K] NUL bytes, ie. for
	# a geometry of 16 heads, 32 sectors per track
	dd if=/dev/zero count=1 bs=$$((# (512 * 32 * 16) - \
	    ($$(stat -f %z ${CDROM}) % (512 * 32 * 16)) )) 2>&- >>${CDROM}
	getextent_cd9660 -f ${CDROM} b_i386.ldr | \
	    ${MKSH} ${WRKDIR}/v${OSrev}/i386/bootxx.sh -B 11 | \
	    dd of=${CDROM} conv=notrunc bs=2048 seek=$$(getextent_cd9660 \
	    -f ${CDROM} -b '$$BootImage$$') 2>/dev/null
.if ${DUALIVE:L} == "no"
	getextent_cd9660 -f ${CDROM} b_i386.ldr | \
	    ${MKSH} ${WRKDIR}/v${OSrev}/i386/bootxx.sh \
	    -g $$((#$$(stat -f %z ${CDROM}) / (512 * 32 * 16))):16:32 \
	    -A -M 4:0x96 -S 2 | \
	    dd of=${CDROM} conv=notrunc bs=512 2>/dev/null
.else
	getextent_cd9660 -f ${CDROM} b_i386.ldr | \
	    ${MKSH} ${WRKDIR}/v${OSrev}/i386/bootxx.sh -A -S 2 | \
	    dd of=${CDROM} conv=notrunc bs=512 seek=${CHAINSECTOR} 2>/dev/null
	getextent_cd9660 -f ${CDROM} b_sparc.ldr | \
	    ${MKSH} ${WRKDIR}/v${OSrev}/sparc/bootxx.sh \
	    -g $$((#$$(stat -f %z ${CDROM}) / (512 * 32 * 16))):16:32 \
	    -0 ${CHAINSECTOR} -S 2 | \
	    dd of=${CDROM} conv=notrunc 2>/dev/null
.endif

clean cleandir cleannobsd: cleanworkdir unconfig
	-rm -f ${CDROM}* bsd{,.gz,.tmp} ${IMAGE}
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
