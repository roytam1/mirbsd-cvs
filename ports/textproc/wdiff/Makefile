# $MirOS: ports/textproc/wdiff/Makefile,v 1.4 2007/09/08 19:47:10 tg Exp $
# $OpenBSD: Makefile,v 1.16 2002/12/23 09:09:12 pvalchev Exp $

COMMENT=		word differences between text files
DISTNAME=		wdiff-0.5
DASH_VER=		2
CATEGORIES=		textproc
MASTER_SITES=		${MASTER_SITE_GNU:=wdiff/}

# GPLv2+
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	autoconf dest
CONFIGURE_ENV+=		ac_cv_path_DIFF=diff \
			ac_cv_path_PAGER=less
INSTALL_TARGET=		install install-man

.include <bsd.port.mk>
