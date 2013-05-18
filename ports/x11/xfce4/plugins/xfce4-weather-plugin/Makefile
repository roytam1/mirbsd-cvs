# $MirOS: ports/x11/xfce4/plugins/xfce4-weather-plugin/Makefile,v 1.3 2005/04/11 15:58:04 tg Exp $
# $OpenBSD: Makefile,v 1.2 2004/04/18 00:28:58 jolan Exp $

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386

COMMENT=			xfce4 plugin showing the temperature/weather conditions
DISTNAME=	xfce4-weather-plugin-0.3.0
MASTER_SITES=	${MASTER_SITE_GOODIES}
HOMEPAGE=	${HOMEPAGE_GOODIES}

MODULES=	devel/gettext

LIB_DEPENDS=	${GTK2} \
		${XML2} \
		${GUI}

.include <bsd.port.mk>
