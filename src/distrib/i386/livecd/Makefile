# $MirOS: src/distrib/i386/livecd/Makefile,v 1.13 2006/04/06 21:58:48 tg Exp $

.include <bsd.own.mk>

CDROM?=		livecd${OSrev}.iso
REALOBJDIR!=	readlink -nf ${.OBJDIR}

all install:

it: ${CDROM}

${CDROM}: unpack addcontrib prepimg nukefiles makeimg

unpack:
	mkdir -p workdir
#.for _i in base dev etc gnu xbase xetc
.for _i in base dev etc gnu
	cd workdir && ${SUDO} tar xzphf ${BSDRELDIR}/rel/${_i}${OSrev}.ngz
.endfor

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

bsd.gz: ${REALOBJDIR}/../generic/bsd
	-rm -f bsd bsd.gz
	gzip -d <${REALOBJDIR}/../generic/bsd >bsd
	print 'rootdev 6 0\nquit' | config -ef bsd	# (6,0) = cd0a
	gzip -n9 bsd

nukefiles:
	cd workdir/usr && ${SUDO} rm -rf \
	    X11R6/{lib/X11/doc,man} {,share/}{doc,info,man}

makeimg: bsd.gz
	${SUDO} dd if=bsd.gz obs=2048 conv=osync of=workdir/bsd
	${SUDO} dd if=workdir/usr/mdec/boot obs=2048 conv=osync \
	    of=workdir/etc/boot.x86
	${SUDO} mkisofs -R -T -L -d -D -N -v -v \
	    -b etc/boot.x86 -c etc/boot.cat -p "Thorsten Glaser" \
	    -P "The http://MirBSD.org/ team and its contributors" \
	    -V "MirOS #${OSrev} BSD/${MACHINE} Live CD" \
	    -volset "$$(uname -slm) Live" -sysid "MirOSBSD" \
	    -no-emul-boot -boot-load-size 4 -boot-info-table \
	    -pad -o ${CDROM} workdir

.PHONY: addcontrib it makeimg nukefiles prepimg unpack

clean cleandir cleannobsd:
	-${SUDO} rm -rf ${CDROM} bsd bsd.gz tempdir workdir

.include <bsd.obj.mk>
.include <bsd.subdir.mk>
