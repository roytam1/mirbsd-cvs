# $MirOS: src/etc/etc.i386/Makefile.inc,v 1.2 2005/03/06 19:05:55 tg Exp $

.if defined(DESTDIR)

snap_md:
	${SUDO} cp ${DESTDIR}/usr/mdec/pxeboot ${DESTDIR}/snapshot/

.endif
