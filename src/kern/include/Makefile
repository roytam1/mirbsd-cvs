# $MirOS: src/kern/include/Makefile,v 1.2 2011/07/06 22:22:08 tg Exp $

HDRS=		libckern.h mirtime.h nzat.h
HDRDST=		${DESTDIR}/usr/include/syskern

_includes: includedirs

includedirs: .PHONY
	${INSTALL} -d -o ${BINOWN} -g ${BINGRP} -m ${DIRMODE} ${HDRDST}

.include <bsd.prog.mk>
