# $MirOS: ports/audio/timidity/Makefile,v 1.6 2010/07/30 21:00:40 tg Exp $
# $OpenBSD: Makefile,v 1.25 2003/10/26 23:49:31 naddy Exp $

COMMENT=		MIDI to WAV renderer and player
DISTNAME=		timidity-0.2i
DASH_VER=		2
CATEGORIES=		audio

MASTER_SITES=		http://www.goice.co.jp/member/mo/timidity/dist/
MASTER_SITES0=		ftp://ftp.kiarchive.ru/pub/misc/hardware/soundcard/gus/
TIINS=			goemon.tgz
DISTFILES=		${TIINS}:0 ${DISTNAME}.tar.gz
EXTRACT_ONLY=		${DISTNAME}.tar.gz

PERMIT_PACKAGE_CDROM=	"copyrighted patches"
PERMIT_PACKAGE_FTP=	"copyrighted patches"
PERMIT_DISTFILES_CDROM=	"copyrighted patches"
PERMIT_DISTFILES_FTP=	"copyrighted patches"

FLAVOURS=		motif curses slang
FLAVOUR?=		curses

.if ${FLAVOUR:L:Mcurses}
MAKE_FLAGS+=		-DCURSES
.endif
.if ${FLAVOUR:Mopenmotif} || ${FLAVOUR:Mlesstif}
FLAVOUR+=		motif
.endif
.if ${FLAVOUR:L:Mmotif}
MAKE_FLAGS+=		-DMOTIF
USE_MOTIF=		any
.endif
.if ${FLAVOUR:L:Mslang}
MAKE_FLAGS+=		-DSLANG
LIB_DEPENDS+=		slang::devel/libslang
.endif

NO_REGRESS=		Yes

INSTALL_TARGET=		install.all
EXTRA_FAKE_FLAGS=	PREFIX=${PREFIX} DESTDIR=${WRKINST}

post-install:
	${INSTALL_MAN} ${WRKSRC}/timidity.1 ${PREFIX}/man/man1
	@cd ${PREFIX}/lib/timidity && \
	${TAR} zxf ${FULLDISTDIR}/${TIINS} && \
	print 'g/dir goemon/s==dir '${TRUEPREFIX:Q}'/lib/timidity/goemon=\nwq' | \
	ed -s goemon.cfg
	print 'g!/usr/local!s!!'${TRUEPREFIX:Q}'!\nwq' | \
	    ed -s ${PREFIX:Q}/lib/timidity/timidity.cfg

.include <bsd.port.mk>
