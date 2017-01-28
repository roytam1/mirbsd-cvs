# $MirOS: ports/devel/autoconf/2.62/Makefile,v 1.3 2009/11/22 00:16:22 tg Exp $

COMMENT=		automatically configure source code on many Un*x platforms
VSN=			2.62
DISTNAME=		autoconf-${VSN}
DASH_VER=		2
CATEGORIES=		devel
HOMEPAGE=		http://www.gnu.org/software/autoconf/

# GNU GPLv2+ (v3 files not installed)
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

.include <mirports.sys.mk>

MASTER_SITES=		${MASTER_SITE_GNU:=autoconf/}
BUILD_DEPENDS+=		:help2man-*:devel/help2man
USE_M4=			new	# XXX maybe "old" is enough?
MODULES+=		m4
B_R_DEPENDS+=		${MODM4_DEPENDS}

CONFIGURE_STYLE=	gnu
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--program-suffix=-${VSN:Q}
CONFIGURE_ENV+=		AWK=${AWK:Q}
CONFIGURE_ENV+=		M4=${M4:Q}
CONFIGURE_ENV+=		EMACS=no
EXTRA_XAKE_FLAGS+=	pkgdatadir=${PREFIX:Q}/share/${DISTNAME:Q}

# many tests appear to fail, for whitespace and lineno. diffs only
REGRESS_DEPENDS+=	::devel/automake/1.9
REGRESS_FLAGS+=		AUTOMAKE_VERSION=1.9

pre-configure:
	print ',g/'${VSN:S/./\./g:Q}'/s//&-MirPorts-${DASH_VER}/g\nwq' | \
	    ed -s ${WRKSRC}/configure

post-install:
	cd ${PREFIX:Q}/info && for a in *.info*; do \
		[[ $$a = *-${VSN:Q}* ]] && continue; \
		pre=$${a%%.info*}; post=$${a#$$pre}; \
		mv "$$a" "$${pre}-${VSN:Q}$$post"; \
	done

.include <bsd.port.mk>
