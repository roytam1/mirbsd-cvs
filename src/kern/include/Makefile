# $MirOS: src/kern/include/Makefile,v 1.4 2011/11/20 18:54:41 tg Exp $

HDRS=		libckern.h md5.h mirhash.h mirtime.h nzat.h
HDRDST=		${DESTDIR}/usr/include/syskern

_includes: includedirs

includedirs: .PHONY
	${INSTALL} -d -o ${BINOWN} -g ${BINGRP} -m ${DIRMODE} ${HDRDST}

.include <bsd.prog.mk>
