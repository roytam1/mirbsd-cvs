#!@SHELL@
# $MirOS: ports/www/opera/files/opera.sh,v 1.10 2007/04/30 12:47:16 tg Exp $

cfg=$HOME/.opera/opera6.ini
[[ -e $cfg ]] && if ! fgrep -q "Synchronous DNS Lookup=1" $cfg; then
	print '[Performance]\nSynchronous DNS Lookup=1' >>$cfg
fi

export OPERA_SCRIPT_PATH=$(readlink -nf $0) OPERA_NUM_XSHM=0
export OPERA_BINARYDIR=@PREFIX@/libexec/ OPERA_DIR=@PREFIX@/share/opera
LD_LIBRARY_PATH=/dbl:@PREFIX@/libexec:${LD_LIBRARY_PATH}
LD_PRELOAD=/dbl/libnss_compat.so.2:/dbl/libnss_dns.so.2:/dbl/libnss_files.so.2:${LD_PRELOAD}
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH%%:}
export OPERA_LD_PRELOAD=${LD_PRELOAD%%:} LD_PRELOAD=${LD_PRELOAD%%:}

exec @PREFIX@/libexec/opera "$@"
