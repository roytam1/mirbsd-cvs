# $MirOS: X11/extras/bdfctool/Makefile,v 1.5 2012/08/23 18:38:56 tg Exp $

PROG=		bdfctool
SRCS=		${PROG}.sh
INSTALL_STRIP=	#no

CLEANFILES+=	testfont.bdf testfont.tmp testfont.tsq testfont.tst

regress: ${PROG}
	./${PROG} -c <${.CURDIR}/testfont.man >testfont.tsq
	./${PROG} -d <testfont.tsq >testfont.bdf
	diff -u testfont.bdf ${.CURDIR}/testfont.out
	./${PROG} -c <${.CURDIR}/testfont.out >testfont.tst
	diff -u testfont.tst testfont.tsq
	print '/^c 0000/w testfont.tmp\n/^c 0000/d\n-r' \
	    \!./${PROG:Q}' -e <testfont.tmp\n,g/　/s//./g\n,g/䷀/s//#/g\n,g/▌/s//|/g\nwq' | \
	    ed -s testfont.tst
	diff -u testfont.tst ${.CURDIR}/testfont.man
	print '/^c 0000/w testfont.tmp\n/^c 0000/d\n-r' \
	    \!./${PROG:Q}' -ae <testfont.tmp\nwq' | \
	    ed -s testfont.tsq
	diff -u testfont.tsq ${.CURDIR}/testfont.man
	@print Basic tests passed.

.include <bsd.prog.mk>
