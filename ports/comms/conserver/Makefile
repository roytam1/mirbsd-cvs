# $OpenBSD: Makefile,v 1.25 2004/03/02 07:57:21 brad Exp $

COMMENT=			manage remote serial consoles via TCP/IP

DISTNAME=	conserver-7.2.7
CATEGORIES=	comms


HOMEPAGE=	http://www.conserver.com

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	ftp://ftp.conserver.com/conserver/

CONFIGURE_STYLE= autoconf
CONFIGURE_ARGS=	--with-64bit \
		--with-master=localhost

REGRESS_TARGET=	test

post-install:
	@${INSTALL_DATA} ${FILESDIR}/README.OpenBSD ${PREFIX}/share/examples/conserver

.include <bsd.port.mk>
