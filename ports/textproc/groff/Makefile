# $MirOS: ports/textproc/groff/Makefile,v 1.8 2008/03/23 16:16:31 tg Exp $

# probably easy to add others, but packing list is different
ONLY_FOR_PLATFORM=		MirBSD:*:* Interix:*:*

COMMENT=			GNU troff compatible typesetter
COMMENT-docs=			documentation for groff
CATEGORIES=			textproc
VERSION=			1.19.2
DASH_VER=			3
DISTNAME=			groff-${VERSION}
PKGNAME-docs=			groff-docs-${VERSION}-${DASH_VER}
HOMEPAGE=			http://www.gnu.org/software/groff/
RESPONSIBLE=			Thorsten Glaser <tg@mirbsd.de>
MASTER_SITES=			${MASTER_SITE_GNU:=groff/old/}
SUBST_VARS+=			VERSION

# GNU GPL Version 2 or later
PERMIT_DISTFILES_CDROM=		Yes
PERMIT_DISTFILES_FTP=		Yes
PERMIT_PACKAGE_CDROM=		Yes
PERMIT_PACKAGE_FTP=		Yes

FLAVOURS=			no_x11
FLAVOUR?=

MULTI_PACKAGES=			-docs
SUBPACKAGE?=

.if ${SUBPACKAGE} == "-docs"
PERMIT_PACKAGE_CDROM=		"GNU FDL 1.2"
PERMIT_PACKAGE_FTP=		"GNU FDL 1.2"
.else
B_R_DEPENDS+=			${GROFF_DEPENDS}
.endif

.if !${FLAVOUR:Mno_x11}
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

.if ${FLAVOUR:Mno_x11}
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
	    -e 's!tbl!g&!g' \
	    -e 's!\.gtbl!.tbl!' \
	    >${PREFIX}/share/groff/man.conf
	cd ${PREFIX}/share/groff && \
	    sed -e 's!gnroff!& -Tascii!g' man.conf >man_7bit.conf && \
	    sed -e 's!gnroff!& -Tlatin1!g' man.conf >man_ltn1.conf && \
	    sed -e 's!gnroff!& -Tutf8!g' man.conf >man_utf8.conf
	cd ${FILESDIR} && ${INSTALL_DATA} an.tmac andoc.tmac gan.tmac \
	    ${PREFIX}/lib/groff/site-tmac/
	cd ${PREFIX}/share/groff/${VERSION}/tmac && ln -f doc.tmac gdoc.tmac

.include <bsd.port.mk>
