# $MirOS: src/etc/etc.i386/make.cfg.md,v 1.4 2006/09/20 19:26:51 tg Exp $
#
# machdep part of ${MAKE}.cfg for i386

_DEFCOPTS:=	-march=i486 -mpush-args -mpreferred-stack-boundary=2
_DEFCOPTS_llvm:=-march=i486 -mtune=pentium-mmx -mpreferred-stack-boundary=2
_DEFCOPTS_pcc:=	# nothing
