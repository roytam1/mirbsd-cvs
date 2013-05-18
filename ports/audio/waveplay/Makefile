# $OpenBSD: Makefile,v 1.17 2003/06/13 00:49:38 pvalchev Exp $
# $FreeBSD: ports/audio/waveplay/Makefile,v 1.2 1999/08/25 04:36:16 obrien Exp $

# assumes unaligned access, no struct padding, little endian
ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386

COMMENT=			simple wav audio player
DISTNAME=		waveplay-20010924
PKGNAME=		${DISTNAME}-1
CATEGORIES=		audio
MASTER_SITES=		http://sore.totto.to/~ysonoda/FreeBSD/ports/

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

EXTRA_MAKE_FLAGS+=	LDADD=-lossaudio
NO_REGRESS=		Yes

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/waveplay
	${INSTALL_DATA} ${WRKSRC}/README ${PREFIX}/share/doc/waveplay/
	${INSTALL_DATA} ${WRKSRC}/README.jp ${PREFIX}/share/doc/waveplay/

.include <bsd.port.mk>
