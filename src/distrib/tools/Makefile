# $MirOS: src/distrib/tools/Makefile,v 1.8 2007/10/01 22:00:24 tg Exp $

all: sundsklbl

.include <bsd.own.mk>

.if ${MACHINE_ARCH} == "i386"
all: i386_chain
.endif

CHAINSECTOR?=	24
CDROM?=		cdrom${OSrev}.iso
DSTTOPDIR?=	/var/www/htdocs/v${OSrev}

CPPFLAGS+=	-DCHAINSECTOR=${CHAINSECTOR}

depend:
prereq:

clean: .PHONY
	-rm -f i386_chain sundsklbl *.o
	-rm -rf ${CDROM} mkisofs.log
	-rm -rf cddir

cleandir: .PHONY clean

i386_chain: i386_chain.o
	ld -o $@ --oformat binary -Ttext 0 $>

sundsklbl: sundsklbl.c
	cd ${.CURDIR} && ${MAKE} -f ${.SYSMK}/bsd.prog.mk \
	    PROG=$@ NOMAN=Yes EXPERIMENTAL=Yes

makecdimage: .PHONY
	-rm -rf cddir ${CDROM} mkisofs.log
	mkdir -p cddir/v${OSrev}/{i386,sparc}
	cp ${DSTTOPDIR}/i386/boot cddir/b_i386.iso
	cp ${DSTTOPDIR}/i386/boot cddir/b_i386.ldr
	cp ${DSTTOPDIR}/sparc/boot cddir/b_sparc.ldr
	cp ${.CURDIR}/../common/00-README ${.CURDIR}/boot.cfg cddir/
	cp ${DSTTOPDIR}/i386/{bsd.rd,pxeboot} cddir/v${OSrev}/i386/
	cp ${DSTTOPDIR}/sparc/{bootxx,bsd.rd} cddir/v${OSrev}/sparc/
	ln cddir/v${OSrev}/sparc/bsd.rd cddir/vmunix	# for kicks
	ln cddir/v${OSrev}/sparc/bsd.rd cddir/bsd	# for idiots
	chmod -R u+w cddir
	mkisofs -r -f -L -d -D -N -v -v -b b_i386.iso -c boot.cat \
	    -no-emul-boot -boot-load-size 4 -boot-info-table \
	    -P 'The http://mirbsd.de/ team and its contributors' \
	    -p 'Copyright © 2002-2007 by The MirOS Project' \
	    -V 'MirOS #${OSrev} BSD manifold-boot CD' \
	    -volset "$$(uname -sl) i386/sparc Setup" -sysid MirOSBSD \
	    -pad -o ${CDROM} cddir 2>&1 | tee mkisofs.log
	dd if=${.CURDIR}/dual_chain.bin of=${CDROM} conv=notrunc

makebootcd: makebootcd_${MACHINE}

makebootcd_i386: .PHONY
	/usr/mdec/installboot -S 24 -v -h 16 -s 63 -I $$(fgrep \
	    b_i386.ldr mkisofs.log | \
	    while read start end rest; do \
		print -- $$start $$end; \
	done) /usr/mdec/bootxx ${CDROM}

makebootcd_sparc: .PHONY
	/usr/mdec/installboot -v $$(fgrep \
	    b_sparc.ldr mkisofs.log | \
	    while read start end rest; do \
		print -- -s $$start -e $$end; \
	done) dummy /usr/mdec/bootxx ${CDROM}

.include <bsd.obj.mk>
