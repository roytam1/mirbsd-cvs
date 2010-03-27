# $MirOS: ports/devel/svk/Makefile,v 1.4 2008/10/04 19:46:50 bsiegert Exp $

COMMENT=		distributed version control system

VERSION=		2.2.0
DASH_VER=		1
DISTNAME=		SVK-v${VERSION}
PKGNAME=		svk-${VERSION}-${DASH_VER}
CATEGORIES=		devel net

HOMEPAGE=		http://svk.bestpractical.com/
MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=../by-authors/id/C/CL/CLKAO/}

RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

B_R_DEPENDS+=		::archivers/p5-Compress-Zlib
B_R_DEPENDS+=		::archivers/p5-PerlIO-via-Bzip2
B_R_DEPENDS+=		::archivers/p5-PerlIO-gzip
B_R_DEPENDS+=		::devel/p5-version
B_R_DEPENDS+=		::devel/p5-YAML-Syck
B_R_DEPENDS+=		::devel/p5-Algorithm-Annotate
B_R_DEPENDS+=		::devel/p5-Algorithm-Diff
B_R_DEPENDS+=		::devel/p5-Data-Hierarchy
B_R_DEPENDS+=		::sysutils/p5-PerlIO-via-dynamic
B_R_DEPENDS+=		::sysutils/p5-PerlIO-via-symlink
B_R_DEPENDS+=		::sysutils/p5-IO-Digest
B_R_DEPENDS+=		::devel/p5-SVN-Simple
B_R_DEPENDS+=		::sysutils/p5-PerlIO-eol
B_R_DEPENDS+=		::devel/p5-App-CLI
B_R_DEPENDS+=		::devel/p5-List-MoreUtils
B_R_DEPENDS+=		::devel/p5-Class-Accessor
B_R_DEPENDS+=		::devel/p5-Class-Data-Inheritable
B_R_DEPENDS+=		::devel/p5-PathTools
B_R_DEPENDS+=		::devel/p5-Universal-require
B_R_DEPENDS+=		::devel/p5-Term-ReadKey
B_R_DEPENDS+=		::devel/p5-File-Temp
B_R_DEPENDS+=		::converters/p5-Encode
B_R_DEPENDS+=		::devel/p5-Locale-Maketext-Lexicon
B_R_DEPENDS+=		::devel/p5-IO-Pager
B_R_DEPENDS+=		::devel/p5-FreezeThaw
B_R_DEPENDS+=		:p5-SVN-Dump-0.04-*:devel/p5-SVN-Dump
B_R_DEPENDS+=		::devel/p5-SVN-Mirror
B_R_DEPENDS+=		::devel/p5-Path-Class
B_R_DEPENDS+=		::devel/p5-Class-Autouse
B_R_DEPENDS+=		::devel/p5-Time-Progress
B_R_DEPENDS+=		::www/p5-libwww

CONFIGURE_STYLE= 	perl
CONFIGURE_ARGS+=	--defaultdeps

.include <bsd.port.mk>
