# $MirOS: ports/lang/pcc/Makefile,v 1.7 2011/04/02 13:14:59 tg Exp $

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
UVERSION=		1.0.999
UDATE=			20110422
HOMEPAGE=		http://pcc.ludd.ltu.se/
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>

.if defined(UDATE) && !empty(UDATE)
DISTNAME=		pcc-${UDATE}
PKGNAME=		pcc-${UVERSION}-${UDATE}-${DASH_VER}
.else
DISTNAME=		pcc-${UVERSION}
.endif

# BSD
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

.if defined(UDATE) && !empty(UDATE)
MASTER_SITES=		http://pcc.ludd.ltu.se/ftp/pub/pcc/
.else
MASTER_SITES=		http://pcc.ludd.ltu.se/ftp/pub/pcc-releases/
.endif
EXTRACT_SUFX=		.tgz

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ENV+=		MPVERSION=MirPorts:${PKGNAME:Q}
NO_REGRESS=		Yes
VERSIONSUBDIR=		1.1.0.DEVEL
SUBST_VARS+=		OStriplet VERSIONSUBDIR

.include <bsd.port.mk>
