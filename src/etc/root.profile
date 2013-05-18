# $MirOS: src/etc/root.profile,v 1.9 2008/05/15 14:29:35 tg Exp $
#-
# initialisation for bourne shell (worst case)

# this is only run if /etc/profile has not been executed
if test -z "$OSNAME"; then
	PATH=/sbin:/usr/sbin:/bin:/usr/bin:/usr/dbin:/usr/dsbin
	HOME=/
	PS1='# '
	export PATH HOME PS1
	umask 022
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
	export EDITOR TERM USER USER_ID
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

/bin/cat <<-'EOF'

	**********************************
	Do not login as root, use sudo(8)!
	**********************************

EOF
:
