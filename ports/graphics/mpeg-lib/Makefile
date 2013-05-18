# $MirOS: ports/graphics/mpeg-lib/Makefile,v 1.1.7.1 2005/03/18 15:46:59 tg Exp $
# $OpenBSD: Makefile,v 1.23 2002/12/29 20:08:46 fgsch Exp $

COMMENT=			collection of C routines to decode MPEG movies
DISTNAME=	mpeg_lib-1.3.1
CATEGORIES=	graphics
MASTER_SITES=	ftp://ftp.bic.mni.mcgill.ca/pub/mpeg/ \
		http://starship.python.net/~gward/mpeglib/

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE= gnu
CONFIGURE_ENV=	OPTIMIZE="${CFLAGS}"

.include <bsd.port.mk>

.if defined(NO_SHARED_LIBS) && ${NO_SHARED_LIBS:L} == "yes"
MAKE_ENV+=	NO_SHARED_LIBS=Yes
.endif
