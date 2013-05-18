# $MirOS: src/kern/include/Makefile,v 1.1 2008/09/06 22:32:01 tg Exp $

HDRS=		libckern.h nzat.h
HDRDST=		${DESTDIR}/usr/include/syskern

_includes: includedirs

includedirs: .PHONY
	${INSTALL} -d -o ${BINOWN} -g ${BINGRP} -m ${DIRMODE} ${HDRDST}

.include <bsd.prog.mk>
