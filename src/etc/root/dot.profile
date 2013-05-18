# $MirOS$
#-
# initialisation for bourne shell (worst case)

# all shells; only if /etc/profile has not run (can't happen)
if test -z "$USER_ID"; then
	PATH=/sbin:/usr/sbin:/bin:/usr/bin
	HOME=/
	test -d /root && HOME=/root
	export PATH HOME
	umask 022
	i='TERM=vt100'
	if test -x /usr/bin/tset; then
		i=$(ulimit -c 0; /usr/bin/tset -sQ \?$TERM)
		TERM=vt100
	fi
	eval $i
	unset i COLORTERM HISTFILE
	EDITOR=/bin/ed
	export TERM EDITOR
fi

# all shells
#<...> insert local stuff here

# exit if sh/ash/sash
test -n $KSH_VERSION || test -n $BASH_VERSION || return

# mksh/bash only
function Lretrocfg	# retrieve kernel config file
{
	$SUDO cat ${1:-/bsd} | strings -n4 | sed -n 's/^=CF=//p'
}
set -o emacs
[[ -n $BASH_VERSION ]] && shopt -s extglob

#<...> insert local stuff here
