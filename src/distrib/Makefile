# $MirOS: src/distrib/Makefile,v 1.2 2005/03/06 18:58:01 tg Exp $
# $OpenBSD: Makefile,v 1.25 2004/05/03 15:18:18 drahn Exp $

.include "Makefile.inc"
REL_NO_KERNEL?=	No

.if	make(obj)
SUBDIR+= special amd64 i386 sparc
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
