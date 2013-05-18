# $MirOS: src/etc/root.profile,v 1.1 2006/09/24 18:13:38 tg Exp $
#-
# initialisation for bourne shell (worst case)

# this is only run if /etc/profile has not been executed
if test -z "$USER_ID"; then
	PATH=/sbin:/usr/sbin:/bin:/usr/bin
	HOME=/
	test -d /root && HOME=/root
	export PATH HOME
	umask 022
	i=TERM=vt100
	if test -x /usr/bin/tset; then
		i=$(ulimit -c 0; /usr/bin/tset -sQ \?$TERM)
		TERM=vt100
	fi
	eval $i
	unset i COLORTERM HISTFILE
	EDITOR=/bin/ed
	export TERM EDITOR
fi

Lretrocfg() {		# retrieve kernel config file
	$SUDO zcat -f ${1:-/bsd} | strings -n4 | sed -n 's/^=CF=//p'
}
