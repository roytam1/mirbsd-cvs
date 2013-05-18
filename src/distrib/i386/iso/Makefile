# $MirOS: src/distrib/i386/iso/Makefile,v 1.17 2006/04/10 21:03:04 tg Exp $
# $OpenBSD: Makefile,v 1.3 2003/03/04 20:24:49 deraadt Exp $

.include <bsd.own.mk>

CDROM?=		cdrom${OSrev}.iso
CDOPTS?=	-v -v -eject driveropts=burnproof
REALOBJDIR!=	readlink -nf ${.OBJDIR} || ( cd ${.OBJDIR} && pwd )

all: ${CDROM}

${CDROM}: prepare-workdir generate-image

prepare-workdir: ${DESTDIR}/usr/mdec/boot ${REALOBJDIR}/../ramdisk/bsd.rd \
    ${.CURDIR}/boot.cfg ${.CURDIR}/00-README
	@if [[ -e Makefile ]]; then \
		echo Error: do a make obj first; \
		exit 1; \
	fi
.ifndef NOPRUNE
	-rm -rf workdir
.endif
	mkdir -p workdir/{etc,v${OSrev}/i386}
	@if [[ -e ${.CURDIR}/contrib ]]; then \
		echo Integrating contrib dir; \
		mkdir workdir/contrib; \
		cd workdir/contrib; \
		lndir ${.CURDIR}/contrib; \
	fi
	dd if=${DESTDIR}/usr/mdec/boot obs=2048 conv=osync \
	    of=workdir/v${OSrev}/i386/boot.liv
	cp workdir/v${OSrev}/i386/boot.liv workdir/v${OSrev}/i386/boot.iso
	dd if=${REALOBJDIR}/../ramdisk/bsd.rd obs=2048 conv=osync \
	    of=workdir/v${OSrev}/i386/bsd.rd
	if [[ -e ${DESTDIR}/usr/mdec/pxeboot ]]; then \
		cp ${DESTDIR}/usr/mdec/pxeboot workdir/v${OSrev}/i386/; \
	fi
	cp ${.CURDIR}/boot.cfg workdir/etc/
	cp ${.CURDIR}/00-README workdir/

generate-image:
	mkisofs -r -f -T -L -d -D -N -v -v \
	    -b v${OSrev}/i386/boot.iso -c boot.cat \
	    -P "The http://MirBSD.org/ team and its contributors" \
	    -p "Copyright © 2002-2006 by The MirOS Project" \
	    -V "MirOS #${OSrev} BSD/${MACHINE} boot-only CD" \
	    -volset "$$(uname -slm) Setup" -sysid "MirOSBSD" \
	    -no-emul-boot -boot-load-size 4 -boot-info-table \
	    -pad -o ${CDROM} workdir 2>&1 | tee mkisofs.log
	${DESTDIR}/usr/mdec/installboot -v -I \
	    $$(fgrep 'workdir/v${OSrev}/i386/boot.liv' mkisofs.log | \
		while read start end rest; do print $$start $$end; done) \
	    ${DESTDIR}/usr/mdec/ldsec ${CDROM}

install:
	cp ${CDROM} ${DESTDIR}/snapshot/

clean cleandir cleannobsd:
	-rm -rf ${CDROM} mkisofs.log workdir

burn-cdrw: burn-cdrw-clean burn-cdr

burn-cdrw-clean:
	cdrecord dev=/dev/rcd0c:0,0,0 gracetime=2 blank=fast ${CDOPTS}

burn-cdr: ${CDROM}
	cdrecord dev=/dev/rcd0c:0,0,0 gracetime=2 ${CDOPTS} -pad ${CDROM}

.PHONY: burn-cdr burn-cdrw burn-cdrw-clean generate-image prepare-workdir

.include <bsd.obj.mk>
.include <bsd.subdir.mk>
