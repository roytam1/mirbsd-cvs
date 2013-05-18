# $MirOS: ports/devel/cvs/Makefile,v 1.22 2011/12/04 19:19:43 tg Exp $

COMMENT=		Concurrent Versions System
CATEGORIES=		devel essentials
VSN=			1.12.13
DASH_VER=		14		# in sync with MirOS-0AB0.1 revision
HOMEPAGE=		http://www.nongnu.org/cvs/
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.org>

# GNU GPLv1, GPLv2
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

DISTNAME=		cvs-${VSN}
MASTER_SITES=		${MASTER_SITE_GNU:gnu/=non-gnu/cvs/source/feature/${VSN}/}
MASTER_SITES0=		${MASTER_SITE_DEBIAN:=c/cvs/}
DISTFILES=		${DISTNAME}${EXTRACT_SUFX} \
			cvs_1.12.13+real-8_i386.deb:0
PATCHFILES=		cvs_1.12.13+real-8.diff.gz:0
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
			--disable-rootcommit \
			--disable-old-info-format-support \
			--enable-config-override=no \
			--with-external-zlib \
			--with-rsh=ssh \
			--with-editor=/bin/ed \
			--with-tmpdir=/var/tmp \
			--with-umask=002 \
			--with-cvs-admin-group=_cvsadmin
# caught by systrace, tries to write to ${LOCALBASE}/lib as check
CONFIGURE_ENV+=		ac_cv_sys_long_file_names=yes
# hardcoded paths
CONFIGURE_ENV+=		ac_cv_path_CSH=${LOCALBASE:Q}/bin/csh
CONFIGURE_ENV+=		ac_cv_path_PS2PDF=false

# see mircvs://contrib/code/Snippets/posixtz.c
.if exists(/usr/lib/libposixtz.so)
REGRESS_ENV+=		GETDATE_LD_PRELOAD=/usr/lib/libposixtz.so
.endif
# this is ugly ugly ugly… get ssh to localhost working if you can
REGRESS_ENV+=		SSH_AUTH_SOCK=${SSH_AUTH_SOCK:Q}
REGRESS_IS_INTERACTIVE=	Yes

pre-configure:
	print '%g/\(MirPorts-\)QQ/s//\1${DASH_VER}/g\nwq' | \
	    ed -s ${WRKSRC}/configure

post-build:
	# we install the PDFs generated in Debian, they are closer
	cd ${WRKDIR}; tar xzf data.tar.gz
	gzip -d <${WRKDIR}/usr/share/doc/cvs/cvs-paper.pdf.gz \
	    >${WRKBUILD}/cvs-paper.pdf
	gzip -d <${WRKDIR}/usr/share/doc/cvs/cvs.pdf.gz \
	    >${WRKBUILD}/cvs.pdf
	gzip -d <${WRKDIR}/usr/share/doc/cvs/cvsclient.pdf.gz \
	    >${WRKBUILD}/cvsclient.pdf
	# we install cvs-switchroot(1) from Debian now
	gzip -d <${WRKDIR}/usr/share/man/man1/cvs-switchroot.1.gz \
	    >${WRKBUILD}/cvs-switchroot.1

post-install:
	cd ${WRKSRC} && ${INSTALL_DATA} AUTHORS BUGS DEVEL-CVS FAQ HACKING \
	    MINOR-BUGS NEWS PROJECTS README TODO doc/HACKING.DOCS \
	    doc/RCSFILES doc/*.ms doc/*.rtf ${PREFIX}/share/cvs/
	cd ${WRKSRC}/contrib && ${INSTALL_DATA} cvs_acls.html cvshelp.man \
	    descend.man descend.sh rcs2sccs.sh sandbox_status.man \
	    ${PREFIX}/share/cvs/contrib/
	${INSTALL_MAN} ${WRKSRC}/contrib/rcs2log.1 ${PREFIX}/man/man1/
	cd ${WRKBUILD} && ${INSTALL_DATA} cvs-paper.pdf cvs.pdf \
	    cvsclient.pdf ${PREFIX}/share/cvs/
	${INSTALL_SCRIPT} ${WRKDIR}/usr/bin/cvs-switchroot ${PREFIX}/bin/
	${INSTALL_MAN} ${WRKBUILD}/cvs-switchroot.1 ${PREFIX}/man/man1/
	mv ${PREFIX}/share/cvs ${PREFIX}/share/doc/

.include <bsd.port.mk>
