# $MirOS: ports/x11/qt3/Makefile,v 1.16 2009/08/16 16:29:03 tg Exp $
# $OpenBSD: Makefile,v 1.58 2006/01/02 16:59:37 espie Exp $
# $FreeBSD: Makefile,v 1.33 1999/02/27 03:09:57 andreas Exp $

COMMENT=			C++ X11 GUI toolkit
COMMENT-examples=			examples and tutorial for qt3
COMMENT-html=			off-line html documentation for qt3
COMMENT-postgresql=			PostgresSQL plugin for qt3
COMMENT-mysql=			MySQL plugin for qt3

PKGNAME=		qt3-${VERSION}-${PL}
PKGNAME-mysql=		qt3-mysql-${VERSION}-${PL}
PKGNAME-postgresql=	qt3-postgresql-${VERSION}-${PL}
PKGNAME-examples=	qt3-examples-${VERSION}-${PL}
FULLPKGNAME=		qt3-mt-${VERSION}-${PL}${PKGDEBUG}
FULLPKGNAME-html=	qt3-html-${VERSION}-${PL}

# XXX this is wrong, let libtool handle it instead
LIBqt-mt_VERSION=	3.35
LIBqui_VERSION=		1.0
QT_PLUGINS=		plugins-${LIBqt-mt_VERSION:R}

VERSION=		3.5
PL=			1
DISTNAME=		qt-x11-free-3.${VERSION}
CATEGORIES=		x11 kde
MASTER_SITES=		ftp://ftp.troll.no/qt/source/
MASTER_SITES0=		http://freedesktop.org/~daisuke/
PATCHFILES=		qt-x11-immodule-unified-qt3.3.5-20051018.diff.bz2:0
PATCH_DIST_STRIP=	-p1

pre-configure:
	cd ${WRKDIST} && ${MKSH} ./make-symlinks.sh

HOMEPAGE=		http://www.trolltech.com/qt/

FLAVOURS=		debug
PSEUDO_FLAVOURS=		mt no_mysql no_postgresql
FLAVOUR?=		no_mysql no_postgresql

# GPL/QPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_X11=		Yes
USE_CXX=		Yes
MAKE_ENV+=		QTDIR=${WRKDIST:Q} EXTRA_SAMPLES=${EXTRA_SAMPLES:Q} \
			SYS_CXX=${_PASS_CXX:T:Q} SYS_CXXFLAGS=${CXXFLAGS:Q}

.include <mirports.sys.mk>
.if defined(_OUR_LDLIBPATH) && !empty(_OUR_LDLIBPATH)
_OUR_LDLIBPATH:=${WRKDIST}/lib:${_OUR_LDLIBPATH}
.else
_OUR_LDLIBPATH=${WRKDIST}/lib
.endif

# For qsettings to write its setup
PORTHOME=		${WRKDIST}

EXTRA_XAKE_FLAGS+=	DESIGNER_SUBDIR=dummy

CONFIGURE_STYLE=	simple
CONFIGURE_ARGS+=	-qt-gif -system-libmng -system-libpng \
			-system-libjpeg -system-zlib \
			-qt-imgfmt-mng -qt-imgfmt-png -qt-imgfmt-jpeg \
			-sm -no-g++-exceptions \
			-v -stl -xrender -no-xft -fast \
			-no-sql-odbc -no-sql-ibase -qt-sql-sqlite \
			-tablet \
			-xinerama \
			-no-cups \
			-inputmethod \
			-I${LOCALBASE}/include/libpng \
			-I${X11BASE}/include/freetype2 \
			-I${LOCALBASE}/include \
			-L${WRKSRC}/lib \
			-L${LOCALBASE}/lib

MULTI_PACKAGES+=	-html



.if ${FLAVOUR:L:Mdebug}
CONFIGURE_ARGS+=	-debug
PKGDEBUG=		-debug
.else
PKGDEBUG=
.endif

CONFIGURE_ARGS+=	-thread

.if !${FLAVOUR:L:Mdebug}
MULTI_PACKAGES+=	-examples
.else
ALL_TARGET=		sub-src sub-tools
.endif

# This is needed to find plugins
CONFIGURE_ARGS+=	-prefix ${QT_LIBDIR}
CONFIGURE_ARGS+=	-plugindir ${QT_PLUGINSDIR}

CONFIGURE_ENV+=		QTDIR=${WRKSRC:Q}

SUBPACKAGE?=

LIB_DEPENDS=
BUILD_DEPENDS+=		::graphics/jpeg
#BUILD_DEPENDS+=	::print/cups

e=
.if ${FLAVOUR:L:Mno_mysql}
e:=$e,no_mysql
.endif
.if ${FLAVOUR:L:Mno_postgresql}
e:=$e,no_postgresql
.endif

.if !empty(FLAVOUR:L:Mno_mysql)
CONFIGURE_ARGS+=	-no-sql-mysql
.else
BROKEN=			depends on mysql, which is broken
MULTI_PACKAGES+=	-mysql
.  if !defined(PACKAGING) || ${SUBPACKAGE} == "-mysql"
LIB_DEPENDS+=		mysqlclient::databases/mysql
.  endif
CONFIGURE_ARGS+=	-I${LOCALBASE}/include/mysql -L${LOCALBASE}/lib/mysql \
			-plugin-sql-mysql
.endif

.if !empty(FLAVOUR:L:Mno_postgresql)
CONFIGURE_ARGS+=	-no-sql-psql
.else
MULTI_PACKAGES+=	-postgresql
.  if !defined(PACKAGING) || ${SUBPACKAGE} == "-postgresql"
LIB_DEPENDS+=		pq:postgresql-client-*:databases/postgresql
BUILD_DEPENDS+=		::databases/postgresql,-server
.  endif
CONFIGURE_ARGS+=	-I${LOCALBASE}/include/postgresql \
			-I${LOCALBASE}/include/postgresql/server \
			-L${LOCALBASE}/lib \
			-I${LOCALBASE}/include -plugin-sql-psql
.endif

.if !defined(PACKAGING) || ${SUBPACKAGE} != "-html"
LIB_DEPENDS+=		mng::graphics/libmng
MODULES+=		graphics/png
.endif

.if defined(PACKAGING) && ${SUBPACKAGE} != "-html" && ${SUBPACKAGE} != ""
LIB_DEPENDS+=		qt-mt.3::x11/qt3$e
.endif

.if defined(PACKAGING) && ${SUBPACKAGE} == "-html"
PKG_ARCH=		*
.endif

QT_INCDIR=		${PREFIX}/include/X11/qt3
TRUEDIR=		${TRUEPREFIX}/lib/qt3
QT_LIBDIR=		${PREFIX}/lib/qt3
QT_MANDIR=		${QT_LIBDIR}/man
QT_EXAMPLES=		${QT_LIBDIR}/examples
QT_TUTORIAL=		${QT_LIBDIR}/tutorial
QT_DOC=			${PREFIX}/share/doc/qt3
QT_PLUGINSDIR=		${QT_LIBDIR}/${QT_PLUGINS}
QT_BINDIR=		${QT_LIBDIR}/bin

# for manpages in MESSAGE
SUBST_VARS=		QT_LIBDIR QT_DOC QT_PLUGINS

DOCS=			FAQ LICENSE.GPL README README-QT.TXT \
			changes-3* \
			README.immodule changes.immodule

VMEM_WARNING=		Yes
NO_REGRESS=		Yes

PROGRAMS3=		designer findtr moc qt20fix qtrename140 uic
PROGRAMS=		assistant linguist lrelease lupdate qm2ts \
			qmake qtconfig

post-patch:
	print '%g/@@CC@@/s//'${_PASS_CC:T:Q}'/\n%g/@@CXX@@/s//'${_PASS_CXX:T:Q}'/\nwq' | \
	    ed -s ${WRKSRC}/mkspecs/openbsd-g++/qmake.conf

.if !${FLAVOUR:L:Mdebug}
post-configure:
	@cd ${WRKSRC} && cp -R examples examples-src
	@find ${WRKSRC}/examples-src -name '*.orig' |xargs rm -f
	@find ${WRKSRC}/examples-src -name '.moc' |xargs rm -rf
	@find ${WRKSRC}/examples-src -name '.obj' |xargs rm -rf
	@cd ${WRKSRC} && cp -R tutorial tutorial-src
	@find ${WRKSRC}/tutorial-src -name '*.orig' |xargs rm -f
	@find ${WRKSRC}/tutorial-src -name '.moc' |xargs rm -rf
	@find ${WRKSRC}/tutorial-src -name '.obj' |xargs rm -rf

pre-install:
	${INSTALL_DATA_DIR} ${QT_EXAMPLES}
	${INSTALL_DATA_DIR} ${QT_TUTORIAL}
	# examples
	cp -R ${WRKSRC}/examples-src/* ${QT_EXAMPLES}
	@cd ${WRKSRC}/examples; for i in *; do \
	if [ -x $$i/$$i ]; then \
	    ${INSTALL_PROGRAM} $$i/$$i ${QT_EXAMPLES}/$$i; \
	fi; done
	@if [ -x ${WRKSRC}/examples/overlay_x11/overlayrubber ]; then \
	    ${INSTALL_PROGRAM} ${WRKSRC}/examples/overlay_x11/overlayrubber \
	    	${QT_EXAMPLES}/overlay_x11/overlayrubber; \
	fi
	cp -R ${WRKSRC}/tutorial-src/* ${QT_TUTORIAL}
	@cd ${WRKSRC}/tutorial; for i in *; do \
	if [ -x $$i/$$i ]; then \
	    ${INSTALL_PROGRAM} $$i/$$i ${QT_TUTORIAL}/$$i; \
	fi; done
.else

post-patch:
	@rm -rf ${WRKSRC}/examples
	@rm -rf ${WRKSRC}/tutorial

.endif

do-install:
	${INSTALL_DATA_DIR} ${QT_INCDIR}
	${INSTALL_MAN_DIR} ${QT_MANDIR}/man1
	${INSTALL_MAN_DIR} ${QT_MANDIR}/man3
	${INSTALL_DATA_DIR} ${QT_DOC}/html
	# includes
	${INSTALL_DATA_DIR} ${QT_INCDIR}/private
	${INSTALL_DATA} ${WRKSRC}/include/*.h ${QT_INCDIR}
	${INSTALL_DATA} ${WRKSRC}/include/private/*.h ${QT_INCDIR}/private
	${INSTALL_DATA_DIR} ${QT_BINDIR} ${QT_PLUGINSDIR}
	# documentation
	${INSTALL_MAN} ${WRKSRC}/doc/man/man1/lrelease.1 ${QT_MANDIR}/man1
	${INSTALL_MAN} ${WRKSRC}/doc/man/man1/lupdate.1 ${QT_MANDIR}/man1
	${INSTALL_MAN} ${WRKSRC}/doc/man/man1/moc.1 ${QT_MANDIR}/man1/moc3.1
	${INSTALL_MAN} ${WRKSRC}/doc/man/man1/uic.1 ${QT_MANDIR}/man1/uic3.1
	@for i in ${WRKSRC}/doc/man/man3/*; do \
	  j=$${i%qt}; \
	  sed -e 's,\.3qt,\.3,g' <$$i >$$j && \
	  	${INSTALL_MAN} $$j ${QT_MANDIR}/man3; \
	done
	cd ${WRKSRC}; ${INSTALL_DATA} ${DOCS} ${QT_DOC}
	cp -R ${WRKSRC}/doc/html/* ${QT_DOC}/html
	cp -R ${WRKSRC}/mkspecs ${QT_LIBDIR}/mkspecs
	# libraries
	@if [ -f ${WRKBUILD}/lib/libqt-mt.a ]; then \
	 ${INSTALL_DATA} ${WRKBUILD}/lib/libqt-mt.a ${PREFIX}/lib/qt3; \
	fi
	@if [ -f  ${WRKBUILD}/lib/libqt-mt.so.$(LIBqt-mt_VERSION) ]; then \
	 ${INSTALL_DATA} ${WRKBUILD}/lib/libqt-mt.so.$(LIBqt-mt_VERSION) ${PREFIX}/lib/qt3; \
	 ln -sf qt3/libqt-mt.so.$(LIBqt-mt_VERSION) ${PREFIX}/lib; \
	fi
	@if [ -f ${WRKBUILD}/lib/libqui.a ]; then \
	 ${INSTALL_DATA} ${WRKBUILD}/lib/libqui.a ${PREFIX}/lib/qt3; \
	fi
	@if [ -f  ${WRKBUILD}/lib/libqui.so.$(LIBqui_VERSION) ]; then \
	 ${INSTALL_DATA} ${WRKBUILD}/lib/libqui.so.$(LIBqui_VERSION) ${PREFIX}/lib/qt3; \
	 ln -sf qt3/libqui.so.$(LIBqui_VERSION) ${PREFIX}/lib; \
	fi
	@${INSTALL_DATA} ${WRKBUILD}/lib/libeditor.a ${PREFIX}/lib/qt3
	@${INSTALL_DATA} ${WRKBUILD}/lib/libdesignercore.a ${PREFIX}/lib/qt3
	@${INSTALL_DATA} ${WRKBUILD}/lib/libqassistantclient.a ${PREFIX}/lib/qt3
.for p in ${PROGRAMS3}
	${INSTALL_PROGRAM} ${WRKBUILD}/bin/$p ${QT_BINDIR}/$p
	@ln -sf ${TRUEPREFIX}/lib/qt3/bin/$p ${PREFIX}/bin/$p3
.endfor
.for p in ${PROGRAMS}
	${INSTALL_PROGRAM} ${WRKBUILD}/bin/$p ${QT_BINDIR}/$p
	@ln -sf ${TRUEPREFIX}/lib/qt3/bin/$p ${PREFIX}/bin/$p
.endfor
	# plugins
	${INSTALL_DATA_DIR} ${QT_PLUGINSDIR}/designer \
		${QT_PLUGINSDIR}/sqldrivers ${QT_PLUGINSDIR}/styles \
		${QT_PLUGINSDIR}/inputmethods

.if empty(FLAVOUR:L:Mno_postgresql)
	${INSTALL_DATA} ${WRKBUILD}/plugins/sqldrivers/libqsqlpsql.so \
	    ${QT_PLUGINSDIR}/sqldrivers
.endif
.if empty(FLAVOUR:L:Mno_mysql)
	${INSTALL_DATA} ${WRKBUILD}/plugins/sqldrivers/libqsqlmysql.so \
	    ${QT_PLUGINSDIR}/sqldrivers
.endif
	${INSTALL_DATA} ${WRKBUILD}/plugins/designer/libwizards.so \
	    ${QT_PLUGINSDIR}/designer
	${INSTALL_DATA} ${WRKBUILD}/plugins/designer/libcppeditor.so \
	    ${QT_PLUGINSDIR}/designer
	${INSTALL_DATA} ${WRKBUILD}/plugins/designer/libdlgplugin.so \
	    ${QT_PLUGINSDIR}/designer
	${INSTALL_DATA} ${WRKBUILD}/plugins/designer/librcplugin.so \
	    ${QT_PLUGINSDIR}/designer
	${INSTALL_DATA} ${WRKBUILD}/plugins/inputmethods/libqimsw-multi.so \
	    ${QT_PLUGINSDIR}/inputmethods
	${INSTALL_DATA} ${WRKBUILD}/plugins/inputmethods/libqimsw-none.so \
	    ${QT_PLUGINSDIR}/inputmethods
	${INSTALL_DATA} ${WRKBUILD}/plugins/inputmethods/libqsimple.so \
	    ${QT_PLUGINSDIR}/inputmethods
	${INSTALL_DATA} ${WRKBUILD}/plugins/inputmethods/libqxim.so \
	    ${QT_PLUGINSDIR}/inputmethods
# compatibility transition
.for p in ${PROGRAMS}
	cd ${PREFIX}/bin && ln -sf $p $p-mt
.  endfor
.for p in ${PROGRAMS3}
	cd ${PREFIX}/bin && ln -sf $p3 $p3-mt
.endfor
	cd ${PREFIX}/lib && ln -sf libqui.so.$(LIBqui_VERSION) libqui-mt.so.$(LIBqui_VERSION)
	cd ${PREFIX}/lib/qt3 && ln -sf libqui.so.$(LIBqui_VERSION) libqui-mt.so.$(LIBqui_VERSION)
# links for qtdir
	cd ${PREFIX}/lib/qt3 && ln -sf . lib
	cd ${PREFIX}/lib/qt3 && ln -sf ../../include/X11/qt3 include
# fix for qmake
	sed -e  s,${WRKDIST},${PREFIX}/lib/qt3, <${WRKBUILD}/.qmake.cache >${WRKBUILD}/mogrified.cache
	${INSTALL_DATA} ${WRKBUILD}/mogrified.cache ${PREFIX}/lib/qt3/.qmake.cache

.include <bsd.port.mk>
