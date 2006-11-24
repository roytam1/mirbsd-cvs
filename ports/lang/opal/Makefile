# $MirOS$

COMMENT=			functional programming language
CATEGORIES=			devel lang
VERSION=			2.3k
DISTNAME=			ocs-${VERSION}-src
PKGNAME=			opal-${VERSION}
HOMEPAGE=			http://uebb.cs.tu-berlin.de/~opal/
RESPONSIBLE=			Thorsten Glaser <tg@mirbsd.de>

# LGPL, GPL; documentation only verbatim copying
PERMIT_DISTFILES_CDROM=		Yes
PERMIT_DISTFILES_FTP=		Yes
PERMIT_PACKAGE_CDROM=		Yes
PERMIT_PACKAGE_FTP=		Yes

.include <mirports.sys.mk>

EXTRACT_SUFX=			.tar.bz2
MASTER_SITES=			${HOMEPAGE}
WRKDIST=			${WRKDIR}/ocs
USE_GMAKE=			Yes
USE_X11=			Yes
NO_REGRESS=			Yes
LIB_DEPENDS+=			readline::devel/libreadline
# XXX can use any tcl/tk; should use module?
B_R_DEPENDS+=			:tk->=8.4:x11/tk/8.4
B_R_DEPENDS+=			:bzip2-*:archivers/bzip2
B_R_DEPENDS+=			:gsed-*:textproc/gsed

CPPFLAGS+=			-I${LOCALBASE}/include/tcl8.4 \
				-I${LOCALBASE}/include/tk8.4

CONFIGURE_STYLE=		autoconf no-autoheader dest
AUTOCONF_NEW=			Yes
.if ${NO_SHARED_LIBS:L} == "yes"
CONFIGURE_ARGS+=		--disable-dynamic
BROKEN=				oasys needs shared libraries
.else
# This has shlib_dirs issues
CONFIGURE_ARGS+=		--enable-dynamic
.endif
CONFIGURE_ARGS+=		--disable-absolute-pathes \
				--enable-oasys \
				--enable-opalwin \
				--enable-reflections \
				--enable-tivi2 \
				--disable-opaljava \
				--enable-proofchecker \
				--disable-locallinks \
				--with-tcl-lib=-ltcl84 \
				--with-tk-lib=-ltk84 \
				--without-java-lib \
				--without-java-incl \
				--without-pizzahome \
				--with-x
# enabling these requires LaTeX and dvips
CONFIGURE_ARGS+=		--disable-doc \
				--disable-dosfop
# if I ever get hold of the author of this configure script...
CONFIGURE_ARGS+=		--with-cflags=${CFLAGS:M*:Q} \
				--with-ldflags=${LDFLAGS:M*:Q}
CONFIGURE_ENV+=			ac_cv_path_TAR=tar
CONFIGURE_ENV+=			ocs_cv_flag_cc_opt= \
				ocs_cv_flag_cc_debug=-g \
				ocs_cv_flag_cc_profile='-g -pg'

# if I ever get hold of the author of this Makefile...
#NO_BUILD=			Yes
MAKE_ENV+=			SED=gsed

OSARCH=				${OSname}${OSrev}-${MACHINE_ARCH}
SUBST_VARS+=			VERSION OSARCH

do-build:
	sed -e 's#@PREFIX@#${TRUEPREFIX}#g' \
	    -e 's#@VERSION@#${VERSION}#g' \
	    -e 's#@OSARCH@#${OSARCH}#g' \
	    <${FILESDIR}/wrapper >${WRKBUILD}/wrapper

post-install:
	${INSTALL_SCRIPT} ${WRKBUILD}/wrapper ${PREFIX}/bin/
	cd ${PREFIX}/ocs-${VERSION}/bin && for f in *; do \
		ln ${PREFIX}/bin/wrapper ${PREFIX}/bin/$$f; \
	done
	rm -f ${PREFIX}/bin/wrapper

.include <bsd.port.mk>
