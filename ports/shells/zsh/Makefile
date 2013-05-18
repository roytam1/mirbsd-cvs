# $MirOS: ports/shells/zsh/Makefile,v 1.3 2009/09/06 16:42:12 tg Exp $
# $OpenBSD: Makefile,v 1.50 2009/06/03 14:35:48 pea Exp $

COMMENT=		Z shell, Bourne shell-compatible
VSN=			4.3.11
DISTNAME=		zsh-${VSN}
CATEGORIES=		shells
HOMEPAGE=		http://www.zsh.org/

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

# from Debian
_PATCHFILES=		${.CURDIR}/0003-regex-match-crash-fix.diff
PATCHFILES=
PATCH_DIST_STRIP=	-p1

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=zsh/}

MODULES+=		converters/libiconv
MODULES+=		devel/libncursesw
LIB_DEPENDS+=		pcre::devel/pcre

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
MODGNU_TYPESCAN=	brk sbrk mknod ioctl
CONFIGURE_ARGS+=	${CONFIGURE_SHARED:S/shared/dynamic/} \
			--enable-zsh-mem \
			--enable-zsh-secure-free \
			--enable-etcdir=${SYSCONFDIR:Q} \
			--enable-maildir-support \
			--with-tcsetpgrp \
			--disable-multibyte \
			--enable-pcre \
			--disable-gdbm
INSTALL_TARGET=		install install.info

# required for regression tests
PORTHOME=		${WRKDIR}
REGRESS_FLAGS=		INSTALL_PROGRAM="install -c -s -m 755" \
			INSTALL_DATA="install -c -m 644" \
			INSTALL="install -c" \
			TMPPREFIX=${WRKBUILD:Q}/tmp \
			TERM=xterm

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/zsh/${VSN}/scripts \
	    ${PREFIX}/share/examples/zsh
	${INSTALL_DATA} ${.CURDIR}/zprofile ${PREFIX}/share/examples/zsh/

.include <bsd.port.mk>
