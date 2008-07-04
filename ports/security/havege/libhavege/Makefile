# $MirOS$

# weird configure trying to cater for build system
ONLY_FOR_PLATFORM+=	*:*:i386	# PIII, PIV, Athlon
ONLY_FOR_PLATFORM+=	*:*:ia64	# Itanium 1 (Merced)
ONLY_FOR_PLATFORM+=	*:*:sparc64	# Ultra, UIII, UIV
ONLY_FOR_PLATFORM+=	*:*:powerpc	# G4

COMMENT=		high-throughput unpredictable random number generator
DISTNAME=		libhavege-1.0
CATEGORIES=		security
HOMEPAGE=		http://www.irisa.fr/caps/projects/hipsor/index.php
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>

# GNU LGPLv2.1
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	"compiles into build-system-dependent code"
PERMIT_PACKAGE_FTP=	"compiles into build-system-dependent code"

MASTER_SITES=		http://www.irisa.fr/caps/projects/hipsor/download/libhavege/
DISTFILES=		${DISTNAME:S/-/_/}.orig${EXTRACT_SUFX}

NO_REGRESS=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/libhavege
	cd ${WRKSRC} && \
	    ${INSTALL_DATA} INSTALL README ${PREFIX}/share/doc/libhavege/

.include <bsd.port.mk>
