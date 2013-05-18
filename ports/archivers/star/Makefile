# $MirOS: ports/archivers/star/Makefile,v 1.2 2006/02/09 12:25:12 tg Exp $
# $OpenBSD: Makefile,v 1.13 2003/02/18 12:59:10 naddy Exp $
# $FreeBSD: Makefile,v 1.7 1998/12/24 13:15:23 dirk Exp $

COMMENT=			unique standard tape archiver with many enhancements

DISTNAME=	star-1.4.3
CATEGORIES=	archivers sysutils
HOMEPAGE=	http://www.fokus.gmd.de/research/cc/glone/employees/joerg.schilling/private/star.html


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	ftp://ftp.berlios.de/pub/star/
EXTRACT_SUFX=	.tar.bz2

FLAVORS=	static
FLAVOR?=

RUN_DEPENDS=	:bzip2-*:archivers/bzip2

.include <bsd.own.mk>

USE_SCHILY=	Yes
MAKE_ENV+=	COPTX=${CFLAGS:Q}
.if ${FLAVOR:L:Mstatic}
MAKE_ENV+=	LDOPTX=-static
.endif

OBJ=	OBJ/${MACHINE}-openbsd-cc

do-install:
.for prog in star tartest
	${INSTALL_PROGRAM} ${WRKBUILD}/${prog}/${OBJ}/${prog} ${PREFIX}/bin
	${INSTALL_MAN} ${WRKSRC}/${prog}/${prog}.1 ${PREFIX}/man/man1
.endfor
	cd ${PREFIX}/bin; ln -sf star ustar
	cd ${PREFIX}/man/man1; ln -sf star.1 ustar.1
	${INSTALL_PROGRAM} ${WRKBUILD}/mt/${OBJ}/smt ${PREFIX}/bin
	${INSTALL_PROGRAM} ${WRKBUILD}/rmt/${OBJ}/rmt ${PREFIX}/libexec/srmt
	perl -pi -e 's,%%SYSCONFDIR%%,${SYSCONFDIR},g' ${WRKSRC}/rmt/rmt.1
	${INSTALL_MAN} ${WRKSRC}/rmt/rmt.1 ${PREFIX}/man/man8/srmt.8
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/star
	${INSTALL_DATA} ${WRKSRC}/rmt/rmt.dfl \
		${PREFIX}/share/examples/star/srmt.conf.sample

NO_REGRESS=	Yes

.include <bsd.port.mk>
