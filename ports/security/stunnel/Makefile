# $MirOS: ports/security/stunnel/Makefile,v 1.2 2005/12/16 22:42:00 tg Exp $
# $OpenBSD: Makefile,v 1.22.4.2 2003/09/03 19:13:48 brad Exp $

COMMENT=			SSL encryption wrapper for standard network daemons
DISTNAME=	stunnel-3.26
CATEGORIES=	security
HOMEPAGE=	http://stunnel.mirt.net/

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	ftp://stunnel.mirt.net/stunnel/ \
		http://www.stunnel.org/download/stunnel/src/ \
		http://mike.daewoo.com.pl/computer/stunnel/ \
		http://opensores.thebunker.net/pub/mirrors/stunnel/ \
		ftp://ftp.fu-berlin.de/unix/security/stunnel/ \
		ftp://ftp.uni-freiburg.de/pub/net/stunnel/ \
		ftp://ftp.all.de/pub2/unix/security/stunnel/

BUILD_DEPENDS=  ::textproc/p5-sdf

CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	--with-pem-dir=${SYSCONFDIR}/ssl \
			--with-random=/dev/arandom
ALL_TARGET=		stunnel stunnel.8

.include <mirports.sys.mk>
.if ${OStype} == OpenBSD
CONFIGURE_ARGS+=	--with-tcp-wrappers
.else
CONFIGURE_ARGS+=	--without-tcp-wrappers
.endif

post-configure:
	rm ${WRKSRC}/stunnel.8

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/stunnel ${PREFIX}/sbin
	${INSTALL_MAN} ${WRKSRC}/stunnel.8 ${PREFIX}/man/man8/

.include <bsd.port.mk>
