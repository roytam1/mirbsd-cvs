# $MirOS: ports/infrastructure/mk/p5.port.mk,v 1.2 2008/03/15 23:16:55 tg Exp $

.ifndef MODPERL_ARCH
MODPERL_ARCH!=	/usr/bin/perl -e 'use Config; print $$Config{archname}, "\n";'
.MAKEFLAGS:=	${.MAKEFLAGS} MODPERL_ARCH=${MODPERL_ARCH:Q}
.endif
.ifndef P5MAN3EXT
P5MAN3EXT!=	/usr/bin/perl -e 'use Config; print ".".$$Config{man3ext};'
.MAKEFLAGS:=	${.MAKEFLAGS} P5MAN3EXT=${P5MAN3EXT:Q}
.endif
.ifndef P5DLEXT
P5DLEXT!=	/usr/bin/perl -e 'use Config; print ".".$$Config{dlext};'
.MAKEFLAGS:=	${.MAKEFLAGS} P5DLEXT=${P5DLEXT:Q}
.endif

P5ARCH=		${P5SITE}/${MODPERL_ARCH}

SUBST_VARS+=	P5ARCH P5SITE P5MAN3EXT P5DLEXT
