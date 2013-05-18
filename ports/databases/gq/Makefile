# $MirOS: ports/databases/gq/Makefile,v 1.3 2006/09/14 00:07:49 tg Exp $
# $OpenBSD: Makefile,v 1.9 2004/04/01 08:44:27 jakob Exp $

BROKEN=			depends on cyrus-sasl, which is broken

COMMENT=			GTK-based LDAP client

VERSION=	0.7.0beta2
DISTNAME=	gq-${VERSION}
CATEGORIES=	databases

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=gqclient/}

HOMEPAGE=	http://biot.com/gq/


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_X11=	Yes
USE_CXX=	Yes

BUILD_DEPENDS=  :cyrus-sasl-*:security/cyrus-sasl	# sasl.h only
LIB_DEPENDS=	gtk.1.2,gdk.1.2::x11/gtk+1 \
		ldap,lber::databases/openldap \
		gdk_pixbuf::graphics/gdk-pixbuf

MODULES=	converters/libiconv

CONFIGURE_STYLE= autoconf
CONFIGURE_ARGS=	--with-ldap-prefix=${LOCALBASE} \
		--with-sasl-prefix=${LOCALBASE}

.include <bsd.port.mk>
