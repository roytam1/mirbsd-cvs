# $MirOS: ports/print/gentium-font/Makefile,v 1.4 2005/12/16 10:44:31 tg Exp $

COMMENT=			freeware font with many latin/greek/cyrillic glyphs
CATEGORIES=		print graphics textproc productivity x11
V=			102
DISTNAME=		Gentium_${V}_W
PKGNAME=		gentium-${V}-0
HOMEPAGE=		http://scripts.sil.org/cms/scripts/page.php?site_id=nrsi&cat_id=FontDownloadsGentium
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>

# OFL
PERMIT_DISTFILES_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_PACKAGE_FTP=	"modified package, would have to change font name"
PERMIT_PACKAGE_CDROM=	"modified package, would have to change font name"

# Backup only
MASTER_SITES=		${_MASTER_SITE_MIRBSD}

EXTRACT_SUFX=		.zip
FETCH_NAME=		${ALLFILES:S@^@${FULLDISTDIR}/@}
WRKDIST=		${WRKDIR}/Gentium${V}

FONTDIR=		${PREFIX}/lib/X11/fonts/gentium
DOCS=			FONTLOG.txt FONTLOG.txt \
			GENTIUM-FAQ.txt FAQ.txt \
			OFL.txt OFL.txt
FONTS=			GenAI${V}.TTF GenAI${V}.ttf \
			GenAR${V}.TTF GenAR${V}.ttf \
			GenI${V}.TTF GenI${V}.ttf \
			GenR${V}.TTF GenR${V}.ttf

SUBST_VARS+=		V
USE_X11=		Yes
NO_BUILD=		Yes
NO_REGRESS=		Yes

do-fetch:
	@( mkdir -p ${FETCH_NAME:H}; cd ${FETCH_NAME:H}; \
	   f=${FETCH_NAME:S@^${FULLDISTDIR}/@@}; if test ! -e $$f; then \
		${ECHO_MSG} ">> $$f doesn't seem to exist on this system."; \
		${_CDROM_OVERRIDE}; site=http://scripts.sil.org/; \
		${ECHO_MSG} ">> Attempting to fetch $$f from $${site}."; \
		if /usr/bin/ftp -Vmo $$f \
		    'xhttp://scripts.sil.org/cms/scripts/render_download.php?site_id=nrsi&format=file&media_id=${DISTNAME}&_sc=1'; then \
			exit 0; \
		fi; exit 1; \
	fi; ) || (cd ${.CURDIR} && exec ${MAKE} ${ALLFILES:S@^@${FULLDISTDIR}/@})

do-install:
	${INSTALL_DATA_DIR} ${FONTDIR}
.for _o _n in ${DOCS} ${FONTS}
	${INSTALL_DATA} ${WRKSRC}/${_o} ${FONTDIR}/${_n}
.endfor
	cd ${FONTDIR} && ${X11BASE}/bin/mkfontscale -x txt .
	cp ${FONTDIR}/fonts.scale ${FONTDIR}/fonts.dir
	fc-cache ${FONTDIR}

.include <bsd.port.mk>
