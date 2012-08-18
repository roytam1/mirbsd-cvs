# $MirOS: X11/extras/bdfctool/Makefile,v 1.1 2012/08/18 14:39:27 tg Exp $

PROG=		bdfctool
SRCS=		${PROG}.sh

CLEANFILES+=	testfont.bdf testfont.tst testfont.tmp

regress: ${PROG}
	./${PROG} -d <${.CURDIR}/testfont.man >testfont.bdf
	diff -u testfont.bdf ${.CURDIR}/testfont.out
	./${PROG} -c <${.CURDIR}/testfont.out >testfont.tst
	print '/^c 0000/w testfont.tmp\n/^c 0000/d\n-r' \
	    ./${PROG:Q}' -e <testfont.tmp\n,g/　/s//./g\n,g/䷀/s//#/g\n,g/▌/s//|/g\nwq' | \
	    ed -s testfont.tst
	diff -u testfont.tst ${.CURDIR}/testfont.man
	@print Basic tests passed.

.include <bsd.prog.mk>
