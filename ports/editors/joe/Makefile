# $MirOS$

COMMENT=		"Joe's Own Editor"
CATEGORIES=		editors
DISTNAME=		joe-3.1jupp3
EXTRACT_SUFX=		.cpio.gz
HOMEPAGE=		http://wiki.mirbsd.de/JuppEditor \
			http://sourceforge.net/projects/joe-editor/
RESPONSIBLE=		Thorsten Glaser <tg@${_DOMAIN_DU_JOUR}>
MASTER_SITES=		${_MASTER_SITE_MIRBSD}

# GNU GPL Version 1
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

WRKDIST=		${WRKDIR}/jupp
CONFIGURE_STYLE=	gnu
EXTRA_FAKE_FLAGS=	sysconfdir=${TRUEPREFIX}/share/examples
DOCS=			HINTS INFO LIST NEWS README TODO

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/joe
.for _i in ${DOCS}
	${INSTALL_DATA} ${WRKSRC}/${_i} ${PREFIX}/share/doc/joe/
.endfor

.include <bsd.port.mk>
