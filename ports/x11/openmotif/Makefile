# $MirOS: ports/x11/openmotif/Makefile,v 1.7 2008/10/04 19:03:48 tg Exp $
# $OpenBSD: Makefile,v 1.20 2004/02/22 16:47:58 naddy Exp $

# unbreak dependencies in ports/infrastructure/mk/bsd.port.mk once fixed!
BROKEN=			installs into /usr/local/X11

CATEGORIES=		x11
COMMENT=			Motif toolkit
COMMENT-debuglibs=			Motif toolkit debug libraries
COMMENT-demos=			Motif toolkit demos
VERSION=		2.1.30
DISTNAME=		motif
PATCHLEVEL=		5
PKGNAME=		openmotif-${VERSION}.${PATCHLEVEL}-0
PKGNAME-demos=		openmotif-demos-${VERSION}.${PATCHLEVEL}-0
PKGNAME-debuglibs=	openmotif-debuglibs-${VERSION}.${PATCHLEVEL}-0
HOMEPAGE=		http://www.opengroup.org/openmotif/

MASTER_SITES=	ftp://ftp.opengroup.org/pub/openmotif/R${VERSION}/tars/ \
		ftp://openmotif.opengroup.org/pub/openmotif/R${VERSION}/tars/ \
		ftp://ftp.kddlabs.co.jp/X11/openmotif/R${VERSION}/tars/
MASTER_SITES0=	ftp://ftp.opengroup.org/pub/openmotif/R${VERSION}/fixes/ \
		ftp://openmotif.opengroup.org/pub/openmotif/R${VERSION}/fixes/ \
		ftp://ftp.kddlabs.co.jp/X11/openmotif/R${VERSION}/fixes/
MASTER_SITES1=	http://www.opengroup.org/openmotif/license/
DISTFILES=	openmotif${VERSION}.tar.gz index.html:1
DIST_SUBDIR=	openmotif
EXTRACT_ONLY=	openmotif${VERSION}.tar.gz

PATCHFILES=		patch1:0 patch2:0 patch3:0 patch4:0 patch5:0
PATCH_DIST_STRIP=	-p1

# license only available on webpage
# http://www.opengroup.org/openmotif/license
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_FTP=	Yes

MULTI_PACKAGES=		-demos -debuglibs
SUBPACKAGE?=

USE_X11=		Yes

ALL_TARGET=		World
INSTALL_TARGET=		install install.man
EXTRA_XAKE_FLAGS+=	CC=${_PASS_CC:T:Q} COPTS="${COPTS}"

# This dialog has been copied from the lesstif port.
.if defined(HAVE_MOTIF) && ${HAVE_MOTIF:L} == "yes"
IS_INTERACTIVE=		Yes

pre-extract:
	@echo "***********************************************************"
	@echo "*                      W a r n i n g                      *"
	@echo "* This port will overwrite your Motif installation.       *"
	@echo "***********************************************************"
	@echo -n "Is this ok? (y/n) ==> "
	@(read ans; \
	  case x"$$ans" in \
	    xy*|xY*) \
		return 0; \
		;; \
	    *) \
		echo "Okay, I won't install it then...."; \
		echo "(Don't worry about the following \"*** Error code 1's)"; \
		return 1; \
		;; \
	esac)
.endif

post-patch:
# fix sections
	@cd ${WRKSRC}/doc/man/man1 && perl -pi -e "s|user cmd|1|" *.1
	@cd ${WRKSRC}/doc/man/man3 && perl -pi -e "s|library call|3|" *.3
# mwmrc is not a kernel interface!!
	@cd ${WRKSRC}/doc/man/man4 && perl -pi -e "s|special file|5|" *.4
	@cd ${WRKSRC}/doc/man/man5 && perl -pi -e "s|file formats|5|" *.5
# Import from our current X installation.
	@cp -f $$(ls ${X11BASE}/lib/X11/config/* \
	    | egrep -v '(Motif|bsdLib.tmpl|cde|\/site.def|host.def)') \
	    ${WRKDIR}/motif/config/cf/
	@mkdir -p ${WRKSRC}/imports/x11
	@cd ${WRKSRC}/imports/x11 && for i in bin include lib; do \
	    [ ! -f $$i ] || rm $$i; \
	    ln -s ${X11BASE}/$$i $$i; \
	done
# respect PREFIX
	@cd ${WRKSRC}/config/cf && \
	    perl -pi -e "s|%%PREFIX%%|${PREFIX}|g" host.def Motif.tmpl

DOCS=	BUGREPORT CLOSEDBUGS COPYRIGHT.MOTIF OPENBUGS README RELEASE RELNOTES
DOCDIR=	${PREFIX}/share/doc/openmotif

post-install:
	@${INSTALL_DATA_DIR} ${DOCDIR}
	@${INSTALL_DATA} ${FULLDISTDIR}/index.html ${DOCDIR}/LICENSE.html
	@for i in ${DOCS}; do ${INSTALL_DATA} ${WRKSRC}/$$i ${DOCDIR}; done
	@${INSTALL_DATA} ${FILESDIR}/README.OpenBSD ${DOCDIR}

.if ${SUBPACKAGE} == "-demos" || ${SUBPACKAGE} == "-debuglibs"
LIB_DEPENDS+=	Xm.2.1::x11/openmotif
.endif

# XXX  Large, complicated, only partially automated test suite available
NO_REGRESS=	Yes

.include <bsd.port.mk>
