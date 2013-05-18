# $MirOS: ports/mailnews/bmf/Makefile,v 1.10 2008/03/09 17:23:04 tg Exp $
# $OpenBSD: Makefile,v 1.8 2004/02/02 23:11:28 pvalchev Exp $

COMMENT=		easy to use Bayesian spam filter
DISTNAME=		bmf-0.9.4
DASH_VER=		4
CATEGORIES=		mail
HOMEPAGE=		http://sourceforge.net/projects/bmf/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=bmf/}

CONFIGURE_STYLE=	simple

FLAVOURS=		mysql
FLAVOUR?=

.if ${FLAVOUR:L:Mmysql}
LIB_DEPENDS+=		:mysql-client-*:databases/mysql
CONFIGURE_ARGS=		--without-libdb --with-mysql="${LOCALBASE}"
CFLAGS+=		"-I${LOCALBASE}/include/mysql"
.else
CONFIGURE_ARGS=		--without-mysql --with-libdb
.endif

RUN_DEPENDS+=		:mailutil-uw->=2004.352-0:mailnews/pine,-mailutil

INSTALL_TARGET=		MANDIR=${PREFIX}/man \
			BINDIR=${PREFIX}/bin \
			install


DOCS=			README ${FILESDIR}/OpenBSD-bmf-mini-howto.html

NO_REGRESS=		Yes

post-build:
.for _i in mbmf.sh mbmf-sm.sh
	sed -e 's#@SHELL@#${SHELL}#g' -e 's#@PREFIX@#${PREFIX}#g' \
	    <${FILESDIR}/${_i} >${WRKBUILD}/${_i}
.endfor

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/bmf
	${INSTALL_DATA} ${WRKSRC}/${DOCS} ${PREFIX}/share/doc/bmf
	${INSTALL_SCRIPT} ${WRKBUILD}/mbmf.sh ${PREFIX}/bin/mbmf
	${INSTALL_SCRIPT} ${WRKBUILD}/mbmf-sm.sh ${PREFIX}/libexec/mbmf-sm

.include <bsd.port.mk>
