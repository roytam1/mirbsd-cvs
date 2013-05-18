#!@SHELL@
# $MirOS: ports/www/opera/files/opera.sh,v 1.6 2006/06/23 14:27:15 tg Exp $

export OPERA_DIR=@PREFIX@/share/opera
export LD_LIBRARY_PATH=/dbl:@PREFIX@/libexec:${LD_LIBRARY_PATH}
export LD_PRELOAD=/dbl/libnss_compat.so.2:/dbl/libnss_dns.so.2:/dbl/libnss_files.so.2:${LD_PRELOAD}

exec @PREFIX@/libexec/opera "$@"
