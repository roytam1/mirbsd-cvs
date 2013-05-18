# $MirOS: ports/devel/pcre/Makefile,v 1.10 2008/03/09 17:22:31 tg Exp $
# $OpenBSD: Makefile,v 1.12 2004/01/14 17:21:52 jakob Exp $

COMMENT=		perl-compatible regular expression library
DISTNAME=		pcre-7.9
CATEGORIES=		devel
MASTER_SITES=		ftp://ftp.csx.cam.ac.uk/pub/software/programming/pcre/ \
			${MASTER_SITE_SOURCEFORGE:=pcre/}
HOMEPAGE=		http://www.pcre.org/

# 3-clause UCB-style
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

FLAVOURS=		no_cxx
FLAVOUR?=

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--enable-static \
			--enable-utf8 \
			--enable-unicode-properties \
			--enable-newline-is-any

.if ${FLAVOUR:Mno_cxx}
CONFIGURE_ARGS+=	--disable-cpp
.else
USE_CXX=		Yes
.endif

.include <bsd.port.mk>
