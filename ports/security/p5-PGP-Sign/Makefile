# $MirOS: ports/security/p5-PGP-Sign/Makefile,v 1.3 2006/09/14 00:13:14 tg Exp $
# $OpenBSD: Makefile,v 1.9 2002/07/15 03:26:24 shell Exp $

COMMENT=			perl module to create/verify PGP signatures
DISTNAME=	PGP-Sign-0.17
PKGNAME=	p5-${DISTNAME}-0
CATEGORIES=	security perl5
MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=PGP/}

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

FLAVOURS=	pgp pgp+ pgp5
FLAVOUR?=	

.if ${FLAVOUR:L:Mpgp}
RUN_DEPENDS=	:pgp-2.*:security/pgp
CONFIGURE_ARGS=	PGPV="${LOCALBASE}/bin/pgpv" PGPS="${LOCALBASE}/bin/pgps" PGPSTYLE="PGP"

.elif ${FLAVOUR:L:Mpgp+}
RUN_DEPENDS=	:pgp-2.*:security/pgp+
CONFIGURE_ARGS=	PGPV="${LOCALBASE}/bin/pgpv" PGPS="${LOCALBASE}/bin/pgps" PGPSTYLE="PGP"

.elif ${FLAVOUR:L:Mpgp5}
RUN_DEPENDS=	:pgp-5.*:security/pgp5
CONFIGURE_ARGS=	PGPV="${LOCALBASE}/bin/pgpv" PGPS="${LOCALBASE}/bin/pgps" PGPSTYLE="PGP5"

.else
RUN_DEPENDS=	:gnupg-*:security/gnupg
CONFIGURE_ARGS=	PGP="${LOCALBASE}/bin/gpg" PGPSTYLE="GPG"
.endif

BUILD_DEPENDS=	${RUN_DEPENDS}
CONFIGURE_STYLE= perl

.include <bsd.port.mk>
