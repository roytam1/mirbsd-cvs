#!@SHELL@
# $MirOS: ports/www/opera/files/opera.sh,v 1.8 2006/12/20 21:39:32 tg Exp $

if ! fgrep "Synchronous DNS Lookup=1" $HOME/.opera/opera6.ini \
    >/dev/null 2>&1; then
	echo 'Warning: read the install notice ("pkg_info -D opera")' >&2
	echo '	 before using the Opera(C) web browser!' >&2
	sleep 3
fi

export OPERA_SCRIPT_PATH=$(readlink -nf $0)
export OPERA_BINARYDIR=@PREFIX@/libexec/ OPERA_DIR=@PREFIX@/share/opera
LD_LIBRARY_PATH=/dbl:@PREFIX@/libexec:${LD_LIBRARY_PATH}
LD_PRELOAD=/dbl/libnss_compat.so.2:/dbl/libnss_dns.so.2:/dbl/libnss_files.so.2:${LD_PRELOAD}
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH%%:}
export OPERA_LD_PRELOAD=${LD_PRELOAD%%:} LD_PRELOAD=${LD_PRELOAD%%:}

exec @PREFIX@/libexec/opera "$@"
