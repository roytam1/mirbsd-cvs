# $MirOS: src/distrib/baselive/Makefile,v 1.3 2006/08/18 22:32:40 tg Exp $

.include <bsd.own.mk>

TOPDIR?=	${.CURDIR}/..
CDROM?=		livecd${OSrev}.iso
REALOBJDIR!=	readlink -nf ${.OBJDIR}

ANONCVSROOT=	anoncvs@anoncvs.mirbsd.org:/cvs

all install:

it: ${CDROM}

.ifdef FINISHED_WORK
${CDROM}: unpack gendev addcontrib prepimg nukefiles makeimg
.else
${CDROM}:
	@print -u2 The baselive cd infrastructure is not ready yet.
	@print -u2 Please try again later.
	@touch $@
.endif

unpack:
	mkdir -p workdir/v${OSrev}
.for _i in base dev etc gnu xbase xetc
	cd workdir && ${SUDO} tar xzphf ${BSDRELDIR}/rel/${_i}${OSrev}.ngz
.endfor
	cd workdir && ln -sf ${TOPDIR}/common/00-README
	cd workdir/v${OSrev} && ln -s ${BSDRELDIR}/rel i386
	${SUDO} cp ${.CURDIR}/boot.* workdir/etc/

gendev: mr.fs

mr.fs:
	dd if=/dev/zero of=mr.fs bs=512 count=8192
	${SUDO} vnconfig -v -c svnd0 mr.fs
	${SUDO} disklabel -w -r svnd0 ipldisc
	${SUDO} newfs -m 0 -o space -c 16 -i 1024 /dev/rsvnd0a
	mkdir -p tmpmnt
	${SUDO} mount /dev/svnd0a tmpmnt
	${SUDO} cp workdir/dev/MAKEDEV tmpmnt/
	cd tmpmnt && ${SUDO} ${MKSH} MAKEDEV all
	@${SUDO} dd if=/dev/arandom bs=512 count=4 of=tmpmnt/.rs
	@df -i tmpmnt
	-${SUDO} umount tmpmnt
	-${SUDO} vnconfig -u svnd0

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
	targpath=$$(readlink -nf workdir); cd tempdir; \
	    CC=${CC:Q} CFLAGS=${CFLAGS:Q}\ ${COPTS:Q} \
	    ${MKSH} ${BSDSRCDIR}/contrib/code/jupp/configure \
	    --prefix=/usr --sysconfdir=/etc && \
	    make && ${SUDO} make install DESTDIR="$$targpath"
	cd tempdir; cp ${BSDSRCDIR}/contrib/code/Snippets/tinyirc.c . && \
	    print 'PROG=tinyirc\nLDADD=-ltermcap\nNOMAN=yes\n.include' \
	    '<bsd.prog.mk>' >mkirc && make -f mkirc && \
	    ${SUDO} make -f mkirc install BINDIR=../workdir/usr/bin

prepimg:
	cd workdir && MACHINE=${MACHINE} \
	    ${SUDO} ${MKSH} ${.CURDIR}/munge_it.sh

bsd.gz: ${REALOBJDIR}/../generic/bsd mr.fs
	-rm -f bsd bsd.gz
	gzip -d <${REALOBJDIR}/../generic/bsd >bsd
	print 'rootdev 6 0\nquit' | config -ef bsd	# (6,0) = cd0a
	${REALOBJDIR}/../common/elfrdsetroot bsd <mr.fs
	gzip -n9 bsd

nukefiles:
	cd workdir && ${SUDO} rm -rf etc/X11 usr/{local/lib/X11,releng} \
	    usr/{,X11R6/}{doc,info,man} usr/X11R6/lib/X11/doc
	-for name in workdir/usr/lib/*@(.so.*|.a); do \
		print -n stripping $$name ...; \
		if [[ $$name = *.a ]]; then \
			${SUDO} strip -g $$name && print; \
		else \
			${SUDO} strip -s $$name && print; \
		fi; \
	done

makeimg: bsd.gz mr.fs
	${SUDO} dd if=bsd.gz obs=2048 conv=osync of=workdir/bsd
	${SUDO} dd if=${BSDOBJDIR}/sys/arch/i386/stand/liveboot/boot \
	    obs=2048 conv=osync of=workdir/v${OSrev}/i386/boot.liv
	cd workdir/v${OSrev}/i386 && ${SUDO} cp boot.liv boot.iso
	sed 's!RMD160 (!&v${OSrev}/i386/!' <workdir/v${OSrev}/i386/RMD160 \
	    >workdir/RMD160
	touch workdir/boot.cat
	cd workdir && rmd160 00-README boot.cat bsd stand/fsrw.cpio \
	    tftpboot/bsd tftpboot/pxeboot v${OSrev}/i386/boot.iso \
	    v${OSrev}/i386/boot.liv >>RMD160
	rm -f workdir/boot.cat
	cd workdir; rm -f boot.cat; sort -uo RMD160 RMD160; gzip -n9 RMD160
	# pad for gzsig(1) application later on
	dd if=/dev/zero count=2 >>workdir/RMD160.gz
	-rm -f ${CDROM}
	cd workdir && ${SUDO} ${MKSH} ${.CURDIR}/mklocatedb.sh \
	    ${REALOBJDIR}/mr.fs
	touch ${CDROM}
	${SUDO} mkisofs -R -L -d -D -N -v -v -f \
	    -b v${OSrev}/i386/boot.iso -c boot.cat -p "Thorsten Glaser" \
	    -P "The http://MirBSD.de/ team and its contributors" \
	    -V "MirOS #${OSrev} BSD/${MACHINE} Live CD" \
	    -volset "$$(uname -slm) Live" -sysid "MirOSBSD" \
	    -no-emul-boot -boot-load-size 4 -boot-info-table \
	    -pad -o ${CDROM} workdir 2>&1 | tee mkisofs.log
	workdir/usr/mdec/installboot -v -I \
	    $$(fgrep 'workdir/v${OSrev}/i386/boot.liv' mkisofs.log | \
		while read start end rest; do print $$start $$end; done) \
	    workdir/usr/mdec/bootxx ${CDROM}

rdsetroot: ${TOPDIR}/common/elfrdsetroot.c
	${HOSTCC} ${HOSTCFLAGS} -DDEBUG -o $@ ${.ALLSRC}

unconfig:
	-${SUDO} umount -f /dev/svnd0a
	-${SUDO} vnconfig -u svnd0

.PHONY:	addcontrib clean cleandir cleannobsd cleanworkdir \
	gendev it makeimg nukefiles prepimg tstmnt tstumnt unconfig unpack

clean cleandir cleannobsd: cleanworkdir
	-rm -f ${CDROM} bsd{,.gz} mkisofs.log mr.fs rdsetroot
	-rm -rf tempdir tmpmnt

cleanworkdir:
	-test ! -e workdir || ${SUDO} rm -rf workdir

tstmnt:
	${SUDO} vnconfig svnd0 ${CDROM}
	${SUDO} mount_cd9660 /dev/svnd0a tmpmnt

tstumnt: unconfig

.include <bsd.obj.mk>
.include <bsd.subdir.mk>
