# $OpenBSD: Makefile,v 1.10 2002/12/29 20:31:40 fgsch Exp $
			
COMMENT=			passive network mapping tool

DISTNAME=		siphon-v.666
PKGNAME=		siphon-0.666-0
CATEGORIES=    		security net


# BSD-style
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes 
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://siphon.datanerds.net/ \
			${MASTER_SITE_PACKETSTORM:=UNIX/utilities/}

CPPFLAGS+=		-I. \
				-DSYSCONFDIR=\"${SYSCONFDIR}\"
EXTRA_MAKE_FLAGS+=	CCFLAGS='-pthread \
				-DSYSCONFDIR="\"${SYSCONFDIR}\""'
MAKE_ENV=		SYSCONFDIR="${SYSCONFDIR}"

NO_REGRESS=		Yes

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/siphon ${PREFIX}/bin
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/siphon
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/siphon
	${INSTALL_DATA} ${WRKSRC}/LICENSE ${PREFIX}/share/doc/siphon
	${INSTALL_DATA} ${WRKSRC}/README ${PREFIX}/share/doc/siphon
	${INSTALL_DATA} ${WRKSRC}/osprints.conf ${PREFIX}/share/examples/siphon

.include <bsd.port.mk>
