#!@SHELL@
# $MirOS: ports/www/opera/files/opera.sh,v 1.5 2006/06/20 18:20:37 tg Exp $

export OPERA_DIR=@PREFIX@/share/opera
export LD_LIBRARY_PATH=/dbl:@PREFIX@/libexec:${LD_LIBRARY_PATH}

exec @PREFIX@/libexec/opera "$@"
