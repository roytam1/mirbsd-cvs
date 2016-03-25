# $MirSecuCron$

PATH=/sbin:/usr/sbin:/bin:/usr/bin
HOME=/
LC_ALL=C
PS1='# '
export PATH HOME LC_ALL PS1
umask 022

# this is only run if /etc/profile has not been executed
if test -z "$OSNAME"; then
	i=TERM=vt100
	if test -x /usr/bin/tset; then
		i=$(ulimit -c 0; /usr/bin/tset -sQ \?$TERM)
		TERM=vt100
	fi
	eval $i
	unset i HISTFILE
	EDITOR=/bin/ed
	USER=root
	USER_ID=0
	export EDITOR TERM USER
fi

Lretrocfg() {		# retrieve kernel config file
	typeset Tin
	typeset Tout
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

print '
	**********************************
	Do not login as root, use sudo(8)!
	**********************************
'
: $MirOS: src/etc/root.profile,v 1.13 2009/07/18 14:09:07 tg Exp $
