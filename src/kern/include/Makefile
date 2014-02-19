# $MirOS: src/kern/include/Makefile,v 1.5 2014/01/11 15:59:41 tg Exp $

HDRS=		libckern.h md5.h mirhash.h mirtime.h
HDRDST=		${DESTDIR}/usr/include/syskern

_includes: includedirs

includedirs: .PHONY
	${INSTALL} -d -o ${BINOWN} -g ${BINGRP} -m ${DIRMODE} ${HDRDST}

.include <bsd.prog.mk>
