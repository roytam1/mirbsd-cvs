#!@SHELL@
# $MirOS: ports/www/opera/files/opera.sh,v 1.4 2006/02/01 20:38:49 tg Exp $
# $OpenBSD: opera.sh,v 1.5 2003/11/09 09:46:26 sturm Exp $

case $0 in /*) OPERA_SCRIPT_PATH=$0;; *) OPERA_SCRIPT_PATH=`/bin/pwd`/$0;; esac
export OPERA_SCRIPT_PATH

PLUGIN_PATH=@PREFIX@/lib/opera/plugins
PLUGIN_PATH=${PLUGIN_PATH}:@LOCALBASE@/lib/ns-plugins
PLUGIN_PATH=${PLUGIN_PATH}:${HOME}/.netscape/plugins
PLUGIN_PATH=${PLUGIN_PATH}:@LOCALBASE@/netscape/plugins
LD_LIBRARY_PATH=/dbl:${LD_LIBRARY_PATH}:@PREFIX@/libexec

export OPERA_DIR=@PREFIX@/share/opera
export OPERA_PLUGIN_PATH=${OPERA_PLUGIN_PATH-${PLUGIN_PATH}}
export LD_LIBRARY_PATH

exec @PREFIX@/libexec/opera "$@"
