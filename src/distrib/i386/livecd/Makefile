# $MirOS: src/distrib/i386/livecd/Makefile,v 1.8 2006/04/05 23:58:35 tg Exp $

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

prepimg: bsd.gz
	cd workdir && ${SUDO} mksh ${.CURDIR}/munge_it.sh
	${SUDO} dd if=bsd.gz obs=2048 conv=osync of=workdir/bsd
	${SUDO} dd if=${DESTDIR}/usr/mdec/boot obs=2048 conv=osync \
	    of=workdir/etc/boot.386

bsd.gz: ${REALOBJDIR}/../generic/bsd
	-rm -f bsd bsd.gz
	gzip -d <${REALOBJDIR}/../generic/bsd >bsd
	print 'rootdev 6 0\nquit' | config -ef bsd	# (6,0) = cd0a
	gzip -n9 bsd

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
