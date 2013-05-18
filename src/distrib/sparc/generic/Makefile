# $MirOS: src/distrib/sparc/generic/Makefile,v 1.2 2006/06/11 01:22:49 tg Exp $

RAMDISK=	GENERIC
SYSDIR=		${.CURDIR}/../../../sys
SYSSUBDIR=	${SYSDIR}/arch/sparc
KERNDIR=	${SYSSUBDIR}/compile/${RAMDISK}

all:	bsd

rebsd:
	rm -f bsd
	cd ${.CURDIR} && exec ${MAKE} KMAKE_CLEAN=: bsd

depend:
	# Nothing here so far...

install:
	cp bsd ${DESTDIR}/snapshot/bsd
	s=$$(printf "find sd\nexit" | config -e ${DESTDIR}/snapshot/bsd | \
	    grep scsibus | awk '{print $$1}'); \
	    printf "add sd0\n%s\n%s\nchange %s\ny\n3\n\n\nquit\n" $$s $$s $$s | \
	    config -e -o ${DESTDIR}/snapshot/bsd.scsi3 ${DESTDIR}/snapshot/bsd

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
