# $MirOS: src/distrib/i386/generic/Makefile,v 1.8 2006/06/11 01:08:29 tg Exp $

RAMDISK=	GENERIC
SYSDIR=		${.CURDIR}/../../../sys
SYSSUBDIR=	${SYSDIR}/arch/i386
KERNDIR=	${SYSSUBDIR}/compile/${RAMDISK}

all:	bsd

rebsd:
	rm -f bsd
	cd ${.CURDIR} && exec ${MAKE} KMAKE_CLEAN=: bsd

depend:
	# Nothing here so far...

install:
	cp bsd ${DESTDIR}/snapshot/bsd

install-root:
	@if [[ -e /bsd ]]; then \
		echo Move /bsd out of the way!; \
		exit 1; \
	elif [[ ! -e /bsd.old ]]; then \
		echo Back up your old kernel to /bsd.old!; \
		exit 1; \
	else \
		set -x; \
		install -c -o root -g daemon -m 400 bsd /; \
	fi

cleandir: clean

clean:
	-rm -rf build
	rm -f bsd

cleannobsd:

.include "../../Makefile.kernel"
.include <bsd.obj.mk>
.include <bsd.subdir.mk>

.PHONY: rebsd install-root
