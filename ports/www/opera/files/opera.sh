#!@SHELL@
# $MirOS: ports/www/opera/files/opera.sh,v 1.7 2006/06/25 06:26:52 tg Exp $

export OPERA_SCRIPT_PATH=$(readlink -nf $0)
export OPERA_BINARYDIR=@PREFIX@/libexec/ OPERA_DIR=@PREFIX@/share/opera
LD_LIBRARY_PATH=/dbl:@PREFIX@/libexec:${LD_LIBRARY_PATH}
LD_PRELOAD=/dbl/libnss_compat.so.2:/dbl/libnss_dns.so.2:/dbl/libnss_files.so.2:${LD_PRELOAD}
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH%%:}
export OPERA_LD_PRELOAD=${LD_PRELOAD%%:} LD_PRELOAD=${LD_PRELOAD%%:}

exec @PREFIX@/libexec/opera "$@"
