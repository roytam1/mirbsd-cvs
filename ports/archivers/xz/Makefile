# $MirOS: ports/archivers/xz/Makefile,v 1.3 2012/10/18 15:31:59 tg Exp $
# $OpenBSD: Makefile,v 1.4 2010/11/08 20:11:13 naddy Exp $

COMMENT=		LZMA compression and decompression tools
DISTNAME=		xz-5.0.4
CATEGORIES=		archivers
HOMEPAGE=		http://tukaani.org/xz/
MASTER_SITES=		${HOMEPAGE}

# Mix of PD(see near EOF), LGPLv2.1+, GPLv2+, GPLv3+
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

# Note on material marked as PD or derived from such in here:
#
# We got an explicit copyright licence from Igor Pavlov, the
# original author of, according to several sources, any such
# material, in both xz-utils and pdlzip (WTFPL-like):
#
# From: Igor Pavlov
# Message-ID: <BFE18C67668F4A56A0965B2115DAB7FA@igor2>
# Subject: Re: LZMA SDK and legalities of public domain
# […]
# I even don't want to think about these restrictions, countries,
# Berne Convention and so on.
# You can use the code. [in projects under OSS licences that
# include code from LZMA SDK (context: mails from me and Lasse)]
# No restrictions from me.
#
# Further files from Lasse Collin contain these notes as well:
# You can do whatever you want with this file.
# You can do whatever you want with the files that have been put into
# the public domain. If you find public domain legally problematic,
# take the previous sentence as a license grant.
#
# Lasse Collin, around <20111118225931.4b7e60e3@tukaani.org>, also
# confirms this, adding an interpretation of this as WTFPL and
# explicitly permits sublicencing and to “change the license”; he
# also confirms the authenticity of Igor Pavlov’s answer.
