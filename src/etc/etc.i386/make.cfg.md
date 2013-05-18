# $MirOS: src/etc/etc.i386/mk.conf.md,v 1.6 2005/04/23 22:06:42 tg Exp $
#
# machdep part of ${MAKE}.cfg for i386

DEFCOPTS=	-Os -fno-strict-aliasing -fno-strength-reduce -Wformat \
		-fno-unit-at-a-time -fno-align-functions -fno-align-labels \
		-falign-loops=4 -falign-jumps=4 -march=i486 -mpush-args \
		-mpreferred-stack-boundary=2
