# $MirOS$

.if defined(DESTDIR)

snap_md: snap_md1 distrib

snap_md1:
	${SUDO} cp ${DESTDIR}/usr/mdec/pxeboot ${DESTDIR}/snapshot/

.endif
