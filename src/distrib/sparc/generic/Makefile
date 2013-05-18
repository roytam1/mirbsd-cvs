# $MirOS: src/distrib/sparc/generic/Makefile,v 1.4 2006/06/12 11:39:17 tg Exp $

.include <bsd.own.mk>
CFLAGS+=	${CDIAGFLAGS} ${COPTS}
HOSTCFLAGS?=	${CFLAGS}

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
	rm -f bsd bsd.net{,.tmp}

cleannobsd:
	-rm -f bsd.net{,.tmp}

bsd.net: bsd
	-rm -f $@.tmp
	gzip -d <bsd >$@.tmp
	# need to strip symbols, elf2aout still has issues converting these
	strip -s $@.tmp
	elf2aout $@.tmp $@ -b
	-rm -f $@.tmp

.include "../../Makefile.kernel"
.include <bsd.obj.mk>
.include <bsd.subdir.mk>

.PHONY: rebsd install-root
