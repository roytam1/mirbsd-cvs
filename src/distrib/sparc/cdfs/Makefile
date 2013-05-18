# $MirOS: src/distrib/sparc/cdfs/Makefile,v 1.4 2006/07/05 04:47:34 tg Exp $
# $OpenBSD: Makefile,v 1.5 2005/03/11 15:40:59 deraadt Exp $

CDROM?=		cdrom${OSrev}.iso
REALOBJDIR!=	readlink -nf ${.OBJDIR} || ( cd ${.OBJDIR} && pwd )

all: ${CDROM}

${CDROM}: prepare-workdir generate-image

prepare-workdir:
	@if [[ -e Makefile ]]; then \
		echo Error: do a make obj first; \
		exit 1; \
	fi
.ifndef NOPRUNE
	-rm -rf workdir
.endif
	mkdir -p workdir/{etc,v${OSrev}/sparc}
	@if [[ -e ${.CURDIR}/contrib ]]; then \
		echo Integrating contrib dir; \
		mkdir workdir/contrib; \
		cd workdir/contrib; \
		lndir ${.CURDIR}/contrib; \
	fi
	cp ${DESTDIR}/usr/mdec/boot ${DESTDIR}/usr/mdec/bootxx \
	    workdir/v${OSrev}/sparc/
	cp ${REALOBJDIR}/../../ramdisk/bsd.rd workdir/v${OSrev}/sparc/
	ln workdir/v${OSrev}/sparc/bsd.rd workdir/bsd.rd
	ln workdir/v${OSrev}/sparc/bsd.rd workdir/bsd
	ln workdir/v${OSrev}/sparc/bsd.rd workdir/vmunix	# for kicks
	cp ${.CURDIR}/boot.cfg workdir/etc/
	cp ${.CURDIR}/00-README workdir/

generate-image:
	mkisofs -r -f -L -d -D -N -v -v \
	    -P "The http://MirBSD.de/ team and its contributors" \
	    -p "Copyright © 2002-2006 by The MirOS Project" \
	    -V "MirOS #${OSrev} BSD/${MACHINE} boot-only CD" \
	    -volset "$$(uname -slm) Setup" -sysid "MirOSBSD" \
	    -pad -o ${CDROM} workdir 2>&1 | tee mkisofs.log
	${SUDO} vnconfig -v -c svnd0 ${CDROM}
	mkdir -p tmpmnt
	${SUDO} mount -t cd9660 /dev/svnd0a ${REALOBJDIR}/tmpmnt
	${SUDO} /usr/mdec/installboot -v \
	    -s $$(fgrep -v Name mkisofs.log | egrep 'v${OSrev}/sparc/boot$$'  | cut -d' ' -f1) \
	    -e $$(fgrep -v Name mkisofs.log | egrep 'v${OSrev}/sparc/boot$$'  | cut -d' ' -f2) \
	    ${REALOBJDIR}/tmpmnt/v${OSrev}/sparc/boot \
	    ${DESTDIR}/usr/mdec/bootxx /dev/rsvnd0c
	${SUDO} disklabel -w svnd0 fakecdrom "MirOS BSD/sparc "
	${SUDO} umount ${REALOBJDIR}/tmpmnt
	${SUDO} vnconfig -u svnd0

install:
	cp ${CDROM} ${DESTDIR}/snapshot/

clean cleandir cleannobsd:
	-rm -rf ${CDROM} mkisofs.log workdir tmpmnt

unconfig:
	-${SUDO} umount -f ${REALOBJDIR}/tmpmnt
	-${SUDO} vnconfig -u svnd0

.include <bsd.obj.mk>
.include <bsd.subdir.mk>
