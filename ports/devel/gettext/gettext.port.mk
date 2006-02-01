# $MirOS: ports/devel/gettext/gettext.port.mk,v 1.1.7.1 2005/03/18 15:44:38 tg Exp $
# $OpenBSD: gettext.port.mk,v 1.8 2001/11/27 17:44:04 brad Exp $

MODULES+=	converters/libiconv

# The RUN_DEPENDS entry is to ensure gettext is installed. This is
# necessary so that we have locale.alias installed on static archs.
# Typically installed in PREFIX/share/locale.
LIB_DEPENDS+=	intl:gettext->=0.10.38:devel/gettext
BUILD_DEPENDS+=	:gettext->=0.10.38:devel/gettext
RUN_DEPENDS+=	:gettext->=0.10.38:devel/gettext
