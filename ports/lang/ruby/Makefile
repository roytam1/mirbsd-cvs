# $MirOS: ports/lang/ruby/Makefile,v 1.3 2006/02/01 15:42:15 tg Exp $
# $OpenBSD: Makefile,v 1.27 2004/02/20 22:52:57 couderc Exp $

# to fix this, use ${OStriplet} or OSname+OSREV or OSname+OSver
BROKEN="OSname and OSrev abuse in lang/ruby/Makefile"

COMMENT=			object oriented script language with threads

VERSION=		1.8.1
DASH_VER=		-1
DISTNAME=		ruby-${VERSION}
PKGNAME=		${DISTNAME}${DASH_VER}
CATEGORIES=		lang

HOMEPAGE=		http://www.ruby-lang.org/

RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		ftp://www.ruby-lang.org/pub/ruby/1.8/ \
			ftp://mirror.nucba.ac.jp/pub/ruby/1.8/ \
			ftp://ftp.kr.freebsd.org/pub/ruby/1.8/

CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}

FLAVORS=		tk
FLAVOR?=

.if ${FLAVOR:L} == "tk"
LIB_DEPENDS=		tcl84.::lang/tcl/8.4 \
			tk84.::x11/tk/8.4

CONFIGURE_ARGS+=	--with-tcl-include=${PREFIX}/include/tcl8.4 \
			--with-tk-include=${PREFIX}/include/tk8.4 \
			--with-X11-dir=${X11BASE} 
.else
CONFIGURE_ARGS+=	--without-x11
.endif

NO_REGRESS=		Yes

.include <mirports.sys.mk>

REV=			1.8
SUB=			${MACHINE_ARCH}-${OSname}${OSrev}
SUBST_VARS=		SUB REV

post-extract:
	cd ${WRKSRC} && mv missing missing-funcs

.include <bsd.port.mk>
