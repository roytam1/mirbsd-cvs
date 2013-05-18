# $MirOS: src/etc/etc.sparc/Makefile.inc,v 1.4 2006/06/10 23:11:30 tg Exp $
# $OpenBSD: Makefile.inc,v 1.13 2005/04/28 22:28:14 deraadt Exp $
# etc.sparc/Makefile.inc -- sparc-specific etc Makefile targets

.include <bsd.own.mk>

.ifdef DESTDIR

snap_md:
	cp ${DESTDIR}/usr/mdec/*boot* ${DESTDIR}/snapshot
	${DESTDIR}/usr/mdec/binstall net /tmp && \
	    mv /tmp/boot.sparc.openbsd ${DESTDIR}/snapshot/boot.net

.endif	# DESTDIR check
