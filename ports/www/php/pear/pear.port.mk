# $MirOS$
# $OpenBSD: pear.port.mk,v 1.1.1.1 2004/10/02 11:32:38 robert Exp $
# PHP PEAR module

RUN_DEPENDS+=    :php-pear-5.0.*:www/php/core,-pear
BUILD_DEPENDS+=  :php-pear-5.0.*:www/php/core,-pear

NO_BUILD=       Yes
NO_REGRESS=     Yes

MAKE_FILE=	${PORTSDIR}/www/php/pear/Makefile.pear
FAKE_FLAGS+=	WRKINST=${WRKINST} WRKDIR=${WRKDIR}

PREFIX=		/var/www
