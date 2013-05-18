# $MirOS: ports/devel/cvs/Makefile,v 1.14 2010/09/16 21:26:09 tg Exp $

IGNORE=wip

COMMENT=		Concurrent Versions System
CATEGORIES=		devel essentials
VSN=			1.12.13
DASH_VER=		9		# in sync with MirOS-0AAC rev.
HOMEPAGE=		http://www.nongnu.org/cvs/
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.org>

# GNU GPLv1, GPLv2
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

DISTNAME=		cvs-${VSN}
MASTER_SITES=		${MASTER_SITE_GNU:gnu/=non-gnu/cvs/source/feature/${VSN}/}

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
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
# cought by systrace, tries to write to ${LOCALBASE}/lib as check
CONFIGURE_ENV+=		ac_cv_sys_long_file_names=yes
# hardcoded paths
CONFIGURE_ENV+=		ac_cv_path_CSH=${LOCALBASE:Q}/bin/csh
CONFIGURE_ENV+=		ac_cv_path_PS2PDF=false

# see mircvs://contrib/code/Snippets/posixtz.c
.if exists(/usr/lib/libposixtz.so)
REGRESS_ENV+=		GETDATE_LD_PRELOAD=/usr/lib/libposixtz.so
.endif

pre-configure:
	print '%g/\(MirPorts-\)QQ/s//\1${DASH_VER}/g\nwq' | \
	    ed -s ${WRKSRC}/configure

post-install:
	cd ${WRKSRC} && ${INSTALL_DATA} AUTHORS BUGS DEVEL-CVS FAQ HACKING \
	    MINOR-BUGS NEWS PROJECTS README TODO doc/HACKING.DOCS \
	    doc/RCSFILES doc/*.ms doc/*.pdf doc/*.rtf ${PREFIX}/share/cvs/
	cd ${WRKSRC}/contrib && ${INSTALL_DATA} cvs_acls.html cvshelp.man \
	    descend.man descend.sh rcs2sccs.sh sandbox_status.man \
	    ${PREFIX}/share/cvs/contrib/
	${INSTALL_MAN} ${WRKSRC}/contrib/rcs2log.1 ${PREFIX}/man/man1/

.include <bsd.port.mk>
