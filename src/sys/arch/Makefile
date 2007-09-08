# $MirOS: src/sys/arch/Makefile,v 1.1.7.1 2005/03/06 16:33:42 tg Exp $

TARCH?=*

all:
	@echo "Not a normal Makefile."

tuv: vers.tgz

vers.tgz:
	find ${TARCH}/compile -name version | sort | \
	    cpio -oC 512 -H ustar -Mdist | gzip -n9 >$@

.PHONY:	all tuv
