# $MirOS: src/etc/etc.i386/make.cfg.md,v 1.1 2005/08/21 11:45:46 tg Exp $
#
# machdep part of ${MAKE}.cfg for i386

DEFCOPTS=	-Os -Wstrict-aliasing -Wformat -fno-align-functions \
		-fno-align-labels -falign-loops=4 -falign-jumps=4 \
		-march=i486 -mpush-args -mpreferred-stack-boundary=2
