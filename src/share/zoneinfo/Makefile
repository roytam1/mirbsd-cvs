# $MirOS: src/share/zoneinfo/Makefile,v 1.10 2014/03/24 08:14:18 tg Exp $

TZDIR?=		${DESTDIR}/usr/share/zoneinfo
DATDIR=		${.CURDIR}/datfiles
YIT=		'${SHELL} -c ${DATDIR}/yearistype.sh'
ZIC?=		zic

TDATA=		africa antarctica asia australasia backward etcetera europe \
		factory northamerica pacificnew southamerica systemv
ALLDATA=	${TDATA} leapseconds
# Adjust the optarg to -p to fit your posixrules need.
ZICFLAGS=	-y ${YIT} -d ${TZDIR} -p Europe/Berlin

obj prereq depend includes all clean cleandir:

install:
	chmod -R u+w ${TZDIR}
	cd ${TZDIR} && \
	    mkdir -p Arctic Brazil Canada Chile Europe Mexico US
	ln -sf Berlin ${TZDIR}/Europe/Bonn
	cd ${DATDIR} && ${ZIC} ${ZICFLAGS} -L leapseconds ${TDATA}
	chown -R ${BINOWN}:${BINGRP} ${TZDIR}
	find ${TZDIR} -type f -print0 | xargs -0r chmod ${NONBINMODE}
	chmod -R a-w ${TZDIR}

.include <bsd.own.mk>
