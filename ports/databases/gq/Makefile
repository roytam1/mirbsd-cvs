# $OpenBSD: Makefile,v 1.9 2004/04/01 08:44:27 jakob Exp $

COMMENT=	"GTK-based LDAP client"

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

BUILD_DEPENDS=  :cyrus-sasl-*:security/cyrus-sasl2	# sasl.h only
LIB_DEPENDS=	gtk.1.2,gdk.1.2::x11/gtk+ \
		ldap,lber::databases/openldap \
		gdk_pixbuf::graphics/gdk-pixbuf

MODULES=	converters/libiconv

CONFIGURE_STYLE= autoconf
CONFIGURE_ARGS=	--with-ldap-prefix=${LOCALBASE} \
		--with-sasl-prefix=${LOCALBASE}

.include <bsd.port.mk>
