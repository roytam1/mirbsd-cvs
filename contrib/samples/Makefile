# $MirOS: contrib/samples/Makefile,v 1.1.7.1 2005/02/05 01:59:40 tg Exp $

BINGRP?=daemon
FILES=	daemon.png devel-keys dot.Xmodmap dot.Xmodmap.light dot.Xresources \
	dot.xinitrc etc_profile kbd-layout kbd-layout.80c kbd-layout.euc-jp \
	myXenvironment openssl.cnf unidata.htm unitable.htm utf-8

realinstall:
	cd ${.CURDIR}; install -c -o ${DOCOWN} -g ${DOCGRP} -m ${DOCMODE} \
	    ${FILES} ${PREFIX}/share/examples/mirex

.include <bsd.prog.mk>
