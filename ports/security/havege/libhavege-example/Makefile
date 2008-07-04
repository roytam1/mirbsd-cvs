# $MirOS$

COMMENT=		usage example for libhavege
CATEGORIES=		security sysutils
DIST_NAME=		libhavege-example
DIST_DATE=		20080407
DIST_SOURCE=		port
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>

# MirOS Licence
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

LIB_DEPENDS+=		havege::security/havege/libhavege

NO_REGRESS=		Yes
MAKE_FILE=		${.SYSMK}/bsd.prog.mk
EXTRA_XAKE_FLAGS+=	PROG=libhavege-example \
			LDADD=-lhavege \
			NOMAN=Yes

.include <bsd.port.mk>
