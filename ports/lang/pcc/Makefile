# $MirOS: ports/lang/pcc/Makefile,v 1.6 2008/12/07 18:58:02 tg Exp $

ONLY_FOR_PLATFORM=	Darwin:*:i386 \
			Darwin:*:powerpc \
			MidnightBSD:*:i386 \
			MidnightBSD:*:sparc64 \
			MirBSD:*:i386 \
			OpenBSD:*:i386 \
			OpenBSD:*:powerpc \
			OpenBSD:*:sparc64 \
			OpenBSD:*:vax

# using wrong assembler syntax
#XXX revisit with 1.0.0
NOT_FOR_PLATFORM+=	Darwin:*:i386

# linking against wrong libraries; segfault atexit
#XXX revisit with 1.0.0
NOT_FOR_PLATFORM+=	Darwin:*:powerpc

COMMENT=		Portable C Compiler
CATEGORIES=		lang
DISTNAME=		pcc-1.0.0
HOMEPAGE=		http://pcc.ludd.ltu.se/
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>

# BSD
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		http://pcc.ludd.ltu.se/ftp/pub/pcc-releases/
EXTRACT_SUFX=		.tgz

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ENV+=		MPVERSION=MirPorts:${PKGNAME:Q}
NO_REGRESS=		Yes
VERSIONSUBDIR=		1.0.0.RELEASE
SUBST_VARS+=		OStriplet VERSIONSUBDIR

.include <bsd.port.mk>
