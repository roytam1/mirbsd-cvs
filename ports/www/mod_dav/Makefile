# $MirOS$
# $OpenBSD: Makefile,v 1.7 2004/05/24 09:34:04 sturm Exp $

# This port currently only works with archs supporting dynamic loading
# and has Apache that supports DSOs.
NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=		class 1 and 2 DAV server for the Apache webserver
PKGNAME=		mod_dav-1.0.3-0
DISTNAME=		mod_dav-1.0.3-1.3.6
CATEGORIES=		www
MASTER_SITES=		http://www.webdav.org/mod_dav/
HOMEPAGE=		http://www.webdav.org/mod_dav/

# Apache
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES+=		textproc/expat

CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	--with-apxs=/usr/sbin/apxs \
			--with-expat=${EXPAT_PREFIX}
NO_REGRESS=		Yes

SUBST_VARS=		PKGNAME

DOCDIR=			share/doc/mod_dav
DOCFILES=		README INSTALL LICENSE.html

post-build:
	@sed 's,!!PREFIX!!,${PREFIX},' \
		< ${FILESDIR}/mod_dav-enable > ${WRKBUILD}/mod_dav-enable

do-install:
	${INSTALL_SCRIPT} ${WRKBUILD}/mod_dav-enable ${PREFIX}/sbin
	${INSTALL_DATA} ${WRKBUILD}/libdav.so ${PREFIX}/lib
	${INSTALL_DATA_DIR} ${PREFIX}/${DOCDIR}
.for f in ${DOCFILES}
	${INSTALL_DATA} ${WRKSRC}/${f} ${PREFIX}/${DOCDIR}
.endfor

.include <bsd.port.mk>
