# $OpenBSD: Makefile,v 1.9 2002/10/28 17:35:02 naddy Exp $

COMMENT=			radius sniffer

DISTNAME=		radiusniff-0.2
CATEGORIES=     	security

PERMIT_PACKAGE_CDROM=	"not specified, vague license"
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	"not specified, vague license"
PERMIT_DISTFILES_FTP=	Yes

EXTRACT_SUFX=		.tgz
MASTER_SITES=		http://adm.freelsd.net/ADM/

WRKSRC=			${WRKDIR}/radiusniff-0.2

NO_REGRESS=		Yes

do-build:
	cd ${WRKSRC} && ${_PASS_CC:Q} -DOPENBSD \
	-DDICTIONARY_FILENAME=\"${PREFIX}/share/radiusniff/dictionary\" \
	-DCLIENTS_FILENAME=\"${PREFIX}/share/radiusniff/clients\" \
	-I${LOCALBASE}/include -L${LOCALBASE}/lib -o radiusniff \
	radiusniff.c md5.c -lpcap -lresolv

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/radiusniff ${PREFIX}/bin
	${INSTALL_DATA_DIR} ${PREFIX}/share/radiusniff/
	${INSTALL_DATA} ${WRKSRC}/{dictionary,clients} ${PREFIX}/share/radiusniff

.include <bsd.port.mk>
