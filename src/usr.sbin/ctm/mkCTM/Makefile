# $MirOS$
# $FreeBSD: src/usr.sbin/ctm/mkCTM/Makefile,v 1.8 2004/12/21 08:47:32 ru Exp $

PROG=	mkctm
SRCS=	mkctm.c
NOMAN=	yes

test:	mkctm
	rm -f tst.out*
	time ./mkctm -v -v /3c/210src  /a/r1/usr/src \
		2>a | md5 -p > /a/tst.out
	ls -l /a/tst.out
	gzip -9 -v /a/tst.out
	ls -l /a/tst.out.gz
	# cd /usr/src/release && ctm -c -v -v  ${.CURDIR}/tst.out

test1:	mkctm
	rm -f tst.out*
	time ./mkctm -v -v /3c/210src  /home/ncvs/src \
		2> b | md5 -p > /a/tst2.out
	ls -l /a/tst2.out
	gzip -9 -v /a/tst2.out
	ls -l /a/tst2.out.gz

.if defined(install_samples)
beforeinstall:
	${INSTALL} ${INSTALL_COPY} -o ${DOCOWN} -g ${DOCGRP} \
	    -m ${DOCMODE} ${.CURDIR}/ctm_conf.* ${DESTDIR}/usr/share/ctm/
	${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} \
	    -m ${BINMODE} ${.CURDIR}/dequeue ${DESTDIR}/usr/share/ctm/
	${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} \
	    -m ${BINMODE} ${.CURDIR}/mkCTM ${DESTDIR}/usr/share/ctm/
.endif

.include <bsd.prog.mk>
