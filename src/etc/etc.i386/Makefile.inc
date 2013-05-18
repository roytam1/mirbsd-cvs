# $MirOS: src/etc/etc.i386/Makefile.inc,v 1.4 2007/10/01 21:27:18 tg Exp $

.if defined(DESTDIR)

snap_md:
	${SUDO} cp ${DESTDIR}/usr/mdec/{{,pxe}boot,mbr*} ${DESTDIR}/snapshot/

.endif
