# $MirOS: ports/games/bnetd/Makefile,v 1.4 2006/09/14 00:09:18 tg Exp $

COMMENT=			Battle.net(R) server emulator
DISTNAME=		bnetd-20050215
CATEGORIES=		net games
MASTER_SITES=		${_MASTER_SITE_MIRBSD}

# GNU GPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

WRKSRC=			${WRKDIST}/src
LIBDIR=			${PREFIX}/libdata/bnetd
DOCSRC=			${WRKDIST}/docs
DOCDIR=			${PREFIX}/share/doc/bnetd
DOCFILES=		../CHANGELOG ../CREDITS ../INSTALL ../README ../TODO \
			FAQ.html README.adbanner README.bits README.bni \
			README.diablo108 README.ladder README.registry \
			TODO.Sherpya TODO_BUCKY TODO_VAP bniheader.txt
LIBFILES=		files/icons_STAR.bni scripts/announce.sh \
			scripts/fsgs2bnetd.pl scripts/ladder.py \
			scripts/process.pl scripts/reform.awk conf/bnalias.list

CONFIGURE_STYLE=	autoconf dest
CONFIGURE_ARGS+=	--localstatedir='$${${DESTDIRNAME}}${LIBDIR}'
NO_REGRESS=		Yes

.include <mirports.sys.mk>

post-install:
	${INSTALL_DATA_DIR} ${DOCDIR} ${LIBDIR}/scripts
	cd ${DOCSRC} && ${INSTALL_DATA} ${DOCFILES} ${DOCDIR}/
.for _i in ${LIBFILES}
	${INSTALL_DATA} ${WRKDIST}/${_i} ${LIBDIR}/${_i}
.endfor
	chmod 644 ${LIBDIR}/conf/*

.include <bsd.port.mk>
