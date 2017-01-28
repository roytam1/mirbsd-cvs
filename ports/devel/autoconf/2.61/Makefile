# $MirOS: ports/devel/autoconf/2.61/Makefile,v 1.4 2009/11/21 17:24:39 tg Exp $

COMMENT=		automatically configure source code on many Un*x platforms
SUFFIX=			-2.61
DISTNAME=		autoconf${SUFFIX}
DASH_VER=		2
CATEGORIES=		devel
MASTER_SITES=		${MASTER_SITE_GNU:=autoconf/}
HOMEPAGE=		http://www.gnu.org/software/autoconf/

# GPL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

BUILD_DEPENDS=		:help2man-*:devel/help2man
USE_M4=			bsd
MODULES+=		m4
B_R_DEPENDS+=		${MODM4_DEPENDS}

CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	--program-suffix=${SUFFIX} \
			--without-lispdir
CONFIGURE_ENV+=		M4=${M4:Q}
CONFIGURE_ENV+=		AWK=${AWK:Q}
EXTRA_XAKE_FLAGS+=	pkgdatadir=${PREFIX:Q}/share/autoconf${SUFFIX}
EXTRA_FAKE_FLAGS+=	DESTDIR=${WRKINST:Q} lispdir=
SUBST_VARS=		SUFFIX

NO_REGRESS=		Yes

pre-configure:
	print ',g/${SUFFIX:S/^-//:S/./\./}/s//&-MirPorts-${DASH_VER}/g\nwq' | \
	    ed -s ${WRKSRC}/configure

post-install:
	cd ${PREFIX}/info && for a in *.info*; do \
		[[ $$a = *${SUFFIX}* ]] && continue; \
		pre=$${a%%.info*}; post=$${a#$$pre}; \
		mv "$$a" "$${pre}${SUFFIX}$$post"; \
	done

.include <bsd.port.mk>
