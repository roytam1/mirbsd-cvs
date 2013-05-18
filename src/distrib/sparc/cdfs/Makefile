#	$MirOS: src/distrib/sparc/cdfs/Makefile,v 1.2 2005/03/06 18:58:06 tg Exp $
#	$OpenBSD: Makefile,v 1.5 2005/03/11 15:40:59 deraadt Exp $

TOP=	${.CURDIR}/..

CDROM=	cd${OSrev}.iso

all: ${CDROM}

${CDROM}:
	-rm -rf ${.OBJDIR}/cd-dir
	mkdir -p ${.OBJDIR}/cd-dir/${OSREV}/sparc
	ln -s ${.CURDIR}/supplement ${.OBJDIR}/cd-dir/contrib
	cp ${DESTDIR}/usr/share/man/COPYRIGHT ${.CURDIR}/supplement
	cp ${.OBJDIR}/../../ramdisk/bsd.rd ${.OBJDIR}/cd-dir/${OSREV}/sparc
	ln ${.OBJDIR}/cd-dir/${OSREV}/sparc/bsd.rd ${.OBJDIR}/cd-dir/bsd.rd
	ln ${.OBJDIR}/cd-dir/bsd.rd ${.OBJDIR}/cd-dir/bsd
	ln ${.OBJDIR}/cd-dir/bsd.rd ${.OBJDIR}/cd-dir/vmunix # for kicks
	cp ${DESTDIR}/usr/mdec/boot ${.OBJDIR}/cd-dir/${OSREV}/sparc
	cp ${DESTDIR}/usr/mdec/bootxx ${.OBJDIR}/cd-dir/${OSREV}/sparc
	(mkhybrid -a -r -f -v -v -T -L -d -D -N -o ${.OBJDIR}/${CDROM} \
	(mkhybrid -a -R -v -v -T -L -d -D -N -o ${.OBJDIR}/${CDROM} \
	    -A "MirOS #${OSrev} ${MACHINE} Boot-CD; http://mirbsd.de/" \
	    -P "© 2002, 2003, 2004  The MirOS Project" \
	    -p "The http://mirbsd.de/ team and its contributors" \
	    -V "MirOS #${OSrev} BSD/${MACHINE} boot-only CD" \
	    -volset "$$(uname -Ml)" ${.OBJDIR}/cd-dir 2>&1) | tee log
	vnconfig -v -c svnd0 ${.OBJDIR}/${CDROM}
	mount -t cd9660 /dev/svnd0a /mnt
	/usr/mdec/installboot -v \
	    -s $$(cat log | grep -v 'Name' | egrep "/cd-dir/${OSREV}/sparc/boot$$" | cut -d' ' -f1) \
	    -e $$(cat log | grep -v 'Name' | egrep "/cd-dir/${OSREV}/sparc/boot$$" | cut -d' ' -f2) \
	    /mnt/${OSREV}/sparc/boot /usr/mdec/bootxx /dev/rsvnd0c
	disklabel -w svnd0 fakecdrom "OpenBSD/sparc   "
	umount /mnt
	vnconfig -u svnd0
	# XXX Some sparc machines fail to load the kernel correctly if the
	# XXX cd image is truncated.  It is not yet known why this happens.
	# XXX For now we pad the image.
	dd if=/dev/zero bs=2k count=200 >> ${.OBJDIR}/${CDROM}

install:
	cp ${CDROM} ${DESTDIR}/snapshot

clean cleandir:
	/bin/rm -f ${CDROM}
	rm -rf cd-dir log

unconfig:
	-umount /mnt
	-vnconfig -u svnd0

.include <bsd.obj.mk>
.include <bsd.subdir.mk>
