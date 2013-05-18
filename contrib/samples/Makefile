# $MirOS: contrib/samples/Makefile,v 1.2 2005/03/22 20:12:02 tg Exp $

BINGRP?=daemon
FILES=	daemon.png devel-keys dot.Xmodmap.us_jp dot.Xmodmap.light dot.Xresources \
	dot.xinitrc etc_profile kbd-layout kbd-layout.80c kbd-layout.euc-jp \
	myXenvironment openssl.cnf unidata.htm unitable.htm utf-8

realinstall:
	cd ${.CURDIR}; install -c -o ${DOCOWN} -g ${DOCGRP} -m ${DOCMODE} \
	    ${FILES} ${PREFIX}/share/examples/mirex

.include <bsd.prog.mk>
