# $OpenBSD: Makefile,v 1.13 2004/05/22 19:54:10 jolan Exp $

COMMENT=			opensource Napster(tm) server

DISTNAME=	opennap-0.44
PKGNAME=	${DISTNAME}-1
CATEGORIES=	audio net
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=opennap/}

HOMEPAGE=	http://opennap.sourceforge.net/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_GMAKE=	Yes
CONFIGURE_STYLE=gnu
CONFIGURE_ARGS=	\
	--enable-email \
	--enable-resume \
	--datadir=${SYSCONFDIR} \
	--with-uid=_opennap \
	--with-gid=_opennap
#	--enable-chroot \  (breaks uid, gid, and ip lookup)

.if ${MACHINE_ARCH} == "vax"
CFLAGS+=	-O0 # XXX compiler bugs
.endif

DOCS=	FAQ README manual.html napster.txt

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/opennap
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/opennap
	cd ${WRKSRC}; ${INSTALL_DATA} ${DOCS} ${PREFIX}/share/doc/opennap
	${INSTALL_DATA} ${WRKSRC}/sample.* ${PREFIX}/share/examples/opennap

.include <bsd.port.mk>
