# $MirOS: ports/misc/magicpoint/Makefile,v 1.9 2008/03/09 19:16:03 tg Exp $
# $OpenBSD: Makefile,v 1.32 2004/04/09 09:52:09 espie Exp $

ONLY_FOR_PLATFORM=	MirBSD:*:* OpenBSD:*:*

COMMENT=		X11-based presentation tool
DISTNAME=		magicpoint-1.10a
DASH_VER=		2
CATEGORIES=		misc productivity
MASTER_SITES=		ftp://sh.wide.ad.jp/WIDE/free-ware/mgp/
HOMEPAGE=		http://member.wide.ad.jp/wg/mgp/

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

FLAVOURS=		no_gif freetype2
FLAVOUR?=

MODULES+=		graphics/png
LIB_DEPENDS+=		mng::graphics/libmng
RUN_DEPENDS+=		pnmscale::graphics/netpbm

USE_X11=		Yes
CONFIGURE_STYLE=	autoconf gnu imake no-autoheader
CONFIGURE_ARGS+=	--disable-vflib
CONFIGURE_ENV+=		mplocalbase=${LOCALBASE:Q}
EXTRA_MAKE_FLAGS+=	CCOPTIONS=

.if !${FLAVOUR:L:Mfreetype2}
CONFIGURE_ARGS+=	--enable-freetype \
			--enable-freetype-charset16 \
			--disable-xft2
MODULES+=		devel/gettext
MODULES+=		print/freetype
.else
CONFIGURE_ARGS+=	--disable-freetype \
			--enable-xft2
MODULES+=		converters/libiconv
.endif

.if ${FLAVOUR:L:Mno_gif}
CONFIGURE_ARGS+=	--disable-gif
.else
USE_CXX=		Yes
CONFIGURE_ARGS+=	--enable-gif
LIB_DEPENDS+=		ungif.5::graphics/libungif
.endif

NO_REGRESS=		Yes

DOCS=			COPYRIGHT COPYRIGHT.jp FAQ README README.fonts \
			README.fonts.jp README.lang README.xft RELNOTES \
			SYNTAX TODO.jp USAGE USAGE.jp
SAMPLES=		README README.jp cloud.jpg dad.eps dad.jpg \
			default.mgp embed-jp.mgp embed.mgp gradation-jp.mgp \
			gradation.mgp mgp-old1.jpg mgp-old2.jpg mgp-old3.jpg \
			mgp.mng mgp1.jpg mgp2.jpg mgp3.jpg mgp3.xbm \
			mgprc-sample multilingual.mgp sample-fr.mgp \
			sample-jp.mgp sample.mgp sendmail6-jp.mgp \
			sendmail6.mgp tutorial-jp.mgp tutorial.mgp v6-jp.mgp \
			v6.mgp v6header.eps v6header.jpg
EMACS=			../mgp-mode.el README mgp.el mgp.sty sample.tex
SCRIPTS=		eqn2eps.sh mgp2html.pl mgp2latex.pl tex2eps.sh

post-extract:
	rm -rf ${WRKDIST}/missing	# crap directory

post-configure:
	cd ${WRKCONF}/contrib/xmindpath && \
	    ${SETENV} ${MODSIMPLE_configure_env} ${SH} ./configure \
	    ${CONFIGURE_ARGS} --prefix='$${DESTDIR}'${PREFIX:Q}

post-build:
	cd ${WRKBUILD}/contrib/xmindpath && \
	    ${SETENV} ${MAKE_ENV} ${MAKE_PROGRAM} ${MAKE_FLAGS}

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/mgp/{emacs,sample}
.for _i in ${DOCS}
	${INSTALL_DATA} ${WRKSRC}/${_i} ${PREFIX}/share/doc/mgp/
.endfor
.for _i in ${SAMPLES}
	${INSTALL_DATA} ${WRKSRC}/sample/${_i} ${PREFIX}/share/doc/mgp/sample/
.endfor
.for _i in ${EMACS}
	${INSTALL_DATA} ${WRKSRC}/contrib/mgp-el/${_i} \
	    ${PREFIX}/share/doc/mgp/emacs/
.endfor
.for _i in ${SCRIPTS}
	${INSTALL_SCRIPT} ${WRKSRC}/contrib/${_i} ${PREFIX}/bin/${_i:R}
.endfor
	cd ${WRKBUILD}/contrib/xmindpath && \
	    ${INSTALL_PROGRAM} xmindpath ${PREFIX}/bin/ && \
	    ${INSTALL_MAN} xmindpath.1 ${PREFIX}/man/man1/

.include <bsd.port.mk>
