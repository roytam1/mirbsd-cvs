# $MirOS$
# $MirOS: ports/security/clamav/Makefile,v 1.3 2006/09/14 00:12:55 tg Exp $

COMMENT=		free virus scanner
VERSION=		0.65
DISTNAME=		clamav-${VERSION}
CATEGORIES=		security
HOMEPAGE=		http://clamav.sourceforge.net/

# GNU GPL
PERMIT_PACKAGE_CDROM=	some dependencies are not allowed for CDROM
PERMIT_PACKAGE_FTP=	some dependencies are not allowed for FTP
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS=		gmp::devel/gmp

RUN_DEPENDS=		::archivers/lha \
			::archivers/unarj \
			::archivers/unrar \
			::archivers/zoo \
			::archivers/arc \
			::archivers/unzip \
			::archivers/bzip2

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=clamav/}

#Stuff the user might want to change
CLAMUSER=		_clamd
CLAMGROUP=		_mailscan

SUBST_VARS=		CLAMUSER CLAMGROUP

CONFIGURE_STYLE=        gnu
CONFIGURE_ARGS+=        ${CONFIGURE_SHARED}
CONFIGURE_ARGS+=        --disable-clamav \
			--enable-dependency-tracking \
			--disable-clamuko \
			--enable-bigstack \
			--with-user=${CLAMUSER} \
			--with-group=${CLAMGROUP} \
                        --disable-cr --disable-milter \
			--sbindir=${PREFIX}/libexec \
			--with-dbdir=${PREFIX}/libdata/clamav

LDFLAGS+=		-pthread
DOCS=			clamav-mirror-howto.pdf clamdoc.pdf signatures.pdf
DOCS+=			clamd_supervised/*.* html/*.*

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/clamav ${PREFIX}/share/examples/clamav
	cd ${WRKSRC}/docs; ${INSTALL_DATA} ${DOCS} ${PREFIX}/share/doc/clamav
	cd ${WRKSRC}/etc; ${INSTALL_DATA} clamav.conf ${PREFIX}/share/examples/clamav
	cd ${WRKSRC}/examples; ${INSTALL_DATA} ex1.c ${PREFIX}/share/examples/clamav

.include <bsd.port.mk>
