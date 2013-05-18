# $MirOS: ports/emulators/redhat/motif/Makefile,v 1.3 2006/02/01 20:38:48 tg Exp $
# $OpenBSD: Makefile,v 1.10 2003/10/31 22:29:41 sturm Exp $

COMMENT=			Motif toolkit Linux libraries
PKGNAME=	redhat_motif-2.1.30-${PL}
MASTER_SITES=	${MASTER_SITE_REDHAT:=contrib/openmotif/linux-rpm/}
DISTFILES=	openmotif-2.1.30-1_ICS.i386.rpm

RUN_DEPENDS+=	::emulators/redhat/base

EXTRACT_FILES=	usr/X11R6/lib/libMrm.so.2.1 \
		usr/X11R6/lib/libUil.so.2.1 \
		usr/X11R6/lib/libXm.so.2.1

do-install:
	@cd ${EMDIR}; ${LOCALBASE}/bin/rpm2cpio \
	    ${FULLDISTDIR}/${DISTFILES} | cpio -idum ${EXTRACT_FILES}

.include <bsd.port.mk>
