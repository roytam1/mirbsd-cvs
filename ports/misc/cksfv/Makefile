# $MirOS$

COMMENT=		checksummer for .sfv files
V=			1.3
CATEGORIES=		archivers misc net
DISTNAME=		cksfv-$V
HOMEPAGE=		http://www.fodder.org/cksfv/
RESPONSIBLE=		Thorsten Glaser <tg@${_DOMAIN_DU_JOUR}>

# GNU GPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${HOMEPAGE}

MAKE_FILE=		BSDmakefile
CPPFLAGS+=		-DVERSION=\"$V\"

pre-patch:
	cp ${FILESDIR}/BSDmakefile ${FILESDIR}/cksfv.1 ${WRKSRC}/

.include <bsd.port.mk>
