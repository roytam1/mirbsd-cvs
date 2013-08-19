# $MirOS$
# $OpenBSD: Makefile,v 1.11 2013/07/17 16:42:12 bcallah Exp $

COMMENT=		decoder for JBIG2 monochrome hi-res image compression format

DISTNAME=		jbig2dec-0.11
DISTFILES=		${DISTNAME}${EXTRACT_SUFX} \
			jb2streams.zip:0
CATEGORIES=		graphics
HOMEPAGE=		http://jbig2dec.sourceforge.net/

# GPLv2+
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=jbig2dec/}
MASTER_SITES0=		http://jbig2dec.sourceforge.net/ubc/

MODULES+=		graphics/png

SEPARATE_BUILD=		Yes
AUTOCONF_NEW=		Yes
CONFIGURE_STYLE=	autoconf

REGRESS_DEPENDS+=	:python-*:lang/python/2.5

post-extract:
	mkdir -p ${WRKDIR}/ubc
	mv ${WRKDIR}/*bmp ${WRKDIR}/*jb2 ${WRKDIR}/ubc/

.include <bsd.port.mk>

_CIPHERS+=		sha256
