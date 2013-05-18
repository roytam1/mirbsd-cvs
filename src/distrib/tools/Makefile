# $MirOS: src/distrib/tools/Makefile,v 1.20 2008/08/05 19:19:57 tg Exp $

all: sundsklbl

.include <bsd.own.mk>

.if ${MACHINE_ARCH} == "i386"
all: prepend_chain
.endif

CHAINSECTOR?=	24
CDROM?=		cdrom${OSrev}.iso
DSTTOPDIR?=	/var/www/htdocs/v${OSrev}

CPPFLAGS+=	-DCHAINSECTOR=${CHAINSECTOR}

depend:
prereq:

clean: .PHONY
	-rm -f i386_chain sundsklbl *.o ${CDROM}
	-rm -rf cddir

cleandir: .PHONY clean

i386_chain: i386_chain.o
	ld -o $@ --oformat binary -Ttext 0 $>

prepend_chain: ${.CURDIR}/mkprepbs.sh i386_chain
	${MKSH} ${.CURDIR}/mkprepbs.sh i386_chain.o i386_chain >$@

sundsklbl: sundsklbl.c
	cd ${.CURDIR} && ${MAKE} -f ${.SYSMK}/bsd.prog.mk \
	    PROG=$@ NOMAN=Yes EXPERIMENTAL=Yes

makecdimage: .PHONY
	-rm -rf cddir ${CDROM}
	mkdir -p cddir/v${OSrev}/{i386,sparc}
	for arch in i386 sparc; do \
		for file in ${DSTTOPDIR}/$$arch/{*boot*,bsd.rd,*mbr*}; do \
			[[ -e $$file ]] || continue; \
			install -m644 $$file cddir/v${OSrev}/$$arch/; \
		done; \
		mv cddir/v${OSrev}/$$arch/boot cddir/b_$$arch.ldr; \
	done
	dd if=/dev/arandom bs=2048 count=1 of=cddir/b_i386.iso	# El Torito
	ln cddir/v${OSrev}/sparc/bsd.rd cddir/vmunix		# for kicks
	ln cddir/v${OSrev}/sparc/bsd.rd cddir/bsd		# for idiots
	cp ${.CURDIR}/../common/00-README ${.CURDIR}/boot.cfg cddir/
	mkisofs -r -b b_i386.iso -c boot.cat -no-emul-boot \
	    -P 'The http://mirbsd.de/ team and its contributors' \
	    -p 'Copyright © 2002-2008 by The MirOS Project' \
	    -V 'MirOS #${OSrev} BSD manifold-boot CD' \
	    -volset "$$(uname -sl) i386/sparc Setup" -sysid MirOSBSD \
	    -pad -o ${CDROM} cddir 2>&1
	getextent_cd9660 -f ${CDROM} b_i386.ldr | \
	    ${MKSH} ${BSDSRCDIR}/usr.sbin/installboot/bxinst.i386 -B 11 | \
	    dd of=${CDROM} conv=notrunc bs=2048 seek=$$(getextent_cd9660 \
	    -f ${CDROM} -b b_i386.iso) 2>/dev/null
	getextent_cd9660 -f ${CDROM} b_i386.ldr | \
	    ${MKSH} ${BSDSRCDIR}/usr.sbin/installboot/bxinst.i386 -S 2 | \
	    dd of=${CDROM} conv=notrunc bs=512 seek=${CHAINSECTOR} 2>/dev/null
	getextent_cd9660 -f ${CDROM} b_sparc.ldr | \
	    ${MKSH} ${BSDSRCDIR}/usr.sbin/installboot/bxinst.sparc \
	    -0 ${CHAINSECTOR} -S 2 | \
	    dd of=${CDROM} conv=notrunc 2>/dev/null

.include <bsd.obj.mk>
