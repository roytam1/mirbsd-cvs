# $OpenBSD: Makefile,v 1.19 2003/09/23 16:44:06 fgsch Exp $

COMMENT=			GNU version of Go

DISTNAME=	gnugo-3.4
CATEGORIES=	games
MASTER_SITES=	${MASTER_SITE_GNU:=gnugo/}


HOMEPAGE=	http://www.gnu.org/software/gnugo/

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	gnu

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/gnugo
	${INSTALL_DATA} ${WRKSRC}/interface/gnugo.el \
		${PREFIX}/share/gnugo

do-regress:
	cd ${WRKSRC}/regression && ${MAKE} all_batches

.include <bsd.port.mk>
