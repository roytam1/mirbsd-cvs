# $MirOS: src/distrib/i386/generic/Makefile,v 1.3 2005/07/01 11:51:43 tg Exp $

RAMDISK=	GENERIC
SYSDIR=		${.CURDIR}/../../../sys
SYSSUBDIR=	${SYSDIR}/arch/i386
KERNDIR=	${SYSSUBDIR}/compile/${RAMDISK}
MAKE_CLEAN?=	${MAKE} clean

all:	bsd

depend:
	# Nothing here so far...

bsd:
	mkdir -p build/${RAMDISK}
	[[ -f build/${RAMDISK}/version || ! -f ${KERNDIR}/version ]] \
	    || cat ${KERNDIR}/version >build/${RAMDISK}/version
	( cd build/${RAMDISK}; config -s ${SYSDIR} -b . \
	    ${SYSSUBDIR}/conf/${RAMDISK} \
	    && ${MAKE_CLEAN} && ${MAKE} depend && exec ${MAKE} bsd )
	mv build/${RAMDISK}/bsd .
	-[[ ! -e ${KERNDIR} ]] \
	    || if ! cat build/${RAMDISK}/version >${KERNDIR}/version; then \
		( print "# warning: kernel version changed"; \
		  print "print $$(<build/${RAMDISK}/version)" \
		     ">${KERNDIR}/version" ) \
		  | tee -a /var/tmp/.buildnotice >&2; \
	    fi

install:
	cp bsd ${DESTDIR}/snapshot/bsd

cleandir: clean

clean:
	-rm -rf build
	rm -f bsd

cleannobsd:
	-rm -rf build

.include <bsd.obj.mk>
.include <bsd.subdir.mk>
