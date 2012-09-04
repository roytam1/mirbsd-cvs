# $MirOS: src/sys/arch/Makefile,v 1.2 2007/09/08 10:55:20 tg Exp $

TARCH?=*

all:
	@echo "Not a normal Makefile."

tuv: vers.tgz

vers.tgz:
	find ${TARCH}/compile -name version | sort | \
	    cpio -oC 512 -H ustar -Mdist | gzip -n9 >$@

tad:
	find ${MACHINE_ARCH}/compile -name version | sort | \
	    cpio -oC 512 -H ustar -Mdist | gzip -n9 >vers-${MACHINE_ARCH}.tgz

.PHONY:	all tuv tad
