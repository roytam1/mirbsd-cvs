# $MirOS: ports/devel/gettext/gettext.port.mk,v 1.3 2006/11/22 18:08:20 tg Exp $
# $OpenBSD: gettext.port.mk,v 1.8 2001/11/27 17:44:04 brad Exp $

MODULES+=	converters/libiconv

# The RUN_DEPENDS entry is to ensure gettext is installed. This is
# necessary so that we have locale.alias installed on static archs.
# Typically installed in PREFIX/share/locale.
LIB_DEPENDS+=	intl:gettext->=0.10.38:devel/gettext
