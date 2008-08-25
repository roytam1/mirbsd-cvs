# $MirOS$
# $OpenBSD: Makefile,v 1.4 2007/09/17 12:14:11 kettenis Exp $

# may be possible to port to MidnightBSD
ONLY_FOR_PLATFORM=	MirBSD:*:i386 \
			OpenBSD:*:i386 OpenBSD:*:amd64

COMMENT=		change resolution on available vbios modes for i8x5/9x5 VGA
DISTNAME=		915resolution-0.5.3
CATEGORIES=		x11
HOMEPAGE=		http://www.geocities.com/stomljen/

# public domain
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		${HOMEPAGE}
NO_REGRESS=		Yes
MAKE_FILE=		${.SYSMK}/bsd.prog.mk
EXTRA_XAKE_FLAGS+=	PROG=915resolution \
			BINDIR=${TRUEPREFIX:Q}/sbin \
			LDADD=-l${MACHINE_ARCH:Q} \
			NOMAN=Yes

post-extract:
	cd ${WRKBUILD} && rm -f 915resolution{,.o}

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/915resolution
	${INSTALL_DATA} ${WRKSRC}/README.txt \
	    ${PREFIX}/share/doc/915resolution/

.include <bsd.port.mk>
