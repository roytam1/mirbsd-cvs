# $MirOS: src/distrib/i386/generic/Makefile,v 1.4 2006/02/01 18:30:49 tg Exp $

RAMDISK=	GENERIC
SYSDIR=		${.CURDIR}/../../../sys
SYSSUBDIR=	${SYSDIR}/arch/i386
KERNDIR=	${SYSSUBDIR}/compile/${RAMDISK}
MAKE_CLEAN?=	${MAKE} clean

all:	bsd

depend:
	# Nothing here so far...

install:
	cp bsd ${DESTDIR}/snapshot/bsd

cleandir: clean

clean:
	-rm -rf build
	rm -f bsd

cleannobsd:
	-rm -rf build

.include "Makefile.kernel"
.include <bsd.obj.mk>
.include <bsd.subdir.mk>
