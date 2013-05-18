# $MirOS: ports/shells/bash/Makefile,v 1.4 2006/02/09 09:36:17 tg Exp $
# $OpenBSD: Makefile,v 1.27 2004/01/13 20:09:39 naddy Exp $

COMMENT=	"GNU Bourne Again Shell"
DISTNAME=	bash-2.05b
PKGNAME=	${DISTNAME}-1
CATEGORIES=	shells
HOMEPAGE=	http://cnswww.cns.cwru.edu/~chet/bash/bashtop.html

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_GNU:=bash/}
MASTER_SITES0=	http://ftp.gnu.org/gnu/bash/bash-2.05b-patches/ \
		${MASTER_SITE_FREEBSD_LOCAL:=obrien/}
DISTFILES=	${DISTNAME}.tar.gz ${DISTNAME:S/-/-doc-/}.tar.gz
.for i in 001 002 003 004 005 006 007
PATCHFILES+=	bash205b-${i}:0
.endfor

FLAVORS=	static
FLAVOR?=

CONFIGURE_STYLE= gnu
MODGNU_CONFIG_GUESS_DIRS= ${WRKSRC} ${WRKSRC}/support
CONFIGURE_ENV+=	ac_cv_lib_intl=no
CONFIGURE_ENV+=	ac_cv_lib_intl_bindtextdomain=no

.if ${FLAVOR:L} == "static"
CONFIGURE_ARGS+=--enable-static-link
.endif

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/bash
	cd ${WRKDIR}/doc && \
	    ${INSTALL_DATA} article.ps article.txt bash.html bash.ps \
		bashbug.ps bashref.html bashref.ps builtins.ps  \
		${PREFIX}/share/doc/bash

.include <bsd.port.mk>
