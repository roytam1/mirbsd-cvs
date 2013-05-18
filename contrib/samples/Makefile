# $MirOS: contrib/samples/Makefile,v 1.9 2007/02/19 05:19:33 tg Exp $

BINGRP?=daemon
FILES+=	daemon.png devel-keys dot.Xmodmap dot.Xresources dot.xinitrc \
	etc_profile kana kbd-layout myXenvironment openssl.cnf ucs2utf8 \
	unidata.htm unidata.txt unitable.htm utf-8

realinstall:
	cd ${.CURDIR}; install -c -o ${DOCOWN} -g ${DOCGRP} -m ${DOCMODE} \
	    ${FILES} ${PREFIX}/share/examples/mirex/

.include <bsd.prog.mk>
