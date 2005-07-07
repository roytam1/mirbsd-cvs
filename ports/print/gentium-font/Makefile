# $MirOS$

COMMENT=	"freeware font with many latin and greek glyphs"
CATEGORIES=	print graphics textproc productivity x11
V=		101
DISTNAME=	Gentium_${V}_W
PKGNAME=	gentium-${V}-0
HOMEPAGE=	http://scripts.sil.org/cms/scripts/page.php?site_id=nrsi&cat_id=FontDownloadsGentium
RESPONSIBLE=	Thorsten Glaser <tg@${_DOMAIN_DU_JOUR}>

# They call it "copyrighted freeware"
PERMIT_DISTFILES_FTP=	Yes
PERMIT_DISTFILES_CDROM=	"must not bundle"
PERMIT_PACKAGE_FTP=	Yes
PERMIT_PACKAGE_CDROM=	"must distribute unmodified package"

EXTRACT_SUFX=	.zip
FETCH_NAME=	${ALLFILES:S@^@${FULLDISTDIR}/@}
WRKDIST=	${WRKDIR}/Gentium${V}

FONTDIR=	${PREFIX}/lib/X11/fonts/gentium
DOCS=		Gentium${V}ReadMe.txt.fmt ReadMe.txt
FONTS=		GenAI${V}.TTF GenAI${V}.ttf GenAR${V}.TTF GenAR${V}.ttf \
		GenI${V}.TTF GenI${V}.ttf GenR${V}.TTF GenR${V}.ttf

SUBST_VARS+=	V
NO_REGRESS=	Yes

do-fetch:
	@( mkdir -p ${FETCH_NAME:H}; cd ${FETCH_NAME:H}; \
	   f=${FETCH_NAME:S@^${FULLDISTDIR}/@@}; if test ! -e $$f; then \
		${ECHO_MSG} ">> $$f doesn't seem to exist on this system."; \
		${_CDROM_OVERRIDE}; site=http://scripts.sil.org/; \
		${ECHO_MSG} ">> Attempting to fetch $$f from $${site}."; \
		if /usr/bin/ftp -Vmo $$f \
		    'http://scripts.sil.org/cms/scripts/render_download.php?site_id=nrsi&format=file&media_id=${DISTNAME}&_sc=1'; then \
			exit 0; \
		fi; exit 1; \
	fi; )

do-build:
.for _o _n in ${DOCS}
	(i=0; cd ${WRKSRC} && print '/^----/+1,$$p\nq' \
	    | ed -s ${_o:S/.fmt$//} | while read x; do print -r -- "$$x"; \
		if [[ $$i = 0 ]]; then \
			[[ $$x = VERSION\ DETAILS* ]] && i=1; \
		else	[[ $$x = Version\ * ]] && print; \
		fi; done | fmt -psw66 >${_o} \
	    && ed -s ${_o} <${FILESDIR}/${_n}.ed)
.endfor

do-install:
	${INSTALL_DATA_DIR} ${FONTDIR}
.for _o _n in ${DOCS} ${FONTS}
	${INSTALL_DATA} ${WRKSRC}/${_o} ${FONTDIR}/${_n}
.endfor
	cd ${FONTDIR} && ${X11BASE}/bin/mkfontscale -x txt .
	cp ${FONTDIR}/fonts.scale ${FONTDIR}/fonts.dir
	fc-cache ${FONTDIR}

.include <bsd.port.mk>
