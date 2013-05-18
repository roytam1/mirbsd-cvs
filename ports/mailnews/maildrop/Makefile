# $OpenBSD: Makefile,v 1.13 2003/05/03 00:02:26 avsm Exp $

COMMENT=			local mail delivery agent with filtering abilities
COMMENT-utils=			userdb and quota tools for the Courier mail suite

VSN=		1.5.3
DISTNAME=	maildrop-${VSN}
CATEGORIES=    	mail

HOMEPAGE=	http://www.flounder.net/~mrsam/maildrop/

MASTER_SITES=  	${MASTER_SITE_SOURCEFORGE:=courier/}
EXTRACT_SUFX=	.tar.bz2

MULTI_PACKAGES=	-utils
SUBPACKAGE?=

FULLPKGNAME-utils= courier-utils-${VSN}-${DASH_VER}

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS=           gdbm.3::databases/gdbm

USE_CXX=		Yes
CONFIGURE_STYLE=	gnu
MAKE_ENV=		INCLUDES="-I${LOCALBASE}/include"
CONFIGURE_ARGS=		--datadir=${PREFIX}/share/doc \
			--enable-sendmail=/usr/sbin/sendmail \
			--enable-maildrop-gid=bin \
			--disable-tempdir --enable-restricted-trusted=1 \
			--enable-syslog=1 --with-etcdir=${SYSCONFDIR} \
			-with-db=gdbm --enable-userdb --enable-maildirquota

DOCFILES=		README INSTALL UPGRADE README.postfix

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/maildrop
.for i in ${DOCFILES}
	${INSTALL_DATA} ${WRKSRC}/$i ${PREFIX}/share/doc/maildrop
.endfor

.include <bsd.port.mk>
