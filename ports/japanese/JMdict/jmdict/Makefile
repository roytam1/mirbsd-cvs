# $MirOS$

COMMENT=		console japanese-english dictionary
CATEGORIES=		japanese
V=			0.3
DISTNAME=		jmdict-$V
PKGNAME=		jmdict-$V-0
EXTRACT_SUFX=		.tar.bz2
HOMEPAGE=		http://mandrill.fuxx0r.net/jmdict.php

# GPL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		http://mandrill.fuxx0r.net/files/

LIB_DEPENDS+=		sqlite::databases/sqlite2
RUN_DEPENDS+=		:jmdict-datfile-*:japanese/jmdict/datfile

USE_CXX=		Yes
MAKE_FILE=		${.CURDIR}/jd.mk
NO_REGRESS=		Yes
CPPFLAGS+=		-DJMDICT_SQL_PATH=\"${LOCALBASE}/share/jmdict-datfile/\"

post-extract:
	cd ${WRKSRC} && for a in *.cpp; do mv $$a $${a%pp}c; done
	cd ${WRKSRC} && mv sqlite.h sqlitexx.h

.include <bsd.port.mk>
