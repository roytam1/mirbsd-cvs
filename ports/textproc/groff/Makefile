# $MirOS$

# probably easy to add others, but packing list is different
ONLY_FOR_PLATFORM=		MirBSD:*:* Interix:*:*

COMMENT=			GNU troff compatible typesetter
COMMENT-docs=			documentation for groff
CATEGORIES=			textproc
VERSION=			1.19.2
PL=				0
DISTNAME=			groff-${VERSION}
PKGNAME=			groff-${VERSION}-${PL}
PKGNAME-docs=			groff-docs-${VERSION}-${PL}
HOMEPAGE=			http://www.gnu.org/software/groff/
RESPONSIBLE=			Thorsten Glaser <tg@mirbsd.de>
MASTER_SITES=			${MASTER_SITE_GNU:=groff/}
SUBST_VARS+=			VERSION

# GNU GPL Version 2 or later
PERMIT_DISTFILES_CDROM=		Yes
PERMIT_DISTFILES_FTP=		Yes
PERMIT_PACKAGE_CDROM=		Yes
PERMIT_PACKAGE_FTP=		Yes

FLAVORS=			console
FLAVOR?=			console

MULTI_PACKAGES=			-docs
SUBPACKAGE?=

.if ${SUBPACKAGE} == "-docs"
PERMIT_PACKAGE_CDROM=		"GNU FDL 1.2"
PERMIT_PACKAGE_FTP=		"GNU FDL 1.2"
.else
BUILD_DEPENDS+=			${GROFF_DEPENDS}
RUN_DEPENDS+=			${GROFF_DEPENDS}
.endif

.if !${FLAVOR:L:Mconsole}
GROFF_DEPENDS+=			:ghostscript-*:print/ghostscript/artifex
GROFF_DEPENDS+=			:psutils-*:print/psutils
GROFF_DEPENDS+=			:netpbm-*:graphics/netpbm
USE_X11=			Yes
.endif

USE_CXX=			Yes
CONFIGURE_STYLE=		autoconf dest
AUTOCONF_NEW=			Yes
CONFIGURE_ENV+=			PAGE=A4
EXTRA_XAKE_FLAGS+=		indexdir=/usr/share/dict/papers

.if ${FLAVOR:L:Mconsole}
CONFIGURE_ARGS+=		--without-x
CONFIGURE_ARGS+=		--without-gs
EXTRA_XAKE_FLAGS+=		make_html= make_install_html=
EXTRA_XAKE_FLAGS+=		make_pdfdoc= make_install_pdfdoc=
EXTRA_XAKE_FLAGS+=		DEVICE=utf8 OTHERDEVDIRS=
.else
CONFIGURE_ARGS+=		--with-appresdir=${_DESTPFX}${PREFIX}/lib/X11/app-defaults
EXTRA_XAKE_FLAGS+=		make_html=html make_pdfdoc=pdfdoc
EXTRA_XAKE_FLAGS+=		make_install_html=install_html
EXTRA_XAKE_FLAGS+=		make_install_pdfdoc=install_pdfdoc
.endif

post-extract:
	-rm -f ${WRKSRC}/doc/groff{,-*}

post-install:
	mv -f ${PREFIX}/info/groff ${PREFIX}/info/groff.info
	(cat /etc/man.conf 2>&- || :) | sed \
	    -e 's!/usr/bin/nrcon!nroff!g' \
	    -e 's!/usr/bin/nroff!nroff!g' \
	    -e 's!nroff!g& -c!g' \
	    -e 's!/usr/bin/tbl!tbl!g' \
	    -e 's!tbl!g&!g' >${PREFIX}/share/groff/man.conf
	${INSTALL_DATA} ${FILESDIR}/{,g}an.tmac ${PREFIX}/lib/groff/site-tmac/
	cd ${PREFIX}/lib/groff/site-tmac && ln -f an.tmac andoc.tmac
	cd ${PREFIX}/share/groff/${VERSION}/tmac && ln -f doc.tmac gdoc.tmac

.include <bsd.port.mk>
