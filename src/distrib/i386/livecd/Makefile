# $MirOS$

.include <bsd.own.mk>

CDROM?=		livecd${OSrev}.iso
REALOBJDIR!=	readlink -nf ${.OBJDIR}

all install:

cd: ${CDROM}

${CDROM}: unpack prepimg makeimg

unpack:
	mkdir -p workdir
.for _i in base dev etc gnu xbase xetc
	cd workdir && ${SUDO} tar xzphf ${BSDRELDIR}/rel/${_i}${OSrev}.ngz
.endfor

prepimg:
	cd workdir && ${SUDO} mksh ${.CURDIR}/munge_it.sh
	dd if=${DESTDIR}/usr/mdec/boot obs=2048 conv=osync \
	    of=workdir/etc/boot.386
	dd if=${REALOBJDIR}/../ramdisk/bsd.rd obs=2048 conv=osync \
	    of=workdir/bsd
	cp ${.CURDIR}/boot.cfg workdir/etc/

makeimg:
	mkisofs -r -f -T -L -d -D -N -v -v \
	    -b etc/boot.386 -c etc/boot.cat \
	    -P "The http://MirBSD.org/ team and its contributors" \
	    -p "Copyright © 2002-2006 by The MirOS Project" \
	    -V "MirOS #${OSrev} BSD/${MACHINE} Live CD" \
	    -volset "$$(uname -slm) Live" -sysid "MirOSBSD" \
	    -no-emul-boot -boot-load-size 4 -boot-info-table \
	    -o ${CDROM} workdir

.PHONY: cd unpack prepimg makeimg

clean cleandir cleannobsd:
	-rm -rf ${CDROM} workdir

.include <bsd.obj.mk>
.include <bsd.subdir.mk>
