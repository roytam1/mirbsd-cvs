# $MirOS: contrib/samples/Makefile,v 1.5 2006/01/31 16:27:52 tg Exp $

BINGRP?=daemon
FILES+=	daemon.png devel-keys dot.Xmodmap.us_jp dot.Xmodmap.light \
	dot.Xmodmap.xapps dot.Xresources dot.xinitrc etc_profile \
	kbd-layout kbd-layout.80c kbd-layout.euc-jp myXenvironment \
	openssl.cnf unidata.htm unidata.txt unitable.htm utf-8

realinstall:
	cd ${.CURDIR}; install -c -o ${DOCOWN} -g ${DOCGRP} -m ${DOCMODE} \
	    ${FILES} ${PREFIX}/share/examples/mirex/

.include <bsd.prog.mk>
