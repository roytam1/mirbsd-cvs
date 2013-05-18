# $MirOS: ports/japanese/jvim/Makefile,v 1.7 2009/08/16 16:27:11 tg Exp $
# $OpenBSD: Makefile,v 1.20 2003/08/04 13:11:48 espie Exp $
# $FreeBSD: Makefile,v 1.1.1.1 1998/07/10 14:05:19 kuriyama Exp $

COMMENT=			Japanized Vim
COMMENT-canna=			Japanized Vim, canna input method
COMMENT-wnn=			Japanized Vim, wnn input method
COMMENT-wnn-canna=		Japanized Vim, canna or wnn input method
DISTNAME=	jvim2.0r+onew2.2.10
PKGNAME=	ja-jvim-2.0r-0
CATEGORIES=	japanese editors
MASTER_SITES=	ftp://ftp.lab.kdd.co.jp/Japan/onew/ \
		ftp://ftp.leo.chubu.ac.jp/pub/editor/jvim/

# public domain; mit/bsd and similar
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

FLAVOURS=	wnn canna
FLAVOUR?=

.if ${FLAVOUR:L:Mwnn}
BROKEN=			depends on Wnn, which is broken
CHOICE=		wnn4
INPUT_METHOD=	wnn4
BUILD_DEPENDS+=	::japanese/Wnn
JPDEF+=		-DWNN_ISDIR
JPLIB+=		-ljd
USE_X11=	Yes
USE_CXX=	Yes # depends on groff, which uses CXX
.endif

.if ${FLAVOUR:L:Mcanna}
.  if ${FLAVOUR:L:Mwnn}
INPUT_METHOD=	wnn4-canna
CHOICE=		wnn4,canna
.  else
INPUT_METHOD=	canna
CHOICE=		canna
.  endif
LIB_DEPENDS+=	canna.1::japanese/canna
JPLIB+=		-lcanna
USE_X11=	Yes
PERMIT_PACKAGE_CDROM=	dependency japanese/onew is not allowed for CDROM
.endif

.if defined(INPUT_METHOD) && !empty(INPUT_METHOD)
BUILD_DEPENDS+=	::japanese/onew,${CHOICE}
JPDEF+=		-DONEW
JPLIB:=		-lonew-${INPUT_METHOD} ${JPLIB}
.endif

WRKDIST=	${WRKDIR}/jvim2.0r
WRKSRC=		${WRKDIST}/src

BFLAGS=		JPDEF='${JPDEF}' \
		JPLIB='${JPLIB}' \
		JPCODE='-DJP=\".EE\"' \
		PREFIX='${PREFIX}' \
		MANDIR='$${PREFIX}/man/ja_JP.EUC' \
		MACHINE=-DBSD_UNIX \
		CC=${_PASS_CC:T:Q}\ ${CFLAGS:Q}\ -Wall

MAKE_FILE=	makefile.junx
ALL_TARGET=	jvim jcat jfold jgrep

MAKE_FLAGS=	${BFLAGS} PREFIX='${PREFIX}'
FAKE_FLAGS=	${BFLAGS} PREFIX='${WRKINST}${PREFIX}'

NO_REGRESS=	Yes

post-install:
	@for file in jcat jgrep jfold jvim; do \
		${STRIP} ${PREFIX}/bin/$$file; \
	done
	@echo "You may have to add man/ja_JP.EUC to _default in /etc/man.conf manually"

.include <bsd.port.mk>
