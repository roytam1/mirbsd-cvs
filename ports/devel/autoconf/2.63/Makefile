# $MirOS: ports/devel/autoconf/2.63/Makefile,v 1.4 2009/11/18 20:54:27 bsiegert Exp $

COMMENT=		automatically configure source code on many Un*x platforms
SUFFIX=			-2.63
DISTNAME=		autoconf${SUFFIX}
DASH_VER=		1
CATEGORIES=		devel
MASTER_SITES=		${MASTER_SITE_GNU:=autoconf/}
HOMEPAGE=		http://www.gnu.org/software/autoconf/

# GNU GPLv3
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

BUILD_DEPENDS=		:help2man-*:devel/help2man
USE_M4=			gnu_1.4.5
MODULES+=		m4
B_R_DEPENDS+=		${MODM4_DEPENDS}

CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	--program-suffix=${SUFFIX} \
			--without-lispdir
CONFIGURE_ENV+=		M4=${M4:Q} AWK=${AWK:Q}
EXTRA_XAKE_FLAGS+=	pkgdatadir=${PREFIX:Q}/share/autoconf${SUFFIX}
EXTRA_FAKE_FLAGS+=	DESTDIR=${WRKINST:Q} lispdir=
SUBST_VARS=		SUFFIX

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
