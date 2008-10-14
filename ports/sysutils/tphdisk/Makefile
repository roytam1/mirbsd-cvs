# $MirOS$

COMMENT=		hibernation file creator for phoenix bios laptops
PKGNAME=		tphdisk-1.0-${DASH_VER}
CATEGORIES=		sysutils

# GNU GPL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		http://samba.org/ftp/unpacked/junkcode/
DISTFILES=		tphdisk.c
EXTRACT_CASES+=		*.c) cp ${FULLDISTDIR}/$$archive ${WRKDIR}/ ;;

WRKDIST=		${WRKDIR}
NO_REGRESS=		Yes
CONFIGURE_STYLE=	bmake
MAKE_FILE=		${.SYSMK}/bsd.prog.mk
EXTRA_XAKE_FLAGS+=	PROG=tphdisk NOMAN=Yes BINDIR=\$${BSD_PREFIX}/sbin

.include <bsd.port.mk>
