# $MirOS: ports/devel/cvs/Makefile,v 1.24 2016/10/22 04:01:32 tg Exp $

COMMENT=		Concurrent Versions System
CATEGORIES=		devel essentials
VSN=			1.12.13
# track both in patches/patch-configure_in as well!
DASH_VER=		16
DEBIAN_REV=		18		# in sync with MirOS-0AB7.4 revision
HOMEPAGE=		http://www.nongnu.org/cvs/
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.org>

# GNU GPLv1, GPLv2+, LGPLv2, MIT, BSD, zlib
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

DISTNAME=		cvs-${VSN}
MASTER_SITES=		${MASTER_SITE_GNU:gnu/=non-gnu/cvs/source/feature/${VSN}/}
MASTER_SITES0=		${MASTER_SITE_DEBIAN:=c/cvs/}
DISTFILES=		${DISTNAME}${EXTRACT_SUFX} \
			cvs_1.12.13+real-${DEBIAN_REV}_i386.deb:0
PATCHFILES=		cvs_1.12.13+real-${DEBIAN_REV}.diff.gz:0
PATCH_DIST_STRIP=	-p1

CONFIGURE_STYLE=	autogen
AUTOCONF_NEW=		Yes
AUTOMAKE_VERSION=	1.9
CONFIGURE_ARGS+=	--disable-nls \
			--enable-client \
			--enable-password-authenticated-client \
			--enable-server \
			--enable-proxy \
			--enable-case-sensitivity \
			--disable-lock-compatibility \
			--enable-rootcommit \
			--disable-old-info-format-support \
			--enable-config-override=no \
			--with-external-zlib \
			--with-rsh=ssh \
			--with-editor=/bin/ed \
			--with-tmpdir=/var/tmp \
			--with-umask=002 \
			--with-cvs-admin-group=_cvsadmin
# hardcoded paths
CONFIGURE_ENV+=		ac_cv_path_CSH=${LOCALBASE:Q}/bin/csh
CONFIGURE_ENV+=		ac_cv_path_PS2PDF=false

# see mircvs://contrib/code/Snippets/posixtz.c
.if exists(/usr/lib/libposixtz.so)
REGRESS_ENV+=		GETDATE_LD_PRELOAD=/usr/lib/libposixtz.so
.endif
# this is ugly ugly ugly… get ssh to localhost working if you can, and rsync
REGRESS_ENV+=		SSH_AUTH_SOCK=${SSH_AUTH_SOCK:Q}
REGRESS_IS_INTERACTIVE=	Yes

post-extract:
	# install the PDFs generated in Debian, they are closer to the truth
	cd ${WRKDIR}; tar xzf data.tar.gz

post-patch:
	# use prebuilt one so to not depend on GNU bison
	-rm -f ${WRKSRC}/lib/getdate.y

post-build:
	# we install cvs-switchroot(1) from Debian now
	gzip -d <${WRKDIR}/usr/share/man/man1/cvs-switchroot.1.gz \
	    >${WRKBUILD}/cvs-switchroot.1

post-install:
	cd ${WRKSRC} && ${INSTALL_DATA} AUTHORS BUGS DEVEL-CVS FAQ HACKING \
	    MINOR-BUGS NEWS PROJECTS README TODO doc/HACKING.DOCS \
	    doc/RCSFILES doc/*.ms doc/*.rtf ${PREFIX}/share/cvs/
	cd ${WRKSRC}/contrib && ${INSTALL_DATA} descend.man rcs2log.1 \
	    sandbox_status.man ${PREFIX}/share/cvs/contrib/
	cd ${WRKSRC}/contrib && ${INSTALL_SCRIPT} descend.sh rcs2sccs.sh \
	    ${PREFIX}/share/cvs/contrib/
	cd ${WRKDIR}/usr/share/doc/cvs && ${INSTALL_DATA} *.html *.pdf \
	    ${PREFIX}/share/cvs/
	${INSTALL_SCRIPT} ${WRKDIR}/usr/bin/cvs-switchroot ${PREFIX}/bin/
	${INSTALL_MAN} ${WRKBUILD}/cvs-switchroot.1 ${PREFIX}/man/man1/
	mv ${PREFIX}/share/cvs ${PREFIX}/share/doc/cvs

.include <bsd.port.mk>
