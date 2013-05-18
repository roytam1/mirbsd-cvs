# $MirOS: ports/devel/p5-Term-ReadKey/Makefile,v 1.5 2007/10/11 21:10:58 bsiegert Exp $
# $OpenBSD: Makefile,v 1.11 2004/01/17 15:58:08 naddy Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=		change terminal modes, and perform non-blocking reads

VSN=			2.30
DISTNAME=		TermReadKey-${VSN}
PKGNAME=		p5-Term-ReadKey-${VSN}-${DASH_VER}
CATEGORIES=		devel perl5


PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=Term/}

CONFIGURE_STYLE=	perl
REGRESS_IS_INTERACTIVE=	Yes

.include <bsd.port.mk>
