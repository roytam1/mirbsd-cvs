# $MirOS: src/share/zoneinfo/Makefile,v 1.3 2006/06/16 22:55:11 tg Exp $

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

obj prereq depend all clean cleandir:

install:
	chmod -R u+w ${TZDIR}
	cd ${TZDIR} && \
	    mkdir -p Arctic Brazil Canada Chile Mexico Mideast SystemV US
	cd ${DATDIR} && ${ZIC} ${ZICFLAGS} -L leapseconds ${TDATA}
	chown -R ${BINOWN}:${BINGRP} ${TZDIR}
	find ${TZDIR} -type f | xargs chmod ${NONBINMODE}
	chmod -R a-w ${TZDIR}

.include <bsd.own.mk>
