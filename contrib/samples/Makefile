# $MirOS: contrib/samples/Makefile,v 1.10 2007/03/30 23:23:25 tg Exp $

BINGRP?=daemon
FILES+=	daemon.png devel-keys dot.Xmodmap dot.Xresources dot.xinitrc \
	etc_profile kana kbd-layout myXenvironment openssl.cnf portmdoc \
	ucs2utf8 unidata.htm unidata.txt unitable.htm utf-8

realinstall:
	cd ${.CURDIR}; install -c -o ${DOCOWN} -g ${DOCGRP} -m ${DOCMODE} \
	    ${FILES} ${PREFIX}/share/examples/mirex/

.include <bsd.prog.mk>
