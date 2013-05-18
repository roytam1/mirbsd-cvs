# $MirOS: src/share/misc/Makefile,v 1.4 2005/07/24 13:08:05 tg Exp $
# $OpenBSD: Makefile,v 1.10 2004/11/19 18:18:53 deraadt Exp $
# from: @(#)Makefile	5.13 (Berkeley) 5/7/91

NOOBJ=	yes
FILES=
FILES+=	acronyms
FILES+=	airport
FILES+=	ascii
FILES+=	birthtoken
FILES+=	countrycodes
FILES+=	eqnchar
FILES+=	getopt
FILES+=	inter.phone
FILES+=	licence.template
FILES+=	man.template
FILES+=	mdoc.template
FILES+=	na.phone
FILES+=	operator
FILES+=	scsi_modes
FILES+=	usb_hid_usages
FILES+=	zipcodes

realinstall:
	cd ${.CURDIR}; install -c -o ${BINOWN} -g ${BINGRP} -m ${SHAREMODE} \
	    ${FILES} ${DESTDIR}${BINDIR}/misc/

.include <bsd.prog.mk>
