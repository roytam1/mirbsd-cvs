# $MirOS: src/distrib/i386/livecd/Makefile,v 1.46 2006/05/29 17:30:20 tg Exp $

.include <bsd.own.mk>

CDROM?=		livecd${OSrev}.iso
REALOBJDIR!=	readlink -nf ${.OBJDIR}
HOSTCFLAGS?=	${CFLAGS} ${COPTS}

ANONCVSROOT=	anoncvs@anoncvs.mirbsd.org:/cvs

all install:

it: ${CDROM}

${CDROM}: unpack gendev addcontrib prepimg nukefiles makeimg

unpack:
	mkdir -p workdir/v${OSrev}
.for _i in base dev etc gnu ports xbase xetc
	cd workdir && ${SUDO} tar xzphf ${BSDRELDIR}/rel/${_i}${OSrev}.ngz
.endfor
	cd workdir && ln -s ${.CURDIR}/../iso/00-README
	cd workdir/v${OSrev} && ln -s ${BSDRELDIR}/rel i386
	cd workdir/etc; \
	    for a in ${.CURDIR}/../iso/boot.cfg ${.CURDIR}/boot.*; do \
		${SUDO} cp $$a .; \
	done
	# create mount points
	${SUDO} mkdir workdir/usr/{mpkg,ports/{Distfiles,Packages}}

gendev: mr.fs

mr.fs:
	dd if=/dev/zero of=mr.fs bs=512 count=8192
	${SUDO} vnconfig -v -c svnd0 mr.fs
	${SUDO} disklabel -w -r svnd0 ipldisc
	${SUDO} newfs -m 0 -o space -c 16 -i 1024 /dev/rsvnd0a
	mkdir -p tmpmnt
	${SUDO} mount /dev/svnd0a tmpmnt
	${SUDO} cp workdir/dev/MAKEDEV tmpmnt/
	cd tmpmnt && ${SUDO} ${MKSH} ./MAKEDEV all
	@${SUDO} dd if=/dev/urandom bs=512 count=8 of=tmpmnt/.rs
	@df -i tmpmnt
	-${SUDO} umount tmpmnt
	-${SUDO} vnconfig -u svnd0

addcontrib: addjupp addtinyirc

addjupp:
	mkdir -p tempdir/jupp
	@if [[ -s ${BSDSRCDIR}/contrib/code/jupp/jupprc ]]; then \
		cd tempdir/jupp; \
		lndir ${BSDSRCDIR}/contrib/code/jupp; \
	else \
		cd tempdir; \
		cvs -Rqz3 -d ${ANONCVSROOT} co \
		    -PAdjupp contrib/code/jupp || rm -rf jupp; \
	fi
	@if [[ -d tempdir/jupp ]]; then \
		targpath=$$(readlink -nf workdir); \
		cd tempdir/jupp; \
		CC=${CC:Q} CFLAGS=${CFLAGS:Q}\ ${COPTS:Q} ${MKSH} \
		    ./configure --prefix=/usr --sysconfdir=/etc; \
		make; \
		${SUDO} make install DESTDIR="$$targpath"; \
	fi

addtinyirc:
	mkdir -p tempdir/tinyirc
	@if [[ -s ${BSDSRCDIR}/contrib/code/Snippets/tinyirc.c ]]; then \
		cd tempdir/tinyirc; \
		lndir ${BSDSRCDIR}/contrib/code/Snippets; \
	else \
		cd tempdir; \
		cvs -Rqz3 -d ${ANONCVSROOT} co \
		    -PAdtinyirc contrib/code/Snippets/tinyirc.c \
		    || rm -rf tinyirc; \
	fi
	@if [[ -s tempdir/tinyirc/tinyirc.c ]]; then \
		targpath=$$(readlink -nf workdir); \
		cd tempdir/tinyirc; \
		${CC} ${CFLAGS} ${COPTS} ${CPPFLAGS} ${LDFLAGS} \
		    ${LDSTATIC} tinyirc.c -ltermcap; \
		${SUDO} install -c -s -o root -g bin -m 555 a.out \
		    $$targpath/usr/bin/tinyirc; \
	fi

prepimg:
	cd workdir && ${SUDO} mksh ${.CURDIR}/munge_it.sh

bsd.gz: ${REALOBJDIR}/../generic/bsd mr.fs rdsetroot
	-rm -f bsd bsd.gz
	gzip -d <${REALOBJDIR}/../generic/bsd >bsd
	print 'rootdev 6 0\nquit' | config -ef bsd	# (6,0) = cd0a
	./rdsetroot bsd <mr.fs
	gzip -n9 bsd

nukefiles:
#	cd workdir && ${SUDO} rm -rf etc/X11 usr/{local/lib/X11,releng} \
#	    usr/{,X11R6/,share/}{doc,info,man} usr/X11R6/lib/X11/doc
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
	    workdir/usr/mdec/ldsec ${CDROM}

rdsetroot:	${.CURDIR}/../../common/elfrdsetroot.c
	${HOSTCC} ${HOSTCFLAGS} -DDEBUG -o $@ ${.ALLSRC}

unconfig:
	-${SUDO} umount -f /dev/svnd0a
	-${SUDO} vnconfig -u svnd0

.PHONY:	addcontrib addjupp addtinyirc clean cleandir cleannobsd cleanworkdir \
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
