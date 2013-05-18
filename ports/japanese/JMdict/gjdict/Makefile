# $MirOS: ports/japanese/jmdict/gjdict/Makefile,v 1.2 2006/10/08 00:45:52 tg Exp $

BROKEN=			not fully ported nightmare
BROKEN+=		- start by fixing x11/gtkmm

COMMENT=		graphical japanese-english dictionary
CATEGORIES=		japanese x11
VSN=			1.0.1
DISTNAME=		gjdict-source-${VSN}
PKGNAME=		gjdict-${VSN}-${DASH_VER}
EXTRACT_SUFX=		.tar.bz2
HOMEPAGE=		http://gjdict.sourceforge.net/

# GPL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=gjdict/}

LIB_DEPENDS+=		sqlite::databases/sqlite2
#LIB_DEPENDS+=		sigc-2?0::devel/libsigc++
# ports/infrastructure/scripts/resolve-lib sucks major arse
LIB_DEPENDS+=		sigc-2.0.0.0::devel/libsigc++
LIB_DEPENDS+=		gtkmm::x11/gtkmm
RUN_DEPENDS+=		:jmdict-datfile-*:japanese/jmdict/datfile

USE_CXX=		Yes
USE_X11=		Yes
CPPFLAGS+=		-DDB_FILENAME=\"${LOCALBASE}/share/jmdict-datfile/dictionary\"

.include <bsd.port.mk>
