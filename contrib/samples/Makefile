# $MirOS$

BINGRP?=daemon
FILES=	daemon.png devel-keys dot.Xmodmap dot.Xmodmap.light dot.Xresources \
	dot.xinitrc etc_profile kbd-layout kbd-layout.80c kbd-layout.euc-jp \
	myXenvironment openssl.cnf utf-8

realinstall:
	cd ${.CURDIR}; install -c -o ${DOCOWN} -g ${DOCGRP} -m ${DOCMODE} \
	    ${FILES} ${PREFIX}/share/examples/mirex

.include <bsd.prog.mk>
