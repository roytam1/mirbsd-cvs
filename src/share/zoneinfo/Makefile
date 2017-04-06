# $MirOS: src/share/zoneinfo/Makefile,v 1.11 2014/09/01 21:41:53 tg Exp $

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
	install -c -o root -g wheel -m 444 ${TZDIR}/UTC \
	    ${DESTDIR}/var/anoncvs/usr/share/zoneinfo/UTC
	cd ${DESTDIR}/var/anoncvs/usr/share/zoneinfo && ln -f UTC posixrules

.include <bsd.own.mk>
