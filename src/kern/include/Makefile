# $MirOS: src/kern/include/Makefile,v 1.3 2011/11/20 04:57:10 tg Exp $

HDRS=		libckern.h md5.h mirtime.h nzat.h
HDRDST=		${DESTDIR}/usr/include/syskern

_includes: includedirs

includedirs: .PHONY
	${INSTALL} -d -o ${BINOWN} -g ${BINGRP} -m ${DIRMODE} ${HDRDST}

.include <bsd.prog.mk>
