# $OpenBSD: Makefile,v 1.44 2004/05/24 07:04:44 kevlo Exp $

BROKEN=			unfetchable distfile

COMMENT=		shell-like command line ftp and sftp client

DISTNAME=	lftp-3.0.3
CATEGORIES=	net
xMASTER_SITES=	http://the.wiretapped.net/mirrors/lftp/ \
		http://the.wiretapped.net/mirrors/lftp/old/ \
		ftp://ftp.ayamura.org/pub/lftp/ \
		ftp://ftp.ayamura.org/pub/lftp/old/ \
		ftp://ftp.yars.free.net/pub/software/unix/net/ftp/client/lftp/ \
		ftp://ftp.yars.free.net/pub/software/unix/net/ftp/client/lftp/old/ \
		http://ftp.yars.free.net/pub/software/unix/net/ftp/client/lftp/ \
		http://ftp.yars.free.net/pub/software/unix/net/ftp/client/lftp/old/
EXTRACT_SUFX=	.tar.bz2

HOMEPAGE=	http://lftp.yar.ru/


PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

CONFIGURE_STYLE= gnu 
CONFIGURE_ARGS=	--with-ssl

MODULES=	devel/gettext

NO_REGRESS=	Yes

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/lftp
	${INSTALL_DATA} ${WRKSRC}/lftp.conf ${PREFIX}/share/examples/lftp/lftp.conf-sample

.include <bsd.port.mk>
