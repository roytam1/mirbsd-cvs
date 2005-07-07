# $MirOS: ports/audio/p5-Audio-CD/Makefile,v 1.1.7.1 2005/03/18 15:43:04 tg Exp $
# $OpenBSD: Makefile,v 1.8 2004/01/17 15:58:06 naddy Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=		"interface to libcdaudio"
DISTNAME=	 	Audio-CD-0.04
PKGNAME=		p5-${DISTNAME}-0
CATEGORIES=		audio perl5


PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=Audio/}

CONFIGURE_STYLE=	perl
CPPFLAGS+=		"-I${LOCALBASE}/include"
LDFLAGS+=		"-L${LOCALBASE}/lib"

LIB_DEPENDS=		cdaudio.1::audio/libcdaudio

.include <bsd.port.mk>
