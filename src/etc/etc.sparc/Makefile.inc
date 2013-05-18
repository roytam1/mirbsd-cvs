# $MirOS: src/etc/etc.sparc/Makefile.inc,v 1.5 2006/06/11 01:22:49 tg Exp $
# $OpenBSD: Makefile.inc,v 1.13 2005/04/28 22:28:14 deraadt Exp $
# etc.sparc/Makefile.inc -- sparc-specific etc Makefile targets

.include <bsd.own.mk>

.ifdef DESTDIR

snap_md:
	cp ${DESTDIR}/usr/mdec/*boot* ${DESTDIR}/snapshot
	printf '\01\03\01\07\060\200\0\07' | \
	    dd of=${DESTDIR}/snapshot/boot.net obs=32 conv=osync && \
	    dd if=${DESTDIR}/usr/mdec/boot of=${DESTDIR}/snapshot/boot.net \
	    bs=32 seek=1 skip=2

.endif	# DESTDIR check
