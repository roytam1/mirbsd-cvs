# $OpenBSD: Makefile,v 1.19 2004/05/10 18:32:41 naddy Exp $

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386

COMMENT=	"ANSI Common Lisp compiler"

DISTNAME=	clisp-2.33
CATEGORIES=	lang
HOMEPAGE=	http://clisp.cons.org/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=clisp/}
EXTRACT_SUFX=	.tar.bz2

MODULES=	devel/gettext

CONFIGURE_STYLE=gnu old
CONFIGURE_ARGS=	--srcdir=${WRKSRC} ${WRKBUILD}

MAKE_FLAGS=	INSTALL='install -c' \
		INSTALL_PROGRAM='install -c -s -m 555' \
		INSTALL_DATA='install -c -m 644'

# configure can't handle multiple blanks
CONFIGURE_SCRIPT=${WRKSRC}/configure.wrapper

pre-configure:
	@(echo '#!/bin/sh'; \
	  echo 'CFLAGS=`echo "$$CFLAGS" | tr -s "[:space:]"`'; \
	  echo '${WRKSRC}/configure $$@') >${CONFIGURE_SCRIPT}; \
	chmod u+rx ${CONFIGURE_SCRIPT}

post-configure:
	@cd ${WRKBUILD} && \
	    ./makemake --fsstnd=openbsd --prefix=${PREFIX} \
		--with-dynamic-ffi >Makefile && \
	make config.lisp

.include <bsd.port.mk>
