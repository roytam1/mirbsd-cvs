# $MirOS: contrib/extraman/Makefile,v 1.4 2015/10/13 20:51:44 tg Exp $

all:
CLEANFILES+=	htmxtr10.ngz

.include <bsd.own.mk>

.ifndef PORTSDIR
PORTSDIR!=	x=$$(echo '.include <mirports.sys.mk>' | env -i "PATH=$$PATH" \
		    mmake -f - ___DISPLAY_MAKEVARS=PORTSDIR \
		    2>/dev/null) || x=; print -nr -- $$x
.endif

.if "${PORTSDIR}" == ""
. error PORTSDIR is empty
.endif

.if !exists(${PORTSDIR}/infrastructure/mk/mirports.bsd.mk)
. error PORTSDIR ${PORTSDIR} incorrect
.endif

.if !exists(${PORTSDIR}/games/bsdgames/Makefile)
. error PORTSDIR ${PORTSDIR} lacking bsdgames port
.endif

.if !exists(${PORTSDIR}/shells/csh/Makefile)
. error PORTSDIR ${PORTSDIR} lacking csh port
.endif

CLEANFILES+=	stamp_portmans
all: stamp_portmans
stamp_portmans:
	rm -rf portmans
	mkdir -p portmans/cat{1,2,3,3p,4,5,6,7,8,9}
	cd ${PORTSDIR:Q}/games/bsdgames && mmake clean && mmake MAN_ONLY=1 \
	    ALL_TARGET=__MANALL INSTALL_TARGET=__MANINSTALL fake
	cd ${PORTSDIR:Q}/shells/csh && mmake clean && mmake \
	    ALL_TARGET=__MANALL INSTALL_TARGET=__MANINSTALL fake
	set -o pipefail && cd $$(cd ${PORTSDIR:Q}/games/bsdgames && \
	    mmake show=WRKINST)/usr/share/man && find cat* -name \*.0 | \
	    cpio -pdluv ${.OBJDIR:Q}/portmans/
	set -o pipefail && cd $$(cd ${PORTSDIR:Q}/shells/csh && \
	    mmake show=WRKINST)/usr/mpkg/man && find cat* -name \*.0 | \
	    cpio -pdluv ${.OBJDIR:Q}/portmans/
	cd ${PORTSDIR:Q}/games/bsdgames && mmake clean
	cd ${PORTSDIR:Q}/shells/csh && mmake clean
	@:>$@

MAN+=		cprng.8
MAN+=		tcpdump.8

MAN+=		bjoe/joe.1
MLINKS+=	joe.1 jmacs.1
MLINKS+=	joe.1 jpico.1
MLINKS+=	joe.1 jstar.1
MLINKS+=	joe.1 jupp.1
MLINKS+=	joe.1 rjoe.1
bjoe/joe.1:
	-rm -rf bjoe
	mkdir bjoe
	cd bjoe && CC=${CC:Q} CFLAGS=${CFLAGS:Q} GCC_NO_WERROR=1 \
	    ${MKSH} ${BSDSRCDIR:Q}/contrib/code/jupp/configure

RxMANS+=	contrib/hosted/tg/code/kwalletcli/kwalletaskpass.1
RxMANS+=	contrib/hosted/tg/code/kwalletcli/kwalletcli.1
RxMANS+=	contrib/hosted/tg/code/kwalletcli/kwalletcli_getpin.1
RxMANS+=	contrib/hosted/tg/code/kwalletcli/pinentry-kwallet.1
RxMANS+=	gnu/usr.bin/cvs/contrib/rcs2log.1

.for _i in ${RxMANS}
MAN+=		${_i:T}
CLEANFILES+=	${_i:T}
${_i:T}: ${BSDSRCDIR}/${_i}
	cp $> $@
.endfor

RxGNAT+=	${.CURDIR}/gnat_ugn_unw
RxGNAT+=	${BSDSRCDIR}/gcc/gcc/ada/gnat_rm
RxGNAT+=	${BSDSRCDIR}/gcc/gcc/ada/gnat-style

.for _i in ${RxGNAT}
CLEANFILES+=	${_i:T}.html
all: ${_i:T}.html
${_i:T}.html: ${_i}.texi
	makeinfo --no-split --html \
	    -I ${BSDSRCDIR}/gcc/gcc/doc/include \
	    -I ${BSDSRCDIR}/gcc/gcc/ada \
	    $>
.endfor

CLEANFILES+=	stamp_xmans
all: stamp_xmans
stamp_xmans:
	rm -rf bxmans
	mkdir bxmans
	cd bxmans && lndir ${BSDSRCDIR:Q}/X11/xc/doc/man/GLU
	cd bxmans && xmkmf -a && exec ${MAKE}
	@:>$@

clean:
	rm -rf bjoe bxmans dst portmans
	rm -f a.out [Ee]rrs mklog core *.core ${CLEANFILES}

lint:
install:
	rm -rf dst
	mkdir -p dst/cat{1,2,3,3p,4,5,6,7,8,9}
	cd portmans && pax -rw -l -pe -v cat*/*.0 ../dst/
	cd bxmans && ${MAKE} MANPATH=${.OBJDIR:Q}/dst install.man
	cd ${.CURDIR:Q} && ${MAKE} MANDIR=${.OBJDIR:Q}/dst/cat \
	    MANOWN="$$(id -un)" MANGRP="$$(id -gn)" maninstall
	(. ${BSDSRCDIR:Q}/scripts/roff2htm; convert_all \
	    ${.OBJDIR:Q}/dst ${.OBJDIR:Q}/dst)
	mkdir -p dst/manINFO
.for _i in ${RxGNAT}
	cp ${_i:T}.html dst/manINFO/
.endfor
	cd dst && find man* -type f -print0 | xargs -0r chmod 644
	ln -s ../man8/praliases.htm dst/man1/praliases.htm
	ln -s add_auvis_randomness.htm dst/man9/add_audio_randomness.htm
	cd dst && find man* \( -name \*.htm -o -name \*.html \) -print0 | \
	    sort -R '' | cpio -o0vC512 -Hsv4cpio -Mdist | \
	    gzip -n9 >../htmxtr10.ngz
	rm -rf dst
	ls -la htmxtr10.ngz
.if defined(RELEASEDIR) && !empty(RELEASEDIR)
	mv -f htmxtr10.ngz ${RELEASEDIR:Q}/
.endif

.include <bsd.prog.mk>
