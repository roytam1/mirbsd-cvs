# $MirOS: src/etc/root.profile,v 1.2 2006/10/18 23:02:23 tg Exp $
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
	local Tin
	local Tout
	Tin=
	Tout=
	if Tin=$(mktemp /tmp/Lretrocfg.iXXXXXXXXXX) && \
	    Tout=$(mktemp /tmp/Lretrocfg.oXXXXXXXXXX); then
		if $SUDO zcat -f ${1:-/bsd} >$Tin 2>/dev/null && \
		    objcopy -O binary --set-section-flags .config.gz=alloc \
		    -j .config.gz $Tin $Tout >/dev/null 2>&1; then
			zcat <$Tout
		else
			print -u2 Error: no .config.gz stored in "${1:-/bsd}"
		fi
	else
		print -u2 Error: cannot mktemp
	fi
	rm -f $Tin $Tout
}
