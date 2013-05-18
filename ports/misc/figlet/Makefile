# $MirOS: ports/misc/figlet/Makefile,v 1.8 2006/06/24 12:51:43 tg Exp $
# $OpenBSD: Makefile,v 1.14 2002/10/27 21:07:53 naddy Exp $

COMMENT=			generates ASCII banner art
DISTNAME=		figlet222
PKGNAME=		figlet-2.2.2-1
CATEGORIES=		misc graphics
HOMEPAGE=		http://www.figlet.org/

# Artistic
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

#MASTER_SITES+=		ftp://ftp.figlet.org/pub/figlet/program/unix/
MASTER_SITES+=		http://public.enst.fr/pkgsrc/distfiles/

DISTFILES=		${DISTNAME}${EXTRACT_SUFX} \
			figlet-fonts-20021023/contributed.tar.gz \
			figlet-fonts-20021023/international.tar.gz \
			figlet-fonts-20021023/ms-dos.tar.gz
EXTRA_MAKE_FLAGS+=	DEFAULTFONTDIR=${PREFIX}/share/figlet
NO_REGRESS=		Yes

post-patch:
	@perl -pi -e 's|%%OPENBSDFIGLET%%|${LOCALBASE}/share/figlet|g' \
	    ${WRKBUILD}/figlist

do-configure:
	cd ${FILESDIR} && pax -rw * ${WRKSRC}/
	cd ${WRKSRC} && ${MAKE} obj

post-extract:
	chmod -R u+w ${WRKSRC}
	cd ${WRKDIR}/contributed && tar xzf Obanner.tgz
	cd ${WRKDIR}/international && tar xzf cjkfonts.tar.gz
	mv ${WRKDIR}/{,*/}*/*.fl? ${WRKSRC}/fonts/

post-install:
	${INSTALL_SCRIPT} ${WRKDIR}/international/febrew \
	    ${PREFIX}/bin/figlet-febrew
	${INSTALL_SCRIPT} ${WRKSRC}/figlist ${PREFIX}/bin/
	${INSTALL_SCRIPT} ${WRKSRC}/showfigfonts ${PREFIX}/bin/
	${INSTALL_DATA_DIR} ${PREFIX}/share/figlet
	${INSTALL_DATA} ${WRKSRC}/fonts/*.{flf,flc} ${PREFIX}/share/figlet/

.include <bsd.port.mk>
