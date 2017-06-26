# $MirOS: ports/net/sirc/Makefile,v 1.34 2017/06/26 00:14:32 tg Exp $

COMMENT=		programmable small perl irc client (UTF-8, TLS, IPv6 ready)
CATEGORIES=		net
DIST_NAME=		sirc
DIST_DATE=		20170626
DIST_SOURCE=		port
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.org>
HOMEPAGE=		http://www.iagora.com/~espel/sirc/sirc.html

# GNU GPLv2
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

RUN_DEPENDS=		:p5-Socket6->=0.08:net/p5-Socket6 \
			:p5-BSD-arc4random-*:security/p5-BSD-arc4random \
			:ssfe-*:comms/ssfe
NO_REGRESS=		Yes

SCRIPTS=		dsircp sirc
MANS=			sirc.1
DATADIR=		${PREFIX}/share/sirc
DATA=			PROGRAMMING README README.socks n0thing.pl \
			sirc.help socks.pl

do-build:
.for _i in ${SCRIPTS}
	@cd ${WRKSRC}; f=$$(realpath ${_i}); rm -f ${_i} && cp $$f ${_i}
	print ',g#@PREFIX@#s##${PREFIX}#g\n,g#@SHELL@#s##${SHELL}#g\n,g#@DIST_DATE@#s##${DIST_DATE}#g\nwq' | \
	    ed -s ${WRKSRC}/${_i}
.endfor

do-install:
	${INSTALL_DATA_DIR} ${DATADIR}
	cd ${WRKSRC} && ${INSTALL_SCRIPT} ${SCRIPTS} ${PREFIX}/bin/
	cd ${WRKSRC} && ${INSTALL_MAN} ${MANS} ${PREFIX}/man/man1/
	cd ${WRKSRC} && ${INSTALL_DATA} ${DATA} ${DATADIR}/

.include <bsd.port.mk>
