# $MirOS: src/etc/etc.sparc/make.cfg.md,v 1.2 2005/08/28 22:41:25 tg Exp $
#
# machdep part of ${MAKE}.cfg for sparc

_DEFCOPTS=	-Os -Wstrict-aliasing -Wformat -fno-align-functions \
		-fno-align-labels -falign-loops=4 -falign-jumps=4 \
		-mcpu=v8 -mtune=supersparc
