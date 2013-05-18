# $MirOS: ports/infrastructure/mk/p5.port.mk,v 1.1 2008/03/14 20:19:43 tg Exp $

MODPERL_ARCH!=	/usr/bin/perl -e 'use Config; print $$Config{archname}, "\n";'
P5MAN3EXT!=	/usr/bin/perl -e 'use Config; print ".".$$Config{man3ext};'
P5DLEXT!=	/usr/bin/perl -e 'use Config; print ".".$$Config{dlext};'

P5ARCH=		${P5SITE}/${MODPERL_ARCH}

SUBST_VARS+=	P5ARCH P5SITE P5MAN3EXT P5DLEXT
