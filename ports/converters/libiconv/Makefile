# $MirOS: ports/converters/libiconv/Makefile,v 1.5 2006/02/01 17:23:35 tg Exp $
# $OpenBSD: Makefile,v 1.16 2003/12/24 00:08:02 brad Exp $

COMMENT=	"character set conversion library"
DISTNAME=	libiconv-1.9.1
PKGNAME=	${DISTNAME}-3
CATEGORIES=	converters devel
MASTER_SITES=	${MASTER_SITE_GNU:=libiconv/}
HOMEPAGE=	http://www.gnu.org/software/libiconv/

# GNU LGPLv2.0
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=autoconf
AUTOCONF_NEW=	Yes
VMEM_WARNING=	Yes
MODGNU_CONFIG_GUESS_DIRS= ${WRKSRC} ${WRKSRC}/libcharset
CONFIGURE_ARGS+= ${CONFIGURE_SHARED}
CONFIGURE_ARGS+= --enable-static \
		 --enable-extra-encodings \
		 --disable-nls \
		 --mandir=${PREFIX}/man

# To avoid clashing with native libiconv (Darwin, MirBSD #9)
CONFIGURE_ARGS+= --libdir=${PREFIX}/giconv/lib \
		 --includedir=${PREFIX}/giconv/include

# Yes, it does need this fuckup.
pre-patch:
	cd ${WRKSRC}/autoconf && cp \
	    config.libpath install-reloc reloc-ldflags ../
	cd ${WRKSRC}/libcharset/autoconf && cp aclocal.m4 config.libpath ../

.include <bsd.port.mk>
