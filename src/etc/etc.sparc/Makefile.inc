# $MirOS: src/etc/etc.sparc/Makefile.inc,v 1.3 2005/07/23 15:00:33 tg Exp $
# $OpenBSD: Makefile.inc,v 1.13 2005/04/28 22:28:14 deraadt Exp $
# etc.sparc/Makefile.inc -- sparc-specific etc Makefile targets

.include <bsd.own.mk>

.ifdef DESTDIR
.if !defined(REL_NO_KERNEL) || ${REL_NO_KERNEL:L} != "yes"
snap_md: bsd distrib bsd.install
.endif

snap_md: bootblocks

bsd.install: bsd
	touch ${.CURDIR}/../sys/arch/sparc/compile/GENERIC/bsd
	cp ${.CURDIR}/../sys/arch/sparc/compile/GENERIC/bsd \
	    ${DESTDIR}/snapshot/bsd
	s=$$(printf "find sd\nexit" | config -e ${DESTDIR}/snapshot/bsd | \
	    grep scsibus | awk '{print $$1}'); \
	    printf "add sd0\n%s\n%s\nchange %s\ny\n3\n\n\nquit\n" $$s $$s $$s | \
	    config -e -o ${DESTDIR}/snapshot/bsd.scsi3 ${DESTDIR}/snapshot/bsd

bsd:
	cd ${.CURDIR}/../sys/arch/sparc/conf && config GENERIC
	cd ${.CURDIR}/../sys/arch/sparc/compile/GENERIC && \
	    ${MAKE} clean && ${MAKE} depend && exec ${MAKE}

bootblocks:
	cp ${DESTDIR}/usr/mdec/*boot* ${DESTDIR}/snapshot
	${DESTDIR}/usr/mdec/binstall net /tmp && \
	  mv /tmp/boot.sparc.openbsd ${DESTDIR}/snapshot/boot.net

.PHONY: bsd bsd.install bootblocks

.endif	# DESTDIR check
