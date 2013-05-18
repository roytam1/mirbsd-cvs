# $MirOS: ports/archivers/xz/Makefile,v 1.2 2010/12/11 20:33:27 tg Exp $
# $OpenBSD: Makefile,v 1.4 2010/11/08 20:11:13 naddy Exp $

COMMENT=		LZMA compression and decompression tools
DISTNAME=		xz-5.0.4
CATEGORIES=		archivers
HOMEPAGE=		http://tukaani.org/xz/
MASTER_SITES=		${HOMEPAGE}

# Mix of PD, LGPLv2.1+, GPLv2+, GPLv3+
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	autogen
AUTOCONF_NEW=		Yes
AUTOMAKE_VERSION=	1.9
MODGNU_TYPESCAN+=	foo
CONFIGURE_ARGS=		${CONFIGURE_SHARED} \
			--disable-nls \
			--disable-threads

MANRENAMETBL=		xz.1
MANLINKTBL+=		xz.1 lzcat.1
MANLINKTBL+=		xz.1 lzma.1
MANLINKTBL+=		xz.1 unlzma.1
MANLINKTBL+=		xz.1 unxz.1
MANLINKTBL+=		xz.1 xzcat.1

post-extract:
	rm -f ${WRKSRC}/m4/lt*.m4 ${WRKSRC}/m4/libtool.m4

post-install:
.for _i in ${MANRENAMETBL}
	cd ${PREFIX}/man/man1 && mv ${_i} ${_i}tbl
.endfor
.for _i _j in ${MANLINKTBL}
	cd ${PREFIX}/man/man1 && rm -f ${_j} && ln -s ${_i}tbl ${_j}tbl
.endfor
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/xz/old
	mv ${PREFIX}/share/doc/xz/examples_old/* \
	    ${PREFIX}/share/examples/xz/old/
	mv ${PREFIX}/share/doc/xz/examples/* ${PREFIX}/share/examples/xz/
	rmdir ${PREFIX}/share/doc/xz/examples{,_old}

.include <bsd.port.mk>
