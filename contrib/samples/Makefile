# $MirOS: contrib/samples/Makefile,v 1.13 2010/12/05 20:19:29 tg Exp $

BINGRP?=daemon
FILES+=	RCStags cvs_automerge cvs_bugs daemon.png devel-keys dot.Xmodmap \
	dot.Xresources dot.xinitrc etc_profile import-3rdpty kana kbd-layout \
	kbd-xf86 myXenvironment openssl.cnf portmdoc ucs2utf8 unidata.htm \
	unidata.txt utf-8

realinstall:
	cd ${.CURDIR}; install -c -o ${DOCOWN} -g ${DOCGRP} -m ${DOCMODE} \
	    ${FILES} ${PREFIX}/share/examples/mirex/

.include <bsd.prog.mk>
