# $MirOS$

TARCH?=*

all:
	@echo "Not a normal Makefile."

tar-up-versions: vers.tgz

vers.tgz:
	find ${TARCH}/compile -name version \
	    | cpio -oC 512 -H ustar \
	    | gzip -n9 >vers.tgz

.PHONY:	all tar-up-versions
