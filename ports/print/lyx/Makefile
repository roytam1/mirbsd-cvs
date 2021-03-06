# $MirOS: ports/print/lyx/Makefile,v 1.4 2008/03/09 17:23:27 tg Exp $
# $OpenBSD: Makefile,v 1.32 2004/04/25 15:34:08 sturm Exp $

COMMENT=	graphical frontend for LaTeX (nearly WYSIWYG)

DISTNAME=	lyx-1.3.4
CATEGORIES=	print

HOMEPAGE=	http://www.lyx.org/

MASTER_SITES=	ftp://ftp.lyx.org/pub/lyx/stable/ \
		ftp://ftp.sdsc.edu/pub/other/lyx/stable/ \
		ftp://ftp.lip6.fr/pub/lyx/stable/ \
		ftp://ftp.chg.ru/pub/TeX/lyx/stable/


# In XForms flavour: quasi-GPL (linked to closed source library)
# In Qt flavour: GPL (this should be preferred for CD distribution)
# see http://www.lyx.org/about/license.php3 for additional info
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES=	devel/gettext

BUILD_DEPENDS+=	:teTeX_base-*:print/teTeX/base
RUN_DEPENDS+=	:teTeX_base-*:print/teTeX/base \
		:ispell-*:textproc/ispell
USE_GMAKE=	Yes

FLAVOURS=	qt xforms
FLAVOUR?=	qt

.if ${FLAVOUR:L} == "qt"
USE_CXX=	Yes
MODULES+=	x11/qt3
MODQT_MT=	Yes
CONFIGURE_ARGS=	--with-frontend=qt ${MODQT_CONFIGURE_ARGS}
CONFIGURE_ENV=	LIBS=-pthread
# A hack until LyX developers apply the patch to qt.m4 to respect $MOC and $UIC
CONFIGURE_ENV+=	ac_moc1=${MODQT_MOC} ac_uic=${MODQT_UIC}
.elif ${FLAVOUR:L} == "xforms"
LIB_DEPENDS+=	forms.1::x11/xforms
.else
ERRORS+= "Fatal: Conflicting flavour: ${FLAVOUR}"
.endif

CONFIGURE_STYLE=	gnu
MODGNU_RECURSE_DIRS=	${WRKSRC}/config

CONFIGURE_ARGS+=--with-extra-lib=${LOCALBASE}/lib \
		--with-extra-inc="${LOCALBASE}/include \
		${LOCALBASE}/include/X11" \
		--without-latex-config

# Necessary because of compilation error.  See:
# http://www.boost.org/libs/graph/doc/trouble_shooting.html
CXXFLAGS+=	-ftemplate-depth-30

NO_REGRESS=	Yes

INSTALL_TARGET=	install-strip

.include <bsd.port.mk>
