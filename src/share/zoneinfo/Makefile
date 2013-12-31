# $MirOS: src/share/zoneinfo/Makefile,v 1.7 2013/09/11 17:01:16 tg Exp $

TZDIR?=		${DESTDIR}/usr/share/zoneinfo
DATDIR=		${.CURDIR}/datfiles
YIT=		'${SHELL} -c ${DATDIR}/yearistype.sh'
ZIC?=		zic

TDATA=		africa antarctica asia australasia etcetera europe \
		factory northamerica pacificnew solar87 solar88 \
		solar89 southamerica systemv backward
ALLDATA=	${TDATA} iso3166.tab leapseconds zone.tab
# Adjust the optarg to -p to fit your posixrules need.
ZICFLAGS=	-y ${YIT} -d ${TZDIR} -p Europe/Berlin

obj prereq depend includes all clean cleandir:

install:
	chmod -R u+w ${TZDIR}
	cd ${TZDIR} && \
	    mkdir -p Arctic Brazil Canada Chile Europe Mexico Mideast US
	ln -sf Berlin ${TZDIR}/Europe/Bonn
	cd ${DATDIR} && ${ZIC} ${ZICFLAGS} -L leapseconds ${TDATA}
	${INSTALL} -c ${DATDIR}/zone.tab ${TZDIR}/
	chown -R ${BINOWN}:${BINGRP} ${TZDIR}
	find ${TZDIR} -type f -print0 | xargs -0r chmod ${NONBINMODE}
	chmod -R a-w ${TZDIR}
	${INSTALL} -c -o ${BINOWN} -g ${BINGRP} -m ${NONBINMODE} \
	    ${DATDIR}/iso3166.tab ${DESTDIR}/usr/share/misc/

.include <bsd.own.mk>
