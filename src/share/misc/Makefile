# $MirOS: src/share/misc/Makefile,v 1.2 2005/03/06 19:38:47 tg Exp $
# $OpenBSD: Makefile,v 1.9 2003/06/03 18:26:59 deraadt Exp $
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
FILES+=	license.template
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
