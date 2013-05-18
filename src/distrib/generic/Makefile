# $MirOS: src/distrib/generic/Makefile,v 1.7 2008/06/13 18:26:55 tg Exp $

.include <bsd.own.mk>
CFLAGS+=	${CDIAGFLAGS} ${COPTS}
HOSTCFLAGS?=	${CFLAGS}

RAMDISK=	GENERIC
SYSDIR=		${.CURDIR}/../../sys

.if exists(${.CURDIR}/Makefile.${MACHINE})
.  include "${.CURDIR}/Makefile.${MACHINE}"
.endif

all:	bsd

rebsd:
	rm -f bsd
	cd ${.CURDIR} && exec ${MAKE} KMAKE_CLEAN=: bsd

depend:

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
		install -c -o root -g wheel -m 644 \
		    build/${RAMDISK}/kvm_bsd.db /var/db/kvm_bsd.new; \
	fi

install-unstripped:
	@if [[ -e /bsd ]]; then \
		echo Move /bsd out of the way!; \
		exit 1; \
	elif [[ ! -e /bsd.old ]]; then \
		echo Back up your old kernel to /bsd.old!; \
		exit 1; \
	fi
	config -ef build/${RAMDISK}/bsd.unstripped <<<'quit'
	install -c -o root -g daemon -m 400 \
	    build/${RAMDISK}/bsd.unstripped /bsd
	install -c -o root -g wheel -m 644 \
	    build/${RAMDISK}/kvm_bsd.db /var/db/kvm_bsd.new

cleandir: clean

clean:
	-rm -rf build ${CLEANFILES}
	rm -f bsd

cleannobsd:
	-rm -rf ${CLEANFILES}

.include "../common/Makefile.kernel"
.include <bsd.obj.mk>
.include <bsd.subdir.mk>

.PHONY: rebsd install-root install-unstripped install.mi install.md
