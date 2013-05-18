# $MirOS: ports/devel/git/Makefile,v 1.1 2009/05/31 18:05:51 tg Exp $

ONLY_FOR_PLATFORM+=	Darwin:*:*	# not tested
ONLY_FOR_PLATFORM+=	MirBSD:*:* OpenBSD:*:*

COMMENT=		Git - Tree History Storage Tool
COMMENT-svn=		Git - Subversion interoperability tools

VSN=			1.6.3.1
DISTNAME=		git-${VSN}
PKGNAME-svn=		git-svn-${VSN}-${DASH_VER}
CATEGORIES=		devel
HOMEPAGE=		http://git-scm.com/

# GNU GPLv2
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

.include <mirports.sys.mk>

MASTER_SITES=		ftp://ftp.de.kernel.org/pub/software/scm/git/ \
			ftp://ftp.kernel.org/pub/software/scm/git/ \
			ftp://ftp.au.kernel.org/pub/software/scm/git/
DOC_DISTFILES=		git-htmldocs-${VSN}${EXTRACT_SUFX} \
			git-manpages-${VSN}${EXTRACT_SUFX}
DISTFILES=		${DISTNAME}${EXTRACT_SUFX} \
			${DOC_DISTFILES}
EXTRACT_ONLY=		${DISTNAME}${EXTRACT_SUFX}

MODULES+=		p5
MODULES+=		converters/libiconv
MODULES+=		textproc/expat
BUILD_DEPENDS+=		:p5-Error->=0.17015:devel/p5-Error

#MULTI_PACKAGES=		-svn
#SUBPACKAGE?=

LIB_DEPENDS+=		curl::net/curl
RUN_DEPENDS+=		::devel/p5-Error
RUN_DEPENDS+=		::net/rsync

.if defined(PACKAGING) && (${SUBPACKAGE} == "-svn")
PKG_ARCH=		*	# XXX does this do anything in MirPorts?
LIB_DEPENDS=
RUN_DEPENDS=		:${PKGNAME}:devel/git
RUN_DEPENDS+=		::devel/p5-Term-ReadKey
RUN_DEPENDS+=		::devel/subversion
RUN_DEPENDS+=		::www/p5-libwww
RUN_DEPENDS+=		::www/p5-URI
.endif

REGRESS_DEPENDS+=	::archivers/zip
REGRESS_DEPENDS+=	::devel/cvsps
REGRESS_DEPENDS+=	::devel/subversion
#REGRESS_ENV+=		LC_ALL=en_US.UTF-8
REGRESS_FLAGS+=		NO_SVN_TESTS=defined
REGRESS_FLAGS+=		HOME=${WRKDIST:Q}/t/trash
REGRESS_TARGET=		test
# see mircvs://contrib/code/Snippets/posixtz.c
.if exists(/usr/lib/libposixtz.so)
REGRESS_ENV+=		LD_PRELOAD=/usr/lib/libposixtz.so
.endif

mp_BASIC_CFLAGS=	${CPPFLAGS} ${CFLAGS:M-I*}
mp_BASIC_LDFLAGS=	${LDFLAGS}
EXTRA_XAKE_FLAGS+=	prefix=${PREFIX:Q} \
			SYSCONFDIR=${SYSCONFDIR:Q} \
			EXPATDIR=${EXPAT_PREFIX:Q} \
			NO_MEMMEM=defined \
			NO_STRTOUMAX=defined \
			NEEDS_SSL_WITH_CRYPTO=defined \
			NEEDS_LIBICONV=defined \
			NO_PTHREADS=defined \
			USE_ST_TIMESPEC=defined \
			NO_TCLTK=defined \
			mp_BASIC_CFLAGS=${mp_BASIC_CFLAGS:M*:Q} \
			mp_BASIC_LDFLAGS=${mp_BASIC_LDFLAGS:M*:Q} \
			V=1
USE_GMAKE=		Yes

post-extract:
	mkdir -p ${WRKSRC:Q}/doc
.for _i in ${DOC_DISTFILES}
	cd ${WRKSRC:Q}/doc && ${TAR} xzf ${FULLDISTDIR}/${_i:Q}${EXTRACT_SUFX}
.endfor
	cd ${WRKSRC:Q} && \
	    rm -f doc/man1/git-p4import.1 && \
	    perl -pi -e 's/usr/share/git'${TRUEPREFIX:Q}'/share/gitg' \
	    Documentation/git-clone.txt \
	    Documentation/git-init.txt \
	    doc/git-clone.html \
	    doc/git-clone.txt \
	    doc/git-init.html \
	    doc/git-init.txt \
	    doc/man1/git-clone.1 \
	    doc/man1/git-init.1

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/git \
	    ${PREFIX}/share/emacs/site-lisp ${PREFIX}/share/gitweb
	${INSTALL_DATA} ${WRKBUILD}/libgit.a ${PREFIX}/lib/
	${INSTALL_DATA} ${WRKBUILD}/contrib/emacs/*.el \
	    ${PREFIX}/share/emacs/site-lisp/
	cd ${WRKBUILD}/doc && \
	    pax -rw -l -s,man7/git.7,man1/git.1, man* ${PREFIX}/man/
	cd ${WRKBUILD}/doc && \
	    pax -rw -l *.html howto/*.html *.txt howto/*.txt \
	    ${PREFIX}/share/doc/git/
	${INSTALL_DATA} ${WRKBUILD}/contrib/hooks/post-receive-email \
	    ${PREFIX}/share/git-core/templates/hooks/post-receive-email.sample
	chown -R ${BINOWN}:${BINGRP} ${PREFIX}/libexec/git
	cd ${WRKSRC}/gitweb && \
	    ${INSTALL_DATA} INSTALL README git-favicon.png git-logo.png \
	    gitweb.cgi gitweb.css ${PREFIX}/share/gitweb/

.include <bsd.port.mk>
