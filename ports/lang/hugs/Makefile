# $MirOS: ports/lang/hugs/Makefile,v 1.5 2006/09/14 00:10:20 tg Exp $
# $OpenBSD: Makefile,v 1.5 2004/05/17 02:24:32 dons Exp $

COMMENT=			Haskell 98 interpreter

VSN=		Nov2003
DISTNAME=	hugs98-${VSN}
PKGNAME=	hugs98-200311-${DASH_VER}
CATEGORIES=	lang
HOMEPAGE=	http://www.haskell.org/hugs/
MASTER_SITES=	http://cvs.haskell.org/Hugs/downloads/${VSN}/
MASTER_SITES0=	ftp://ftp.cse.unsw.edu.au/pub/users/dons/hugs98/

DISTFILES=	${DISTNAME}.tar.gz ${DISTNAME}-regress.tar.bz2:0

CONFIGURE_STYLE=dest
CONFIGURE_ARGS+=--with-pthreads --disable-ffi --libdir=${PREFIX}/share

WRKBUILD=	${WRKDIST}/src
ALL_TARGET=

do-configure:
	@(cd ${WRKBUILD}/unix && ${CONFIGURE_ENV} ./configure ${CONFIGURE_ARGS})

do-regress:
	@(cd ${WRKDIST}/tests && sh testScript static tcheck rts libs)

# BSDish
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

.include <bsd.port.mk>
