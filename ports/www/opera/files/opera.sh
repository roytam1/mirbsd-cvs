#!@SHELL@
# $MirOS: ports/www/opera/files/opera.sh,v 1.13 2008/10/05 16:10:06 tg Exp $

ulimit -c 0

cfg=$HOME/.opera/opera6.ini
[[ -e $cfg ]] && if ! fgrep -q "Synchronous DNS Lookup=1" $cfg; then
	print '[Performance]\nSynchronous DNS Lookup=1' >>$cfg
fi

export OPERA_SCRIPT_PATH=$(realpath $0) OPERA_NUM_XSHM=0
export OPERA_BINARYDIR=@PREFIX@/libexec/ OPERA_DIR=@PREFIX@/share/opera
LD_LIBRARY_PATH=/lib:@PREFIX@/libexec:${LD_LIBRARY_PATH}
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH%%:}

exec @PREFIX@/libexec/opera "$@"
