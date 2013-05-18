# $MirOS: ports/infrastructure/mk/p5.port.mk,v 1.3 2009/12/28 14:55:14 tg Exp $

.ifndef MODPERL_ARCH
MODPERL_ARCH!=	/usr/bin/perl -e 'use Config; print $$Config{archname}, "\n";'
.  if ${__MAKEFLAGS_HACKERY:L} == "yes"
.MAKEFLAGS:=	${.MAKEFLAGS} MODPERL_ARCH=${MODPERL_ARCH:Q}
.  endif
.endif
.ifndef P5MAN3EXT
P5MAN3EXT!=	/usr/bin/perl -e 'use Config; print ".".$$Config{man3ext};'
.  if ${__MAKEFLAGS_HACKERY:L} == "yes"
.MAKEFLAGS:=	${.MAKEFLAGS} P5MAN3EXT=${P5MAN3EXT:Q}
.  endif
.endif
.ifndef P5DLEXT
P5DLEXT!=	/usr/bin/perl -e 'use Config; print ".".$$Config{dlext};'
.  if ${__MAKEFLAGS_HACKERY:L} == "yes"
.MAKEFLAGS:=	${.MAKEFLAGS} P5DLEXT=${P5DLEXT:Q}
.  endif
.endif

P5ARCH=		${P5SITE}/${MODPERL_ARCH}

SUBST_VARS+=	P5ARCH P5SITE P5MAN3EXT P5DLEXT
