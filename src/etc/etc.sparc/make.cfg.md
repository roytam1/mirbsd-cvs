# $MirOS: src/etc/etc.sparc/mk.conf.md,v 1.3 2005/04/17 22:27:05 tg Exp $
#
# machdep part of ${MAKE}.cfg for sparc

DEFCOPTS=	-Os -fno-strict-aliasing -fno-strength-reduce -Wformat \
		-fno-unit-at-a-time -fno-align-functions -fno-align-labels \
		-falign-loops=4 -falign-jumps=4 -mcpu=v8 -mtune=supersparc
