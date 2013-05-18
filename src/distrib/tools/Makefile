# $MirOS: src/distrib/tools/Makefile,v 1.10 2007/10/02 18:34:47 tg Exp $

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
	for arch in i386 sparc; do \
		for file in ${DSTTOPDIR}/$$arch/{*boot*,bsd.rd,*mbr*}; do \
			[[ -e $$file ]] || continue; \
			install -m644 $$file cddir/v${OSrev}/$$arch/; \
		done; \
		mv cddir/v${OSrev}/$$arch/boot cddir/b_$$arch.ldr; \
	done
	cp cddir/b_i386.ldr cddir/b_i386.iso		# El Torito
	ln cddir/v${OSrev}/sparc/bsd.rd cddir/vmunix	# for kicks
	ln cddir/v${OSrev}/sparc/bsd.rd cddir/bsd	# for idiots
	cp ${.CURDIR}/../common/00-README ${.CURDIR}/boot.cfg cddir/
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
	done) ${DSTTOPDIR}/i386/bootxx ${CDROM}

makebootcd_sparc: .PHONY
	fgrep b_sparc.ldr mkisofs.log | \
	    ${MKSH} ${BSDSRCDIR}/usr.sbin/installboot/bxinst.sparc | \
	    dd of=${CDROM} bs=512 seek=1 conv=notrunc

.include <bsd.obj.mk>
