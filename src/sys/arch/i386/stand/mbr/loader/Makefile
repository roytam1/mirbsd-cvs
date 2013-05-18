# $MirOS$

PROG=		mbrldr
CLEANFILES+=	mbrcode.h

all: mbrcode.h

mbrcode.h: ${PROG}
	print '/* $$Mir''OS$$ */\n/*-\n * Automatically' \
	    'generated, do not edit!\n * ${PROG} Version' \
	    '${V} for ${MACHINE}\n */' >$@
	hexdump -ve '8/1 "0x%02X, " "\n"' ${.ALLSRC} >>$@

.include <bsd.prog.mk>
