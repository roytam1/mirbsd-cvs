# $MirOS: ports/www/php/pear/pear.port.mk,v 1.3 2005/09/11 02:34:18 tg Exp $
# $OpenBSD: pear.port.mk,v 1.2 2005/02/04 21:23:39 alek Exp $
# PHP PEAR module

RUN_DEPENDS+=		:php-pear-5.0.*:www/php/core,-pear
BUILD_DEPENDS+=		:php-pear-5.0.*:www/php/core,-pear

NO_BUILD=		Yes
.if !target(do-regress)
NO_REGRESS=		Yes
.endif

MAKE_FILE=		${PORTSDIR}/www/php/pear/Makefile.pear
EXTRA_FAKE_FLAGS+=	WRKINST=${WRKINST} WRKDIR=${WRKDIR}

PREFIX=			${WWW_PREFIX}

PEAR_LIBDIR=		${PREFIX}/pear/lib
PEAR_PHPBIN=		${LOCALBASE}/bin/php
