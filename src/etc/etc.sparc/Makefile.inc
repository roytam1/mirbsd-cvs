# $MirOS: src/etc/etc.i386/Makefile.inc,v 1.3 2006/02/14 20:47:53 tg Exp $

.if defined(DESTDIR)

snap_md:
	${SUDO} cp ${DESTDIR}/usr/mdec/boot{,xx} ${DESTDIR}/snapshot/

.endif
