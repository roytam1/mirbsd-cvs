# $MirOS: src/distrib/Makefile,v 1.6 2005/12/04 17:24:41 tg Exp $
# $OpenBSD: Makefile,v 1.27 2005/01/13 22:27:13 deraadt Exp $

.include <bsd.own.mk>
REL_NO_KERNEL?= No

.if	make(obj)
SUBDIR+= special i386 sparc
.elif	!make(install)
.  if ${REL_NO_KERNEL:L} != "yes"
SUBDIR+= special
.  else
all:
	@print ============================================================
	@print ATTENTION: No kernel built, do that manually!
	@print ============================================================
.  endif
.endif

.if exists(${MACHINE})
SUBDIR+= ${MACHINE}

unconfig:
	cd ${MACHINE}; ${MAKE} unconfig

.endif

.include <bsd.subdir.mk>
