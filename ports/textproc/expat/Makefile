# $MirOS: ports/textproc/expat/Makefile,v 1.3 2006/09/14 00:14:03 tg Exp $
# $OpenBSD: Makefile,v 1.20 2003/10/19 22:37:21 brad Exp $
# $FreeBSD: Makefile,v 1.2 1999/08/31 02:09:14 peter Exp $

COMMENT=		XML 1.0 parser written in C
DISTNAME=		expat-2.0.0
DASH_VER=		1
CATEGORIES=		textproc
#MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=expat/}
MASTER_SITES=		${MASTER_SITE_FREEBSD} # temporary location, sf has problems
HOMEPAGE=		http://expat.sourceforge.net/

# BSD
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--libdir=${PREFIX}/pkgview/expat/lib \
			--includedir=${PREFIX}/pkgview/expat/include

.include <bsd.port.mk>
