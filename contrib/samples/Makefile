# $MirOS: contrib/samples/Makefile,v 1.8 2007/02/07 01:16:28 tg Exp $

BINGRP?=daemon
FILES+=	daemon.png devel-keys dot.Xmodmap dot.Xresources dot.xinitrc \
	etc_profile kana kbd-layout kbd-layout.80c kbd-layout.euc-jp \
	myXenvironment openssl.cnf ucs2utf8 unidata.htm unidata.txt \
	unitable.htm utf-8

realinstall:
	cd ${.CURDIR}; install -c -o ${DOCOWN} -g ${DOCGRP} -m ${DOCMODE} \
	    ${FILES} ${PREFIX}/share/examples/mirex/

.include <bsd.prog.mk>
