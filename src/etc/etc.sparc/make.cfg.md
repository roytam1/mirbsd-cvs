# $MirOS: src/etc/etc.sparc/make.cfg.md,v 1.1 2005/08/21 11:45:47 tg Exp $
#
# machdep part of ${MAKE}.cfg for sparc

DEFCOPTS=	-Os -Wstrict-aliasing -Wformat -fno-align-functions \
		-fno-align-labels -falign-loops=4 -falign-jumps=4 \
		-mcpu=v8 -mtune=supersparc
