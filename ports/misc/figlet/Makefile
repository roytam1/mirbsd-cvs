# $MirOS: ports/misc/figlet/Makefile,v 1.9 2006/09/14 00:11:13 tg Exp $
# $OpenBSD: Makefile,v 1.14 2002/10/27 21:07:53 naddy Exp $

COMMENT=		Frank, Ian and Glen's letters: generates ASCII art
DISTNAME=		figlet222
PKGNAME=		figlet-2.2.2-2
CATEGORIES=		misc graphics
HOMEPAGE=		http://www.figlet.org/

# The Academic Free License v2.1
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES+=		ftp://ftp.figlet.org/pub/figlet/program/unix/
#MASTER_SITES0=		ftp://ftp.figlet.org/pub/figlet/fonts/
MASTER_SITES0=		${_MASTER_SITE_MIRBSD}

DISTFILES=		${DISTNAME}${EXTRACT_SUFX} \
			figlet-fonts-20021023/contributed.tar.gz:0 \
			figlet-fonts-20021023/international.tar.gz:0 \
			figlet-fonts-20021023/ms-dos.tar.gz:0
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
	# resolve duplicates
	mv ${WRKDIR}/contributed/{banner,banner-sm}.flf
	set -e; for base in computer gothic roman; do \
		mv ${WRKDIR}/contributed/C64-fonts/$$base{,-C64}.flf; \
	done
	# install additional font packs
	mv ${WRKDIR}/contributed/*/*.fl? ${WRKDIR}/*/*.fl? ${WRKSRC}/fonts/

post-install:
	${INSTALL_SCRIPT} ${WRKDIR}/international/febrew \
	    ${PREFIX}/bin/figlet-febrew
	${INSTALL_SCRIPT} ${WRKSRC}/figlist ${PREFIX}/bin/
	${INSTALL_SCRIPT} ${WRKSRC}/showfigfonts ${PREFIX}/bin/
	${INSTALL_DATA_DIR} ${PREFIX}/share/figlet
	${INSTALL_DATA} ${WRKSRC}/fonts/*.{flf,flc} ${PREFIX}/share/figlet/
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/figlet
	${INSTALL_DATA} ${WRKSRC}/figfont.txt ${PREFIX}/share/doc/figlet/

.include <bsd.port.mk>
