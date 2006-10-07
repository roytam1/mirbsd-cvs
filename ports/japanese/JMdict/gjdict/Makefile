# $MirOS$

BROKEN=			not fully ported nightmare

COMMENT=		graphical japanese-english dictionary
CATEGORIES=		japanese x11
V=			1.0.1
DISTNAME=		gjdict-source-$V
PKGNAME=		gjdict-$V-0
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
