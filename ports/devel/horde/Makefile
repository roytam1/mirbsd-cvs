# $MirOS: ports/devel/horde/Makefile,v 1.4 2006/09/14 00:08:16 tg Exp $
# $OpenBSD: Makefile,v 1.12 2004/05/01 16:16:34 avsm Exp $ 

BROKEN=			needs upgrading to PHP5
BROKEN+=		\n\tdomxml doesn't exist in PHP5

COMMENT=		modular framework for web-based applications
V=		2.2.5
DISTNAME=	horde-${V}
CATEGORIES=	devel www
HOMEPAGE=	http://www.horde.org/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_HORDE:=horde/tarballs/}

NO_BUILD=	Yes
NO_REGRESS=	Yes
PKG_ARCH=	*
EXTRACT_ONLY=

PREFIX=		${WWW_PREFIX}
INSTDIR=	${PREFIX}/horde
SUBST_VARS=	INSTDIR WWW_PREFIX

RUN_DEPENDS=	:php-core->=4.3.1:www/php/core \
		:php-mcrypt->=4.3.1:www/php/extensions,-mcrypt \
		:php-pear->=4.3.1:www/php/core,-pear \
		::devel/pear-Log \
		::mailnews/pear-Mail-Mime
#		:php-domxml->=4.3.1:www/php/extensions,-domxml \

do-install:
	@cd ${PREFIX} && tar zxf ${FULLDISTDIR}/${DISTNAME}${EXTRACT_SUFX}
	@mv ${INSTDIR}-${V} ${INSTDIR}

.include <bsd.port.mk>
