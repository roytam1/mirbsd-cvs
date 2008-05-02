# $MirOS: ports/lang/pcc/Makefile,v 1.1.201.1 2008/05/02 18:29:52 tg Exp $

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
NOT_FOR_PLATFORM+=	Darwin:*:i386

# linking against wrong libraries; segfault atexit
NOT_FOR_PLATFORM+=	Darwin:*:powerpc

COMMENT=		Portable C Compiler
CATEGORIES=		lang
CVS_DISTREPO=		:pserver:anonymous@pcc.ludd.ltu.se:/cvsroot
CVS_DISTDATE=		2008/05/02
CVS_DISTMODS=		pcc
HOMEPAGE=		http://pcc.ludd.ltu.se/
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>

# BSD
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ENV+=		MPVERSION=MirPorts:${PKGNAME:Q}
NO_REGRESS=		Yes

post-extract:
	cd files && pax -rw os ${WRKSRC}/

.include <bsd.port.mk>
