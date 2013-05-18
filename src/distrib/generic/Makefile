# $MirOS: src/distrib/i386/generic/Makefile,v 1.10 2006/06/16 13:12:56 tg Exp $

.include <bsd.own.mk>
CFLAGS+=	${CDIAGFLAGS} ${COPTS}
HOSTCFLAGS?=	${CFLAGS}

RAMDISK=	GENERIC
SYSDIR=		${.CURDIR}/../../sys
SYSSUBDIR=	${SYSDIR}/arch/${MACHINE}
KERNDIR=	${SYSSUBDIR}/compile/${RAMDISK}

.if exists(${.CURDIR}/Makefile.${MACHINE})
.  include "${.CURDIR}/Makefile.${MACHINE}"
.endif

all:	bsd

rebsd:
	rm -f bsd
	cd ${.CURDIR} && exec ${MAKE} KMAKE_CLEAN=: bsd

depend:
	# Nothing here so far...

install: install.mi install.md

install.mi:
	cp bsd ${DESTDIR}/snapshot/bsd

install.md:

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
	-rm -rf build ${CLEANFILES}
	rm -f bsd

cleannobsd:
	-rm -rf ${CLEANFILES}

.include "../Makefile.kernel"
.include <bsd.obj.mk>
.include <bsd.subdir.mk>

.PHONY: rebsd install-root install.mi install.md
