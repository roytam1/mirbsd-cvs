# $MirOS: src/distrib/i386/livecd/Makefile,v 1.7 2006/04/05 23:40:47 tg Exp $

.include <bsd.own.mk>

CDROM?=		livecd${OSrev}.iso
REALOBJDIR!=	readlink -nf ${.OBJDIR}

all install:

it: ${CDROM}

${CDROM}: unpack prepimg nukefiles makeimg

unpack:
	mkdir -p workdir
#.for _i in base dev etc gnu xbase xetc
.for _i in base dev etc gnu
	cd workdir && ${SUDO} tar xzphf ${BSDRELDIR}/rel/${_i}${OSrev}.ngz
.endfor

prepimg:
	cd workdir && ${SUDO} mksh ${.CURDIR}/munge_it.sh
	${SUDO} dd if=${DESTDIR}/usr/mdec/boot obs=2048 conv=osync \
	    of=workdir/etc/boot.386
	${SUDO} dd if=${REALOBJDIR}/../ramdisk/bsd.rd obs=2048 conv=osync \
	    of=workdir/bsd
	${SUDO} install -c -o root -g wheel -m 644 ${.CURDIR}/boot.cfg \
	    workdir/etc/

nukefiles:
	cd workdir/usr && ${SUDO} rm -rf X11R6/lib/X11/doc X11R6/man \
	    lib/libgcj.* share/{doc,gnat,info,java,man}

makeimg:
	${SUDO} mkisofs -R -T -L -d -D -N -v -v \
	    -b etc/boot.386 -c etc/boot.cat \
	    -P "The http://MirBSD.org/ team and its contributors" \
	    -p "Copyright © 2002-2006 by The MirOS Project" \
	    -V "MirOS #${OSrev} BSD/${MACHINE} Live CD" \
	    -volset "$$(uname -slm) Live" -sysid "MirOSBSD" \
	    -no-emul-boot -boot-load-size 4 -boot-info-table \
	    -pad -o ${CDROM} workdir

.PHONY: it unpack prepimg makeimg nukefiles

clean cleandir cleannobsd:
	-${SUDO} rm -rf ${CDROM} workdir

.include <bsd.obj.mk>
.include <bsd.subdir.mk>
