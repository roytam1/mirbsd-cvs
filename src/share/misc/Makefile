# $MirOS$
# $OpenBSD: Makefile,v 1.9 2003/06/03 18:26:59 deraadt Exp $
# from: @(#)Makefile	5.13 (Berkeley) 5/7/91

NOOBJ=	yes
FILES=	acronyms airport ascii birthtoken countrycodes eqnchar getopt \
	inter.phone licence.template man.template \
	mdoc.template na.phone operator \
	scsi_modes usb_hid_usages usb_hid_usages zipcodes

realinstall:
	cd ${.CURDIR}; install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${FILES} \
	    ${DESTDIR}${BINDIR}/misc

.include <bsd.prog.mk>
