# $MirOS: src/etc/root/dot.profile,v 1.4 2005/07/23 15:00:35 tg Exp $
# $OpenBSD: dot.profile,v 1.5 2005/03/30 21:18:33 millert Exp $
#
# sh/ksh/mksh/bash initialisation

if [ -z "$USER_ID" ]; then
	# Do this only if /etc/profile has _not_ yet run!
	PATH=/sbin:/usr/sbin:/bin:/usr/bin:/usr/X11R6/bin:/usr/local/sbin:/usr/local/bin:/usr/mpkg/bin:/usr/mpkg/sbin
	export PATH
	: ${HOME='/root'}
	export HOME
	umask 022

	if [ -x /usr/bin/tset ]; then
		eval $(/usr/bin/tset -sQ \?$TERM)
	fi
	# End of /etc/profile replacement
fi

# Add local stuff here:
