# $MirOS: src/etc/etc.i386/make.cfg.md,v 1.5 2008/11/10 20:43:06 tg Exp $
#
# machdep part of ${MAKE}.cfg for i386

_DEFCOPTS:=	-march=i486 -mpush-args -mpreferred-stack-boundary=2 \
		-momit-leaf-frame-pointer
_DEFCOPTS_llvm:=-march=i486 -mtune=pentium-mmx -mpreferred-stack-boundary=2
_DEFCOPTS_pcc:=	# nothing
_DEFcTOsOPTS:=	-masm=intel
