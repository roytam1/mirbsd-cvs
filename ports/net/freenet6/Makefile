# $MirOS: ports/net/freenet6/Makefile,v 1.6 2008/11/08 23:03:59 tg Exp $

COMMENT=			Freenet6 IPv6 Tunnel Broker Client
NO_REGRESS=	Yes

CATEGORIES=	net
DISTNAME=	freenet6-2.1

HOMEPAGE=	http://www.freenet6.net/
RESPONSIBLE=	Stephen Paskaluk <sap@mirbsd.org>

# GNU General Public License, Version 2
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

EXTRACT_SUFX=	.tgz
MASTER_SITES=	${_MASTER_SITE_MIRBSD}

MAKE_FLAGS+=	target=mirbsd CC=${_PASS_CC:T:Q}
WRKDIST=	${WRKDIR}/tspc2
TRUEPREFIX?=	${PREFIX}
TSPDIR=		${TRUEPREFIX}/libexec/tspc

BINFILES=	sbin/tspc libexec/tspc/template/checktunnel.sh libexec/tspc/template/mirbsd.sh
DATAFILES=	share/examples/tspc/tspc.conf.sample

post-patch:
	cp ${FILESDIR}/mirbsd.sh ${WRKSRC}/template/
	cp -r ${FILESDIR}/mirbsd/ ${WRKSRC}/platform/
	cp ${FILESDIR}/mk-mirbsd.mk ${WRKSRC}/Mk/

do-install:
	cd ${WRKSRC} && ${MAKE} install target=mirbsd installdir=${PREFIX}
	$(STRIP) ${PREFIX}/bin/tspc
.for i in $(BINFILES)
	chmod ${BINMODE} ${PREFIX}/$i; chown ${BINOWN}:${BINGRP} ${PREFIX}/$i
.endfor
.for i in $(DATAFILES)
	mv ${PREFIX}/$i ${PREFIX}/${i}.fake
	sed 's#^tsp_dir=.*$$#tsp_dir=${TSPDIR}#' \
		<${PREFIX}/$i.fake \
		>${PREFIX}/$i; 
	chmod 600 ${PREFIX}/$i; chown ${BINOWN}:${BINGRP} ${PREFIX}/$i
.endfor

.include <bsd.port.mk>
