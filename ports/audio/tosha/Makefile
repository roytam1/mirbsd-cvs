# $MirOS: ports/audio/tosha/Makefile,v 1.4 2008/10/04 19:02:57 tg Exp $
# $OpenBSD: Makefile,v 1.22 2003/08/09 17:39:16 pvalchev Exp $

COMMENT=		read CD digital audio data through the SCSI bus
DISTNAME=		tosha-0.6
DASH_VER=		1
CATEGORIES=		audio

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_FREEBSD_LOCAL:=markp/}

MAKE_ENV=		SYSCONFDIR=${SYSCONFDIR:Q} CC=${_PASS_CC:T:Q}

NO_REGRESS=		Yes

post-patch:
	cp ${FILESDIR}/libscsi* ${WRKSRC}/

.include <bsd.port.mk>
