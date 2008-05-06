# $MirOS$

COMMENT=		tools for manipulating patch files

VERSION=		0.2.31
DISTNAME=		patchutils-${VERSION}
CATEGORIES=		textproc devel

HOMEPAGE=		http://cyberelk.net/tim/software/patchutils/
MASTER_SITES=		http://cyberelk.net/tim/data/patchutils/stable/
EXTRACT_SUFX=		.tar.bz2

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE= 	autoconf
AUTOCONF_NEW=		Yes

BASH_SCRIPTS=		editdiff.in espdiff.in move-to-front \
			tests/combine2/run-test tests/combine3/run-test

pre-patch:
.for i in ${BASH_SCRIPTS}
	echo "1s/bash/mksh/\nwq" | ed ${WRKSRC}/$i
.endfor


.include <bsd.port.mk>
