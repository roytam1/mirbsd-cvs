# $MirOS$

MODPERL_ARCH!=	/usr/bin/perl -e 'use Config; print $$Config{archname}, "\n";'

P5ARCH=		${P5SITE}/${MODPERL_ARCH}

SUBST_VARS+=	P5ARCH
