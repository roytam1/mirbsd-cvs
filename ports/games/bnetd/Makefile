# $MirOS$

COMMENT=	"Battle.net(r) server emulator"
DISTNAME=	bnetd-0.4.25
CATEGORIES=	net games
MASTER_SITES=	${_MASTER_SITE_MIRBSD}

# GNU GPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

WRKSRC=			${WRKDIST}/src
LIBDIR=			${PREFIX}/libdata/bnetd
DOCSRC=			${WRKDIST}/docs
DOCDIR=			${PREFIX}/share/doc/bnetd
DOCFILES=		FAQ.html README.adbanner README.bits README.bni \
			README.diablo108 README.ladder README.registry \
			bniheader.txt ../CREDITS ../README

CONFIGURE_STYLE=	autoconf dest
CONFIGURE_ARGS+=	--localstatedir='$${${DESTDIRNAME}}${LIBDIR}'

.include <mirports.sys.mk>
.if ${MKC_USAP:L} == "yes"
IGNORE=			'disallowed: Your IP system is broken'
.endif

post-extract:
	-rm -f ${WRKSRC}/bnetd/command.c.orig

post-install:
	chmod 644 ${LIBDIR}/conf/*
	${INSTALL_DATA_DIR} ${DOCDIR}
	cd ${DOCSRC} && ${INSTALL_DATA} ${DOCFILES} ${DOCDIR}/

.include <bsd.port.mk>
