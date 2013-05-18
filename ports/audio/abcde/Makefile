# $MirOS: ports/audio/abcde/Makefile,v 1.8 2009/08/16 15:19:58 bsiegert Exp $
# $OpenBSD: Makefile,v 1.7 2004/04/13 21:07:48 brad Exp $

COMMENT=	command-line utility to rip and encode audio cds

V=		2.1.19
# cd-diskid version number
V2=		0.9
DISTNAME=	abcde_$V.orig
PKGNAME=	abcde-$V-0
CATEGORIES=	audio

HOMEPAGE=	http://www.hispalinux.es/~data/abcde.php

# Artistic and GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MS=		http://www.hispalinux.es/~data/files/
MASTER_SITES=	${MS}
MASTER_SITES0=	${MS}cd-discid/
MASTER_SITES1=	http://lly.org/~rcw/id3/
DISTFILES=	${DISTNAME}.tar.gz \
		cd-discid_${V2}.orig.tar.gz:0

RUN_DEPENDS=	:cdparanoia-*:audio/cdparanoia

FLAVOURS=	lame
FLAVOUR?=	

NO_REGRESS=	Yes
WRKDIST=	${WRKDIR}/abcde-$V

.if ${FLAVOUR:L:Mlame}
DISTFILES+=		id3_0.12.orig.tar.gz:1
RUN_DEPENDS+=		:lame-*:audio/lame
USE_X11=		Yes # inherited
PERMIT_PACKAGE_CDROM=	dependency lame not allowed
.else
RUN_DEPENDS+=		:vorbis-tools-*:audio/vorbis-tools
USE_CXX=		Yes # inherited
.endif

post-patch:
.if ${FLAVOUR:L:Mlame}
	perl -pi -e 's,OUTPUTTYPE=ogg,OUTPUTTYPE=mp3,g' ${WRKSRC}/abcde
.endif

do-build:
	cd ${WRKDIR}/cd-discid-${V2} && \
	    ${_PASS_CC:Q} ${CFLAGS} -o cd-discid cd-discid.c
.if ${FLAVOUR:L:Mlame}
	cd ${WRKDIR}/id3-0.12 && \
	    perl -pi -e 's,#include <getopt.h>,/*#include <getopt.h>*/,g' id3.c && \
	    ${_PASS_CC:Q} ${CFLAGS} -o id3 id3.c
.endif

do-install:
	${INSTALL_SCRIPT} ${WRKSRC}/abcde ${PREFIX}/bin
	${INSTALL_SCRIPT} ${WRKSRC}/cddb-tool ${PREFIX}/bin
	${INSTALL_PROGRAM} ${WRKDIR}/cd-discid-${V2}/cd-discid ${PREFIX}/bin
	${INSTALL_MAN} ${WRKSRC}/abcde.1 ${PREFIX}/man/man1
	${INSTALL_MAN} ${WRKSRC}/cddb-tool.1 ${PREFIX}/man/man1
	${INSTALL_MAN} ${WRKDIR}/cd-discid-${V2}/cd-discid.1 ${PREFIX}/man/man1
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/abcde
	${INSTALL_DATA} ${WRKSRC}/abcde.conf ${PREFIX}/share/examples/abcde
.if ${FLAVOUR:L:Mlame}
	${INSTALL_PROGRAM} ${WRKDIR}/id3-0.12/id3 ${PREFIX}/bin
	${INSTALL_MAN} ${WRKDIR}/id3-0.12/id3.1 ${PREFIX}/man/man1
.endif

.include <bsd.port.mk>
