# $MirOS: src/distrib/baselive/Makefile,v 1.39 2008/10/30 17:47:32 tg Exp $

.include <bsd.own.mk>

# common variables
REALOBJDIR!=	realpath ${.OBJDIR}
TOPDIR?=	${.CURDIR}/..

DUALIVE?=	No
BATCH?=		No

.if ${DUALIVE:L} == "no"
STUFFDIR=	${BSDRELDIR}/rel
.else
STUFFDIR=	${DUALIVE}/i386
.endif

.MAIN: all

KERNEL_PREP=	print 'rootdev 6 0\nquit' | config -ef bsd.tmp
.if exists(${REALOBJDIR}/../../sys/arch/i386/stand/liveboot/boot)
BOOT=		${REALOBJDIR}/../../sys/arch/i386/stand/liveboot/boot
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
.if ${DUALIVE:L} != "no"
# no need as long as it's < 300 KiB and makefs -o no-trailing-padding isn't used
#CDROM_PAD?=	16 * 32
.endif
CDROM_PAD?=	1
CDROM_OPTS+=	applicationid=NetBSD_makefs
.if ${DUALIVE:L} != "no"
CDROM_OPTS+=	label=MirOS~v${OSrev}~BSD~DuaLive~CD
.else
CDROM_OPTS+=	label=MirOS~v${OSrev}~BSD/i386~Live~CD
.endif
CDROM_OPTS+=	preparer=MirBSD_and_its_contributors
CDROM_OPTS+=	publisher=Copyright_\<c\>_2002=2008_The_MirOS_Project
CDROM_OPTS+=	rockridge
.if ${DUALIVE:L} != "no"
CDROM_OPTS+=	volumeid=$$(uname -sl | tr -- '- \#' :_):DuaLive
.else
CDROM_OPTS+=	volumeid=$$(uname -slm | tr -- '- \#' :_):BaseLive
.endif
#CDROM_OPTS+=	v=1

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
.for _i in base dev etc gnu xbase xetc xsrv
	cd ${WRKDIR} && ${SUDO} tar xzphf ${STUFFDIR}/${_i}${OSrev}.ngz
.endfor
	cd ${STUFFDIR} && pax -rw . ${WRKDIR}/v${OSrev}/i386/
.if ${DUALIVE:L} != "no"
	cd ${DUALIVE} && pax -rw sparc ${WRKDIR}/v${OSrev}/
.endif
	${SUDO} chown -R 0:0 ${WRKDIR}/v${OSrev}
	cp ${TOPDIR}/common/{00-README,01-3RDPTY} ${WRKDIR}/
.if ${DUALIVE:L} != "no"
	cat ${TOPDIR}/common/boot.cfg.i386 ${.CURDIR}/boot.cfg.dual \
	    ${.CURDIR}/boot.cfg.tail | sudo dd of=${WRKDIR}/boot.cfg
.else
	cat ${TOPDIR}/common/boot.cfg.i386 ${.CURDIR}/boot.cfg.tail | \
	    sudo dd of=${WRKDIR}/boot.cfg
.endif
	${SUDO} cp ${.CURDIR}/i386/boot.* ${WRKDIR}/

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
					${SUDO} strip -g $$name && print; \
				fi; \
				break; \
			done; \
		else \
			${SUDO} strip -s $$name && print; \
		fi; \
	done
.endif

makeimg: cdrom-prepare cdrom-generate

cdrom-prepare: bsd.gz
	${SUDO} dd if=bsd.gz obs=2048 conv=osync of=${WRKDIR}/bsd
.if ${DUALIVE:L} != "no"
	${SUDO} cp ${DUALIVE}/sparc/boot ${WRKDIR}/b_sparc.ldr
	# fix path to default kernel file in second-stage boot loader
	set -A sect_text -- $$(objdump -wh --target=a.out-sunos-big \
	    ${WRKDIR}/b_sparc.ldr | fgrep .text); \
	(( fofs_text = 0x$${sect_text[5]} )); \
	nm --target=a.out-sunos-big ${WRKDIR}/b_sparc.ldr |& \
	while read -p adr typ sym; do \
		[[ $$sym = @(___defkernel|_start) ]] || continue; \
		eval typeset -i10 sym$$sym=0x\$$adr; \
	done; \
	typeset -Uui10 ofs; \
	(( ofs = sym___defkernel - sym_start + fofs_text )); \
	print -n v${OSrev}/sparc/bsd.rd\\0 | \
	    ${SUDO} dd of=${WRKDIR}/b_sparc.ldr bs=1 seek=$$ofs conv=notrunc
	${SUDO} strip --target=a.out-sunos-big ${WRKDIR}/b_sparc.ldr
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
	    cksum -a cksum -a rmd160 -a tiger 0* bsd b_* stand/* >>CKSUM
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
	    ${SUDO} chown 0:0 0?-* $$([[ ! -e NONFREE.TXT ]] || \
	    print NONFREE.TXT) CKSUM.gz b_* ?oot* ?sd*; \
	    ${SUDO} chmod 444 0?-* $$([[ ! -e NONFREE.TXT ]] || \
	    print NONFREE.TXT) CKSUM.gz b_* ?oot* ?sd*; \
	    ${SUDO} chown 0:0 .; ${SUDO} chmod 555 .; \
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
	    tr ' ~' ', ')" ${CDROM}~ ${WRKDIR}
	${SUDO} chown $$(id -u) ${CDROM}~ ${WRKDIR}
	chmod 755 ${WRKDIR}
.if ${CDROM_PAD} == 1
	mv ${CDROM}~ ${CDROM}
.else
	dd if=${CDROM}~ of=${CDROM} obs=$$((${CDROM_PAD} * 512)) conv=osync
	${SUDO} rm -f ${CDROM}~
.endif
	getextent_cd9660 -f ${CDROM} b_i386.ldr | \
	    ${MKSH} ${WRKDIR}/v${OSrev}/i386/bootxx.sh -B 11 | \
	    dd of=${CDROM} conv=notrunc bs=2048 seek=$$(getextent_cd9660 \
	    -f ${CDROM} -b '$$BootImage$$') 2>/dev/null
.if ${DUALIVE:L} == "no"
	getextent_cd9660 -f ${CDROM} b_i386.ldr | \
	    ${MKSH} ${WRKDIR}/v${OSrev}/i386/bootxx.sh -S 2 | \
	    dd of=${CDROM} conv=notrunc bs=512 2>/dev/null
.else
	getextent_cd9660 -f ${CDROM} b_i386.ldr | \
	    ${MKSH} ${WRKDIR}/v${OSrev}/i386/bootxx.sh -S 2 | \
	    dd of=${CDROM} conv=notrunc bs=512 seek=${CHAINSECTOR} 2>/dev/null
	getextent_cd9660 -f ${CDROM} b_sparc.ldr | \
	    ${MKSH} ${WRKDIR}/v${OSrev}/sparc/bootxx.sh \
	    -g $$(($$(stat -f %z ${CDROM}) / (512 * 32 * 16))):16:32 \
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
