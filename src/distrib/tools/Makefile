# $MirOS: src/distrib/tools/Makefile,v 1.49 2017/01/29 00:51:05 tg Exp $

all: sundsklbl

.include <bsd.own.mk>

.if ${MACHINE_ARCH} == "i386"
all: i386_chain
.endif

CHAINSECTOR?=	24
.if defined(SERIALSPEED)
CDROM?=		cdrom${SERIALSPEED}.iso
.endif
CDROM?=		cdrom${OSrev}.iso
DSTTOPDIR?=	/var/www/htdocs/v${OSrev}

CPPFLAGS+=	-DCHAINSECTOR=${CHAINSECTOR}

depend:
prereq:

clean: .PHONY
	-rm -f i386_chain sundsklbl *.o eltorito.loo ${CDROM}*
	-rm -rf cddir

cleandir: .PHONY clean

i386_chain: i386_chain.o
	ld -o $@ --oformat binary -Ttext 0 $>

sundsklbl: sundsklbl.c
	cd ${.CURDIR} && ${MAKE} -f ${.SYSMK}/bsd.prog.mk \
	    PROG=$@ NOMAN=Yes EXPERIMENTAL=Yes

CDROM_OPTS+=	applicationid=NetBSD_makefs
CDROM_OPTS+=	bootimage=i386\;eltorito.loo
CDROM_OPTS+=	no-emul-boot
CDROM_OPTS+=	label=MirOS~v${OSrev}~BSD~manifold-boot~CD
CDROM_OPTS+=	no-trailing-padding
CDROM_OPTS+=	preparer=MirBSD_and_its_contributors
CDROM_OPTS+=	publisher=Copyright_\<c\>_2002=2018_The_MirOS_Project
CDROM_OPTS+=	rockridge
CDROM_OPTS+=	rr-squash
CDROM_OPTS+=	volumeid=$$(uname -sl | tr -- '- \#' :_):i386\;sparc:Setup
#CDROM_OPTS+=	v=1

makecdimage: .PHONY
	-rm -rf cddir ${CDROM}*
	dd if=/dev/arandom bs=2048 count=1 of=eltorito.loo 2>&-	# El Torito
	mkdir -p cddir/{boot/grub,v${OSrev}/{i386,sparc}}
	for arch in i386 sparc; do \
		for file in ${DSTTOPDIR}/$$arch/{*boot*,bsd.rd,*mbr*}; do \
			[[ -e $$file ]] || continue; \
			install -m644 $$file cddir/v${OSrev}/$$arch/; \
		done; \
		mv cddir/v${OSrev}/$$arch/boot cddir/b_$$arch.ldr; \
	done
	cp cddir/b_sparc.ldr cddir/v${OSrev}/sparc/boot.net
	# fix path to default kernel file in second-stage boot loader
	set -A dump -- $$(dd if=cddir/b_sparc.ldr bs=4 count=64 | \
	    hexdump -ve '1/1 "%02X"' | sed 's/\(........\)/ \1/g'); i=0; \
	while (( i < 64 )); do [[ $${dump[i++]} = 2035560? ]] && break; done; \
	if [[ $$i = 64 || $${dump[i-1]} != 20355601 ]]; then \
		print -u2 found invalid or no patch field version; exit 1; \
	fi; ofs=$$((#0x$${dump[i+1]})); \
	print -n v${OSrev}/sparc/bsd.rd\\0 | \
	    dd of=cddir/b_sparc.ldr bs=1 seek=$$ofs conv=notrunc
	ln cddir/v${OSrev}/sparc/bsd.rd cddir/vmunix		# for kicks
	cp ${.CURDIR}/../common/00-README cddir/
.if defined(SERIALSPEED)
	sed \
	    -e 's!^boot .*$$!boot /v${OSrev}/i386/bsd.rd!' \
	    -e 's/@SPEED@/${SERIALSPEED}/g' \
	    ${.CURDIR}/boot.cfg.serial >cddir/boot.cfg
.else
	cat ${.CURDIR}/../common/boot.cfg.i386 >cddir/boot.cfg
.endif
	cat ${.CURDIR}/../baselive/boot.cfg.dual >>cddir/boot.cfg
	cp ${.CURDIR}/../common/extra/loopback.cfg cddir/boot/grub/
.if defined(WAIT)
	@print === press RETURN; read x
.endif
	makefs -t cd9660 -o "$$(print -r -- ${CDROM_OPTS} | tr ' ~' ', ')" \
	    ${CDROM} cddir
	# pad the ISO with ]0;256K] NUL bytes, ie. for
	# a geometry of 16 heads, 32 sectors per track
	dd if=/dev/zero count=1 bs=$$((# (512 * 32 * 16) - \
	    ($$(stat -f %z ${CDROM}) % (512 * 32 * 16)) )) 2>&- >>${CDROM}
	getextent_cd9660 -f ${CDROM} b_i386.ldr | \
	    ${MKSH} ${BSDSRCDIR}/usr.sbin/installboot/bxinst.i386 -B 11 | \
	    dd of=${CDROM} conv=notrunc bs=2048 seek=$$(getextent_cd9660 \
	    -f ${CDROM} -b '$$BootImage$$') 2>/dev/null
	getextent_cd9660 -f ${CDROM} b_i386.ldr | \
	    ${MKSH} ${BSDSRCDIR}/usr.sbin/installboot/bxinst.i386 -A -S 2 | \
	    dd of=${CDROM} conv=notrunc bs=512 seek=${CHAINSECTOR} 2>/dev/null
	getextent_cd9660 -f ${CDROM} b_sparc.ldr | \
	    ${MKSH} ${BSDSRCDIR}/usr.sbin/installboot/bxinst.sparc \
	    -g $$((#$$(stat -f %z ${CDROM}) / (512 * 32 * 16))):16:32 \
	    -0 ${CHAINSECTOR} -S 2 | \
	    dd of=${CDROM} conv=notrunc 2>/dev/null

.include <bsd.obj.mk>
