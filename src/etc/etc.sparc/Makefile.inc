#	$MirOS$
#	$OpenBSD: Makefile.inc,v 1.11 2002/05/13 07:22:43 espie Exp $
#	etc.sparc/Makefile.inc -- sparc-specific etc Makefile targets

.include <bsd.own.mk>

.ifdef DESTDIR
.if !defined(REL_NO_KERNEL) || ${REL_NO_KERNEL:L} != "yes"
snap_md: bsd distrib
.endif

snap_md: bootblocks
	touch ${.CURDIR}/../sys/arch/sparc/compile/GENERIC/bsd
	cp ${.CURDIR}/../sys/arch/sparc/compile/GENERIC/bsd \
	    ${DESTDIR}/snapshot/bsd
	s=$$(printf "find sd\nexit" | config -e ${DESTDIR}/snapshot/bsd | \
	    grep "ukc>  " | awk '{print $$2}'); \
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

.PHONY: bsd bootblocks

.endif	# DESTDIR check
