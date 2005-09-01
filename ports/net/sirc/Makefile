# $MirOS$

COMMENT=		"programmable small perl irc client (utf-8, IPv6 ready)"
CATEGORIES=		net
DIST_NAME=		sirc
DIST_DATE=		20050901
#PKGNAME=		${DIST_NAME}-1:${DIST_DATE}-0
DIST_SOURCE=		port
RESPONSIBLE=		Thorsten Glaser <tg@66h.42h.de>
HOMEPAGE=		http://www.iagora.com/~espel/sirc/sirc.html

# GNU GPLv2
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

RUN_DEPENDS=		:p5-Socket6->=0.08:net/p5-Socket6 \
			:ssfe-*:comms/ssfe

SCRIPTS=		dsircp sirc
MANS=			sirc.1
DATADIR=		${PREFIX}/share/sirc
DATA=			PROGRAMMING README README.socks n0thing.pl \
			sirc.help socks.pl

do-build:
.for _i in ${SCRIPTS}
	@cd ${WRKSRC}; f=$$(readlink -nf ${_i}); rm -f ${_i} && cp $$f ${_i}
	print '%g#@PREFIX@#s##${PREFIX}#g\nwq' | ed -s ${WRKSRC}/${_i}
.endfor

do-install:
	${INSTALL_DATA_DIR} ${DATADIR}
	cd ${WRKSRC} && ${INSTALL_SCRIPT} ${SCRIPTS} ${PREFIX}/bin/
	cd ${WRKSRC} && ${INSTALL_MAN} ${MANS} ${PREFIX}/man/man1/
	cd ${WRKSRC} && ${INSTALL_DATA} ${DATA} ${DATADIR}/

.include <bsd.port.mk>
