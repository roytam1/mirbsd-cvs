# $OpenBSD: Makefile,v 1.4 2002/10/28 01:38:45 naddy Exp $
# $FreeBSD: ports/net/nslint/Makefile,v 1.10 2000/04/09 18:12:37 cpiazza Exp $

COMMENT=			performs consistency checks on BIND files

DISTNAME=		nslint-2.0.2
CATEGORIES=     	net


PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		ftp://ftp.ee.lbl.gov/

FLAVOURS=		static
FLAVOUR?=

.if ${FLAVOUR:L} == "static"
CONFIGURE_ENV+=		LDFLAGS=-static
.endif

CONFIGURE_STYLE=	gnu
ALL_TARGET=		nslint
INSTALL_TARGET=		install install-man

NO_REGRESS=		Yes

.include <bsd.port.mk>
