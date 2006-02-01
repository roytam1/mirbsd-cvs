#!@SHELL@
# $MirOS: ports/www/opera/files/opera.sh,v 1.3 2006/01/18 11:26:17 tg Exp $
# $OpenBSD: opera.sh,v 1.5 2003/11/09 09:46:26 sturm Exp $

PLUGIN_PATH=@PREFIX@/lib/opera/plugins
PLUGIN_PATH=${PLUGIN_PATH}:@LOCALBASE@/lib/ns-plugins
PLUGIN_PATH=${PLUGIN_PATH}:${HOME}/.netscape/plugins
PLUGIN_PATH=${PLUGIN_PATH}:@LOCALBASE@/netscape/plugins
LD_LIBRARY_PATH=/dbl:${LD_LIBRARY_PATH}:@PREFIX@/libexec

export OPERA_DIR=@PREFIX@/share/opera
export OPERA_PLUGIN_PATH=${OPERA_PLUGIN_PATH-${PLUGIN_PATH}}
export LD_LIBRARY_PATH

exec @PREFIX@/libexec/opera "$@"
