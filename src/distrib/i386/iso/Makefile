# $MirOS$
# $OpenBSD: Makefile,v 1.3 2003/03/04 20:24:49 deraadt Exp $

.include <bsd.own.mk>

CDROM?=	cdrom${OSrev}.iso

all: ${CDROM}

${CDROM}: ${DESTDIR}/usr/share/man/COPYRIGHT ${DESTDIR}/usr/mdec/boot \
		${.OBJDIR}/../ramdisk/bsd.rd ${.CURDIR}/boot.cfg
.if !defined(NOPRUNE)
	-rm -rf ${.OBJDIR}/workdir
.endif
	mkdir -p ${.OBJDIR}/workdir/i386 ${.OBJDIR}/workdir/etc
	-rm -f ${.OBJDIR}/workdir/contrib
	mkdir ${.OBJDIR}/workdir/contrib
	@cd ${.CURDIR}; \
		here=$$(/bin/pwd); bsdsrcdir=$$(cd ${BSDSRCDIR}; /bin/pwd); \
		bsdobjdir=$$(cd ${BSDOBJDIR}; /bin/pwd); \
		subdir=$${here#$${bsdsrcdir}/}; \
		dest=$${bsdobjdir}/$$subdir/workdir; \
		cd $$dest/contrib; lndir $$here/supplement
	cp ${DESTDIR}/usr/share/man/COPYRIGHT ${.OBJDIR}/workdir/contrib
	dd if=${DESTDIR}/usr/mdec/boot obs=2048 conv=osync \
	    of=${.OBJDIR}/workdir/i386/boot
	gzip -cn9 ${.OBJDIR}/../ramdisk/bsd.rd >${.OBJDIR}/workdir/i386/bsd
	cp ${.CURDIR}/boot.cfg ${.OBJDIR}/workdir/etc/
	mkisofs -r -f -T -L -d -D -N -v -v -b i386/boot -c i386/boot.cat \
	    -A "MirOS #${OSrev} ${MACHINE} Boot-CD; http://mirbsd.de/" \
	    -P "© 2002, 2003, 2004  The MirOS Project" \
	    -p "The http://mirbsd.de/ team and its contributors" \
	    -V "MirOS #${OSrev} BSD/${MACHINE} boot-only CD" \
	    -no-emul-boot -boot-load-size 4 -boot-info-table \
	    -volset "$$(uname -sl)" -o ${.OBJDIR}/${CDROM} ${.OBJDIR}/workdir

install:
	cp ${CDROM} ${DESTDIR}/snapshot

clean cleandir cleannobsd:
	/bin/rm -f ${CDROM}
	rm -rf workdir
	-cd ${.CURDIR}/supplement && rm -rf $$(<.cvsignore)

burn-cdrw: burn-cdrw-clean burn-cdr

burn-cdrw-clean:
	cdrecord dev=/dev/rcd0c:0,0,0 gracetime=2 blank=fast ${CDOPTS}

burn-cdr: ${CDROM}
	cdrecord dev=/dev/rcd0c:0,0,0 gracetime=2 ${CDOPTS} ${CDROM}

.PHONY: burn-cdr burn-cdrw-clean burn-cdrw

.include <bsd.obj.mk>
.include <bsd.subdir.mk>
