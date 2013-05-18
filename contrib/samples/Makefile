# $MirOS: contrib/samples/Makefile,v 1.7 2006/10/17 21:41:03 tg Exp $

BINGRP?=daemon
FILES+=	daemon.png devel-keys dot.Xmodmap.us_jp dot.Xmodmap.light \
	dot.Xmodmap.xapps dot.Xresources dot.xinitrc etc_profile kana \
	kbd-layout kbd-layout.80c kbd-layout.euc-jp myXenvironment \
	openssl.cnf ucs2utf8 unidata.htm unidata.txt unitable.htm utf-8

realinstall:
	cd ${.CURDIR}; install -c -o ${DOCOWN} -g ${DOCGRP} -m ${DOCMODE} \
	    ${FILES} ${PREFIX}/share/examples/mirex/

.include <bsd.prog.mk>
