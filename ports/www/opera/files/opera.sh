#!@SHELL@
# $MirOS: ports/www/opera/files/opera.sh,v 1.11 2007/05/22 19:56:58 tg Exp $

cfg=$HOME/.opera/opera6.ini
[[ -e $cfg ]] && if ! fgrep -q "Synchronous DNS Lookup=1" $cfg; then
	print '[Performance]\nSynchronous DNS Lookup=1' >>$cfg
fi

export OPERA_SCRIPT_PATH=$(readlink -nf $0) OPERA_NUM_XSHM=0
export OPERA_BINARYDIR=@PREFIX@/libexec/ OPERA_DIR=@PREFIX@/share/opera
LD_LIBRARY_PATH=/lib:@PREFIX@/libexec:${LD_LIBRARY_PATH}
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH%%:}

exec @PREFIX@/libexec/opera "$@"
