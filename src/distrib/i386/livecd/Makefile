# $MirOS: src/distrib/i386/livecd/Makefile,v 1.7 2006/04/05 23:40:47 tg Exp $

.include <bsd.own.mk>

CDROM?=		livecd${OSrev}.iso
REALOBJDIR!=	readlink -nf ${.OBJDIR}
HOSTCFLAGS?=	${CFLAGS} ${COPTS}

all install:

it: ${CDROM}

${CDROM}: unpack gendev addcontrib prepimg nukefiles makeimg

unpack:
	mkdir -p workdir/v8
.for _i in base dev etc gnu xbase xetc
	cd workdir && ${SUDO} tar xzphf ${BSDRELDIR}/rel/${_i}${OSrev}.ngz
.endfor
	cd workdir/v8 && ln -s ${BSDRELDIR}/rel i386
	cd workdir/etc; \
	    for a in ${.CURDIR}/../iso/boot.cfg ${.CURDIR}/boot.*; do \
		${SUDO} ln -fs $$a; \
	done

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

addcontrib:
	mkdir -p tempdir/jupp
	@if [[ -s ${BSDSRCDIR}/contrib/code/jupp/jupprc ]]; then \
		cd tempdir/jupp; \
		lndir ${BSDSRCDIR}/contrib/code/jupp; \
	else \
		cd tempdir; \
		cvs -Rqz3 -d _anoncvs@anoncvs.66h.42h.de:/cvs co \
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

prepimg:
	cd workdir && ${SUDO} mksh ${.CURDIR}/munge_it.sh

bsd.gz: ${REALOBJDIR}/../generic/bsd mr.fs rdsetroot
	-rm -f bsd bsd.gz
	gzip -d <${REALOBJDIR}/../generic/bsd >bsd
	print 'rootdev 6 0\nquit' | config -ef bsd	# (6,0) = cd0a
	./rdsetroot bsd <mr.fs
	gzip -n9 bsd

nukefiles:
	cd workdir/usr && ${SUDO} rm -rf \
	    X11R6/{lib/X11/doc,man} {,share/}{doc,info,man} releng

makeimg: bsd.gz
	${SUDO} dd if=bsd.gz obs=2048 conv=osync of=workdir/bsd
	${SUDO} dd if=${BSDOBJDIR}/sys/arch/i386/stand/liveboot/boot \
	    obs=2048 conv=osync of=workdir/etc/boot.x86
	-rm -f ${CDROM}
	touch ${CDROM}
	${SUDO} mkisofs -R -T -L -d -D -N -v -v -f \
	    -b etc/boot.x86 -c etc/boot.cat -p "Thorsten Glaser" \
	    -P "The http://MirBSD.org/ team and its contributors" \
	    -V "MirOS #${OSrev} BSD/${MACHINE} Live CD" \
	    -volset "$$(uname -slm) Live" -sysid "MirOSBSD" \
	    -no-emul-boot -boot-load-size 4 -boot-info-table \
	    -pad -o ${CDROM} workdir 2>&1 | tee mkisofs.log
	workdir/usr/mdec/installboot -v -I \
	    $$(fgrep 'workdir/usr/mdec/boot' mkisofs.log | \
		while read start end rest; do print $$start $$end; done) \
	    workdir/usr/mdec/ldsec ${CDROM}

rdsetroot:	${.CURDIR}/../../common/elfrdsetroot.c
	${HOSTCC} ${HOSTCFLAGS} -DDEBUG -o $@ ${.ALLSRC}

unconfig:
	-${SUDO} umount -f /dev/svnd0a
	-${SUDO} vnconfig -u svnd0

.PHONY:	addcontrib clean cleandir cleannobsd gendev it makeimg \
	nukefiles prepimg tstmnt tstumnt unconfig unpack

clean cleandir cleannobsd:
	-rm -f ${CDROM} bsd{,.gz} mkisofs.log mr.fs rdsetroot
	-rm -rf tempdir tmpmnt
	-${SUDO} rm -rf workdir

tstmnt:
	${SUDO} vnconfig svnd0 ${CDROM}
	${SUDO} mount_cd9660 /dev/svnd0a tmpmnt

tstumnt: unconfig

.include <bsd.obj.mk>
.include <bsd.subdir.mk>
